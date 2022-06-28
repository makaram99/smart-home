#ifndef MAIN_H
#define MAIN_H

/*--------------------------------------------------------------------*/
/* 			                                                          */
/* 								Includes                              */
/* 			                                                          */
/*--------------------------------------------------------------------*/
#include <util/delay.h>
#include <math.h>

#include "LIB/LSTD_TYPES.h"
#include "LIB/LBIT_MATH.h"

#include "MCAL/MDIO/MDIO_Interface.h"
#include "MCAL/MGIE/MGIE_Interface.h"
#include "MCAL/MADC/MADC_Interface.h"
#include "MCAL/TIMER2/TIMER2_Interface.h"

#include "HAL/SERVO_M/SERVO_Interface.h"
#include "HAL/HCLCD/HCLCD_Interface.h"
#include "HAL/KEY_PAD/HKPD_Interface.h"
#include "HAL/DC_MOTOR/DC_MOTOR.h"
#include "HAL/DC_MOTOR_POT/DC_MOTOR_POT.h"

#include "Free_RTOS/FreeRTOS.h"
#include "Free_RTOS/task.h"
#include "Free_RTOS/semphr.h"


/*--------------------------------------------------------------------*/
/* 			                                                          */
/* 						    TASKS PROTOTYPES                          */
/* 			                                                          */
/*--------------------------------------------------------------------*/
void taskGetPassword(void * pv);
void taskDisplaySystemState(void * pv );
void taskControlGasLevel(void * pv);
void taskControlTemperature(void * pv);
void taskReadSensors(void * pv);
void ADC_SetNotification(void);

/*--------------------------------------------------------------------*/
/* 			                                                          */
/* 					ORDINARY FUNCTIONS PROTOTYPES                     */
/* 			                                                          */
/*--------------------------------------------------------------------*/

void System_Init(u8 u8_AdcChannelToRead);
void displayDoorState(void);
void displayTemperatureValue(void);
void displayFireState(void);
void displayEntryPasswordSecurity(void);
void controlDoor(void);
u8 comparePasswords(const u8 * const pass1, const u8 * const pass2, const u8 length);

#endif /* MAIN_H */