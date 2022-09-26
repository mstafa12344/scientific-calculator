#include "STD_Types.h"
#include "BIT_Math.h"
#include <avr/delay.h>
#include "DIO_int.h"
#include "keypad_int.h"
#include "keypad_cfg.h"
#include "keypad_priv.h"
void KeyPad_voidInit(void)
{
	uint8 u8CounLoc1,u8CounLoc2;
	
	for(u8CounLoc1=0;u8CounLoc1<ROWS_NUMBERS;u8CounLoc1++)
	{
		DIO_enuWritePin(au8Rows[u8CounLoc1],1);
		
	}
	for(u8CounLoc2=0;u8CounLoc2<COLS_NUMBERS;u8CounLoc2++)
	{
		DIO_enuActivatePullUp(au8cols[u8CounLoc2],1);
	}
	
}
uint8 KeyPad_voidPressedKey(void)
{
	uint8 u8OutCountLoc;
	uint8 u8INCountLoc;
	uint8 u8KeyResult;
	uint8 u8flag=0;
	uint8 u8ReturnResult=0XFF;
	
	for( u8OutCountLoc=0; u8OutCountLoc<ROWS_NUMBERS;u8OutCountLoc++)
	{
		DIO_enuWritePin(au8Rows[u8OutCountLoc],0);
		
		for(u8INCountLoc=0;u8INCountLoc<COLS_NUMBERS;u8INCountLoc++)
		{
			DIO_enuReadPin(au8cols[u8INCountLoc],&u8KeyResult);
			if(u8KeyResult==0)
			{
				
				_delay_ms(20);
				
				u8ReturnResult=KeyPad_au8SitchKey[u8OutCountLoc][u8INCountLoc];
				u8flag=1;
				break;	
			}
			
		}
		DIO_enuWritePin(au8Rows[u8OutCountLoc],1);
		
		if(u8flag==1)
		{
			break;
		}
	}
	return u8ReturnResult;
}
