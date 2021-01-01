																			 /*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           timer.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        Prototypes of functions included in the lib_led, funct_led .c files
** Correlated files:    lib_led.c, funct_led.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#ifndef LED_H_
#define LED_H_

#include <stdint.h>

/* lib_led */
void LED_init(void);
void LED_deinit(void);

/* funct_led */
void LED_On(unsigned int num);
void LED_Off(unsigned int num);
void LEDs_set_byte(uint8_t val);
uint8_t LEDS_get_byte(void);

#endif
