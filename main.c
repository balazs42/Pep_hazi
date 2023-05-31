#include "em_adc.h"
#include "em_chip.h"
#include "em_device.h"
#include "em_timer.h"
#include "segmentlcd.h"
#include "segmentlcd_individual.h"

#include "collision_detection.h"
#include "display_score.h"
#include "uart_comm.h"
#include "generate_asteroids.h"
#include "init_sw.h"

#include <FreeRTOS.h>
#include <semphr.h>
#include <task.h>

#define DISP_PRIO 2
#define COLL_DET_PRIO 2
#define MOVE_FRWD_PRIO 2
#define RESET_PRIO 5

SemaphoreHandle_t player_pos_mutex; // Player pos mutex

// Handles to suspend tasks when game ends
TaskHandle_t disp_handle;
TaskHandle_t coll_det_handle;
TaskHandle_t move_frwd_handle;
TaskHandle_t reset_map_handle;
TaskHandle_t blink_dp_handle;

// Global LCD variables
SegmentLCD_UpperCharSegments_TypeDef
    upperCharSegments[SEGMENT_LCD_NUM_OF_UPPER_CHARS];
SegmentLCD_LowerCharSegments_TypeDef
    lowerCharSegments[SEGMENT_LCD_NUM_OF_LOWER_CHARS];

/******************************************************************************
 * Initialize application.
 ******************************************************************************/
void app_init(void) {
  /* Chip errata
CHIP_Init();*/

  // Initializing: gpio clock, lcd, buttons
  init();

  // Initializing UART IRQ handler, creating UART handling task
  initUart();

  player_pos_mutex = xSemaphoreCreateMutex();

  xTaskCreate(vTaskResetMap, "Resetting map", 1024, NULL,
              tskIDLE_PRIORITY + RESET_PRIO, &reset_map_handle);
  xTaskSuspend(reset_map_handle);
  
  xTaskCreate(vTaskBlinkDP, "Blink decimalpoints", 1024, NULL,
              tskIDLE_PRIORITY + 1, &blink_dp_handle);
  xTaskSuspend(blink_dp_handle); // Suspending immediately

  xTaskCreate(vTaskDisp, "Display screen", 2048, NULL,
              tskIDLE_PRIORITY + DISP_PRIO, &disp_handle);

  xTaskCreate(vTaskCollDet, "Collision", 2048, NULL,
              tskIDLE_PRIORITY + COLL_DET_PRIO, &coll_det_handle);

  xTaskCreate(vTaskMoveFrwd, "Move Forward" 2048, NULL,
              tskIDLE_PRIORITY + MOVE_FRWD_PRIO, &move_frwd_handle);


  

  // Enabling GPIO interrupts for the buttons
  GPIO_IntEnable(0xFFFFF);

  xTaskDelete(NULL); // Deleting main
}

/***************************************************************************/ /**
  * App ticking function.
  ******************************************************************************/
void app_process_action(void) {}