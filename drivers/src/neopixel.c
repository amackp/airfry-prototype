/*
 * neopixel.c
 *
 *  Created on: Jan 2, 2021
 *      Author: abema
 */

#include "../inc/neopixel.h"

COLOR neopixel_leds[NEOPIXEL_LED_COUNT];

// Send color intensity value for a single channel
static void ShowChannel(uint8_t value) {
    uint8_t i;
    for ( i = 0; i < 8; i++) {
        if ((value >> (7-i)) & 1) { NEOPIXEL_SEND_ONE; }
        else { NEOPIXEL_SEND_ZERO; }
    }
}


void neopixel_Init() {

    P1SEL &= ~NEOPIXEL_PIN;
    P1SEL2 &= ~NEOPIXEL_PIN;
    P1DIR |= NEOPIXEL_PIN;

    neopixel_Clear();
    neopixel_Show();
}


void neopixel_Clear() {
    uint8_t i;

    for (i = 0; i < NEOPIXEL_LED_COUNT; i++) {
        neopixel_leds[i] = NEOPIXEL_OFF;
    }
}


void neopixel_Show() {
    uint8_t i;
    NEOPIXEL_SEND_RESET;

    for ( i = 0; i < NEOPIXEL_LED_COUNT; i++) {
        // channel order is GRB... monsters
        ShowChannel(neopixel_leds[i].green);
        ShowChannel(neopixel_leds[i].red);
        ShowChannel(neopixel_leds[i].blue);
    }

}


uint8_t neopixel_SetColor(uint8_t index, COLOR color) {

        if (index < NEOPIXEL_LED_COUNT) {
            neopixel_leds[index] = color;
    //        Invalidate();
        }
        else
            return 1;
        return 0;
}

uint8_t neopixel_SetColorAndShow(uint8_t index, COLOR color) {

    if (index < NEOPIXEL_LED_COUNT) {
        neopixel_leds[index] = color;
        neopixel_Show();
    }
    else
        return 1;
    return 0;
}

