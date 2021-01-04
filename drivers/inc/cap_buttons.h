/*
 * cap_buttons.h
 *
 *  Created on: Jan 3, 2021
 *      Author: abema
 */

#ifndef DRIVERS_INC_CAP_BUTTONS_H_
#define DRIVERS_INC_CAP_BUTTONS_H_

#include <msp430.h>
#include <stdint.h>

#define NUMBER_BUTTONS 15

typedef enum{
    //modes
    BUTTON_AIRFRY = 0x00,
    BUTTON_BAKE,
    BUTTON_ROAST,
    BUTTON_DEHYDRATE,
    BUTTON_PREHEAT,
    BUTTON_GRILL,

    //toggles
    BUTTON_SMOKE_EXT,
    BUTTON_TIME_TEMP_TOGGLE,
    BUTTON_TURN_REM,

    //arrows
    BUTTON_TIME_UP,
    BUTTON_TIME_DOWN,
    BUTTON_TEMP_DOWN,
    BUTTON_TEMP_UP,

    //power
    BUTTON_STOP_CANCEL,
    BUTTON_POWER,
    BUTTON_START,

    //nonpressable buttons
    BUTTON_GRILL_LOW,
    BUTTON_GRILL_MED,
    BUTTON_GRILL_HIGH,
    BUTTON_GRILL_MAX,

    BUTTON_NULL
}button_function_t;

typedef enum{
    BUTTON_STATE_OFF,
    BUTTON_STATE_ON,
    BUTTON_STATE_PRESSED
}button_state_t;

typedef enum{
    TYPE_WHITE,
    TYPE_WHITE_BLUE,
    TYPE_WHITE_RED
}button_type_t;

typedef struct{
    button_function_t function;
    uint8_t port;
    uint8_t pin;
    button_type_t type;
    button_state_t state;
    uint8_t assc_leds[2];   //indexes of leds accociated with button

}button_map_t;




#endif /* DRIVERS_INC_CAP_BUTTONS_H_ */
