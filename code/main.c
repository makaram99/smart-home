/************************************************************************************
 * @file    main.c
 * @author  Silence is the key #13 - Team:
 *          - Mahmoud Karam Emara (ma.karam272@gmail.com)
 *          - Ahmed Abdelgawad Kamal (ahmedabdelgawad234@gmail.com)
 *          - Mina Ghobrial Abdulla (menaghobrial98@gmail.com)
 *          - Hossam Mostafa Abd El-Aziz (hossam11015@gmail.com)
 *          - Ahmed Mohamed Mannaa (ahmed.mg.manna3@gmail.com)
 * @brief   Smart Home Security System
 * @details This is the main file of the system. It consists of the following functions:
 *          * Gas Sensor to sense the gas level in the house.
 *          * Temperature Sensor to sense the temperature in the house.
 *          * Keypad to enter the password to open the door.
 *          * Motor to open/close the door when the password is correct.
 *          * Buzzer to alert the user when the system is in alarm mode:
 *              - The password is incorrect for 3 times.
 *              - The gas level is above the critical level.
 *          * LCD to display the system's data (temperature, door status, gas level).
 * @version 1.0.0
 * @date    2022-06-28
 * @copyright Copyright (c) 2022 
 ************************************************************************************/

#include "main.h"
#include "main_cfg.h"

/*----------------------------------------------------------------------------------*/
/* 																				    */
/*                                  GLOBAL DATA                                     */
/* 																				    */
/*----------------------------------------------------------------------------------*/

/************************************************************************************
 * @brief Semaphor used by the ADC to indicate that the conversion is done. It is 
 *        given by the ADC ISR, and taken inside the taskReadSensors().
 ***********************************************************************************/
xSemaphoreHandle ADC_Semaphore;

/************************************************************************************
 * @brief The ADC channel to be read. It toggles between the channels of the gas 
 *        sensor and the temperature sensor. So, each time the taskReadSensors()
 *        starts a new conversion, it reads the next channel.
 ***********************************************************************************/
u8 u8_AdcChannelToRead = 0;

/*----------------------------------------------------------------------------------*/
/* 																				    */
/*                                      MAIN                                        */
/* 																				    */
/*----------------------------------------------------------------------------------*/
int main(void) {

    /*!< Initial ADC channel to be read */
    u8_AdcChannelToRead = system.inputs.gas.u8_AdcChannel;

    /*!< Initialize the system */
    System_Init(u8_AdcChannelToRead);

    /* Create ADC semaphore     */
    ADC_Semaphore = xSemaphoreCreateCounting(1, 0); 

    /* Create tasks         */
	xTaskCreate(taskReadSensors         , NULL, 100, NULL, 8, NULL);
	xTaskCreate(taskControlGasLevel     , NULL, 120, NULL, 4, NULL);
	xTaskCreate(taskControlTemperature  , NULL, 100, NULL, 2, NULL);
	xTaskCreate(taskDisplaySystemState  , NULL, 100, NULL, 7, NULL);
	xTaskCreate(taskGetPassword         , NULL, 100, NULL, 3, NULL);

    /* Start scheduler      */
	vTaskStartScheduler();

	while(1) {

	}

    return 0;
}

/*----------------------------------------------------------------------------------*/
/* 																				    */
/*                                      TASKS                                       */
/* 																				    */
/*----------------------------------------------------------------------------------*/

/************************************************************************************
 * @brief   Task to get the password from the keypad.
 * @details This task is responsible for getting the password from the keypad. If the
 *          password is:
 *          * Correct: raise the flag to open the door.
 *          * Incorrect: decrease the number of attempts to open the door. If the number
 *                       of attempts is 0, raise the flag to alert the user (buzzer).
 * @param pv RTOS task parameter. Not used.
 ************************************************************************************/
