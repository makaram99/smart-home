#ifndef HCLCD_INTERFACE_H_
#define HCLCD_INTERFACE_H_

/*LCD DISPLAY CLEAR Command --> No options*/
#define DISPLAY_CLEAR   0b00000001

#define HCLCD_LINE1    1
#define HCLCD_LINE2    2

void HCLCD_Vid8Bits_Init(void);
void HCLCD_Vid4Bits_Init(void);

void HCLCD_VidWriteChar_8Bits(u8 Copy_u8Data);

void HCLCD_VidSendChar_4Bits(u8 Copy_u8Data);

void HCLCD_VidWriteCommand_8Bits(u8 Copy_u8Command);
void HCLCD_VidWriteCommand_4Bits(u8 Copy_u8Command);


void HCLCD_VidWriteString_8Bits(u8* PCopy_u8String);
void HCLCD_VidWriteString_4Bits(u8* PCopy_u8String);

void HCLCD_VidWriteNumber_8Bits(u32 Copy_u8Number);
void HCLCD_VidWriteNumber_4Bits(u32 Copy_u8Number);

void HCLCD_VidSetPosition(u8 Copy_u8LineNumber , u8 Copy_u8PositionNumber);

void HCLCD_VidSetPosition_4BitsMode(u8 Copy_u8LineNumber , u8 Copy_u8PositionNumber);
#endif
