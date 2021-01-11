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

    for(uint8_t j = 0; j < BUTTON_NULL; j++){
        buttons[j].debounce = 0;
    }

#if 1
    uint8_t i = 0;
    //AIRFRY
    buttons[i].port = 2;
    buttons[i].pin = BIT0;
    buttons[i].function = BUTTON_AIRFRY;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 32;
    buttons[i].assc_leds[1] = 31;
    buttons[i].type = TYPE_WHITE_BLUE;
    i++;

    //BAKE
    buttons[i].port = 2;
    buttons[i].pin = BIT1;
    buttons[i].function = BUTTON_BAKE;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 30;
    buttons[i].assc_leds[1] = 29;
    buttons[i].type = TYPE_WHITE_BLUE;
    i++;

    buttons[i].port = 2;
    buttons[i].pin = BIT2;
    buttons[i].function = BUTTON_ROAST;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 28;
    buttons[i].assc_leds[1] = 27;
    buttons[i].type = TYPE_WHITE_BLUE;
    i++;

    buttons[i].port = 2;
    buttons[i].pin = BIT4;
    buttons[i].function = BUTTON_DEHYDRATE;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 26;
    buttons[i].assc_leds[1] = 25;
    buttons[i].type = TYPE_WHITE_BLUE;
    i++;

    buttons[i].port = 2;
    buttons[i].pin = BIT3;
    buttons[i].function = BUTTON_PREHEAT;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 24;
    buttons[i].assc_leds[1] = 23;
    buttons[i].type = TYPE_WHITE_BLUE;
    i++;

    buttons[i].port = 2;
    buttons[i].pin = BIT5;
    buttons[i].function = BUTTON_TIME_UP;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 22;
    buttons[i].assc_leds[1] = 0xff;
    buttons[i].type = TYPE_WHITE;
    i++;

    buttons[i].port = 2;
    buttons[i].pin = BIT6;
    buttons[i].function = BUTTON_TIME_DOWN;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 21;
    buttons[i].assc_leds[1] = 0xff;
    buttons[i].type = TYPE_WHITE;
    i++;

    buttons[i].port = 2;
    buttons[i].pin = BIT7;
    buttons[i].function = BUTTON_STOP_CANCEL;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 20;
    buttons[i].assc_leds[1] = 19;
    buttons[i].type = TYPE_WHITE;
    i++;

    buttons[i].port = 3;
    buttons[i].pin = BIT0;
    buttons[i].function = BUTTON_POWER;
    buttons[i].state = BUTTON_STATE_ON;
    buttons[i].assc_leds[0] = 18;
    buttons[i].assc_leds[1] = 0xff;
    buttons[i].type = TYPE_WHITE;
    i++;

    buttons[i].port = 3;
    buttons[i].pin = BIT1;
    buttons[i].function = BUTTON_START;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 17;
    buttons[i].assc_leds[1] = 16;
    buttons[i].type = TYPE_WHITE;
    i++;

    buttons[i].port = 3;
    buttons[i].pin = BIT2;
    buttons[i].function = BUTTON_TURN_REM;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 15;
    buttons[i].assc_leds[1] = 14;
    buttons[i].type = TYPE_WHITE_BLUE;
    i++;

    buttons[i].port = 3;
    buttons[i].pin = BIT3;
    buttons[i].function = BUTTON_TEMP_DOWN;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 13;
    buttons[i].assc_leds[1] = 0xff;
    buttons[i].type = TYPE_WHITE;
    i++;

    buttons[i].port = 3;
    buttons[i].pin = BIT4;
    buttons[i].function = BUTTON_TEMP_UP;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 12;
    buttons[i].assc_leds[1] = 0xff;
    buttons[i].type = TYPE_WHITE;
    i++;

    buttons[i].port = 3;
    buttons[i].pin = BIT5;
    buttons[i].function = BUTTON_GRILL;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 11;
    buttons[i].assc_leds[1] = 10;
    buttons[i].type = TYPE_WHITE_RED;
    i++;

    buttons[i].port = 3;
    buttons[i].pin = BIT6;
    buttons[i].function = BUTTON_SMOKE_EXT;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 1;
    buttons[i].assc_leds[1] = 0;
    buttons[i].type = TYPE_WHITE_BLUE;
    i++;

    //NOT USED IN 4B
    buttons[i].port = 0;
    buttons[i].pin = BIT0;
    buttons[i].function = BUTTON_TIME_TEMP_TOGGLE;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 0xff;
    buttons[i].assc_leds[1] = 0xff;
    buttons[i].type = TYPE_WHITE;
    i++;

    buttons[i].port = 0;
    buttons[i].pin = BIT6;
    buttons[i].function = BUTTON_GRILL_LOW;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 9;
    buttons[i].assc_leds[1] = 8;
    buttons[i].type = TYPE_WHITE_RED;
    i++;

    buttons[i].port = 0;
    buttons[i].pin = BIT6;
    buttons[i].function = BUTTON_GRILL_MED;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 7;
    buttons[i].assc_leds[1] = 6;
    buttons[i].type = TYPE_WHITE_RED;
    i++;

    buttons[i].port = 0;
    buttons[i].pin = BIT6;
    buttons[i].function = BUTTON_GRILL_HIGH;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 5;
    buttons[i].assc_leds[1] = 4;
    buttons[i].type = TYPE_WHITE_RED;
    i++;

    buttons[i].port = 0;
    buttons[i].pin = BIT6;
    buttons[i].function = BUTTON_GRILL_MAX;
    buttons[i].state = BUTTON_STATE_OFF;
    buttons[i].assc_leds[0] = 3;
    buttons[i].assc_leds[1] = 2;
    buttons[i].type = TYPE_WHITE_RED;
