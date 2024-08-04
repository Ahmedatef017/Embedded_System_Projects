
#include "../../LIB/StdTypes.h"
#include "../../MCAL/UART/UART_interface.h"

#include "UartServices.h"


/*******************************************************************/
void S_UART_SendStringSynch(u8*str)
{
	u8 i;
	for(i=0;str[i];i++)
	{
		M_UART_voidSend(str[i]);
	}
	M_UART_voidSend('#');
}

void S_UART_ReceiveStringSynch(u8*str)
{
	u8 i=0;
	str[i]=M_UART_u8Receive();
	for(;str[i]!='#';)
	{
		i++;
		str[i]=M_UART_u8Receive();
	}
	str[i]=0;
}
/********************************************************************/
u8*RX_str;

static void RX_FUNC (void);
void S_UART_void_ReceiveStringAsynch(u8*str)
{
	M_UART_void_RX_SetCallBack(RX_FUNC);
	M_UART_void_RX_InterruptEnable();
	RX_str=str;

}
static void RX_FUNC (void)
{
    static u8 i=0;
	RX_str[i]=M_UART_u8ReceiveNoBlock();
	if(RX_str[i]!='#')
	{
		i++;
		RX_str[i]=M_UART_u8ReceiveNoBlock();
	}
	else{
		RX_str[i]= 0;
		i=0;
	}

	if(i>20)
	{
		i=0;
	}

}
/***********************************************/
u8*rs_str;
static void rx_func (void);

void S_UART_void_ReceiveCharAsynch(u8*data_var)
{
	M_UART_void_RX_SetCallBack(rx_func);
	M_UART_void_RX_InterruptEnable();
	rs_str=data_var;
}
static void rx_func (void)
{
	*rs_str = M_UART_u8ReceiveNoBlock();
}

/***********************************************************************/
 u8*TX_STR;
 void TX_FUNC(void);

 void S_UART_SendStringAsynch(u8*str)
 {
	 M_UART_voidSend(str[0]);
	 TX_STR=str;
	 M_UART_void_TX_SetCallBack(TX_FUNC);
	 M_UART_void_TX_InterruptEnable();

 }

 void TX_FUNC(void)
 {
	 static u8 i=1;
	 if(TX_STR[i]!='#')
	 {
		 M_UART_voidSendNoBlock(TX_STR[i]);
		 i++;
	 }
	 else
	 {
		 i=1;
	 }
 }
