#include "STD_Types.h"
#include "keypad_cfg.h"
#include "keypad_priv.h"

uint8 KeyPad_au8SitchKey[ROWS_NUMBERS][COLS_NUMBERS]=
{
	{'7','8','9','/'},
	{'4','5','6','X'},
	{'1','2','3','-'},
	{'z','0','=','+'}
	
};

uint8 au8Rows[ROWS_NUMBERS]={16,17,18,19};
uint8 au8cols[COLS_NUMBERS]={20,21,22,23};
