
#include "STD_Types.h"
#include "BIT_MAth.h"
#include <avr/delay.h>

#include "DIO_int.h"
#include "LCD_int.h"
#include "LCD_cfg.h"
#include "LCD_priv.h"

void LCD_voidInit(void)
{
	uint8 u8CntrLoc ;
	uint8 u8CmdLoc  ;
	for(u8CntrLoc = 0 ; u8CntrLoc < LCD_MAX_NUM ; u8CntrLoc++)
	{
		if (LCD_astrConfig[u8CntrLoc].strLcdPinOutCfg.u8LcdMode== LCD_8BIT_MODE)
		{
				_delay_ms(30);
				u8CmdLoc = 0b00110000|
				LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8LineMode << 3|
				LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8CharFont << 2;
				LCD_enuWriteCmd (u8CntrLoc , u8CmdLoc);
				_delay_ms(1);
				u8CmdLoc = 0b00001000|
				LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8DisplayState << 2|
				LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8CursorState << 1|
				LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8BlinkState << 0;
				LCD_enuWriteCmd (u8CntrLoc , u8CmdLoc);
				_delay_ms(1);
				LCD_enuWriteCmd (u8CntrLoc , 0x01);
				_delay_ms(2);
				u8CmdLoc = 0b00000100|
				LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8IncreMode << 1|
				LCD_astrConfig[u8CntrLoc].strLcdOptionCfg.u8WindowMode << 0;
				LCD_enuWriteCmd (u8CntrLoc , u8CmdLoc);
				_delay_ms(1);
				
				
				
				
				
		}
		else
		{
			
		}
		
	}
}
tenuErrorStatus LCD_enuWriteCmd(uint8 u8LcdIndxCpy , uint8 u8LcdCmdCpy)
{
 tenuErrorStatus enuReturStateLoc = E_OK ;
 if(u8LcdIndxCpy < LCD_MAX_NUM)
 {
	//write DIO rs
	DIO_enuWritePin(LCD_astrConfig[u8LcdIndxCpy].strLcdPinOutCfg.au8ControlPins[0] , 0) ;
   // help cmd	
   LCD_voidHelp(u8LcdIndxCpy, u8LcdCmdCpy);
   
   
 }
 else
 {
	 enuReturStateLoc = E_NOK_PARAM_OUT_OF_RANGE ;
 }
	return enuReturStateLoc ;
}
tenuErrorStatus LCD_enuWriteData(uint8 u8LcdIndxCpy , uint8 u8LcdDataCpy)
{
tenuErrorStatus enuReturStateLoc = E_OK ;
 if(u8LcdIndxCpy < LCD_MAX_NUM)
 {
	//write DIO rs
	DIO_enuWritePin(LCD_astrConfig[u8LcdIndxCpy].strLcdPinOutCfg.au8ControlPins[0] , 1) ;
   // help cmd	
   LCD_voidHelp(u8LcdIndxCpy, u8LcdDataCpy);
   
   
 }
 else
 {
	 enuReturStateLoc = E_NOK_PARAM_OUT_OF_RANGE ;
 }
	return enuReturStateLoc ;
	
}
	
void LCD_voidSendString(uint8 u8LcdIndxCpy ,uint8 *Copy_pu8String)
{
	for(int i=0; Copy_pu8String[i] != '\0' ; i++)
		  LCD_enuWriteData(u8LcdIndxCpy,Copy_pu8String[i]);

}

void LCD_voidSendNumber(uint8 u8LcdIndxCpy,uint32 number)
{
	uint8 counter ,tempval=0;
	uint32 u32ReversNumLoc=0,u32ReminderLoc1,u32ReminderLoc2,tempNumber=number;

	for(counter=-1;tempval==0;counter++)
	{
		tempval=tempNumber%10;
		tempNumber=tempNumber/10;
	}
	/*first we reverse the number*/
	while(number!=0)
	{
		u32ReminderLoc1= number%10;
		u32ReversNumLoc= u32ReversNumLoc*10+u32ReminderLoc1;
		number=number/10;
	}

	while(u32ReversNumLoc!=0)
	{
		u32ReminderLoc2=u32ReversNumLoc%10;
		LCD_enuWriteData(u8LcdIndxCpy,u32ReminderLoc2+'0');
		u32ReversNumLoc=u32ReversNumLoc/10;
	}
	while(counter!=0)
	{
		LCD_enuWriteData(u8LcdIndxCpy,'0');
		counter--;
	}
}

void LCD_vidGoToXY(uint8 u8LcdIndxCpy,uint8 Copy_u8Location,uint8 Copy_u8LineNum)
{
    switch (Copy_u8LineNum)
    {
          case 1 :
        	  LCD_enuWriteCmd(u8LcdIndxCpy,0x80+Copy_u8Location);
        	  break;
          case 2 :
        	  LCD_enuWriteCmd(u8LcdIndxCpy,0xC0+Copy_u8Location);
        	  break;
    }
}

void LCD_voidWriteSpicalCaracter(uint8 u8LcdIndxCpy,uint8 Copy_u8PatternNumper,uint8* Copy_u8Patterns)
{
	uint8 Local_u8CGRAMAddress=0,Local_u8Iterator;
	Local_u8CGRAMAddress=Copy_u8PatternNumper*8;
	LCD_enuWriteCmd(0,Local_u8CGRAMAddress+0X40);
	for(Local_u8Iterator=0;Local_u8Iterator<8;Local_u8Iterator++)
	{
		LCD_enuWriteData(0,Copy_u8Patterns[Local_u8Iterator]);
	}


}





static void LCD_voidHelp(uint8 u8LcdIndxCpy, uint8 u8LcdCmdDataCpy)
{
	uint8 u8CntrLoc ;
	/* rw low*/
	DIO_enuWritePin(LCD_astrConfig[u8LcdIndxCpy].strLcdPinOutCfg.au8ControlPins[1] , 0) ;
    /* EN latch high */
	DIO_enuWritePin(LCD_astrConfig[u8LcdIndxCpy].strLcdPinOutCfg.au8ControlPins[2] , 1) ;
    if (LCD_astrConfig[u8LcdIndxCpy].strLcdPinOutCfg.u8LcdMode== LCD_8BIT_MODE)
	{
		for(u8CntrLoc = 0 ; u8CntrLoc < 8 ; u8CntrLoc++)
		{
			DIO_enuWritePin(LCD_astrConfig[u8LcdIndxCpy].strLcdPinOutCfg.au8DataPins[u8CntrLoc],GET_BIT(u8LcdCmdDataCpy,u8CntrLoc));
		}
	
	}
	else
	{
		for(u8CntrLoc = 4 ; u8CntrLoc < 8; u8CntrLoc++)
		{
			DIO_enuWritePin(LCD_astrConfig[u8LcdIndxCpy].strLcdPinOutCfg.au8DataPins[u8CntrLoc],GET_BIT(u8LcdCmdDataCpy,u8CntrLoc));
			u8LcdCmdDataCpy = u8LcdCmdDataCpy<<4 ;
			DIO_enuWritePin(LCD_astrConfig[u8LcdIndxCpy].strLcdPinOutCfg.au8DataPins[u8CntrLoc],GET_BIT(u8LcdCmdDataCpy,u8CntrLoc));
			
		}
	

		
	}
	
	/* EN latch low */
	DIO_enuWritePin(LCD_astrConfig[u8LcdIndxCpy].strLcdPinOutCfg.au8ControlPins[2] , 0) ;
    _delay_ms(2);
}
  
   
   
   
   
   
   
   
   
   
   
   
