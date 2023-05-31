#include "uart_comm.h"

static uint8_t dataBuff[3];
static uint8_t dataIdx = 0;

SemaphoreHandle_t USRT_binary;

// Configure the USART peripheral
void USART_Config(void)
{
  USART_InitAsync_TypeDef init = USART_INITASYNC_DEFAULT;
  init.baudrate = 115200;
  USART_InitAsync(USART1, &init);
}

// Enable the USART interrupt
void USART_EnableInterrupts(void)
{
  USART_IntEnable(USART1, USART_IEN_RXDATAV);
  NVIC_EnableIRQ(USART1_RX_IRQn);
}

// USART interrupt handler
void USART1_RX_IRQHandler(void)
{
    BaseType_t xSwitchRequired = pdFALSE;

    // Read the received data from the USART data register
    uint8_t data = USART_Rx(USART1);
    if(data == 27)
    {
        // Semaphore isn't taken form ISR because it would block the run
        // Instead using GiveFromISR function to signal that we used global interface
        dataBuff[0] = 27;
        dataBuff[1] = USRT_Rx(USART1);
        dataBuff[2] = USRT_Rx(USART1);
        xSemaphoreGiveFromISR(USRT_binary, &xSwitchRequired)

        // Signaling that a high priority task was blocked by the ISR
        if(xSwitchRequired == pdTRUE)
            portYIELD_FROM_ISR();

    }

  
  // Write data to the USART data register to transmit data
  //USART_Tx(USART1, data);
}

// Task to handle UART communication
void vTaskUart(void *pvParam)
{
    while (1)
    {
        // Process the received data, if the binary semaphore is available
        if(xSemaphoreTake(USRT_binary, portMAX_DELAY) == pdTRUE)
        {
        // Check if an arrow key is pressed
            if (data[0] == 27) // ESC character
            {
                // Wait for the next character to determine which arrow key is pressed
                uint8_t next_data = USART_Rx(USART1);
                if (next_data == '[')
                {
                    uint8_t arrow_key = USART_Rx(USART1);
                    switch (arrow_key)
                    {
                    case 'A': // Up arrow key
                        break;
                    case 'B': // Down arrow key
                        break;
                    case 'C': // Right arrow key
                        move_right();
                        break;
                    case 'D': // Left arrow key
                        move_left();
                        break;
                    default:
                        break;
                    }
                }
            }
            xSemaphoreGive(USRT_binary);
        }

        // Send a response back through the USART module
        USART_Tx(USART1, data);

        vTaskDelay(100 / portTICK_RATE_MS);
    }
}

void initUart()
{
    USRT_binary = xSemaphoreCreateBinary();
    USART_Config();
    USART_EnableInterrupts();

    // Create a task to handle UART communication
    xTaskCreate(vTaskUart, "UART_Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL);

    //vTaskStartScheduler();
}