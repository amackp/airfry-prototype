/*
 * cap_buttons.c
 *
 *  Created on: Jan 3, 2021
 *      Author: abema
 */

#include "../inc/cap_buttons.h"
#include "../inc/neopixel.h"

button_map_t buttons[BUTTON_NULL];

void button_io_init(){
    //for 4b concept

#ifdef CONCEPT_5A
#else
    uint8_t i = 0;
    //AIRFRY
    buttons[i].port = 2;
    buttons[i].pin = BIT0;
    buttons[i].function = BUTTON_AIRFRY;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 0;
    buttons[i].assc_leds[1] = 1;
    i++;

    //BAKE
    buttons[i].port = 2;
    buttons[i].pin = BIT1;
    buttons[i].function = BUTTON_BAKE;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 2;
    buttons[i].assc_leds[1] = 3;
    i++;

    buttons[i].port = 2;
    buttons[i].pin = BIT2;
    buttons[i].function = BUTTON_ROAST;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 4;
    buttons[i].assc_leds[1] = 5;
    i++;

    buttons[i].port = 2;
    buttons[i].pin = BIT4;
    buttons[i].function = BUTTON_DEHYDRATE;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 6;
    buttons[i].assc_leds[1] = 7;
    i++;

    buttons[i].port = 2;
    buttons[i].pin = BIT3;
    buttons[i].function = BUTTON_PREHEAT;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 8;
    buttons[i].assc_leds[1] = 9;
    i++;

    buttons[i].port = 2;
    buttons[i].pin = BIT5;
    buttons[i].function = BUTTON_TIME_UP;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 12;
    buttons[i].assc_leds[1] = 0xff;
    i++;

    buttons[i].port = 2;
    buttons[i].pin = BIT6;
    buttons[i].function = BUTTON_TIME_DOWN;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 13;
    buttons[i].assc_leds[1] = 0xff;
    i++;

    buttons[i].port = 2;
    buttons[i].pin = BIT7;
    buttons[i].function = BUTTON_STOP_CANCEL;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 10;
    buttons[i].assc_leds[1] = 11;
    buttons[i].type = 0;
    i++;

    buttons[i].port = 3;
    buttons[i].pin = BIT0;
    buttons[i].function = BUTTON_POWER;
    buttons[i].state = BUTTON_STATE_ON;
    buttons[i].assc_leds[0] = 14;
    buttons[i].assc_leds[1] = 0xff;
    i++;

    buttons[i].port = 3;
    buttons[i].pin = BIT1;
    buttons[i].function = BUTTON_START;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 15;
    buttons[i].assc_leds[1] = 16;
    i++;

    buttons[i].port = 3;
    buttons[i].pin = BIT2;
    buttons[i].function = BUTTON_TURN_REM;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 17;
    buttons[i].assc_leds[1] = 18;
    i++;

    buttons[i].port = 3;
    buttons[i].pin = BIT3;
    buttons[i].function = BUTTON_TEMP_DOWN;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 19;
    buttons[i].assc_leds[1] = 0xff;
    i++;

    buttons[i].port = 3;
    buttons[i].pin = BIT4;
    buttons[i].function = BUTTON_TEMP_UP;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 20;
    buttons[i].assc_leds[1] = 0xff;
    i++;

    buttons[i].port = 3;
    buttons[i].pin = BIT5;
    buttons[i].function = BUTTON_GRILL;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 21;
    buttons[i].assc_leds[1] = 22;
    i++;

    buttons[i].port = 3;
    buttons[i].pin = BIT6;
    buttons[i].function = BUTTON_SMOKE_EXT;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 31;
    buttons[i].assc_leds[1] = 32;
    i++;

    //NOT USED IN 4B
    buttons[i].port = 0;
    buttons[i].pin = BIT0;
    buttons[i].function = BUTTON_TIME_TEMP_TOGGLE;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 0xff;
    buttons[i].assc_leds[1] = 0xff;
    i++;

    buttons[i].port = 0;
    buttons[i].pin = BIT6;
    buttons[i].function = BUTTON_GRILL_LOW;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 23;
    buttons[i].assc_leds[1] = 24;
    i++;

    buttons[i].port = 0;
    buttons[i].pin = BIT6;
    buttons[i].function = BUTTON_GRILL_MED;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 25;
    buttons[i].assc_leds[1] = 26;
    i++;

    buttons[i].port = 0;
    buttons[i].pin = BIT6;
    buttons[i].function = BUTTON_GRILL_HIGH;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 27;
    buttons[i].assc_leds[1] = 28;
    i++;

    buttons[i].port = 0;
    buttons[i].pin = BIT6;
    buttons[i].function = BUTTON_GRILL_MAX;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 29;
    buttons[i].assc_leds[1] = 30;
#endif

    P2SEL = 0;
    P2SEL2 = 0;
    P2DIR = 0;
    P2REN = 0xff;
    P2OUT = 0xff;
    P2IE = 0xff;
    P2IES = 0xff;

    P3SEL = 0;
    P3SEL2 = 0;
    P3DIR = BIT7;
    P3REN = ~BIT7;
    P3OUT = ~BIT7;
}


void change_button_state(button_function_t button, button_state_t new_state){
    for(uint8_t i = 0; i < BUTTON_NULL; i++){
        if(buttons[i].function == button){
            buttons[i].state = new_state;
        }
    }
}

void update_button_leds(){
    for(uint8_t i = 0; i < BUTTON_NULL; i++){
        switch(buttons[i].state){
        case BUTTON_STATE_OFF:
            neopixel_SetColor(buttons[i].assc_leds[0], COLOR_OFF);
            neopixel_SetColor(buttons[i].assc_leds[1], COLOR_OFF);
            break;
        case BUTTON_STATE_ON:

            break;
        case BUTTON_STATE_PRESSED:
            break;
        }
    }
}



uint8_t buttons_new_press = 0xff;

void update_press_from_interrupt(uint8_t port, uint8_t int_mask){
    for(uint8_t i = 0; i < BUTTON_NULL; i++){
        if(buttons[i].port == port){
            if(buttons[i].pin == int_mask){
                buttons_new_press = i;
                return;
            }
        }
    }
    buttons_new_press = 0xfe; //multiple buttons were pressed at once
}
button_function_t buttons_check(){
    button_function_t ret = BUTTON_NULL;
    if(buttons_new_press != 0xff){
        ret = buttons[buttons_new_press].function;
        buttons_new_press = 0xff;
    }
    return ret;
}


#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void){
    update_press_from_interrupt(2, P2IFG);
}
