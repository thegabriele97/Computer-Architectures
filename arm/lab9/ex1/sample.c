/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: to control led through EINT buttons 
 *        	- key1 switches on LED10 
 *				  - key2 switches off all LEDs 
 *			    - int0 switches on LED 11
 * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Paolo BERNARDI - PoliTO - last modified 07/12/2020
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include "LPC17xx.H"
#include "led/led.h"
#include "button_EXINT/button.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; 
#endif

int main (void) {
	
  SystemInit();
  LED_init();
  BUTTON_init();
	
	SCB->SCR |= (1 << SCB_SCR_SLEEPDEEP_Pos);
	LPC_SC->PCON |= (1 << 0);
	LPC_SC->PCON &= ~(1 << 1);
	
  while (1) {
		__WFI();
	}

}
