/*
 * init_sw.c
 *
 *  Created on: 2022. nov. 16.
 *      Author: H�zi Bal�zs
 *
 *      Initializing the software: GPIO clock,
 *    	Push buttons, and the LCD screen
 */
#include "init_sw.h"

// Enabling clocks
void enable_clk(void)
{
	CMU_ClockEnable(cmuClock_GPIO, true);
	CMU_ClockEnable(cmuClock_TIMER0, true);
}

/***************************************************************************//**
* @brief  Gpio callback
* @param  pin - pin which triggered interrupt
******************************************************************************/
void gpioCallback(uint8_t pin)
{
	if (pin == 9)
		move_left();
	else if (pin == 10)
		move_right();
}

//	Push buttons initialization
void init_buttons(void)
{
	/* Enable GPIO in CMU */
	CMU_ClockEnable(cmuClock_GPIO, true);

	/* Initialize GPIO interrupt dispatcher */
	GPIOINT_Init();

	/* Configure PB9 and PB10 as input */
	GPIO_PinModeSet(gpioPortB, 9, gpioModeInput, 0);
	GPIO_PinModeSet(gpioPortB, 10, gpioModeInput, 0);

	/* Register callbacks before setting up and enabling pin interrupt. */
	GPIOINT_CallbackRegister(9, gpioCallback);
	GPIOINT_CallbackRegister(10, gpioCallback);

	/* Set falling edge interrupt for both ports */
	GPIO_IntConfig(gpioPortB, 9, true, false, true);
	GPIO_IntConfig(gpioPortB, 10, true, false, true);

}

// LCD screen initalization
void init_lcd(void)
{
	SegmentLCD_Init(false);
}

// Software initialization
void init(void)
{
	// Enabling clocks
	enable_clk();

	// Initializing LCD screen
	init_lcd();

	// Initializing Push Buttons
	init_buttons();
}
