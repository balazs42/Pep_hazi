/*
 * game_handler.h
 *
 *  Created on: 2022. nov. 16.
 *      Author: H�zi Bal�zs
 */

#ifndef SRC_GAME_HANDLER_H_
#define SRC_GAME_HANDLER_H_

// Includes
#include "em_chip.h"
#include "em_device.h"
#include "em_timer.h"

#include "collision_detection.h"
#include "display_score.h"
#include "generate_asteroids.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#define DISP_D 100
#define MOVE_FRWD_D 500

// External variables
extern SemaphoreHandle_t player_pos_mutex;
extern TaskHandle_t disp_handle;

// Functions
void clear_prev_player_pos(void);
void reset_map(void);
void reset_to_start(void);
void show_player(void);

// Callback functions
void move_right(void);
void move_left(void);

// Tasks

// Moving the player forward, if last digit reached, resetting map
void vTaskMoveFrwd(void *pvParam); // Moving the player forward

// Displaying player position, asteroids, and score
void vTaskDisp(void *pvParam); 

// Resetting map
void vTaskResetMap(void *pvParam); 

#endif /* SRC_GAME_HANDLER_H_ */