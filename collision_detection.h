/*
 * collision_detection.h
 *
 *  Created on: 2022. nov. 16.
 *      Author: H�zi Bal�zs
 */

#ifndef SRC_COLLISION_DETECTION_H_
#define SRC_COLLISION_DETECTION_H_

// Includes
#include "em_chip.h"
#include "em_device.h"
#include "lcd_handling.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

// External variables
extern SemaphoreHandle_t player_pos_mutex;

extern TaskHandle_t disp_handle;
extern TaskHandle_t coll_det_handle;
extern TaskHandle_t move_frwd_handle;
extern TaskHandle_t reset_map_handle;
extern TaskHandle_t blink_dp_handle;

// Player position
extern uint8_t player_dig_pos;
extern uint8_t player_segm_pos;

// Functions
uint8_t collided(void);
void endGame(void);

// Task

// Task that blinks decimal points
void vTaskBlinkDP(void *pvParam);

// Task that check collision on the specified intervall
void vTaskCollDet(void *pvParam);

#endif /* SRC_COLLISION_DETECTION_H_ */
