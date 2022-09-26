

#ifndef LCD_INT_H
#define LCD_INT_H

void LCD_voidInit(void);
tenuErrorStatus LCD_enuWriteCmd(uint8 u8LcdIndxCpy , uint8 u8LcdCmdCpy);
tenuErrorStatus LCD_enuWriteData(uint8 u8LcdIndxCpy , uint8 u8LcdDataCpy);
void LCD_voidSendString(uint8 u8LcdIndxCpy ,uint8 *Copy_pu8String);
void LCD_voidSendNumber(uint8 u8LcdIndxCpy,uint32 number);
void LCD_vidGoToXY(uint8 u8LcdIndxCpy,uint8 Copy_u8Location,uint8 Copy_u8LineNum);
void LCD_voidWriteSpicalCaracter(uint8 u8LcdIndxCpy,uint8 Copy_u8PatternNumper,uint8* Copy_u8Patterns);


#endif
