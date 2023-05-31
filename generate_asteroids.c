/*
 * generate_asteroids.c
 *
 *  Created on: 2022. nov. 16.
 *      Author: H�zi Bal�zs
 *
 *      Asteroids are generated randomly through the map.
 *      First we set asteroid positions to default 0 value,
 *      then we assing 3 random different digital places on
 *      the LCD, then we assign 3 random segments int these
 *      3 random digits, and after these we check, if any of
 *      the digital places is the last digit (7), if so, then
 *      assigning new random segment on that digit, because on
 *      that we can use 2 more segments to put the asteroids on.
 *
 */
#include "generate_asteroids.h"

uint8_t asteroid_dig_pos[3];
uint8_t asteroid_segm_pos[3];

extern SegmentLCD_LowerCharSegments_TypeDef
    lowerCharSegments[SEGMENT_LCD_NUM_OF_LOWER_CHARS];

// Possible positions: 0->a, 3->d, 4->e, 5->f, 6->g & 10->m, 1->b, 2->c
const int pos[7] = {0, 3, 4, 5, 6, 1, 2};

// Generating asteroids
void generate_asteroids(void) {
  for (int i = 0; i < 3; i++) {
    asteroid_dig_pos[i] = 0;
    asteroid_segm_pos[i] = 0;
  }

  // Generating which digital positions the asteroids are
  asteroid_dig_pos[0] = rand() % 6 + 1;

  // Getting 3 different random numbers for 3 different digit
  while (asteroid_dig_pos[0] == asteroid_dig_pos[1] ||
         asteroid_dig_pos[0] == asteroid_dig_pos[2] ||
         asteroid_dig_pos[1] == asteroid_dig_pos[2]) {
    asteroid_dig_pos[1] = rand() % 6 + 1;
    asteroid_dig_pos[2] = rand() % 6 + 1;
  }

  // Generating which segments to be displayed on each digit
  while (asteroid_segm_pos[0] == asteroid_segm_pos[1] ||
         asteroid_segm_pos[0] == asteroid_segm_pos[2] ||
         asteroid_segm_pos[1] == asteroid_segm_pos[2]) {
    asteroid_segm_pos[0] = rand() % 5;
    asteroid_segm_pos[1] = rand() % 5;
    asteroid_segm_pos[2] = rand() % 5;
  }

  // Last segment -> more possible spots
  for (int i = 0; i < 3; i++)
    if (asteroid_dig_pos[i] == 6)
      asteroid_segm_pos[i] = rand() % 7;
}

// Showing asteroids on screen
void show_asteroids(void) {
  int j = 0, i;
  while (j < 3) {
    i = pos[asteroid_segm_pos[j]];
    switch (i) {
    case 0:
      lowerCharSegments[asteroid_dig_pos[j]].a = 1;
      asteroid_segm_pos[j] = 0;
      break;
    case 1: // For last segment
      lowerCharSegments[asteroid_dig_pos[j]].b = 1;
      asteroid_segm_pos[j] = 1;
      break;
    case 2: // For last segment
      lowerCharSegments[asteroid_dig_pos[j]].c = 1;
      asteroid_segm_pos[j] = 2;
      break;
    case 3:
      lowerCharSegments[asteroid_dig_pos[j]].d = 1;
      asteroid_segm_pos[j] = 3;
      break;
    case 4:
      lowerCharSegments[asteroid_dig_pos[j]].e = 1;
      asteroid_segm_pos[j] = 4;
      break;
    case 5:
      lowerCharSegments[asteroid_dig_pos[j]].f = 1;
      asteroid_segm_pos[j] = 5;
      break;
    case 6:
      lowerCharSegments[asteroid_dig_pos[j]].g = 1;
      lowerCharSegments[asteroid_dig_pos[j]].m = 1;
      asteroid_segm_pos[j] = 6;
      break;
    default:
      break;
    }
    j++;
  }
  SegmentLCD_LowerSegments(lowerCharSegments);
}