#else
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
    P3REN = 0xff;
    P3OUT = 0xff;
}

button_state_t get_button_state(button_function_t button){
    for(uint8_t i = 0; i < BUTTON_NULL; i++){
        if(buttons[i].function == button){
            return buttons[i].state;
        }
    }
    return BUTTON_STATE_NULL;
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
            neopixel_SetColor(buttons[i].assc_leds[0], COLOR_BLACK);
            neopixel_SetColor(buttons[i].assc_leds[1], COLOR_BLACK);
            break;
        case BUTTON_STATE_ON:
            neopixel_SetColor(buttons[i].assc_leds[0], COLOR_RGB(50,50,50));
            neopixel_SetColor(buttons[i].assc_leds[1], COLOR_RGB(50,50,50));
            break;
        case BUTTON_STATE_PRESSED:
            if(buttons[i].type == TYPE_WHITE_BLUE){
                neopixel_SetColor(buttons[i].assc_leds[0], COLOR_RGB(0,0,75));
                neopixel_SetColor(buttons[i].assc_leds[1], COLOR_RGB(0,0,75));
            }
            else {//if(buttons[i].type == TYPE_WHITE_RED){
                neopixel_SetColor(buttons[i].assc_leds[0], COLOR_RGB(0,75,0));
                neopixel_SetColor(buttons[i].assc_leds[1], COLOR_RGB(0,75,0));
            }
            break;
        }
    }
}



uint8_t buttons_new_press = 0xff;

void button_decrement_debounce(){
    for(uint8_t i = 0; i < BUTTON_NULL; i++){
        if(buttons[i].debounce != 0){
            buttons[i].debounce--;
        }
    }
}

void update_press_from_interrupt(uint8_t port, uint8_t int_mask){
    for(uint8_t i = 0; i < BUTTON_NULL; i++){
        if(buttons[i].port == port){
            if(buttons[i].pin == int_mask){

                if(buttons[i].debounce == 0){
                    if(port == 2){
                        while(!(P2IN & buttons[i].pin)){
                            buttons[i].debounce++;
                            delay_ms(1);
                            if(buttons[i].debounce > 5){
                                break;
                            }
                        }
                        if(buttons[i].debounce > 5){
                            buttons[i].debounce = 0;
                            buttons_new_press = i;
                        }
                    }
                    else if(port == 3){
                        while(!(P3IN & buttons[i].pin)){
                            buttons[i].debounce++;
                            delay_ms(1);
                            if(buttons[i].debounce > 5){
                                break;
                            }
                        }
                        if(buttons[i].debounce > 5){
                            buttons[i].debounce = 0;
                            buttons_new_press = i;
                        }
                    }
                }
                return;
            }
        }
    }
    //buttons_new_press = 0xfe; //multiple buttons were pressed at once
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
    P2IFG = 0;
}
