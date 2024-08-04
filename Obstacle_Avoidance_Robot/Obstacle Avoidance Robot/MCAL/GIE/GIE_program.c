
/*----------------------------------------------------------------------------*/
/*-- @breief: GIE_program.c          -----------------------------------------*/
/*-- @Author: Ahmed Atef Abdelrahman -----------------------------------------*/
/*-- @date:    Sep 16, 2023          -----------------------------------------*/
/*----------------------------------------------------------------------------*/
#include "../../LIB/BitMath.h"
#include "../../LIB/StdTypes.h"
#include "GIE_private.h"
#include "GIE_interface.h"

void M_Global_Interrupt_Enable(void)
{
	SET_BIT(SREG,GIE);
}
void M_Global_Interrupt_Disable(void)
{
	CLEAR_BIT(SREG,GIE);
}
