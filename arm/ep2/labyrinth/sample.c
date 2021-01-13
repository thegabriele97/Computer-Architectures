/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "joystick/joystick.h"
#include "RIT/RIT.h"
#include "stdint.h"
#include "blind_labyrinth.h"
#include "lab_map.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; 
#endif

int main(void) {
	SystemInit();
	
  LCD_Initialization();
	TP_Init();

	joystick_init();
	init_RIT(0x001E8480);				// 20 ms: RIT used to poll the joystick
	init_timer(0, 0x004C4B40);	// 200 ms: RIT is used to move the robot
	
	TouchPanel_Calibrate();
	LCD_Clear(Blue2);
	GUI_Text(60, 20, (uint8_t *)"Blind Labyrinth", Yellow, Blue2);
	
	LCD_DrawRect(LCD_START_START_X, LCD_START_START_Y, LCD_START_LENGTH, LCD_START_WIDTH, White);
	GUI_Text(20, 280, (uint8_t *)"Restart", Blue2, White);
	
	LCD_DrawRect(LCD_CLR_START_X, LCD_CLR_START_Y, LCD_CLR_LENGTH, LCD_CLR_WIDTH, Yellow);
	GUI_Text(170, 280, (uint8_t *)"Clear", Black, Yellow);
	
	LCD_DrawRect(LCD_MAP_START_X, LCD_MAP_START_Y, 13*15 + 1, 15*15 + 1, White);
	GUI_Text(60, 110, (uint8_t *)"Touch to Start", Blue2, White);
	GUI_Text(76, 125, (uint8_t *)"a New Game", Blue2, White);
	
	enable_RIT();
	
	LPC_SC->PCON |= 0x1;
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	{
		__ASM("wfi");
  }
}
