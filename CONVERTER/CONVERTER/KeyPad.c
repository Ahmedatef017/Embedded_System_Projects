

#include "KeyPad.h"

u8 KEYPAD_GetKey(void)
{
	u8 r,c,key=NO_KEY;
	DIO_WritePin(FIRST_OUTPUT,HIGH);
	DIO_WritePin(FIRST_OUTPUT+1,HIGH);
	DIO_WritePin(FIRST_OUTPUT+2,HIGH);
	DIO_WritePin(FIRST_OUTPUT+3,HIGH);
	
	for(r=0;r<ROWS;r++)
	{
		DIO_WritePin(FIRST_OUTPUT+r,LOW);
		for(c=0;c<COLS;c++)
		{
			if(DIO_ReadPin(FIRST_INPUT+c)==LOW)
			{
				key=KeysArray[r][c];
				while(DIO_ReadPin(FIRST_INPUT+c)==LOW);
			}
		}
		DIO_WritePin(FIRST_OUTPUT+r,HIGH);
	}
	
	return key;
}

s32 KEYPAD_ScanDecimel(u8 k,s32 num)
{
			num=num*10+(k-'0');
			return num;
}

//s32 KEYPAD_ScanDecimel(u8 k)
//{
	//s32 num = 0;
	//num=num*10+(k-'0');
	//return num;
//}

s32 KEYPAD_ScanHex(u8 k,s32 num)
{
	if(k>='0'&&k<='9')
	{
		num=num*16+k-'0';
	}
	else if((k>='A'&&k<='F'))  //str[i]-10+'A'
	{
		switch (k)
		{
			case 'A':
			num=num*16+10;
			break;
			
			case 'B':
			num=num*16+11;
			break;
			
			case 'C':
			num=num*16+12;
			break;
			
			case 'D':
			num=num*16+13;
			break;
			
			case 'E':
			num=num*16+14;
			break;
			
			case 'F':
			num=num*16+15;
			break;
		}
	}
	
	return num;
}
s32 KEYPAD_ScanBinary(u8 k,s32 num)
{
	if(k=='1'||k=='0')
	{
		num=num*2+k-'0';
	}
	return num;
}