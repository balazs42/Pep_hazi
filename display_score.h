/*
 * display_score.h
 *
 *  Created on: 2022. nov. 16.
 *      Author: H�zi Bal�zs
 */

#ifndef SRC_DISPLAY_SCORE_H_
#define SRC_DISPLAY_SCORE_H_

// Includes
#include "em_chip.h"
#include "em_device.h"
#include "lcd_handling.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"

// External variables
extern SegmentLCD_UpperCharSegments_TypeDef
    upperCharSegments[SEGMENT_LCD_NUM_OF_UPPER_CHARS];

extern int score;

// Function

// Displaying the score on the upper LCD
void show_score(void);

#endif /* SRC_DISPLAY_SCORE_H_ */