#include"..\..\LIB\LSTD_TYPES.h"
#include"..\..\MCAL\MDIO\MDIO_Interface.h"

#include"HCLCD_Private.h"
#include"HCLCD_Config.h"
#include"HCLCD_Interface.h"

#include"util/delay.h"

void HCLCD_VidWriteCommand_8Bits(u8 Copy_u8Command)
{
	/*select Command register--> Write zero on Rs pin*/
	MDIO_Error_State_SetPinValue(RS,CONTROL_PORT,PIN_LOW);
	/*select Write mode--> Write zero on RW pin*/
	//MDIO_Error_State_SetPinValue(RW,CONTROL_PORT,PIN_LOW);
	/*Send Command ON port Data*/
	MDIO_Error_State_SetPortValue(DATA_PORT,Copy_u8Command);
	/*Send Enable*/
	MDIO_Error_State_SetPinValue(E,CONTROL_PORT,PIN_HIGH);
	_delay_ms(2);
	MDIO_Error_State_SetPinValue(E,CONTROL_PORT,PIN_LOW);
	_delay_ms(2);
	MDIO_Error_State_SetPinValue(E,CONTROL_PORT,PIN_HIGH);	
}

void HCLCD_Vid8Bits_Init(void)
{
	/*LCD Data and control port intialization*/
	MDIO_Error_State_SetPortDirection(DATA_PORT,PORT_OUTPUT);
	MDIO_Error_State_SetPinDirection(RS,CONTROL_PORT,PIN_OUTPUT);
	//MDIO_Error_State_SetPinDirection(RW,CONTROL_PORT,PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(E,CONTROL_PORT,PIN_OUTPUT);

	/*wait to 30ms*/
	_delay_ms(30);
	/*send function set command*/
	HCLCD_VidWriteCommand_8Bits(HCLCD_FUNCTION_SET);
	_delay_ms(1);
	/*send Display on/off  command*/
	HCLCD_VidWriteCommand_8Bits(HCLCD_DISPLAY_ON_OFF);
	_delay_ms(1);
	/*send Display Clear  command*/
	HCLCD_VidWriteCommand_8Bits(DISPLAY_CLEAR);
	_delay_ms(2);
	/*send Entry Mode  set command*/
	HCLCD_VidWriteCommand_8Bits(HCLCD_ENTRY_MODE_SET);
}
void HCLCD_VidWriteChar_8Bits(u8 Copy_u8Data)
{
	/*select Data register--> Write one on Rs pin*/
	MDIO_Error_State_SetPinValue(RS,CONTROL_PORT,PIN_HIGH);
	/*select Write mode--> Write zero on RW pin*/
	//MDIO_Error_State_SetPinValue(RW,CONTROL_PORT,PIN_LOW);
	/*Send Command ON port Data*/
	MDIO_Error_State_SetPortValue(DATA_PORT,Copy_u8Data);
	/*Send Enable*/
	MDIO_Error_State_SetPinValue(E,CONTROL_PORT,PIN_HIGH);
	_delay_ms(2);
	MDIO_Error_State_SetPinValue(E,CONTROL_PORT,PIN_LOW);
	_delay_ms(2);
	MDIO_Error_State_SetPinValue(E,CONTROL_PORT,PIN_HIGH);	
}

void HCLCD_VidWriteString_8Bits(u8* PCopy_u8String)
{
	u8 Loc_u8Count=0;
	while(PCopy_u8String[Loc_u8Count]!=NULL)
	{
		HCLCD_VidWriteChar_8Bits(PCopy_u8String[Loc_u8Count]);
		Loc_u8Count++;
	}
}
void HCLCD_VidWriteNumber_8Bits(u32 Copy_u8Number)
{
	u8 ARR_Digits[10];
	u8 LOC_Count=0;
	if(Copy_u8Number>0)
	{
		while(Copy_u8Number!=0)
		{
			ARR_Digits[LOC_Count]=Copy_u8Number%10;
			Copy_u8Number/=10;
			LOC_Count++;
		}
		for(s8 i=LOC_Count-1;i>=0;i--)
		{
			HCLCD_VidWriteChar_8Bits(ARR_Digits[i]+'0');
		}
	}
	else
	{
		HCLCD_VidWriteChar_8Bits('0');
	}
}
void HCLCD_VidSetPosition(u8 Copy_u8LineNumber , u8 Copy_u8PositionNumber)
{
	if((Copy_u8LineNumber==HCLCD_LINE1)&&((Copy_u8PositionNumber>=0)&&(Copy_u8PositionNumber<16)))
	{
		HCLCD_VidWriteCommand_8Bits((LINE1_OFFSET_ADDRESS+Copy_u8PositionNumber));
	}
	else if((Copy_u8LineNumber==HCLCD_LINE2)&&((Copy_u8PositionNumber>=0)&&(Copy_u8PositionNumber<16)))
	{
		HCLCD_VidWriteCommand_8Bits((LINE2_OFFSET_ADDRESS+Copy_u8PositionNumber));
	}
	else
	{
		/*Do Nothing*/
	}
}

