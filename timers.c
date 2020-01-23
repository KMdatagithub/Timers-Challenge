/*
 * timers.c
 *
 * Created: 1/20/2020 5:34:11 PM
 *  Author: Khaled Magdy
 */ 
#include "timers.h"

static En_timer0perscaler_t gen_TMR0PS;
static En_timer1perscaler_t gen_TMR1PS;
static En_timer2perscaler_t gen_TMR2PS;

/*==================[ Timer0 Control Functions ]==================*/
/*
 * Description: It Initializes Timer0 Module
 * @param en_mode:           Set Timer0 Mode OF Operation
 * @param en_OC0:            Set Output Compare Mode (enabled, disabled, etc)
 * @param en_prescal:        Sets The Timer0 Prescaler Value (8, 64, 256, 1024, NO)
 * @param u8_initialValue:   Sets The Timer0 Initial TCNT0 Ticks Count
 * @param u8_outputCompare:  Sets The Output Compare Register Value OCR0
 * @param en_interruptMask:  Sets The Interrupt Mode For TMR0 (polling, overflow, or compare match)
 */
void timer0Init(En_timer0Mode_t en_mode,En_timer0OC_t en_OC0,En_timer0perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, En_timer0Interrupt_t en_interruptMask)
{
	TCCR0 =  0x00;
	TCCR0 = (en_mode | en_OC0);
	TCNT0 = u8_initialValue;
	OCR0  = u8_outputCompare;	
	gen_TMR0PS = en_prescal;
    TIMSK |= en_interruptMask;
	SREG |= (0x80);
}
/*
 * Description: It Sets The Start Value For Timer0 Ticks
 * @param u8_value: Sets The TMR0 Initial Value
 */
void timer0Set(uint8_t u8_value)
{
	TCNT0 = u8_value;
}
/*
 * Description: It Returns The Number OF Ticks In TCNT0
 * @return: The Current Value OF Timer0 Ticks
 */
uint8_t timer0Read(void)
{
	return TCNT0;
}
/*
 * Description: It Sets The TMR0 Prescaler, So It Starts Counting!
 */
void timer0Start(void)
{
	TCCR0 |= gen_TMR0PS;
}
/*
 * Description: It Clears The TMR0 Prescaler, So It Stops Counting!
 */
void timer0Stop(void)
{
	TCCR0 =  T0_NO_CLOCK;
}
/*
 * Description: It Halts The CPU For A Specified Amount OF Time (in msec)
 * @param u16_delay_in_ms: Number OF Milli_seconds For The Delay
 */
void timer0DelayMs(uint16_t u16_delay_in_ms)
{
	timer0Init(T0_COMP_MODE, T0_OC0_DIS, T0_PRESCALER_64, 0, 250, T0_INTERRUPT_CMP);
	timer0Start();
	while(u16_delay_in_ms)
	{
		// Poll For TMR0 Compare Match Flag Bit
		while(!(GET_BIT(TIFR,1)));
		// Set The Flag Bit To Clear It
		SET_BIT(TIFR,1);
		u16_delay_in_ms--;
	}
}
/*
 * Description: It Halts The CPU For A Specified Amount OF Time (in usec)
 * @param u32_delay_in_us: Number OF Micro_seconds For The Delay
 */
void timer0DelayUs(uint32_t u32_delay_in_us)
{
	timer0Init(T0_COMP_MODE, T0_OC0_DIS, T0_PRESCALER_NO, 0, 14, T0_INTERRUPT_CMP);
	timer0Start();
	while(u32_delay_in_us)
	{
		while(!(GET_BIT(TIFR,1)));
		SET_BIT(TIFR,1);
		u32_delay_in_us--;
	}	
}
/*================================================================*/
/*==================[ Timer1 Control Functions ]==================*/
/**
 * Description:           It Initializes Timer1 Module
 * @param en_mode:        Select The Required Mode OF Operation    
 * @param en_OC:          Set The Mode OF Output Compare (set, clear, toggle, disable)
 * @param en_prescal:     Set The Timer1 Prescaler Value
 * @param initialValue:   Set The Timer1 Initial Value (TCNT1)
 * @param outputCompare:  Set The Timer1 Output Compare Value (OCRA, OCRB)
 * @param interruptMask:  Select The Timer1 Interrupt Mode
 */
void timer1Init(En_timer1Mode_t en_mode,En_timer1OC_t en_OC,En_timer1perscaler_t en_prescal, uint16_t u16_initialValue, uint16_t u16_outputCompareA, uint16_t u16_outputCompareB,uint16_t u16_inputCapture, En_timer1Interrupt_t en_interruptMask)
{
	TCCR1 = 0;
	TCCR1 = (en_mode | en_OC);
	gen_TMR1PS = en_prescal;
	TCNT1 = u16_initialValue;
	OCR1A = u16_outputCompareA;
	OCR1B = u16_outputCompareB;
	ICR1 = u16_inputCapture;
    TIMSK |= en_interruptMask;
    SREG  |= (0x80);
}
/*
 * Description: It Sets The Start Value For Timer1 Ticks
 * @param u16_value: Sets The TMR1 Initial Value
 */
void timer1Set(uint16_t u16_value)
{
	TCNT1 = u16_value;
}
/*
 * Description: It Returns The Number OF Ticks In TCNT1
 * @return: The Current Value OF Timer1 Ticks
 */
