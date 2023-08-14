#define F_CPU  8000000
#include <util/delay.h>

#include "MemMap.h"
#include "Utiles.h"
#include "StdTypes.h"
#include "DIO_Interface.h"
#include "KeyPad.h"
#include "LCD.h"

int main(void)
{

	DIO_InIt();
	LCD_Init();

	u8 k,flag=0,convFlag=0,Invalid_flag=0,operation=0,From_D=0,From_H=0,From_B=0,To_D=0,To_H=0,To_B=0;
	s32 num=0;
	LCD_WriteString(" Hello Ahmed");
	LCD_SetCurser(1,3);
	LCD_WriteString("CONVERTER.");
	_delay_ms(1000);
	LCD_Clear();
	while(1)
	{


		if(convFlag==0)
		{
			lCD_GoToWriteSring(0,0,"Convert From:    ");
			lCD_GoToWriteSring(1,0,"1.D  2.H  3.B       ");
			Invalid_flag=0;
		}
		else if(convFlag==1)
		{
			lCD_GoToWriteSring(0,0,"Convert To:     ");
			lCD_GoToWriteSring(1,0,"1.D  2.H  3.B       ");
			Invalid_flag=0;
		}
		k=KEYPAD_GetKey();
		if(k!=NO_KEY)
		{
			if(convFlag==0)
			{
				if(k=='1')
				{
					From_D++;
				}
				else if(k=='2')
				{
					From_H++;
				}
				else if(k=='3')
				{
					From_B++;
				}
				else
				{
					LCD_Clear();
					lCD_GoToWriteSring(0,0,"Invalid Oper.!");
					Invalid_flag=1;
					_delay_ms(1000);
				}
				if(Invalid_flag==0)
				{
					convFlag++;
				}
				
			}
			
			else if(convFlag==1)
			{
				if(k=='1')
				{
					To_D++;
					//lCD_GoToWriteNumber(0,0,To_D);
				}
				else if(k=='2')
				{
					To_H++;
				}
				else if(k=='3')
				{
					To_B++;
				}
				else
				{
					LCD_Clear();
					lCD_GoToWriteSring(0,0,"Invalid Oper.!");
					Invalid_flag=1;
					_delay_ms(1000);
				}
				if(Invalid_flag==0)
				{
					convFlag++;
				}
				
				_delay_ms(100);
				
				if(From_D==1)
				{
					lCD_GoToWriteSring(0,0,"D:             ");
					if(To_H==1)
					{
						lCD_GoToWriteSring(1,0,"H:             ");
					}
					else if(To_B)
					{
						lCD_GoToWriteSring(1,0,"B:             ");
					}
					else if(To_D==1)
					{
						lCD_GoToWriteSring(1,0,"D:             ");
					}
				}
				else if(From_H==1)
				{
					lCD_GoToWriteSring(0,0,"H:             ");
					if(To_D==1)
					{
						lCD_GoToWriteSring(1,0,"D:             ");
					}
					else if(To_B)
					{
						lCD_GoToWriteSring(1,0,"B:             ");
					}
					else if(To_H)
					{
						lCD_GoToWriteSring(1,0,"H:             ");
					}
				}
				else if(From_B==1)
				{
					lCD_GoToWriteSring(0,0,"B:             ");
					if(To_H==1)
					{
						lCD_GoToWriteSring(1,0,"H:             ");
					}
					else if(To_D)
					{
						lCD_GoToWriteSring(1,0,"D:             ");
					}
					else if(To_B)
					{
						lCD_GoToWriteSring(1,0,"B:             ");
					}
				}
				
			}
			else if(convFlag==2)
			{
				
				if((k>='0'&& k<='9')||(k=='A' || k=='B')||(k>='D' && k<='F'))
				{
					if(flag==0)
					{
						LCD_SetCurser(0,3);
						LCD_WriteString("           ");
						LCD_SetCurser(0,3);
						flag=1;
					}
					LCD_WriteChar(k);
					if(From_D==1)
					{
						num=KEYPAD_ScanDecimel(k,num);
					}
					else if (From_B==1)
					{
						num=KEYPAD_ScanBinary(k,num);
						
					}
					else if(From_H==1)
					{
						num=KEYPAD_ScanHex(k,num);
					}
				}
				
				if(k=='=')
				{
					
					LCD_SetCurser(1,3);
					if(To_D==1)
					{
						LCD_WriteNumber(num);
					}
					else if(To_B==1)
					{
						LCD_WriteBinary_8D(num);
					}
					else if(To_H==1)
					{
						LCD_WriteHex(num);
					}
					LCD_WriteString("            ");
					num=0;
					flag=0;
					
					From_H=0; From_D=0; From_B=0;
					To_H=0; To_D=0; To_B=0;
					
				}
				if(k=='C')
				{
					
					LCD_Clear();
					convFlag=0;
				}
				
			}
			
		}
		
		
	}


}