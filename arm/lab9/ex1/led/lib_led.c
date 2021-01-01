/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           timer.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        Atomic led init functions
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "led.h"

/*----------------------------------------------------------------------------
  Function that initializes LEDs and switch them off
 *----------------------------------------------------------------------------*/

void LED_init(void) {
  LPC_PINCON->PINSEL4 &= 0xffff0000;		//P2.0 .. P2.7 as GPIO pins
	LPC_GPIO2->FIODIR0 |= 0xff;						//P2.0 .. P2.7 GPIO as output
	
	LPC_GPIO2->FIOPIN0 = 0x00;						//P2.0 .. P2.7 to 0
}

void LED_deinit(void) {

  //LPC_GPIO2->FIODIR &= 0xFFFFFF00;  //P2.0...P2.7 Output LEDs on PORT2 defined as Output
}
