/************************************************************************************
 * @file    main_cfg.c
 * @author  Silence is the key #13 - Team:
 *          - Mahmoud Karam Emara (ma.karam272@gmail.com)
 *          - Ahmed Abdelgawad Kamal (ahmedabdelgawad234@gmail.com)
 *          - Mina Ghobrial Abdulla (menaghobrial98@gmail.com)
 *          - Hossam Mostafa Abd El-Aziz (hossam11015@gmail.com)
 *          - Ahmed Mohamed Mannaa (ahmed.mg.manna3@gmail.com)
 * @brief   Configuration of the Smart Home Security System
 * @details To configure the default system variables, the user should:
 *          * Configure the system's default password data:
 *              * The default password (i.e., "1234")
 *              * Maximum password length (i.e., 4 characters)
 *              * Maximum password attempts (i.e., 3 attempts)
 *          * Configure the system's flags initial state:
 *              * correctPassword: The system's password is correct
 *              * buzzer: The system's buzzer state (i.e., off)
 *              * openDoor: The system's door state (i.e., closed) 
 *              * fire: The system's fire sensor state (i.e., no fire)
 *              All flags are set to 0 by default.
 *          * Configure the system's sensors data:
 *              * The system's temperature sensor data:
 *                  * The system's maximum temperature value in Celsius (i.e., 150)
 *                  * The system's critical temperature value in Celsius (i.e., 40)
 *                  * The ADC channel of the system's temperature sensor
 *              * The system's gas sensor data:
 *                  * The system's maximum gas value in percentage (100%)
 *                  * The system's critical gas value in percentage (50%)
 *                  * The ADC channel of the system's gas sensor
 *              Sensors critical values are the values that will trigger the system's
 *              alarm.
 * @version 1.0.0
 * @date    2022-06-28
 * @copyright Copyright (c) 2022 
 ************************************************************************************/

/*--------------------------------------------------------------------*/
/* 			                                                          */
/* 								Includes                              */
/* 			                                                          */
/*--------------------------------------------------------------------*/
#include "LIB/LSTD_TYPES.h"
#include "LIB/LBIT_MATH.h"
#include "main_cfg.h"



/*--------------------------------------------------------------------*/
/* 			                                                          */
/* 					CHANGE THE FOLLOWING TO YOUR NEEDS                */
/* 			                                                          */
/*--------------------------------------------------------------------*/

SYSTEM_t system = {
	.sensors.temperature = {
		.u8_MaxValue 				= 150,		/* Maximum temperature: 150 C */
        .u8_CriticalValue           = 40,       /* Critical temperature: 40 C */
		.u8_CurrentValue 			= 0,		/* Current temperature reading */
		.u16_CurrentValueInBinary 	= 0,		/* Current temperature reading in binary */
		.u8_AdcChannel				= 7,		/* ADC channel for temperature sensor */
	},
	.sensors.gas = {
		.u8_MaxValue 				= 100,		/* Maximum gas: 100 % */
        .u8_CriticalValue           = 50,       /* Critical gas: 50 % */
		.u8_CurrentValue 			= 0,		/* Current gas level reading */
		.u16_CurrentValueInBinary 	= 0,		/* Current gas level reading in binary */
		.u8_AdcChannel				= 0,		/* ADC channel for gas sensor */
	},
	.password = {
		.value 		= {'1', '2', '3', '4'},	    /* Password: 1234 */
		.attemps 	= 3,					    /* Number of attemps to enter password */
		.maxAttemps = 3						    /* Maximum number of attemps to enter password */
	},  
	.flag = {   
		.correctPassword 	= 0,			    /* Flag to check if the password is correct */
		.buzzer 		    = 0,			    /* Flag to enable the buzzer */
		.openDoor 			= 0,			    /* Flag to open the door */
        .fire 		        = 0,			    /* Flag to fire the alarm */
	}
};
