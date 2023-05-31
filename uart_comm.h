#ifndef UART_COMM_H
#define UART_COMM_H
#include "em_usart.h"
#include "game_handler.h"


// Configure the USART peripheral
void USART_Config(void);

// Enable the USART interrupt
void USART_EnableInterrupts(void);

// USART interrupt handler
void USART1_RX_IRQHandler(void);

// Task to handle UART communication
void vTaskUart(void *pvParam);

void initUart();

#endif /*UART_COMM_H*/