void taskGetPassword(void * pv) {
	u8 i = 0, enteredKey = 0, isPasswordCorrect = 0;
	u8 enteredPassword[PASSWORD_LENGTH] = {0};

	while(1) {
		/*!< Getting the key pressed from the keyboard. */
        enteredKey = HKPD_U8GetKeyPressed();

        /*!< Check if the user pressed a key */
		if(enteredKey) {
            /*!< If the user pressed a key, then save it to the enteredPassword array */
            enteredPassword[i] = enteredKey;
            ++i;    /*!< Increment the index of the enteredPassword array */

			/**************************************************************************
			 * @brief   Checking if the password is fully entered.
             * @details If the password is:
             *          * Correct: system.flag.correctPassword is set to 1. 
             *          * Wrong: system.flag.correctPassword is set to 0 and 
             *                   system.password.attemps is decremented. 
             * @note    If system.password.attemps is 0, the system.flag.buzzer is 
             *          set to 1.
			 **************************************************************************/
            if(PASSWORD_LENGTH == i) {
                isPasswordCorrect = comparePasswords(enteredPassword, system.password.value, PASSWORD_LENGTH);
				
                if(isPasswordCorrect) {
                    system.flag.correctPassword = 1;
                    system.flag.openDoor = 1;
                } else {
                    system.flag.correctPassword = 0;
                    --system.password.attemps;

                    if(system.password.attemps == 0) {
                        system.flag.buzzer = 1;
                    }
                }

                controlDoor();

				vTaskDelay(100);

                if(system.password.attemps == 0) {
                    system.password.attemps = system.password.maxAttemps;
                }
                system.flag.correctPassword = 0;
				i = 0;
			}
        }
		vTaskDelay(20);
	}
}

/************************************************************************************
 * @brief   Task to display the system's data.
 * @details This task is responsible for displaying the system's data. It displays:
 *          * The temperature.
 *          * The door status.
 *          * The fire alarm status.
 *          * The door security status.
 * @param pv RTOS task parameter. Not used.
 ************************************************************************************/
void taskDisplaySystemState(void * pv) {

	while(1) {        
        displayDoorState();        
        displayTemperatureValue();
        displayFireState();
        displayEntryPasswordSecurity();

		vTaskDelay(200);
	}
}

/************************************************************************************
 * @brief   Task to read the sensors.
 * @details This task is responsible for reading the sensors. It reads the gas level
 *          and the temperature. It uses the ADC in Non-Blocking mode, to enhances
 *          the responsiveness of the system.
 * @param pv RTOS task parameter. Not used.
 ************************************************************************************/
void taskReadSensors(void * pv) {
	u8 LOC_u8SemState = 0;

	while(1) {
		/* Trying to take the semaphore, with 5 ticks timeout */
        LOC_u8SemState = xSemaphoreTake(ADC_Semaphore, 5);

		/*!< Check if the ADC semaphore is available */
        if(pdPASS == LOC_u8SemState) {
            
            /**************************************************************************
             * @brief Read temperature sensor or gas sensor depending on the 
             *        system.inputs.gas.u8_AdcChannel, then swap the ADC channel
             *        to read the next sensor in the next iteration. 
             *************************************************************************/
            if(u8_AdcChannelToRead == system.inputs.gas.u8_AdcChannel) {
                system.inputs.gas.u16_CurrentValueInBinary = MADC_u16ADCRead();
                u8_AdcChannelToRead = system.inputs.temperature.u8_AdcChannel;
            } else if(u8_AdcChannelToRead == system.inputs.temperature.u8_AdcChannel) {
                system.inputs.temperature.u16_CurrentValueInBinary = MADC_u16ADCRead();
                u8_AdcChannelToRead = system.inputs.gas.u8_AdcChannel;
            } else {
                /* MISRA C */
            }


            /*!< Starting the conversion of the ADC channel specified in the argument. */
            MADC_u16ADC_StartConversion_With_Interrupt(u8_AdcChannelToRead);
        } else {
            /*Do Nothing*/
        }

        vTaskDelay(10);
	}
}

