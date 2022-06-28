/*
 * DC_MOTOR.c
 *
 * Created: 4/18/2022 9:46:43 AM
 *  Author: Dell
 */ 

#include "DC_MOTOR_POT.h"

#include"../../MCAL/MDIO/MDIO_Interface.h"
#include "DC_MOTOR_POT_CFG.h"

void H_DcMotorPotInit(void)
{
	MDIO_Error_State_SetPinDirection(IN_1_POT, DC_M_POT_PORT, PIN_OUTPUT);
	//MDIO_Error_State_SetPinDirection(IN_2, DC_M_PORT, PIN_OUTPUT);
	//M_Pwm0Init();
}

void H_DcMotorPotStart(u8 u8_local_direction)
{
	//switch(u8_local_direction)
	//{
		//case CLK_W:
			MDIO_Error_State_SetPinValue(IN_1_POT, DC_M_POT_PORT, PIN_HIGH);
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

void H_DcMotorPotStop(void)
{
	MDIO_Error_State_SetPinValue(IN_1_POT, DC_M_POT_PORT, PIN_LOW);
	//MDIO_Error_State_SetPinValue(IN_2, DC_M_PORT, PIN_LOW);
}
