#ifndef MDIO_INTERFACE_H_
#define MDIO_INTERFACE_H_

#define MDIO_PORTA   0
#define MDIO_PORTB   1
#define MDIO_PORTC   2
#define MDIO_PORTD   3

#define PIN_OUTPUT    1
#define PIN_INPUT     0

#define PORT_OUTPUT    255
#define PORT_INPUT     0

#define PIN_HIGH    1
#define PIN_LOW     0

typedef enum
{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
}Pin_t;

/*Set Pin Direction Function */
Error_State MDIO_Error_State_SetPinDirection(u8 Copy_u8PinNumber,u8  Copy_u8PortNumber,u8 Copy_u8PinDirection);  
/*Set Port Direction Function */
Error_State MDIO_Error_State_SetPortDirection(u8 Copy_u8PortNumber,u8 Copy_u8PortDirection);
/*Set Pin Value Function */
Error_State MDIO_Error_State_SetPinValue(u8 Copy_u8PinNumber,u8 Copy_u8PortNumber,u8 Copy_u8PinValue);
/*Set Port Value Function */
Error_State MDIO_Error_State_SetPortValue(u8 Copy_u8PortNumber,u8 Copy_u8PortValue);
/*Get Pin Value Function */
Error_State MDIO_Error_State_GetPinValue(u8 Copy_u8PinNumber,u8 Copy_u8PortNumber,u8* P_u8PinValue);

/*Toggle Pin Value Function */

/*Active Pull Up Resistor Function*/

/*Set Nipple Direction Function */

/*Set Nipple Values Function */
Error_State MDIO_Error_State_SetNippleValue(u8 Copy_u8PinStart,u8 Copy_u8PortNumber,u8 Copy_u8Value);

#endif

