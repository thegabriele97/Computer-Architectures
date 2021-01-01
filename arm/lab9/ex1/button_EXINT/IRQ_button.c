#include "button.h"
#include "lpc17xx.h"

#include "../led/led.h"

void EINT0_IRQHandler(void) {
	LEDs_set_byte(0x00);
	LPC_SC->EXTINT = (1 << 0);
}


void EINT1_IRQHandler(void) {
	LEDs_set_byte(LEDS_get_byte() + 1);
	LPC_SC->EXTINT = (1 << 1);
}

void EINT2_IRQHandler(void) {
	LEDs_set_byte(LEDS_get_byte() - 1);
	LPC_SC->EXTINT = (1 << 2);
}
