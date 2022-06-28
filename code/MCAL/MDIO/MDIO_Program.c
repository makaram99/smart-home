
#include"..\..\LIB\LSTD_TYPES.h"
#include"..\..\LIB\LBIT_MATH.h"

#include"MDIO_Private.h"
#include"MDIO_Interface.h"

/*Set Pin Direction Function */
Error_State MDIO_Error_State_SetPinDirection(u8 Copy_u8PinNumber,u8  Copy_u8PortNumber,u8 Copy_u8PinDirection)
{
	Error_State LOC_Error_State_ReturnState=OK;
	if((Copy_u8PinNumber>=0)&&(Copy_u8PinNumber<8))
	{
		switch(Copy_u8PortNumber)
		{
		case MDIO_PORTA:
			if(Copy_u8PinDirection==PIN_OUTPUT)
			{
				SET_BIT(DDRA,Copy_u8PinNumber);
			}
			else if(Copy_u8PinDirection==PIN_INPUT)
			{
				CLR_BIT(DDRA,Copy_u8PinNumber);
			}
			else
			{
				LOC_Error_State_ReturnState=NOK;
			}
			break;
		case MDIO_PORTB:
			if(Copy_u8PinDirection==PIN_OUTPUT)
			{
				SET_BIT(DDRB,Copy_u8PinNumber);
			}
			else if(Copy_u8PinDirection==PIN_INPUT)
			{
				CLR_BIT(DDRB,Copy_u8PinNumber);
			}
			else
			{
				LOC_Error_State_ReturnState=NOK;
			}
			break;
		case MDIO_PORTC:
			if(Copy_u8PinDirection==PIN_OUTPUT)
			{
				SET_BIT(DDRC,Copy_u8PinNumber);
			}
			else if(Copy_u8PinDirection==PIN_INPUT)
			{
				CLR_BIT(DDRC,Copy_u8PinNumber);
			}
			else
			{
				LOC_Error_State_ReturnState=NOK;
			}
			break;	
		case MDIO_PORTD:
			if(Copy_u8PinDirection==PIN_OUTPUT)
			{
				SET_BIT(DDRD,Copy_u8PinNumber);
			}
			else if(Copy_u8PinDirection==PIN_INPUT)
			{
				CLR_BIT(DDRD,Copy_u8PinNumber);
			}
			else
			{
				LOC_Error_State_ReturnState=NOK;
			}
			break;
		default:
			LOC_Error_State_ReturnState=NOK;
			break;
		}
	}
	else
	{
		LOC_Error_State_ReturnState=NOK;
	}

	return LOC_Error_State_ReturnState;
}
/*Set Port Direction Function */
Error_State MDIO_Error_State_SetPortDirection(u8 Copy_u8PortNumber,u8 Copy_u8PortDirection)
{
	Error_State LOC_Error_State_ReturnState=OK;
	if((Copy_u8PortDirection==PORT_OUTPUT)||(Copy_u8PortDirection==PORT_INPUT))
	{
		switch(Copy_u8PortNumber)
		{
		case MDIO_PORTA:
			DDRA=Copy_u8PortDirection;
			break;
		case MDIO_PORTB:
			DDRB=Copy_u8PortDirection;
			break;
		case MDIO_PORTC:
			DDRC=Copy_u8PortDirection;
			break;
		case MDIO_PORTD:
			DDRD=Copy_u8PortDirection;
			break;
		default:
			LOC_Error_State_ReturnState=NOK;
			break;
		}
	}
	else
	{
		LOC_Error_State_ReturnState=NOK;
	}
	return LOC_Error_State_ReturnState;
}

/*Set Pin Value Function */
Error_State MDIO_Error_State_SetPinValue(u8 Copy_u8PinNumber,u8 Copy_u8PortNumber,u8 Copy_u8PinValue)
{
	Error_State LOC_Error_State_ReturnState=OK;

	if((Copy_u8PinNumber>=0)&&(Copy_u8PinNumber<8))
	{
		switch(Copy_u8PortNumber)
		{
		case MDIO_PORTA:
			if(Copy_u8PinValue==PIN_HIGH)
			{
				SET_BIT(PORTA,Copy_u8PinNumber);
			}
			else if(Copy_u8PinValue==PIN_LOW)
			{
				CLR_BIT(PORTA,Copy_u8PinNumber);
			}
			else
			{
				LOC_Error_State_ReturnState=NOK;
			}
			break;
		case MDIO_PORTB:
			if(Copy_u8PinValue==PIN_HIGH)
			{
				SET_BIT(PORTB,Copy_u8PinNumber);
			}
			else if(Copy_u8PinValue==PIN_LOW)
			{
				CLR_BIT(PORTB,Copy_u8PinNumber);
			}
			else
			{
				LOC_Error_State_ReturnState=NOK;
			}
			break;
		case MDIO_PORTC:
			if(Copy_u8PinValue==PIN_HIGH)
			{
				SET_BIT(PORTC,Copy_u8PinNumber);
			}
			else if(Copy_u8PinValue==PIN_LOW)
			{
				CLR_BIT(PORTC,Copy_u8PinNumber);
			}
			else
			{
				LOC_Error_State_ReturnState=NOK;
			}
			break;	
		case MDIO_PORTD:
			if(Copy_u8PinValue==PIN_HIGH)
			{
				SET_BIT(PORTD,Copy_u8PinNumber);
			}
			else if(Copy_u8PinValue==PIN_LOW)
			{
				CLR_BIT(PORTD,Copy_u8PinNumber);
			}
			else
			{
				LOC_Error_State_ReturnState=NOK;
			}
			break;
		default:
			LOC_Error_State_ReturnState=NOK;
			break;
		}
	}
	else
	{
		LOC_Error_State_ReturnState=NOK;
	}

	return LOC_Error_State_ReturnState;
}

