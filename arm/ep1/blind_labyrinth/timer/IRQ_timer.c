/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"
#include "../led/led.h"
#include "stdint.h"
#include "../blind_labyrinth.h"

extern game_t game_bl;

void TIMER0_IRQHandler (void) {
	static uint8_t count = 0x0;
	
	if (game_bl.robot.dir_obstacle.is_dist0_obstacle) {
		if (count) {
			LED_On(LED_RUN);
		} else {
			LED_Off(LED_RUN);
		}
		
		count = (count + 1) & 0x1;
	} else {
		if (count < 0x5) {
			LED_Off(LED_RUN);
		} else if (count < 0xa) {
			LED_On(LED_RUN);
		}
		
		if (count == 0x5) {
			go_on(&game_bl);
		}
		
		count = (count + 1) % 0xa;
	}
	
	LPC_TIM0->IR = 1;			/* clear interrupt flag */
	return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void) {
	static uint8_t count = 0x0;
	uint8_t max_cnt;
	
	if (game_bl.robot.dir_obstacle.is_dist0_obstacle) {
		max_cnt = (1 << 1);
	} else if (game_bl.robot.dir_obstacle.is_dist2_obstacle) {
		max_cnt = (1 << 2);
	} else if (game_bl.robot.dir_obstacle.is_dist5_obstacle) {
		max_cnt = (1 << 3);
	} else {
		max_cnt = (1 << 0);
	}
	
	if (count < (max_cnt >> 1)) {	// Duty cycle is 50% so..
		LED_Off(game_bl.robot.dir_obstacle.direction); // N.B. the direction is the same as the led number. WOW!
	} else if (count < (max_cnt >> 0)) {
		LED_On(game_bl.robot.dir_obstacle.direction);
	}
		
	count = (count + 1) % max_cnt;
	
	LPC_TIM1->IR = 1;			/* clear interrupt flag */
	return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