void HCLCD_VidWriteCommand_4Bits(u8 Copy_u8Command)
{
	u8 LOC_u8CopyCommand;
	/*select Command register--> Write zero on Rs pin*/
	MDIO_Error_State_SetPinValue(RS,CONTROL_PORT,PIN_LOW);
	/*select Write mode--> Write zero on RW pin*/
	//MDIO_Error_State_SetPinValue(RW,CONTROL_PORT,PIN_LOW);
	/*Send  Command*/
	LOC_u8CopyCommand=(Copy_u8Command&0x0F)<<HCLCD_PINSTART;
	MDIO_Error_State_SetNippleValue(HCLCD_PINSTART,DATA_PORT,LOC_u8CopyCommand);
	/*Send Enable*/
	MDIO_Error_State_SetPinValue(E,CONTROL_PORT,PIN_HIGH);
	_delay_ms(2);
	MDIO_Error_State_SetPinValue(E,CONTROL_PORT,PIN_LOW);
}
void HCLCD_Vid4Bits_Init(void)
{
	s8 LOC_u8PinCount;
	/*LCD Data and control port initialization*/
	for(LOC_u8PinCount=HCLCD_PINEND;LOC_u8PinCount>=HCLCD_PINSTART;LOC_u8PinCount--)
	{
	MDIO_Error_State_SetPinDirection(LOC_u8PinCount,DATA_PORT,PIN_OUTPUT);
	}
	MDIO_Error_State_SetPinDirection(RS,CONTROL_PORT,PIN_OUTPUT);
	//MDIO_Error_State_SetPinDirection(RW,CONTROL_PORT,PIN_OUTPUT);
	MDIO_Error_State_SetPinDirection(E,CONTROL_PORT,PIN_OUTPUT);
	/*wait to 30ms*/
	_delay_ms(30);
	/*send function set command*/
	HCLCD_VidWriteCommand_4Bits(HCLCD_FUNCTION_SET>>4);
	HCLCD_VidWriteCommand_4Bits(HCLCD_FUNCTION_SET>>4);
	HCLCD_VidWriteCommand_4Bits(HCLCD_FUNCTION_SET);
	_delay_ms(1);
	/*send Display on/off  command*/
	HCLCD_VidWriteCommand_4Bits(HCLCD_DISPLAY_ON_OFF>>4);
	HCLCD_VidWriteCommand_4Bits(HCLCD_DISPLAY_ON_OFF);
	_delay_ms(1);
	/*send Display Clear  command*/
	HCLCD_VidWriteCommand_4Bits(DISPLAY_CLEAR>>4);
	HCLCD_VidWriteCommand_4Bits(DISPLAY_CLEAR);
	_delay_ms(2);
	/*send Entry Mode  set command*/
	HCLCD_VidWriteCommand_4Bits(HCLCD_ENTRY_MODE_SET>>4);
	HCLCD_VidWriteCommand_4Bits(HCLCD_ENTRY_MODE_SET);
}
void HCLCD_VidWriteChar_4Bits(u8 Copy_u8Data)
{
	u8 LOC_u8CopyData;
	/*select Data register--> Write One on Rs pin*/
	MDIO_Error_State_SetPinValue(RS,CONTROL_PORT,PIN_HIGH);
	/*select Write mode--> Write zero on RW pin*/
	//MDIO_Error_State_SetPinValue(RW,CONTROL_PORT,PIN_LOW);
	/*Send Data*/
	LOC_u8CopyData=(Copy_u8Data&0x0F)<<HCLCD_PINSTART;
	MDIO_Error_State_SetNippleValue(HCLCD_PINSTART,DATA_PORT,LOC_u8CopyData);
	/*Send Enable*/
	MDIO_Error_State_SetPinValue(E,CONTROL_PORT,PIN_HIGH);
	_delay_ms(20);
	MDIO_Error_State_SetPinValue(E,CONTROL_PORT,PIN_LOW);
}
void HCLCD_VidSendChar_4Bits(u8 Copy_u8Data)
{
	HCLCD_VidWriteChar_4Bits(Copy_u8Data>>4);
	HCLCD_VidWriteChar_4Bits(Copy_u8Data);
}
void HCLCD_VidWriteString_4Bits(u8* PCopy_u8String)
{
	u8 Loc_u8Count=0;
	while(PCopy_u8String[Loc_u8Count]!=NULL)
	{
		HCLCD_VidSendChar_4Bits(PCopy_u8String[Loc_u8Count]);
		Loc_u8Count++;
	}
}
void HCLCD_VidWriteNumber_4Bits(u32 Copy_u8Number)
{
	u8 ARR_Digits[10];
	u8 LOC_Count=0;
	if(Copy_u8Number>0)
	{
		while(Copy_u8Number!=0)
		{
			ARR_Digits[LOC_Count]=Copy_u8Number%10;
			Copy_u8Number/=10;
			LOC_Count++;
		}
		for(s8 i=LOC_Count-1;i>=0;i--)
		{
			HCLCD_VidSendChar_4Bits(ARR_Digits[i]+'0');
		}
	}
	else
	{
		HCLCD_VidSendChar_4Bits('0');
	}
}
void HCLCD_VidSetPosition_4BitsMode(u8 Copy_u8LineNumber , u8 Copy_u8PositionNumber)
{
	if((Copy_u8LineNumber==HCLCD_LINE1)&&((Copy_u8PositionNumber>=0)&&(Copy_u8PositionNumber<16)))
	{
		HCLCD_VidWriteCommand_4Bits((LINE1_OFFSET_ADDRESS+Copy_u8PositionNumber)>>4);
		HCLCD_VidWriteCommand_4Bits((LINE1_OFFSET_ADDRESS+Copy_u8PositionNumber));
	}
	else if((Copy_u8LineNumber==HCLCD_LINE2)&&((Copy_u8PositionNumber>=0)&&(Copy_u8PositionNumber<16)))
	{
		HCLCD_VidWriteCommand_4Bits((LINE2_OFFSET_ADDRESS+Copy_u8PositionNumber)>>4);
		HCLCD_VidWriteCommand_4Bits((LINE2_OFFSET_ADDRESS+Copy_u8PositionNumber));
	}
	else
	{
		/*Do Nothing*/
	}
}