/************************************************************************************
 * @brief   Task to control the gas level.
 * @details This task is responsible for controlling the gas level. It checks if the
 *          gas level is above the threshold and if it is:
 *          * Above: Open the window, and raise the flag to alert the user (buzzer).
 *          * Below: Close the window, and downset the flag of the alert.
 * @note    The gas level is read from the ADC using a potentiometer. It is converted
 *          to a percentage of the full scale.
 * @param pv RTOS task parameter. Not used.
 ************************************************************************************/
void taskControlGasLevel(void * pv) {
	while(1) {
        system.inputs.gas.u8_CurrentValue = (u8)(((u32)system.inputs.gas.u16_CurrentValueInBinary * system.inputs.gas.u8_MaxValue) / 1024.0f);

		if(system.inputs.gas.u8_CurrentValue >= system.inputs.gas.u8_CriticalValue) {
			H_DcMotorPotStart(CLK_W);
            system.flag.fire = 1;
		} else {
            system.flag.fire = 0;
			H_DcMotorPotStop();
		}

		vTaskDelay(15);
	}
}

/************************************************************************************
 * @brief   Task to control the temperature.
 * @details This task is responsible for controlling the temperature. It checks if the
 *          temperature is above the threshold and if it is:
 *          * Above: Open the fan.
 *          * Below: Stop the fan.
 * @note    Temperature is measured using the LM35 sensor. The LM35 sensor is 
 *          connected to the ADC. The sensor gives 10mV for every degree Celsius. So,
 *          you can measure the temperature in degrees Celsius by dividing the
 *          ADC voltage value by 10mV.
 * @param pv RTOS task parameter. Not used.
 ************************************************************************************/
void taskControlTemperature(void * pv) {
	while(1) {
        system.inputs.temperature.u8_CurrentValue = (u8)((system.inputs.temperature.u16_CurrentValueInBinary * 500.0f) / 1024.0f);

        system.inputs.temperature.u8_CurrentValue = round(system.inputs.temperature.u8_CurrentValue);

        if(system.inputs.temperature.u8_CurrentValue > system.inputs.temperature.u8_CriticalValue) {
            H_DcMotorStart(CLK_W);
        } else {
            H_DcMotorStop();
        }
        
		vTaskDelay(15);
	}
}

/*----------------------------------------------------------------------------------*/
/* 																				    */
/*                                ORDINARY FUNCTIONS                                */
/* 																				    */
/*----------------------------------------------------------------------------------*/

void ADC_SetNotification(void) {
    /* This code is giving the ADC_Semaphore. */
    xSemaphoreGive(ADC_Semaphore);
}

/*************************************************************************************
 * @brief   Initialize system peripherals.
 * @param u8_AdcChannelToRead: The initial ADC channel to be read at the beginning.
 ************************************************************************************/
