/*--------------------------------------------------------------------*/
/* 			                                                          */
/* 								Includes                              */
/* 			                                                          */
/*--------------------------------------------------------------------*/
#include "LIB/LSTD_TYPES.h"
#include "LIB/LBIT_MATH.h"

#include "main.h"
#include "main_cfg.h"



/*--------------------------------------------------------------------*/
/* 			                                                          */
/* 					CHANGE THE FOLLOWING TO YOUR NEEDS                */
/* 			                                                          */
/*--------------------------------------------------------------------*/

SYSTEM_t system = {
	.inputs.temperature = {
		.u8_MaxValue 				= 150,		/* Maximum temperature: 150 C */
        .u8_CriticalValue           = 40,       /* Critical temperature: 40 C */
		.u8_CurrentValue 			= 0,		/* Current temperature reading */
		.u16_CurrentValueInBinary 	= 0,		/* Current temperature reading in binary */
		.u8_AdcChannel				= 7,		/* ADC channel for temperature sensor */
	},
	.inputs.gas = {
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
