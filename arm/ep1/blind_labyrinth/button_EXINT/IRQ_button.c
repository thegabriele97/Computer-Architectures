#include "button.h"
#include "lpc17xx.h"
#include "stdint.h"
#include "../RIT/RIT.h"
#include "../timer/timer.h"
#include "../blind_labyrinth.h"
#include "../led/led.h"

volatile game_t game_bl;

/* INT0	*/
void EINT0_IRQHandler(void) {		
	
	LED_Off(LED_RUN);
	LED_Off(NORTH);
	LED_Off(SOUTH);
	LED_Off(EAST);
	LED_Off(WEST);
	
	game_bl = new_game(new_robot());
	
	enable_RIT();
	enable_timer(1);
	NVIC_DisableIRQ(EINT0_IRQn);	// Deactivated until reset
	
	LPC_SC->EXTINT &= (1 << 0);
}


/* KEY1	*/
void EINT1_IRQHandler(void) {
	LPC_SC->EXTINT &= (1 << 1);
}

/* KEY2	*/
void EINT2_IRQHandler(void) {	
  LPC_SC->EXTINT &= (1 << 2); 
}
