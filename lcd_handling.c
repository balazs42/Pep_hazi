/*
 * lcd_handling.c
 *
 *  Created on: 2022. nov. 16.
 *      Author: H�zi Bal�zs
 *
 *      LCD screen erasing functions
 */
#include "lcd_handling.h"

extern SegmentLCD_LowerCharSegments_TypeDef lowerCharSegments[];
extern SegmentLCD_UpperCharSegments_TypeDef upperCharSegments[];

//------------------------------------------
// Lower LCD erase
//------------------------------------------
void clear_lower_lcd_screen(void) {
  for (uint8_t i = 0; i < SEGMENT_LCD_NUM_OF_LOWER_CHARS; i++)
    lowerCharSegments[i].raw = 0;

  SegmentLCD_LowerSegments(lowerCharSegments);
}

//------------------------------------------
// Upper LCD erase
//------------------------------------------
void clear_upper_lcd_screen(void) {
  for (uint8_t i = 0; i < SEGMENT_LCD_NUM_OF_UPPER_CHARS; i++)
    upperCharSegments[i].raw = 0;

  SegmentLCD_UpperSegments(upperCharSegments);
}
