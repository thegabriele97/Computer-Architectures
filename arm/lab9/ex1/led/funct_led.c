/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_led.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        High level led management functions
** Correlated files:    lib_led.c, funct_led.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "led.h"

/*----------------------------------------------------------------------------
  Function that turns on requested LED
 *----------------------------------------------------------------------------*/
void LED_On(unsigned int num) {
	LPC_GPIO2->FIOSET0 |= (1 << num);
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void LED_Off(unsigned int num) {
  LPC_GPIO2->FIOCLR0 |= (1 << num);
}

void LEDs_set_byte(uint8_t val) {
	LPC_GPIO2->FIOPIN0 = val;
}

uint8_t LEDS_get_byte() {
	return LPC_GPIO2->FIOPIN0;
}
