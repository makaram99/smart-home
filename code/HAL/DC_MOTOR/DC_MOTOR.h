/*
 * DC_MOTOR.h
 *
 * Created: 4/18/2022 9:46:58 AM
 *  Author: Dell
 */ 


#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include"..\..\LIB\LSTD_TYPES.h"
#include"DC_MOTOR_CFG.h"

void H_DcMotorInit(void);
void H_DcMotorSetDirection(u8);
void H_DcMotorSetSpeed(u32);
void H_DcMotorStart(u8);
void H_DcMotorStop(void);

#define CLK_W      1
#define A_CLK_W    2



#endif /* DC_MOTOR_H_ */
