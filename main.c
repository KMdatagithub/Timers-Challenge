/*
 * ATmega32_Test.c
 *
 * Created: 1/17/2020 1:26:47 PM
 * Author : Khaled Magdy
 */ 
#include "registers.h"
#include "softwareDelay.h"
#include "gpio.h"
#include "led.h"
#include "pushButton.h"
#include "timers.h"

//-----------------------------------------------------------------------------
//  Please Note That All Applications Are Listed Down Below But Commented-Out
//-----------------------------------------------------------------------------
// Requirements (1 -> 6)

int main(void)
{
	Led_Init(LED_0);
	while(1) 
    {
		Led_On(LED_0);
		timer1DelayMs(70);
		Led_Off(LED_0);
		timer1DelayMs(70);
    } 
}

//------------------------------------------------------------
// Application 1 (7-Segments Counter) 0:99
// Requirement (7)
/*
int main(void)
{
	sevenSegInit(SEG_0);
	sevenSegInit(SEG_1);
	uint8_t counter = 0, c=0, digit0, digit1;
	while(1)
	{
		digit1 = counter/10;
		digit0 = counter%10;
		
		sevenSegWrite(SEG_0, digit0);
		sevenSegEnable(SEG_0);
		sevenSegDisable(SEG_1);
		softwareDelayMs(10);
		
		sevenSegWrite(SEG_1, digit1);
		sevenSegEnable(SEG_1);
		sevenSegDisable(SEG_0);
		softwareDelayMs(10);
		
		c++;
		if(c==50)   // Each 1 Second
		{
		  c=0;
		  counter++;
		  if(counter==100)
		    counter = 0;
		}
    }
}
*/
//------------------------------------------------------
// Application 2 (Button & LED)
// Requirement (8)
/*
int main(void)
{
	pushButtonInit(BTN_1);
	Led_Init(LED_1);
	while(1)
	{
		if(pushButtonGetStatus(BTN_1) == Pressed)
		{
			Led_On(LED_1);
			softwareDelayMs(300);
			if(pushButtonGetStatus(BTN_1) == Pressed)
			  softwareDelayMs(1700);
			else
			  softwareDelayMs(700);
			Led_Off(LED_1);
		}
	}
}
*/
//------------------------------------------------------
// Application 3 (State Machine)
// Requirement (9)
/*
typedef enum En_state_t{
	GO,
	STOP,
	RDY,
}En_state_t;
int main(void)
{
	uint8_t current_state = 0;
	Led_Init(LED_1);
	Led_Init(LED_2);
	Led_Init(LED_3);
	while(1)
	{
		switch (current_state)
		{
			case GO:
			         Led_On(LED_1); Led_Off(LED_2); Led_Off(LED_3);
					 current_state = STOP;
					 break;
		    case STOP:
		    		 Led_On(LED_2); Led_Off(LED_1); Led_Off(LED_3);
		    		 current_state = RDY;
		    		 break;
			case RDY:
			         Led_On(LED_3); Led_Off(LED_1); Led_Off(LED_2);
			         current_state = GO;
					 break;
		    default:
			         break;
		}
		softwareDelayMs(1000);	
	}
}
*/