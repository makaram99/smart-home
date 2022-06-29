/************************************************************************************
 * @file    main_cfg.h
 * @author  Silence is the key #13 - Team:
 *          - Mahmoud Karam Emara (ma.karam272@gmail.com)
 *          - Ahmed Abdelgawad Kamal (ahmedabdelgawad234@gmail.com)
 *          - Mina Ghobrial Abdulla (menaghobrial98@gmail.com)
 *          - Hossam Mostafa Abd El-Aziz (hossam11015@gmail.com)
 *          - Ahmed Mohamed Mannaa (ahmed.mg.manna3@gmail.com)
 * @brief   Configuration of the Smart Home Security System
 * @details This file contains:
 *          * Configuration of the system's macros.
 *          * typedefs for the system's data types and structures.
 * @version 1.0.0
 * @date    2022-06-28
 * @copyright Copyright (c) 2022 
 ************************************************************************************/
#ifndef MAIN_CFG_H
#define MAIN_CFG_H

/*--------------------------------------------------------------------*/
/* 			                                                          */
/* 						CHANGE THESE VALUES TO YOUR NEEDS			  */
/* 			                                                          */
/*--------------------------------------------------------------------*/
#define PASSWORD_LENGTH  	(4U)



/*--------------------------------------------------------------------*/
/* 			                                                          */
/* 					DO NOT CHANGE THE FOLLOWING                       */
/* 			                                                          */
/*--------------------------------------------------------------------*/

/**********************************************************************/
/* 								TYPEDEFS                              */
/**********************************************************************/

/**********************************************************************
 * @brief This is the structure that holds the system's state flags
 **********************************************************************/
typedef struct {
	u8 correctPassword;
	u8 buzzer;
	u8 openDoor;
    u8 fire;
} FLAG_t;

/**********************************************************************
 * @brief This is the structure that holds the system's password data
 **********************************************************************/
typedef struct {
	u8 value[PASSWORD_LENGTH];
	u8 attemps;
	const u8 maxAttemps;
} PASSWORD_t;

/**********************************************************************
 * @brief This is the structure that holds the system's sensors data
 **********************************************************************/
typedef struct {
	u16 u16_CurrentValueInBinary;
    u8  u8_CriticalValue;
    u8  u8_MaxValue;
	u8	u8_CurrentValue;
	u8	u8_AdcChannel;
} SENSOR_t;

typedef struct {
	SENSOR_t temperature;
	SENSOR_t gas;
} SYSTEM_INPUTS_t;

/**********************************************************************
 * @brief This is the structure that holds the system's data
 * 		  that is used to control the system and display it on the LCD
 * 		  screen.
 * 		  The system's data is:
 * 			* The system's state flags:
 * 				* correctPassword: The system's password is correct
 * 				* buzzer: The system's buzzer is enabled
 * 				* openDoor: The system's door should be opened
 * 			* The system's password data:
 * 				* The system's password value
 * 				* The system's password attemps counter
 * 			* The system's sensors data:
 * 				* The system's temperature sensor data:
 * 					* The system's current temperature value in Celsius
 * 					* The system's current temperature value in binary
 * 					* The system's maximum temperature value in Celsius
 * 				* The system's gas sensor data
 * 					* The system's current gas level value in binary
 * 					* The system's maximum gas level in percentage
 * 					* The system's current gas level in percentage
 **********************************************************************/
typedef struct {
	SYSTEM_INPUTS_t sensors;
	PASSWORD_t 	    password;
	FLAG_t 		    flag;
} SYSTEM_t;


/**********************************************************************/
/* 								EXTERNS                               */
/**********************************************************************/

extern SYSTEM_t system;


#endif 	/* MAIN_CFG_H */
