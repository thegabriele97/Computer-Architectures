
#include "button.h"
#include "lpc17xx.h"

/**
 * @brief  Function that initializes Buttons
 */
void BUTTON_init(void) {

  LPC_PINCON->PINSEL4    |= (1 << 20);		 /* External interrupt 0 pin selection */
	LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
  LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */

	/* Enabling pins as input useful when they are switched to GPIO functionality */
	LPC_GPIO2->FIODIR &= ~(1 << 0xc);
	LPC_GPIO2->FIODIR &= ~(1 << 0xb);
	
  LPC_SC->EXTMODE = 0x7;

  NVIC_EnableIRQ(EINT2_IRQn);              /* enable irq in nvic                 */
	//NVIC_SetPriority(EINT2_IRQn, 1);				 /* priority, the lower the better     */
  
	NVIC_EnableIRQ(EINT1_IRQn);              /* enable irq in nvic                 */
	//NVIC_SetPriority(EINT1_IRQn, 2);				 
  
	NVIC_EnableIRQ(EINT0_IRQn);              /* enable irq in nvic                 */
	//NVIC_SetPriority(EINT0_IRQn, 3);				 /* decreasing priority	from EINT2->0	 */
}
