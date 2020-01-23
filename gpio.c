#include "gpio.h"
#include "registers.h"

void gpioPortDirection(uint8_t u8_port, uint8_t u8_direction)
{
	switch(u8_port)
	{
		case GPIOA:
		            PORTA_DIR = u8_direction;
					break;
		case GPIOB:
		            PORTB_DIR = u8_direction;
					break;
		case GPIOC:
		            PORTC_DIR = u8_direction;
					break;
		case GPIOD:
		            PORTD_DIR = u8_direction;
					break;
		default:
		            break;
	}
}

void gpioPortWrite(uint8_t u8_port, uint8_t u8_value)
{
    switch(u8_port)
   {
        case GPIOA:
                    PORTA_DATA = u8_value;
                    break;
        case GPIOB:
                    PORTB_DATA = u8_value;
                    break;
        case GPIOC:
                    PORTC_DATA = u8_value;
                    break;
        case GPIOD:
                    PORTD_DATA = u8_value;
                    break;
        default:
                    break;
   }
}

void gpioPortToggle(uint8_t u8_port)
{
   switch(u8_port)
   {
        case GPIOA:
                    PORTA_DATA = ~PORTA_DATA;
                    break;
        case GPIOB:
                    PORTB_DATA = ~PORTB_DATA;
                    break;
        case GPIOC:
                    PORTC_DATA = ~PORTC_DATA;
                    break;
        case GPIOD:
                    PORTD_DATA = ~PORTD_DATA;
                    break;
        default:
                    break;
   }
}

uint8_t gpioPortRead(uint8_t u8_port)
{
   uint8_t Port_State;
   switch(u8_port)
   {
        case GPIOA:
                     Port_State = PORTA_PIN;
                     break;
        case GPIOB:
                     Port_State = PORTB_PIN;
                     break;
        case GPIOC:
                     Port_State = PORTC_PIN;
                     break;
        case GPIOD:
                     Port_State = PORTD_PIN;
                     break;
        default:
                     break;
   }
   return Port_State;
}

void gpioPinDirection(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_direction)
{
   if(u8_direction == OUTPUT)
   {
	 switch(u8_port)
	 {
		case GPIOA:
	            	PORTA_DIR |= (u8_pins);
		            break;
		case GPIOB:
		            PORTB_DIR |= (u8_pins);
		            break;
		case GPIOC:
		            PORTC_DIR |= (u8_pins);
		            break;
		case GPIOD:
		            PORTD_DIR |= (u8_pins);
		            break;
		default:
		            break;
	 }    
   }
   else if(u8_direction == INPUT)
   {
	 switch(u8_port)
     {
		   case GPIOA:
		                PORTA_DIR &= (~u8_pins);
		                break;
		   case GPIOB:
		                PORTB_DIR &= (~u8_pins);
		                break;
		   case GPIOC:
		                PORTC_DIR &= (~u8_pins);
		                break;
		   case GPIOD:
		                PORTD_DIR &= (~u8_pins);
		                break;
		   default:
		                break;
	 }
   }
}

void gpioPinWrite(uint8_t u8_port, uint8_t u8_pins, uint8_t u8_value)
{
	if(u8_value == HIGH)
	{
		switch(u8_port)
		{
			case GPIOA:
			            PORTA_DATA |= (u8_pins);
			            break;
			case GPIOB:
			            PORTB_DATA |= (u8_pins);
			            break;
			case GPIOC:
			            PORTC_DATA |= (u8_pins);
			            break;
			case GPIOD:
		             	PORTA_DATA |= (u8_pins);
			            break;
			default:
			            break;
		}
	}
	else if(u8_value == LOW)
	{
		switch(u8_port)
		{
			case GPIOA:
			            PORTA_DATA &= (~u8_pins);
			            break;
			case GPIOB:
			            PORTB_DATA &= (~u8_pins);
			            break;
			case GPIOC:
			            PORTC_DATA &= (~u8_pins);
	            		break;
			case GPIOD:
			            PORTA_DATA &= (~u8_pins);
			            break;
			default:
			            break;
		}
	}   
}

void gpioPinToggle(uint8_t u8_port, uint8_t u8_pins)
{
   switch(u8_port)
   {
        case GPIOA:
                     PORTA_DATA ^= (u8_pins);
					 break;
	    case GPIOB:
		             PORTB_DATA ^= (u8_pins);
		             break;		
	    case GPIOC:
		             PORTC_DATA ^= (u8_pins);
		             break;	 
        case GPIOD:
			         PORTD_DATA ^= (u8_pins);
		             break;
   }
}

uint8_t gpioPinRead(uint8_t u8_port, uint8_t u8_pin)
{
   uint8_t Ret_State;
   switch(u8_port)
  {
        case GPIOA:
                    Ret_State = PORTA_PIN & u8_pin;
                    break;
        case GPIOB:
                    Ret_State = PORTB_PIN & u8_pin;
                    break;
        case GPIOC:
                    Ret_State = PORTC_PIN & u8_pin;
                    break;
        case GPIOD:
                    Ret_State = PORTD_PIN & u8_pin;
                    break;
        default:
                    break;
  }
  return Ret_State;
}

