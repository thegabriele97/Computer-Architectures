
#include "button.h"
#include "lpc17xx.h"

/**
 * @brief  Function that initializes Buttons
 */
void BUTTON_init(void) {

  LPC_PINCON->PINSEL4 |= (1 << 20);	
  LPC_PINCON->PINSEL4	&= ~(1 << 21); 
	
	LPC_PINCON->PINSEL4 |= (1 << 22);
	LPC_PINCON->PINSEL4	&= ~(1 << 23);
	
  LPC_PINCON->PINSEL4 |= (1 << 24);
	LPC_PINCON->PINSEL4	&= ~(1 << 25);

  LPC_SC->EXTMODE = 0x7;				// Interrupt triggers on edges
	LPC_SC->EXTPOLAR &= 0x8;	 	// Interrupt triggers on rising edges for the first 3 bits

  NVIC_EnableIRQ(EINT2_IRQn);              /* enable irq in nvic                 */
  NVIC_EnableIRQ(EINT1_IRQn);              /* enable irq in nvic                 */
  NVIC_EnableIRQ(EINT0_IRQn);              /* enable irq in nvic                 */
}
