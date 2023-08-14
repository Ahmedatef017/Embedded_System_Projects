
#include "DIO_Interface.h"


const DIO_PinMode_type PinsModeArray[TOTAL_PINS]={
	INFREE,      /* Port A Pin 0 lm35 */
	OUTPUT,      /* Port A Pin 1 pot LDR */
	OUTPUT,      /* Port A Pin 2 rain */
	OUTPUT,      /* Port A Pin 3 flame */
	OUTPUT,      /* Port A Pin 4 gas */
	OUTPUT,      /* Port A Pin 5 fan */
	OUTPUT,      /* Port A Pin 6 buzzer*/
	INFREE,      /* Port A Pin 7 yellow led */
	OUTPUT,		 /* Port B Pin 0 */
	OUTPUT,		 /* Port B Pin 1 */
	OUTPUT,      /* Port B Pin 2 /INT0*/
	OUTPUT,      /* Port B Pin 3 /INT0*/
	OUTPUT,		 /* Port B Pin 4 */
	OUTPUT,		 /* Port B Pin 5 */
	OUTPUT,		 /* Port B Pin 6 */
	OUTPUT,		 /* Port B Pin 7 */
	OUTPUT,		 /* Port C Pin 0 keypad in*/
	OUTPUT,		 /* Port C Pin 1 */
	OUTPUT,		 /* Port C Pin 2 */
	OUTPUT,		 /* Port C Pin 3 */
	INPULL,		 /* Port C Pin 4 keypad out*/
	INPULL,		 /* Port C Pin 5 */
	INPULL,		 /* Port C Pin 6 */
	INPULL,		 /* Port C Pin 7 */
	OUTPUT,		 /* Port D Pin 0 */
	OUTPUT,		 /* Port D Pin 1 */
	INPULL,      /* Port D Pin 2  /INT0*/
	INPULL,      /* Port D Pin 3  / INT1 */
	INPULL,		 /* Port D Pin 4  OC1B servo */
	INPULL,		 /* Port D Pin 5  OC1A */
	INPULL,		 /* Port D Pin 6  ultrasonic   ICP*/
	INPULL		 /* Port D Pin 7 */
};
