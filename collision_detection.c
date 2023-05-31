#include "collision_detection.h"

#define BLINK_DP_D 500
#define COLL_DET_D 200

// Asteroid positions
uint8_t asteroid_dig_pos[3];
uint8_t asteroid_segm_pos[3];

// Detecting collision between player and asteroid
uint8_t collided(void) {
  xSemaphoreTake(player_pos_mutex, portMAX_DELAY);

  for (int i = 0; i < 3; i++) {
    if (player_dig_pos ==
            asteroid_dig_pos[i] && // If the player's digit and segment position
                                   // is the same as one
        player_segm_pos ==
            asteroid_segm_pos[i]) // of the asteroids, then it's a collision ->
                                  // returning true
      return 1;
  }

  xSemaphoreGive(player_pos_mutex);
  return 0;
}

// If a collision was detected end game
void endGame(void) {
  GPIO_IntDisable(0xFFFFF); // Disabling GPIO interrupts
  while (1) {
    // Suspending tasks
    xTaskSuspend(coll_det_handle);
    xTaskSuspend(move_frwd_handle);
    xTaskSuspend(disp_handle);

    // Clearing screen
    clear_lower_lcd_screen();
    clear_upper_lcd_screen();

    // Write boom
    SegmentLCD_Write(" BOOM");

    // Blinking decimal points
    xTaskResume(blink_dp_handle);

    // To restart the game RESET BUTTON must be pressed; TODO: other way around
  }
}

// Task that blinks decimal points
void vTaskBlinkDP(void *pvParam) {
  bool on = false;
  while (1) {
    // Decimal points on
    SegmentLCD_Symbol(LCD_SYMBOL_DP2, on);
    SegmentLCD_Symbol(LCD_SYMBOL_DP3, on);
    SegmentLCD_Symbol(LCD_SYMBOL_DP4, on);
    SegmentLCD_Symbol(LCD_SYMBOL_DP5, on);
    SegmentLCD_Symbol(LCD_SYMBOL_DP6, on);

    on = !on;

    xTaskDelay(BLINK_DP_D / portTICK_RATE_MS);
  }
}

// Task that check collision on the specified intervall
void vTaskCollDet(void *pvParam) {
  while (1) {
    if (collided()) {
      endGame(); // Suspends tasks, prints 'BOOM' and resumes Decimal point
                 // blinking task
    }
    xTaskDelay(COLL_DET_D / portTICK_RATE_MS);
  }
}