/*
 * init_sw.h
 *
 *  Created on: 2022. nov. 16.
 *      Author: H�zi Bal�zs
 */

#ifndef SRC_INIT_SW_H_
#define SRC_INIT_SW_H_

// Includes
#include "em_chip.h"
#include "em_cmu.h"
#include "em_device.h"
#include "em_gpio.h"
#include "em_timer.h"
#include "game_handler.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"


void enable_clk(void);
void init_buttons(void);
void init_lcd(void);
void init(void);

#endif /* SRC_INIT_SW_H_ */