/*Set Port Value Function */
Error_State MDIO_Error_State_SetPortValue(u8 Copy_u8PortNumber,u8 Copy_u8PortValue)
{
	Error_State LOC_Error_State_ReturnState=OK;
	switch(Copy_u8PortNumber)
	{
	case MDIO_PORTA:
		PORTA=Copy_u8PortValue;
		break;
	case MDIO_PORTB:
		PORTB=Copy_u8PortValue;
		break;
	case MDIO_PORTC:
		PORTC=Copy_u8PortValue;
		break;	
	case MDIO_PORTD:
		PORTD=Copy_u8PortValue;
		break;	
	default:
		LOC_Error_State_ReturnState=NOK;
		break;
	}
	return LOC_Error_State_ReturnState;
}

/*Get Pin Value Function */
Error_State MDIO_Error_State_GetPinValue(u8 Copy_u8PinNumber,u8 Copy_u8PortNumber,u8* P_u8PinValue)
{
	Error_State LOC_Error_State_ReturnState=OK;

	if(((Copy_u8PinNumber>=0)&&(Copy_u8PinNumber<8))&&(P_u8PinValue!=NULL_POINTER))
	{
		switch(Copy_u8PortNumber)
		{
		case MDIO_PORTA:
			*P_u8PinValue=GET_BIT(PINA,Copy_u8PinNumber);
			break;
		case MDIO_PORTB:
			*P_u8PinValue=GET_BIT(PINB,Copy_u8PinNumber);
			break;
		case MDIO_PORTC:
			*P_u8PinValue=GET_BIT(PINC,Copy_u8PinNumber);
			break;
		case MDIO_PORTD:
			*P_u8PinValue=GET_BIT(PIND,Copy_u8PinNumber);
			break;
		default:
			LOC_Error_State_ReturnState=NOK;
			break;		
		}
	}
	else
	{
		LOC_Error_State_ReturnState=NOK;
	}

	return LOC_Error_State_ReturnState;
}
/*Set Nipple Direction Function */

/*Set Nipple Values Function */
Error_State MDIO_Error_State_SetNippleValue(u8 Copy_u8PinStart,u8 Copy_u8PortNumber,u8 Copy_u8Value)
{
	Error_State LOC_Error_State_ReturnState=OK;
	if(Copy_u8PinStart<=4)
	{
		switch(Copy_u8PortNumber)
		{
		case MDIO_PORTA:
		/*for(u8 i=Copy_u8PinStart;i<=7;i++)
		{
			CLR_BIT(PORTA,i);
		}*/
			PORTA&=(~(0x0F<<Copy_u8PinStart));
			PORTA|=Copy_u8Value;
			break;
		case MDIO_PORTB:
			/*for(u8 i=Copy_u8PinStart;i<=Copy_u8PinEnd;i++)
		{
			CLR_BIT(PORTA,i);
		}*/
			PORTB&=(~(0x0F<<Copy_u8PinStart));
			PORTB|=Copy_u8Value;
			break;
		case MDIO_PORTC:
			/*for(u8 i=Copy_u8PinStart;i<=Copy_u8PinEnd;i++)
		{
			CLR_BIT(PORTA,i);
		}*/
			PORTC&=(~(0x0F<<Copy_u8PinStart));
			PORTC|=Copy_u8Value;
			break;
		case MDIO_PORTD:
			/*for(u8 i=Copy_u8PinStart;i<=Copy_u8PinEnd;i++)
		{
			CLR_BIT(PORTA,i);
		}*/
			PORTD&=(~(0x0F<<Copy_u8PinStart));
			PORTD|=Copy_u8Value;
			break;
		default:
			LOC_Error_State_ReturnState=NOK;
		}
	}
	else
	{
		LOC_Error_State_ReturnState=NOK;
	}
	return LOC_Error_State_ReturnState;
}
