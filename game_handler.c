/*
 * game_handler.c
 *
 *  Created on: 2022. nov. 16.
 *      Author: H�zi Bal�zs
 *
 *      Gameplay: By every 'timer' delay the player's
 *      position is shifted forward relative to its x - y
 *      position. GPIO interrupts (push button presses)
 *      can shift the player's direction properly to the
 *      specification. After each shifting, the player's
 *      old position is erased from the screen, and the new
 *      position is represented.
 */

#include "game_handler.h"

// Player position
uint8_t player_dig_pos;
uint8_t player_segm_pos;

// Player's score before start
int score = -1;

// UP=1, DOWN=-1, RIGHT=0
int dir = 0;

// Player's direction
uint8_t player_dir;

// Previous positions of the player -> Erasing those segments from the lcd
uint8_t prev_player_dig_pos;
uint8_t prev_player_segm_pos;

// Lower segment displayer
SegmentLCD_LowerCharSegments_TypeDef
    lowerCharSegments[SEGMENT_LCD_NUM_OF_LOWER_CHARS];

// Clearing previous position of player from LCD
// Only setting off segments, not refreshing the whole screen
void clear_prev_player_pos(void) {
  xSemaphoreTake(player_pos_mutex, portMAX_DELAY);

  switch (prev_player_segm_pos) {
  case 0: // Setting 0->a segment as on
    lowerCharSegments[prev_player_dig_pos].a = 0;
    break;
  case 3: // Setting 3->d segment as on
    lowerCharSegments[prev_player_dig_pos].d = 0;
    break;
  case 4: // Setting 4->e segment as on
    lowerCharSegments[prev_player_dig_pos].e = 0;
    break;
  case 5: // Setting 5->f segment as on
    lowerCharSegments[prev_player_dig_pos].f = 0;
    break;
  case 6: // Setting middle segments, 6,10->g, m as on
    lowerCharSegments[prev_player_dig_pos].g = 0;
    lowerCharSegments[prev_player_dig_pos].m = 0;
    break;
  default:
    break;
  }

  xSemaphoreGive(player_pos_mutex);
}

// Clearing map and generating new asteroids
void reset_map(void) {
  clear_lower_lcd_screen();

  // Generating then showing asteroids
  generate_asteroids();
}

// Resetting player positions to the first segment, incrementing score
void reset_to_start(void) {
  // Incrementing score, then displaying it
  score++;

  xSemaphoreTake(player_pos_mutex, portMAX_DELAY);

  // Resetting as first digit
  player_dig_pos = 0;

  // Starting segment is the middle one
  player_segm_pos = 6;

  xSemaphoreGive(player_pos_mutex);
}

// Showing player on LCD screen
void show_player(void) {
  xSemaphoreTake(player_pos_mutex, portMAX_DELAY);

  switch (player_segm_pos) {
  case 0: // Setting 0->a segment as on
    lowerCharSegments[player_dig_pos].a = 1;
    break;
  case 3: // Setting 3->d segment as on
    lowerCharSegments[player_dig_pos].d = 1;
    break;
  case 4: // Setting 4->e segment as on
    lowerCharSegments[player_dig_pos].e = 1;
    break;
  case 5: // Setting 5->f segment as on
    lowerCharSegments[player_dig_pos].f = 1;
    break;
  case 6: // Setting middle segments, 6,10->g, m as on
    lowerCharSegments[player_dig_pos].g = 1;
    lowerCharSegments[player_dig_pos].m = 1;
    break;
  default:
    break;
  }

  xSemaphoreGive(player_pos_mutex);

  // Clearing previous position
  clear_prev_player_pos();

  // Showing current position
  SegmentLCD_LowerSegments(lowerCharSegments);
}

/*
 *
 *	MOVE FUNCTIONS ARE CALLBACKS ATTACHED TO BUTTON INTERRUPTS
 *
 */

// Moving right
void move_right(void) {
  xSemaphoreTake(player_pos_mutex, portMAX_DELAY);

  // Checking current semgent's position
  switch (player_segm_pos) {
  case 0:
    if (player_dig_pos == 6) {
      player_segm_pos = 5; // Next position
      player_dir = 1;      // direction vertical

      prev_player_dig_pos = 6; // Previous position
      prev_player_segm_pos = 0;

      reset_to_start();
      return;
    } else {
      player_dig_pos++; // Next position
      player_segm_pos = 5;
      player_dir = 1; // direction vertical

      prev_player_dig_pos = player_dig_pos - 1; // Previous position
      prev_player_segm_pos = 0;
    }
    break;
  case 3:
    if (player_dig_pos == 6) {
      player_segm_pos = 5; // Next position
      player_dir = 1;      // direction vertical

      prev_player_dig_pos = 6; // Previous position
      prev_player_segm_pos = 3;

      reset_to_start();
      return;
    } else {
      player_dig_pos++; // Next position
      player_segm_pos = 5;
      player_dir = 1; // direction vertical

      prev_player_dig_pos = player_dig_pos - 1; // Previous position
      prev_player_segm_pos = 3;
    }
    break;
  case 4:
    player_segm_pos = 3; // Next position
    player_dir = 0;      // direction horizontal

    prev_player_dig_pos = player_dig_pos; // Previous position
    prev_player_segm_pos = 4;
    break;
  case 5:
    player_segm_pos = 6; // Next position
    player_dir = 0;      // direction horizontal

    prev_player_dig_pos = player_dig_pos; // Previous position
    prev_player_segm_pos = 5;
    break;
  case 6:
    if (player_dig_pos == 6) {
      player_segm_pos = 4; // Next position
      player_dir = 1;      // direction vertical

      prev_player_dig_pos = 6; // Previous position
      prev_player_segm_pos = 6;

      reset_to_start();
      return;
    } else {
      player_dig_pos++; // Next position
      player_segm_pos = 4;
      player_dir = 1; // direction vertical

      prev_player_dig_pos = player_dig_pos - 1; // Previous position
      prev_player_segm_pos = 6;
    }
    break;
  default:
    break;
  }
  xSemaphoreGive(player_pos_mutex);
}

