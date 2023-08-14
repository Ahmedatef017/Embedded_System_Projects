
/**********************************DIO REGISTERS****************************/
#define  PORTA  (*(volatile unsigned char *)0X3B)
#define  DDRA   (*(volatile unsigned char *)0X3A)
#define  PINA   (*(volatile unsigned char *)0X39)

#define  PORTB  (*(volatile unsigned char *)0X38)
#define  DDRB   (*(volatile unsigned char *)0X37)
#define  PINB   (*(volatile unsigned char *)0X36)

#define  PORTC  (*(volatile unsigned char *)0X35)
#define  DDRC   (*(volatile unsigned char *)0X34)
#define  PINC   (*(volatile unsigned char *)0X33)

#define  PORTD  (*(volatile unsigned char *)0X32)
#define  DDRD   (*(volatile unsigned char *)0X31)
#define  PIND   (*(volatile unsigned char *)0X30)

#define SET_BIT(reg,bit)        (reg|=(1<<bit))
#define CLR_BIT(reg,bit)        (reg&=~(1<<bit))
#define TOG_BIT(reg,bit)        (reg^=~(1<<bit))
#define WRITE_BIT(reg,bit,val)  (reg&=(val<<bit))
#define READ_BIT(reg,bit)       ((reg>>bit)&1)

typedef unsigned char  u8;
typedef signed char    s8;

#define  SEG_PORT    PORTA
/***************************************************************************/
#define F_CPU 8000000
#include <util/delay.h>
/***************************************************************************/
void segment_display_BCD(unsigned char n)
{
	int x = n/10;
	int y = n%10;
	PORTA = y|x<<4;
}

int main(void)
{
	DDRA = 0Xff;
	DDRC = 0;       //BUTTON 2  INC
	PORTC  = 0XFF;
	DDRD = 0;       // BUTTON 1  DEC  && BUTTON 3 MODE
	PORTD  = 0XFF;
	DDRB = 0xFF;   // LED
	/*********stop watch***********/
	
	u8 ModeFlag = 0;
	u8 i = 30;
	u8 resumeFlag = 1;
	u8 last_value2 = i;
	u8 last_value1;
	u8 f=0;
	segment_display_BCD(i);
	while (1)
	{
		if(READ_BIT(PIND,0)==0)   //BUT MODE
		{
			ModeFlag = !ModeFlag;
			while(READ_BIT(PIND,0)==0);
		}
		
		if(ModeFlag==0)
		{
			// BUT resume
			if(READ_BIT(PIND,4)==0)
			{
				resumeFlag=!resumeFlag;
				f=0;
				while(READ_BIT(PIND,4)==0);
			}

			if(resumeFlag ==0 &&  f==0)
			{
				i--;
				segment_display_BCD(i);
				_delay_ms(100);
				
				if(i==0 )
				{
					// LED on
					PORTB = 0b00000010;
					_delay_ms(1000);
					PORTB = 0;
					last_value1 = last_value2;
					f=1;
				}
				
			}
			//pause
			else
			{
				segment_display_BCD(i);
			}
			
			// BUT reset
			if(READ_BIT(PINC,4)==0)
			{
				i=last_value2;
				segment_display_BCD(i);
				resumeFlag=1;
				while(READ_BIT(PINC,4)==0);
			}
			
		}
		else
		{
			// BUT inc
			if(READ_BIT(PINC,4)==0)
			{
				i++;
				if(i==100)
				{
					i=0;
				}
				_delay_ms(300);
				segment_display_BCD(i);
				while(READ_BIT(PINC,4)==0)
				{
					i++;
					
					if(i==100)
					{
						i=0;
					}
					_delay_ms(50);
					segment_display_BCD(i);
					
				}

				
				
			}
			// BUT dec
			if(READ_BIT(PIND,4)==0)
			{
				i--;
				
				if(i==255)
				{
					i=99;
				}
				_delay_ms(300);
				segment_display_BCD(i);
				while(READ_BIT(PIND,4)==0)
				{
					i--;
					
					if(i==255)
					{
						i=99;
					}
					_delay_ms(50);
					segment_display_BCD(i);
				}

				
			}
			last_value2 = i;
			
		}
		
	}
}