void System_Init(u8 u8_AdcChannelToRead) {

	HCLCD_Vid4Bits_Init();

	/*ADC Init*/
	MGIE_VidEnable();
	MADC_VidSetCallBack(ADC_SetNotification);
	MADC_VidADCInterruptEnable();
	MADC_VidInit();
	MADC_u16ADC_StartConversion_With_Interrupt(u8_AdcChannelToRead);

	/* Init sensors*/
	MDIO_Error_State_SetPinDirection(PIN0,MDIO_PORTA,PIN_INPUT);
	MDIO_Error_State_SetPinDirection(PIN7,MDIO_PORTA,PIN_INPUT);

	/* LEDS Init*/
	MDIO_Error_State_SetPinDirection(PIN0, MDIO_PORTC, PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(PIN1, MDIO_PORTC, PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(PIN2, MDIO_PORTC, PIN_OUTPUT);

	/* BUZZER Init */
	MDIO_Error_State_SetPinDirection(PIN5,MDIO_PORTC,PIN_OUTPUT);

	/* KEYPAD INIT */
	HKPD_VidInit();
	/* SERVO INIT */
	// H_ServoInit();

	//DC Motor Init
	H_DcMotorInit();

	/* Pot DC Motor Init */
	H_DcMotorPotInit();
}

/********************************************************************************
 * @brief   Display the current state of the door: open or closed.
 * @details If the door is open, "D: Open" is displayed. 
 *          If the door is closed, "D: Close" is displayed.
 * @note    This funnction writes to the LCD at the line 1, position 0, and uses
 *          8 positions to write the string. So, avoid writing to the first 8
 *          positions of the LCD in line 1.
 *******************************************************************************/
void displayDoorState(void) {
    /* Writing the string "D: " to the LCD at the line 1, position 0 */
    HCLCD_VidSetPosition_4BitsMode(HCLCD_LINE1, 0);
	HCLCD_VidWriteString_4Bits((u8*)"D: ");

    /***************************************************************************
     * @brief Checking if the door is open or not, and writing the string 
     *        "Open" or "Close" to the LCD.
     **************************************************************************/
    if(system.flag.openDoor) {
		HCLCD_VidSetPosition_4BitsMode(HCLCD_LINE1, 3);
		HCLCD_VidWriteString_4Bits((u8*)"Open ");
	}else {
		HCLCD_VidSetPosition_4BitsMode(HCLCD_LINE1, 3);
		HCLCD_VidWriteString_4Bits((u8*)"Close");
	}
}

/********************************************************************************
 * @brief   Display the current temperature of the room.
 * @details The current temperature is displayed in the LCD. "T: xxC" is displayed.
 * @note    This funnction writes to the LCD at the line 1, position 10, and uses
 *          7 positions to write the string. So, avoid writing to the last 7
 *          positions of the LCD in line 1.
 *******************************************************************************/
void displayTemperatureValue(void) {
    
    /* Writing the string "T: " to the LCD at the line 1, position 10 */
    HCLCD_VidSetPosition_4BitsMode(HCLCD_LINE1, 10);
	HCLCD_VidWriteString_4Bits((u8*)"T: ");
	
    /* Writing the temperature value to the LCD. */
    HCLCD_VidWriteNumber_4Bits(system.inputs.temperature.u8_CurrentValue);
    HCLCD_VidWriteString_4Bits((u8*)"C");
    
    /* Adding spaces to the LCD display to clear the previous value. */
    if(system.inputs.temperature.u8_CurrentValue < 10) {
			HCLCD_VidWriteString_4Bits((u8*)"  ");
	} else if(system.inputs.temperature.u8_CurrentValue < 100) {
		HCLCD_VidWriteString_4Bits((u8*)" ");
	}
}

/********************************************************************************
 * @brief   Checking if the fire alarm is on or not
 * @details If the fire alarm is on, the string "FIRE" is written to the LCD, and
 *          the buzzer is on.
 *          Otherwise, the string "NoFire" is written to the LCD.
 * @note    This funnction writes to the LCD at the line 2, position 0, and uses
 *          6 positions to write the string. So, avoid writing to the first 6
 *          positions of the LCD in line 2.
 *******************************************************************************/
void displayFireState(void) {
    
    /* Setting the position of the cursor to the second line and the first column. */
    HCLCD_VidSetPosition_4BitsMode(HCLCD_LINE2, 0);

    /****************************************************************************
     * @brief If the fire alarm is on, it will turn on the buzzer and display "FIRE" 
     *        on the LCD. If it is off, it will turn off the buzzer and display 
     *        "NoFire" on the LCD.
     ***************************************************************************/
    if(system.flag.fire) {
        MDIO_Error_State_SetPinValue(PIN5, MDIO_PORTC, PIN_HIGH);   /*!< Turn on the buzzer. */
        HCLCD_VidWriteString_4Bits((u8*)"FIRE  ");
    } else {
        /* Setting the pin value to low, only if the buzzer flag is off. */
        if(!system.flag.buzzer) {
            MDIO_Error_State_SetPinValue(PIN5, MDIO_PORTC, PIN_LOW);    /*!< Turn off the buzzer. */
        }

        HCLCD_VidWriteString_4Bits((u8*)"NoFIRE");
    }
}

/********************************************************************************
 * @brief   Display the security of the house (Password).
 * @details If the password is:
 *          * Correct: "AMAN(x)" is written to the LCD, where x
 *                     is the number of attempts.
 *          * Wrong: "7RAMY(0)" is written to the LCD, where 0 denotes the number 
 *                   of attempts left is 0. And the buzzer is on for 3 seconds. 
 *                   We assume that the police arrives during the 3 seconds.
 * @note    This funnction writes to the LCD at the line 2, position 6, and uses
 *          4 positions to write the string. So, avoid writing to the last 4
 *          positions of the LCD in line 2.
 *******************************************************************************/
void displayEntryPasswordSecurity(void) {

    /* Setting the position of the cursor to the second line and the 8th column. */
    HCLCD_VidSetPosition_4BitsMode(HCLCD_LINE2, 8);
    
    /****************************************************************************
     * @brief If the password is correct, it will display "AMAN(x)" where x
     *        is the number of attempts.
     *        If the password is wrong, it will display "7RAMY(0)" where 0 
     *        denotes the number of attempts left is 0. And the buzzer is on 
     *        for 3 seconds. We assume that the police arrives during the 3 
     *        seconds.
     ***************************************************************************/
    if(system.flag.buzzer) {
		HCLCD_VidWriteString_4Bits((u8*)"7RAMY(0)");

        /* Turning on the buzzer for 3 seconds. Police arrives during the 3 seconds.*/
        MDIO_Error_State_SetPinValue(PIN5, MDIO_PORTC, PIN_HIGH);
        vTaskDelay(3000);                                        
        
        /*!< Turn off the buzzer only if the fire alarm is off. This is to prevent
         *   the buzzer from turning off when the fire alarm is on. */
        if(!system.flag.fire) {    
            MDIO_Error_State_SetPinValue(PIN5, MDIO_PORTC, PIN_LOW);
        }

        /* Setting the flag to 0 and the password attemps to the max attemps. */
        system.flag.buzzer = 0;
	} else {    /*!< buzzer flag is off. */
		HCLCD_VidWriteString_4Bits((u8*)"AMAN(");
		HCLCD_VidWriteNumber_4Bits(system.password.attemps);
        HCLCD_VidWriteString_4Bits((u8*)") ");
	}
}

/********************************************************************************
 * @brief   Compare the password entered by the user with the default password.
 * @retaur  If the password is correct, return 1. Otherwise, return 0.
 *******************************************************************************/
u8 comparePasswords(const u8 * const pass1, const u8 * const pass2, const u8 length) {
    u8 i = 0, state = 1;

	for(i = 0; i < length; ++i) {
		if(pass1[i] != pass2[i]) {
			state = 0;
			break;
		}
	}

    return state;
}

/********************************************************************************
 * @brief It controls the door of the house. Open the door if the user enters the
 *        correct password. Otherwise, close the door.
 *******************************************************************************/
void controlDoor(void) {
    if(system.flag.openDoor) {       
        SET_BIT(PORTC, 0); //RED
        CLR_BIT(PORTC, 1); //Green
        vTaskDelay(2000);

        CLR_BIT(PORTC, 0); //RED
        SET_BIT(PORTC, 1); //Green
        vTaskDelay(2000);

        CLR_BIT(PORTC, 1); //Green
        SET_BIT(PORTC, 2); //Blue
        vTaskDelay(2000);

        SET_BIT(PORTC, 1); //Green
        CLR_BIT(PORTC, 2); //Blue

        system.flag.openDoor = 0;
    } else {
        SET_BIT(PORTC, 1);
        CLR_BIT(PORTC, 0);
        CLR_BIT(PORTC, 2);
    }
}
