#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "stdint.h"
#include "../timer/timer.h"
#include "stdbool.h"
#include "../blind_labyrinth.h"

#define IS_RUNBTN_PRESSED()				(((LPC_GPIO2->FIOPIN >> 0xc) & 0x1) == 0 && ((LPC_PINCON->PINSEL4 & (1 << 24)) == 0))		
#define IS_ROTBTN_PRESSED()				(((LPC_GPIO2->FIOPIN >> 0xb) & 0x1) == 0 && ((LPC_PINCON->PINSEL4 & (1 << 22)) == 0))	

extern game_t game_bl;

void RIT_IRQHandler (void) {
	static bool is_run_pressed = false;
	static bool is_rot_pressed = false;
	extern bool is_first_excluded;
	static uint8_t count = 0x0;
	
	if (is_exit_reached(game_bl)) {
		disable_timer(0);
		disable_timer(1);
			
		if (count < 0xa) {
			LED_Off(LED_RUN);
			LED_Off(NORTH);
			LED_Off(SOUTH);
			LED_Off(EAST);
			LED_Off(WEST);
		} else if (count < 0x14) {
			LED_On(LED_RUN);
			LED_On(NORTH);
			LED_On(SOUTH);
			LED_On(EAST);
			LED_On(WEST);
		}

		count = (count + 1) % 0x14;
	} else {
		if (!is_run_pressed && IS_RUNBTN_PRESSED()) { // Intercepts button press
			
			is_first_excluded = true;
			if (!(LPC_TIM0->TCR & 0x1)) { // Timer enabled once. The check is done in order to remove bouncing effects
				enable_timer(0);
			}
			
			is_run_pressed = true;
		} else if (is_run_pressed && !IS_RUNBTN_PRESSED()) { // Intercepts button release
			disable_timer(0);
			LED_Off(LED_RUN);
			
			is_run_pressed = false;
			LPC_PINCON->PINSEL4 |= (1 << 24); // Re enabling interrupt
			disable_RIT();
		}
		
		if (!is_run_pressed) { // Rot is intercepted only when run is not pressed
			
			if (is_rot_pressed && !IS_ROTBTN_PRESSED()) { // Intercepts button release
				LED_Off(game_bl.robot.dir_obstacle.direction); // Turning off the current led
				set_dir(&game_bl, game_bl.robot.dir_obstacle.direction - 1);
			}
			
			is_rot_pressed = IS_ROTBTN_PRESSED();
			if (!is_rot_pressed) {
				LPC_PINCON->PINSEL4 |= (1 << 22); // Re enabling interrupt
				disable_RIT();
			}
		}
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
  return;
}
