/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: to control led through EINT buttons and manage the bouncing effect
 *        	- key1 switches on the led at the left of the current led on, 
 *					- it implements a circular led effect. 	
  * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Paolo BERNARDI - PoliTO - last modified 15/12/2020
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include <stdio.h>
#include "LPC17xx.H"
#include "led/led.h"
#include "button_EXINT/button.h"
#include "timer/timer.h"
#include "RIT/RIT.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag;
#endif

int main (void) {
	
	SystemInit();
  LED_init();
  BUTTON_init();
	
	init_RIT(0x004c4b40);			
	init_timer(0, 0x002625A0); // Timer 0 ->  100 ms Interrupt (10 Hz), to handle running led
	init_timer(1, 0x0017D784); // Timer 1 -> 62.5 ms Interrupt (16 Hz), to handle direction leds
	
	LPC_TIM0->MCR &= ~(1 << 2); // Timer 0 -> disabling Stop on match. Reset on match is still enabled
	LPC_TIM1->MCR &= ~(1 << 5); // Timer 1 -> disabling Stop on match. Reset on match is still enabled
	
	LPC_SC->PCON |= 0x1;
	LPC_SC->PCON &= ~(0x2);						
		
  while (1) {
		__ASM("wfi");
  }

}
