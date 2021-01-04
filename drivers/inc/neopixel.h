/*
 * neopixel.h
 *
 *  Created on: Jan 2, 2021
 *      Author: abema
 */

#ifndef DRIVERS_INC_NEOPIXEL_H_
#define DRIVERS_INC_NEOPIXEL_H_


#include <msp430.h>
#include <stdint.h>
#include <stdbool.h>
#include "../../utility/delay.h"
#include "../../utility/color.h"


#define NEOPIXEL_PIN            BIT7  // P1.7
#define NEOPIXEL_LED_COUNT      33

#define _300NS                  1
#define _900NS                  10
#define _600NS                  6
#define _60US                   1000

//static uint8_t p1bak;

// outer ring neopixels //
#define NEOPIXEL_SEND_ZERO      P1OUT |= NEOPIXEL_PIN; \
                                __delay_cycles(_300NS); \
                                P1OUT &= ~NEOPIXEL_PIN; \
                                __delay_cycles(_900NS);


#define NEOPIXEL_SEND_ONE       P1OUT |= NEOPIXEL_PIN; \
                                __delay_cycles(_600NS); \
                                P1OUT &= ~NEOPIXEL_PIN; \
                                __delay_cycles(_600NS);


#define NEOPIXEL_SEND_RESET     P1OUT &= ~NEOPIXEL_PIN; \
                                delay_us(80);


#define NEOPIXEL_OFF        BLACK

//uint8_t neopixel_valid;



static void ShowChannel(uint8_t value);
void        neopixel_Init();
void        neopixel_Clear();
void        neopixel_Show();
uint8_t     neopixel_SetColor(uint8_t index, COLOR color);
uint8_t     neopixel_SetColorAndShow(uint8_t index, COLOR color);

#endif /* DRIVERS_INC_NEOPIXEL_H_ */
