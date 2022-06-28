/*
 * DC_MOTOR.c
 *
 * Created: 4/18/2022 9:46:43 AM
 *  Author: Dell
 */ 

#include "DC_MOTOR.h"
#include "DC_MOTOR_CFG.h"
//#include "../../MCAL/TIMER_0/TIMER_0.h"
#include"../../MCAL/MDIO/MDIO_Interface.h"

void H_DcMotorInit(void)
{
	MDIO_Error_State_SetPinDirection(IN_1, DC_M_PORT, PIN_OUTPUT);
	//MDIO_Error_State_SetPinDirection(IN_2, DC_M_PORT, PIN_OUTPUT);
	//M_Pwm0Init();
}

void H_DcMotorStart(u8 u8_local_direction)
{
	//switch(u8_local_direction)
	//{
		//case CLK_W:
			MDIO_Error_State_SetPinValue(IN_1, DC_M_PORT, PIN_HIGH);
			//MDIO_Error_State_SetPinValue(IN_2, DC_M_PORT, PIN_LOW);
		//break;
		//case A_CLK_W:
			//MDIO_Error_State_SetPinValue(IN_1, DC_M_PORT, PIN_LOW);
			//MDIO_Error_State_SetPinValue(IN_2, DC_M_PORT, PIN_HIGH);
		//break;
		//default:
		//break;
	//}
}

void H_DcMotorStop(void)
{
	MDIO_Error_State_SetPinValue(IN_1, DC_M_PORT, PIN_LOW);
	//MDIO_Error_State_SetPinValue(IN_2, DC_M_PORT, PIN_LOW);
}
