/*
 * display_score.c
 *
 *  Created on: 2022. nov. 16.
 *      Author: H�zi Bal�zs
 *
 *      Using the upper Char Segments of the LCD screen
 *      Representing numbers up to 99
 *      **Improvements: Adding 2 more decimal places
 */
#include "display_score.h"

// Displaying score until 2 decimal places
void show_score(void) {
  clear_upper_lcd_screen();

  uint8_t single = score % 10;
  uint8_t dec = (uint8_t)(score / 10);

  switch (single) {
  case 0:
    upperCharSegments[0].a = 1;
    upperCharSegments[0].b = 1;
    upperCharSegments[0].c = 1;
    upperCharSegments[0].d = 1;
    upperCharSegments[0].e = 1;
    upperCharSegments[0].f = 1;
    break;
  case 1:
    upperCharSegments[0].b = 1;
    upperCharSegments[0].c = 1;
    break;
  case 2:
    upperCharSegments[0].a = 1;
    upperCharSegments[0].b = 1;
    upperCharSegments[0].g = 1;
    upperCharSegments[0].e = 1;
    upperCharSegments[0].d = 1;
    break;
  case 3:
    upperCharSegments[0].a = 1;
    upperCharSegments[0].b = 1;
    upperCharSegments[0].g = 1;
    upperCharSegments[0].c = 1;
    upperCharSegments[0].d = 1;
    break;
  case 4:
    upperCharSegments[0].f = 1;
    upperCharSegments[0].g = 1;
    upperCharSegments[0].b = 1;
    upperCharSegments[0].c = 1;
    break;
  case 5:
    upperCharSegments[0].a = 1;
    upperCharSegments[0].f = 1;
    upperCharSegments[0].g = 1;
    upperCharSegments[0].c = 1;
    upperCharSegments[0].d = 1;
    break;
  case 6:
    upperCharSegments[0].a = 1;
    upperCharSegments[0].f = 1;
    upperCharSegments[0].g = 1;
    upperCharSegments[0].e = 1;
    upperCharSegments[0].c = 1;
    upperCharSegments[0].d = 1;
    break;
  case 7:
    upperCharSegments[0].a = 1;
    upperCharSegments[0].b = 1;
    upperCharSegments[0].c = 1;
    break;
  case 8:
    upperCharSegments[0].a = 1;
    upperCharSegments[0].b = 1;
    upperCharSegments[0].c = 1;
    upperCharSegments[0].d = 1;
    upperCharSegments[0].e = 1;
    upperCharSegments[0].f = 1;
    upperCharSegments[0].g = 1;
    break;
  case 9:
    upperCharSegments[0].a = 1;
    upperCharSegments[0].f = 1;
    upperCharSegments[0].b = 1;
    upperCharSegments[0].g = 1;
    upperCharSegments[0].c = 1;
    upperCharSegments[0].d = 1;
    break;
  default:
    break;
  }

  switch (dec) {
  case 0:
    upperCharSegments[1].a = 1;
    upperCharSegments[1].b = 1;
    upperCharSegments[1].c = 1;
    upperCharSegments[1].d = 1;
    upperCharSegments[1].e = 1;
    upperCharSegments[1].f = 1;
    break;
  case 1:
    upperCharSegments[1].b = 1;
    upperCharSegments[1].c = 1;
    break;
  case 2:
    upperCharSegments[1].a = 1;
    upperCharSegments[1].b = 1;
    upperCharSegments[1].g = 1;
    upperCharSegments[1].e = 1;
    upperCharSegments[1].d = 1;
    break;
  case 3:
    upperCharSegments[1].a = 1;
    upperCharSegments[1].b = 1;
    upperCharSegments[1].g = 1;
    upperCharSegments[1].c = 1;
    upperCharSegments[1].d = 1;
    break;
  case 4:
    upperCharSegments[1].f = 1;
    upperCharSegments[1].g = 1;
    upperCharSegments[1].b = 1;
    upperCharSegments[1].c = 1;
    break;
  case 5:
    upperCharSegments[1].a = 1;
    upperCharSegments[1].f = 1;
    upperCharSegments[1].g = 1;
    upperCharSegments[1].c = 1;
    upperCharSegments[1].d = 1;
    break;
  case 6:
    upperCharSegments[1].a = 1;
    upperCharSegments[1].f = 1;
    upperCharSegments[1].g = 1;
    upperCharSegments[1].e = 1;
    upperCharSegments[1].c = 1;
    upperCharSegments[1].d = 1;
    break;
  case 7:
    upperCharSegments[1].a = 1;
    upperCharSegments[1].b = 1;
    upperCharSegments[1].c = 1;
    break;
  case 8:
    upperCharSegments[1].a = 1;
    upperCharSegments[1].b = 1;
    upperCharSegments[1].c = 1;
    upperCharSegments[1].d = 1;
    upperCharSegments[1].e = 1;
    upperCharSegments[1].f = 1;
    upperCharSegments[1].g = 1;
    break;
  case 9:
    upperCharSegments[1].a = 1;
    upperCharSegments[1].f = 1;
    upperCharSegments[1].b = 1;
    upperCharSegments[1].g = 1;
    upperCharSegments[1].c = 1;
    upperCharSegments[1].d = 1;
    break;
  default:
    break;
  }
  SegmentLCD_UpperSegments(upperCharSegments);
}