uint16_t timer1Read(void)
{
	return TCNT1;
}
/*
 * Description: It Sets The TMR1 Prescaler, So It Starts Counting!
 */
void timer1Start(void)
{
	TCCR1 |= gen_TMR1PS;
}
/*
 * Description: It Clears The TMR1 Clock, So It Stops Counting!
 */
void timer1Stop(void)
{
	TCCR1 = T1_NO_CLOCK;
}
/*
 * Description: It Halts The CPU For A Specified Amount OF Time (in msec)
 * @param u16_delay_in_ms: Number OF Milli_seconds For The Delay
 */
void timer1DelayMs(uint16_t u16_delay_in_ms)
{
	timer1Init(T1_COMP_MODE_OCR1A_TOP, T1_OC1_DIS, T1_PRESCALER_64, 0, 250, 0, 0, T1_INTERRUPT_CMP_1A);
	timer1Start();
	while(u16_delay_in_ms)
	{
		while(!(GET_BIT(TIFR,4)));
		SET_BIT(TIFR,4);
		u16_delay_in_ms--;
	}	
}
/*
 * Description: It Halts The CPU For A Specified Amount OF Time (in usec)
 * @param u32_delay_in_us: Number OF Micro_seconds For The Delay
 */
void timer1DelayUs(uint32_t u32_delay_in_us)
{
	timer1Init(T1_COMP_MODE_OCR1A_TOP, T1_OC1_DIS, T1_PRESCALER_NO, 0, 14, 0, 0, T1_INTERRUPT_CMP_1A);
	timer1Start();
	while(u32_delay_in_us)
	{
		while(!(GET_BIT(TIFR,4)));
		SET_BIT(TIFR,4);
		u32_delay_in_us--;
	}	
}
/*================================================================*/
/*==================[ Timer2 Control Functions ]==================*/
/*
 * Description: It Initializes Timer2 Module
 * @param en_mode:           Set Timer2 Mode OF Operation
 * @param en_OC:             Set Output Compare Mode (enabled, disabled, etc)
 * @param en_prescal:        Sets The Timer2 Prescaler Value (8, 64, 256, 1024, NO)
 * @param u8_initialValue:   Sets The Timer2 Initial TCNT2 Ticks Count
 * @param u8_outputCompare:  Sets The Output Compare Register Value OCR2
 * @param u8_assynchronous: 
 * @param en_interruptMask:  Sets The Interrupt Mode For TMR2 (polling, overflow, or compare match)
 */
void timer2Init(En_timer2Mode_t en_mode,En_timer2OC_t en_OC,En_timer2perscaler_t en_prescal, uint8_t u8_initialValue, uint8_t u8_outputCompare, uint8_t u8_assynchronous, En_timer2Interrupt_t en_interruptMask)
{
	TCCR2 =  0x00;
	TCCR2 = (en_mode | en_OC);
	TCNT2 = u8_initialValue;
	OCR2  = u8_outputCompare;
	gen_TMR2PS = en_prescal;
	TIMSK |= en_interruptMask;
	SREG  |= (0x80);
}
/*
 * Description: It Sets The Start Value For Timer2 Ticks
 * @param u8_value: Sets The TMR2 Initial Value
 */
void timer2Set(uint8_t u8_a_value)
{
	TCNT2 = u8_a_value;
}
/*
 * Description: It Returns The Number OF Ticks In TCNT2
 * @return: The Current Value OF Timer2 Ticks
 */
uint8_t timer2Read(void)
{
	return TCNT2;
}
/*
 * Description: It Sets The TMR2 Prescaler, So It Starts Counting!
 */
void timer2Start(void)
{
	TCCR2 |= gen_TMR2PS;
}
/*
 * Description: It Clears The TMR2 Prescaler, So It Stops Counting!
 */
void timer2Stop(void)
{
	TCCR2 =  T2_NO_CLOCK;
}
/*
 * Description: It Halts The CPU For A Specified Amount OF Time (in msec)
 * @param u16_delay_in_ms: Number OF Milli_seconds For The Delay
 */
void timer2DelayMs(uint16_t u16_delay_in_ms)
{
	timer2Init(T2_COMP_MODE, T2_OC2_DIS, T2_PRESCALER_64, 0, 250, 0, T2_INTERRUPT_CMP);
	timer2Start();
	while(u16_delay_in_ms)
	{
		while(!(GET_BIT(TIFR,7)));
		SET_BIT(TIFR,7);
		u16_delay_in_ms--;
	}
}
/*
 * Description: It Halts The CPU For A Specified Amount OF Time (in usec)
 * @param u32_delay_in_us: Number OF Micro_seconds For The Delay
 */
void timer2DelayUs(uint32_t u32_delay_in_us)
{
	timer2Init(T2_COMP_MODE, T2_OC2_DIS, T2_PRESCALER_NO, 0, 14, 0, T2_INTERRUPT_CMP);
	timer2Start();
	while(u32_delay_in_us)
	{
		while(!(GET_BIT(TIFR,7)));
		SET_BIT(TIFR,7);
		u32_delay_in_us--;
	}
}
/*================================================================*/
/*====================[ Timers ISR Handlers ]=====================*/

ISR(TIMER0_COMP_vect)
{
	//-----
}