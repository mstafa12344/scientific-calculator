#include "STD_Types.h"
#include "BIT_Math.h"
#include <avr/delay.h>
#include "DIO/DIO_int.h"
#include "LCD/LCD_int.h"
#include "KeyPad/KEYPAD_int.h"
void main(void)
{
	DIO_voidInit();
	LCD_voidInit();
	KeyPad_voidInit();
	uint16 u16Number1=0,u16Number2=0;
	sint32 S32Result=0;
	uint8 u8TempVarLoc=0,u8OperationLoc=0;
	
	while(1)
	{
		uint16 u16Number1=0,u16Number2=0;
		sint32 S32Result=0;
		uint8 u8TempVarLoc=0,u8OperationLoc=0;
		LCD_enuWriteCmd(0,0X01);
		
		while(1)
		{
			u8TempVarLoc=KeyPad_voidPressedKey();
			if(u8TempVarLoc!=0XFF)
			{

				LCD_enuWriteData(0,u8TempVarLoc);
				_delay_ms(500);

				if(u8TempVarLoc=='+'||u8TempVarLoc=='-'||u8TempVarLoc=='X'||u8TempVarLoc=='/')
				{
					u8OperationLoc=u8TempVarLoc;
					break;
				}
				else
				{
					u16Number1=(u16Number1*10);
					u16Number1=(u16Number1)+(u8TempVarLoc-48);


				}
			}

		}

		while(1)
		{
			u8TempVarLoc=KeyPad_voidPressedKey();
			if(u8TempVarLoc!=0XFF)
			{
				LCD_enuWriteData(0,u8TempVarLoc);
				_delay_ms(500);
				if(u8TempVarLoc=='=')
				{
					break;
				}
				else
				{
					u16Number2=(u16Number2*10);
					u16Number2=(u16Number2)+(u8TempVarLoc-48);
				}
			}

		}

		if(u8OperationLoc=='+')
		{
			S32Result=u16Number2+u16Number1;
			LCD_voidSendNumber(0,S32Result);
			_delay_ms(5000);
		}
		else if(u8OperationLoc=='-')
		{
			if(u16Number1>u16Number2)
			{
			S32Result=u16Number1-u16Number2;
			LCD_voidSendNumber(0,S32Result);
			_delay_ms(5000);
			}
			else if(u16Number2>u16Number1)
			{
				S32Result=u16Number2-u16Number1;
				LCD_enuWriteData(0,'-');
				LCD_voidSendNumber(0,S32Result);
				_delay_ms(5000);

			}
		}
		else if(u8OperationLoc=='X')
		{
			S32Result=u16Number1*u16Number2;
			LCD_voidSendNumber(0,S32Result);
			_delay_ms(5000);
		}
		else
		{
			if(u16Number2==0)
			{

				LCD_enuWriteData(0,'E');
				LCD_enuWriteData(0,'R');
				LCD_enuWriteData(0,'R');
				LCD_enuWriteData(0,'O');
				LCD_enuWriteData(0,'R');
				_delay_ms(5000);
			}
			else
			{
			S32Result=u16Number1/u16Number2;
			LCD_voidSendNumber(0,S32Result);
			_delay_ms(5000);
			}
		}

	}

}