// Moving left
void move_left(void) {
  xSemaphoreTake(player_pos_mutex, portMAX_DELAY);
  switch (player_segm_pos) {
  case 0:
    if (player_dig_pos == 6) {
      player_segm_pos = 4; // Next position
      player_dir = 1;      // direction vertical

      prev_player_dig_pos = 6; // Previous position
      prev_player_segm_pos = 0;

      reset_to_start();
      return;
    } else {
      player_dig_pos++; // Next position
      player_segm_pos = 4;
      player_dir = 1; // direction vertical

      prev_player_dig_pos = player_dig_pos - 1; // Previous position
      prev_player_segm_pos = 0;
    }
    break;
  case 3:
    if (player_dig_pos == 6) {
      player_segm_pos = 4; // Next position
      player_dir = 1;      // direction vertical

      prev_player_dig_pos = 6; // Previous position
      prev_player_segm_pos = 3;

      reset_to_start();
      return;
    } else {
      player_dig_pos++; // Next position
      player_segm_pos = 4;
      player_dir = 1; // direction vertical

      prev_player_dig_pos = player_dig_pos - 1; // Previous position
      prev_player_segm_pos = 3;
    }
    break;
  case 4:
    player_segm_pos = 6; // Next position
    player_dir = 0;      // direction horizontal

    prev_player_dig_pos = player_dig_pos; // Previous position
    prev_player_segm_pos = 4;
    break;
  case 5:
    player_segm_pos = 0; // Next position
    player_dir = 0;      // direction horizontal

    prev_player_dig_pos = player_dig_pos; // Previous position
    prev_player_segm_pos = 5;
    break;
  case 6:
    if (player_dig_pos == 6) {
      player_segm_pos = 5; // Next position
      player_dir = 1;      // direction vertical

      prev_player_dig_pos = 6; // Previous position
      prev_player_segm_pos = 6;
      return;
    } else {
      player_dig_pos++; // Next position
      player_segm_pos = 5;
      player_dir = 1; // direction vertical

      prev_player_dig_pos = player_dig_pos - 1; // Previous position
      prev_player_segm_pos = 6;
    }

    break;
  default:
    break;
  }
  xSemaphoreGive(player_pos_mutex);
}

// Currently not in use, but could be used some way around
void restart_game(void) {
  score = 0;
  xTaskResume(coll_det_handle);
  xTaskResume(move_frwd_handle);
  xTaskResume(disp_handle);
  xTaskResume(reset_map_handle);
}

/**
 *
 *
 * 	THIS IS CONTROLLED BY THE TASK MANAGER
 *
 */

// Moving the player forward, if last digit reached, resetting map
void vTaskMoveFrwd(void *pvParam) {
  while (1) {
    xSemaphoreTake(player_pos_mutex, portMAX_DELAY);

    if (player_dir == 1) // Vertical
    {
      switch (player_segm_pos) {
      case 4:
        player_segm_pos = 5; // Next position

        prev_player_dig_pos = player_dig_pos; // Previous position
        prev_player_segm_pos = 4;
        break;
      case 5:
        player_segm_pos = 4; // Next position

        prev_player_dig_pos = player_dig_pos; // Previous position
        prev_player_segm_pos = 5;
        break;
      default:
        break;
      }
    } else // Horizontal
    {
      if (player_dig_pos == 6) {
        prev_player_dig_pos = 6; // Previous position
        prev_player_segm_pos = player_segm_pos;

        xTaskResume(reset_map_handle); // If this is the last digit, then
                                       // resetting player position
      } else {
        player_dig_pos++; // Next position

        prev_player_dig_pos = player_dig_pos - 1; // Previous position
        prev_player_segm_pos = player_segm_pos;
      }
    }

    xSemaphoreGive(player_pos_mutex);

    vTaskDelay(MOVE_FRWD_D / portTICK_RATE_MS);
  }
}

// Displaying player position, asteroids, and score
void vTaskDisp(void *pvParam) {
  while (1) {
    show_player();
    show_asteroids();
    vTaskDelay(DISP_D / portTICK_RATE_MS);
  }
}

// Resets the player position
void vTaskResetMap(void *pvParam) {
  while (1) {
    reset_map(); // Generating new asteroids

    reset_to_start(); // Resettin player to start

    show_asteroids(); // Showing the asteroids

    show_score(); // Shwoing new score

    xTaskSuspend(NULL); // Suspending task because it only needs to run once
  }
}