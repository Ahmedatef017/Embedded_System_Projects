#define F_CPU 8000000
#include <util/delay.h>
#include "DIO_Interface.h"
#include "LCD.h"
#include "Utiles.h"

#if LCD_MODE==LCD_8BIT
static void WriteInstuction(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
}
static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteInstuction(0x38); //8bit mode  2lines
	_delay_ms(1);
	WriteInstuction(0x0c);
	_delay_ms(1);
	WriteInstuction(0x01);//clear
	_delay_ms(2);
	WriteInstuction(0x06);//increase ddram adderss   shift off
}
#elif LCD_MODE==LCD_4BIT
static void WriteInstuction(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,(DIO_PinVoltage_type)READ_BIT(ins,7));
	DIO_WritePin(D6,(DIO_PinVoltage_type)READ_BIT(ins,6));
	DIO_WritePin(D5,(DIO_PinVoltage_type)READ_BIT(ins,5));
	DIO_WritePin(D4,(DIO_PinVoltage_type)READ_BIT(ins,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	DIO_WritePin(D7,(DIO_PinVoltage_type)READ_BIT(ins,3));
	DIO_WritePin(D6,(DIO_PinVoltage_type)READ_BIT(ins,2));
	DIO_WritePin(D5,(DIO_PinVoltage_type)READ_BIT(ins,1));
	DIO_WritePin(D4,(DIO_PinVoltage_type)READ_BIT(ins,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
}
static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D7,(DIO_PinVoltage_type)READ_BIT(data,7));
	DIO_WritePin(D6,(DIO_PinVoltage_type)READ_BIT(data,6));
	DIO_WritePin(D5,(DIO_PinVoltage_type)READ_BIT(data,5));
	DIO_WritePin(D4,(DIO_PinVoltage_type)READ_BIT(data,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	DIO_WritePin(D7,(DIO_PinVoltage_type)READ_BIT(data,3));
	DIO_WritePin(D6,(DIO_PinVoltage_type)READ_BIT(data,2));
	DIO_WritePin(D5,(DIO_PinVoltage_type)READ_BIT(data,1));
	DIO_WritePin(D4,(DIO_PinVoltage_type)READ_BIT(data,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteInstuction(0x02);
	WriteInstuction(0x28); //8bit mode  2lines
	_delay_ms(1);
	WriteInstuction(0x0c);
	_delay_ms(1);
	WriteInstuction(0x01);//clear
	_delay_ms(2);
	WriteInstuction(0x06);//increase ddram adderss   shift off
}
#endif


/**************************LCD Services***************************/
void LCD_Create_Character(u8 *Pattern,u8 Location) {

	u8 iLoop=0;

	WriteInstuction(0x40+(Location*8)); //Send the Address of CGRAM
	for(iLoop=0;iLoop<8;iLoop++)
	WriteData(Pattern[iLoop]); //Pass the bytes of pattern on LCD
	WriteInstuction(0x80);   // set DDRAM ADDRESS
}

void LCD_Clear(void)
{
	WriteInstuction(0x01);//clear
	_delay_ms(2);
}

void lCD_GoToWriteSring(u8 line,u8 cell,c8*str)
{
	if(line==0)
	{
		WriteInstuction(0x80+cell);
	}
	else
	{
		WriteInstuction(0x80+0x40+cell);
	}
	
	u8 i;
	for(i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
}

void LCD_WriteChar(u8 ch)
{
	WriteData(ch);
}


void LCD_ClearLocation(u8 line,u8 cell)
{
	LCD_SetCurser(line,cell);
	LCD_WriteChar(' ');
}


void LCD_ClearLocations(u8 line,u8 cell,u8 count)
{
	LCD_SetCurser(line,cell);
	for(u8 i=0;i<count;i++)
	LCD_WriteChar(' ');
}

void LCD_WriteNumber(s64 num)
{
	u8 i=0;
	s8 j;
	u8 str[16];
	if(num==0)
	{
		LCD_WriteChar('0');
		return;
	}
	if(num<0)
	{
		LCD_WriteChar('-');
		num = num*(-1);
	}
	while(num>0)
	{
		str[i]=num%10+'0';
		num=num/10;
		i++;
	}
	for(j=i-1;j>=0;j--)
	{
		LCD_WriteChar(str[j]);
	}
}


void LCD_WriteString(c8*str)
{
	u8 i;
	for(i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
}


void LCD_WriteBinary(u8 num)
{
	s8 i;
	u8 flag=0;
	for(i=7;i>=0;i--)
	{
		if(READ_BIT(num,i)==1)
		{
			flag=1;
		}
		if(flag==1)
		{
			if(READ_BIT(num,i)==1)
			{
				LCD_WriteChar('1');
			}
			else
			{
				LCD_WriteChar('0');
			}
		}
		
	}
}


void LCD_WriteBinary_8D(u8 num)
{
	s8 i;
	for(i=7;i>=0;i--)
	{
		LCD_WriteChar(READ_BIT(num,i)+'0');
	}
}


void LCD_WriteHex(u8 num)
{
	u8 Ln=num&0x0f;
	u8 Hn=num>>4;
	if(Hn<=9)
	{
		LCD_WriteChar(Hn+'0');
	}
	else
	{
		LCD_WriteChar(Hn-10+'A');
	}
	if(Ln<=9)
	{
		LCD_WriteChar(Ln+'0');
	}
	else
	{
		LCD_WriteChar(Ln-10+'A');
	}
}

void LCD_WriteNumber_4D(u16 num)//8542
{
	LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar(((num%10)/1)+'0');
}


void LCD_SetCurser(u8 line,u8 cell)
{
	if(line==0)
	{
		WriteInstuction(0x80+cell);
	}
	else
	{
		WriteInstuction(0x80+0x40+cell);
	}
}