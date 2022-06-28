#include"../../LIB/LSTD_TYPES.h"
#include"../../LIB/LBIT_MATH.h"
#include"../../MCAL/TIMER2/TIMER2_Interface.h"
#include"../../MCAL/MDIO/MDIO_Interface.h"


void H_ServoInit(void)
{
	MDIO_Error_State_SetPinDirection(PIN7, MDIO_PORTD, PIN_OUTPUT);
	TIMER2_VidInit();
	//M_Pwm2Init();
}
void H_ServoSetAngle(u16 u16_local_angle)
{
	f64 f64_local_DutyCycle = ( ( ( 5 * u16_local_angle ) / 180 ) + 5 );
	M_Pwm2SetDutyCycle(f64_local_DutyCycle);
}
void H_ServoStart(void)
{
	M_Pwm2Start();
}
void H_ServoStop(void)
{
	M_Pwm2Stop();
}
