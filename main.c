#include <msp430.h>				
#include "drivers/inc/MAX7219.h"
#include "drivers/inc/neopixel.h"
#include "drivers/inc/cap_buttons.h"
#include "utility/clock.h"
#include "utility/delay.h"
#include "utility/math.h"

display_t display;

#define BEEP_SHORT 50
#define BEEP_LONG 150

typedef enum{
    STATE_OFF = 0x00,
    STATE_IDLE,
    STATE_PREHEAT,
    STATE_ADDFOOD,
    STATE_COOKING,
    STATE_END,
    STATE_PAUSED
}ui_state_t;

typedef struct{
    ui_state_t current_state;
    ui_state_t last_state;

    button_function_t active_function;

    //display info
    uint16_t temp;
    uint16_t time;
    uint8_t preheat_time;

    //feature flags
    uint8_t turn_reminder:1;
    uint8_t smoke_extract:1;

    //user config fields
    uint8_t turn_edit:1;
    uint8_t smoke_edit:1;
    uint8_t temp_edit:1;

    uint16_t time_min;
    uint16_t time_max;

    uint16_t temp_min;
    uint16_t temp_max;
}ui_struct_t;

ui_struct_t ui;

void buzzer_beep(uint16_t time){
    P1DIR |= BIT0;
    P1OUT |= BIT0;
    delay_ms(time);
    P1OUT &= ~BIT0;
    //P1DIR &= ~BIT0;
}

static const display_character_t digits_order[10] = {
                                        DIG_0,
                                        DIG_1,
                                        DIG_2,
                                        DIG_3,
                                        DIG_4,
                                        DIG_5,
                                        DIG_6,
                                        DIG_7,
                                        DIG_8,
                                        DIG_9,
};

void display_preheat(){
    display_set_digit(&display, 0, CHAR_NULL);
    display_set_digit(&display, 1, CHAR_P);
    display_set_digit(&display, 2, CHAR_R);
    display_set_digit(&display, 3, CHAR_E);
    display_set_digit(&display, 4, CHAR_H);
    display_set_digit(&display, 5, CHAR_E);
    display_set_digit(&display, 6, CHAR_A);
    display_set_digit(&display, 7, CHAR_T);

}

void display_addfood(){
    display_set_digit(&display, 0, CHAR_NULL);
    display_set_digit(&display, 1, CHAR_A);
    display_set_digit(&display, 2, CHAR_D);
    display_set_digit(&display, 3, CHAR_D);
    display_set_digit(&display, 4, CHAR_F);
    display_set_digit(&display, 5, CHAR_O_LOWER);
    display_set_digit(&display, 6, CHAR_O_LOWER);
    display_set_digit(&display, 7, CHAR_D);
}

void display_turnfood(){
    display_set_digit(&display, 0, CHAR_T);
    display_set_digit(&display, 1, CHAR_U);
    display_set_digit(&display, 2, CHAR_R);
    display_set_digit(&display, 3, CHAR_N_LOWER);
    display_set_digit(&display, 4, CHAR_F);
    display_set_digit(&display, 5, CHAR_O_LOWER);
    display_set_digit(&display, 6, CHAR_O_LOWER);
    display_set_digit(&display, 7, CHAR_D);
}

void display_end(){
    display_clear(&display);
    display_set_digit(&display, 5, CHAR_E);
    display_set_digit(&display, 6, CHAR_N_LOWER);
    display_set_digit(&display, 7, CHAR_D);
}

void display_time_remaining(uint32_t time){
    uint16_t hours, minutes, seconds;
    uint8_t inc_dots = g_uptime&BIT0?DOTS:CHAR_NULL;
    int i, dig;
    if(time >= 60*60){
        hours = time/(60*60);
        minutes = (time/60)%60;
        i = 3;
        while(i >= 2){
           if(minutes <= 0){
               display_set_digit(&display, i, DIG_0|inc_dots);
           }
           else{
               dig = minutes%10;
               display_set_digit(&display, i, digits_order[dig]|inc_dots);
               minutes = minutes/10;
           }
           i--;
        }
        while(i >=0){
           if(hours <= 0){
               display_set_digit(&display, i, DIG_0|inc_dots);
           }
           else{
               dig = hours%10;
               display_set_digit(&display, i, digits_order[dig]|inc_dots);
               hours = hours/10;
           }
           i--;
        }
    }
    else{
        minutes = time/60;
        seconds = time%60;
        i = 3;
        while(i >= 2){
           if(seconds <= 0){
               display_set_digit(&display, i, DIG_0|inc_dots);
           }
           else{
               dig = seconds%10;
               display_set_digit(&display, i, digits_order[dig]|inc_dots);
               seconds = seconds/10;
           }
           i--;
        }
        while(i >=0 ){
           if(minutes <= 0){
               display_set_digit(&display, i, DIG_0|inc_dots);
           }
           else{
               dig = minutes%10;
               display_set_digit(&display, i, digits_order[dig]|inc_dots);
               minutes = minutes/10;
           }
           i--;
        }
    }
}

void display_show_temp_time(){
    int temp = ui.temp;
    int i = 6;
    int dig = 0;
    while(i >=4 ){
       if(temp <= 0){
           display_set_digit(&display, i, DIG_0);
       }
       else{
           dig = temp%10;
           display_set_digit(&display, i, digits_order[dig]);
           temp = temp/10;
       }
       i--;
    }
    display_set_digit(&display, 7, CHAR_F);

    temp = ui.time%60;
    while(i>=2){

        if(temp <= 0){
            display_set_digit(&display, i, DIG_0|DOTS);
        }
        else{
            dig = temp%10;
            display_set_digit(&display, i, digits_order[dig]|DOTS);
            temp = temp/10;
        }
        i--;
    }
    if(ui.time > 60){
        temp = ui.time/60;
        while(i>=0){

            if(temp <= 0){
                display_set_digit(&display, i, DIG_0|DOTS);
            }
            else{
                dig = temp%10;
                display_set_digit(&display, i, digits_order[dig]|DOTS);
                temp = temp/10;
            }
            i--;
        }
    }
    else{
        display_set_digit(&display, 0, DIG_0 | DOTS);
        display_set_digit(&display, 1, DIG_0 | DOTS);
    }


}

void show_leds_displays(){
    display_show(&display);
    neopixel_Show();
}

void set_idle_state(){
    buttons_idle_state();
    display_clear(&display);
    display_set_digit(&display, 2, DIG_0);
    display_set_digit(&display, 3, CHAR_N);
    show_leds_displays();
    update_state(STATE_IDLE);
    ui.active_function = BUTTON_NULL;
}

void set_temp(uint16_t temp, uint16_t min, uint16_t max){
    ui.temp = temp;
    ui.temp_max = max;
    ui.temp_min = min;
    ui.temp_edit = (min!=max);
}

void set_time(uint16_t time, uint8_t preheat, uint16_t time_min, uint16_t time_max){
    ui.preheat_time = preheat;
    ui.time = time;
    ui.time_min = time_min;
    ui.time_max = time_max;
}

void set_flags(bool turn, bool fan, bool turn_edit, bool fan_edit){
    ui.turn_reminder = turn;
    ui.smoke_extract = fan;
    ui.turn_edit = turn_edit;
    ui.smoke_edit = fan_edit;
}

void update_state(ui_state_t new_state){
    ui.last_state = ui.current_state;
    ui.current_state = new_state;
}

uint32_t preheat_entry = 0;
uint32_t add_entry = 0;
uint32_t pause_entry = 0;
uint32_t cook_entry = 0;

int32_t cooking_time_remaining = 0;
uint32_t cooking_time_total = 0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT

    clock_init();
    neopixel_Init();
    button_io_init();
    display_init();
    ui.last_state = STATE_COOKING;
    ui.current_state = STATE_OFF;
    P1DIR |= BIT1;
    P1OUT &= ~BIT1;

    P3DIR |= BIT7;
    P3OUT |= BIT7;
    P3REN &= ~BIT7;

    P2IFG = 0;
    __bis_SR_register(GIE); //enable global interrupts
    volatile int i = 0;
//    while(0){
//        button_function_t new_function = buttons_check();
//        //button_decrement_debounce();
//        if(new_function != BUTTON_NULL){
//            change_button_state(new_function,(get_button_state(new_function)+1)%BUTTON_STATE_NULL);
//            update_button_leds();
//            neopixel_Show();
//            //buzzer_beep(50);
//
//
//            display_clear(&display);
//            display_set_digit(&display, i, DIG_8 | DOTS);
//            i = (i+1)%8;
//            display_show(&display);
//        }
//        button_decrement_debounce();
//    }

	while(1)
	{
	    button_function_t new_function = buttons_check();
	    button_decrement_debounce();

	    switch(ui.current_state){
	    case STATE_OFF:
	        if(ui.last_state != STATE_OFF){
	            ui.last_state = STATE_OFF;
	            display_clear(&display);
	            buttons_off_state();
	            show_leds_displays();
	        }
	        switch(new_function){
                case BUTTON_POWER:
                    set_idle_state();
                    buzzer_beep(BEEP_SHORT);
                    break;
                default:
                    break;
	        }

	        break;
	    case STATE_IDLE:
	        if(ui.last_state != STATE_IDLE){
	            ui.last_state = STATE_IDLE;
	            set_idle_state();
	        }
	        if(new_function != BUTTON_NULL){
	            if(ui.active_function == BUTTON_NULL && new_function > BUTTON_POWER){
	                break;
	            }
	            if(new_function != BUTTON_GRILL && new_function == ui.active_function){
                    set_idle_state();
                    break;
	            }

	            switch(new_function){
	            case BUTTON_POWER:
	                update_state(STATE_OFF);
	                buzzer_beep(BEEP_SHORT);
	                break;
	            case BUTTON_AIRFRY:
	                ui.active_function = new_function;

	                set_time(20, 2, 1, 60);
	                set_temp(400, 170, 400);
	                set_flags(1, 0, 1, 0);
	                break;
	            case BUTTON_BAKE:
                    ui.active_function = new_function;

                    set_time(20, 2, 1, 120);
                    set_temp(350, 170, 400);
                    set_flags(0, 0, 1, 0);

	                break;
	            case BUTTON_ROAST:
                    ui.active_function = new_function;

                    set_time(25, 2, 1, 120);
                    set_temp(400, 170, 400);
                    set_flags(1, 0, 1, 0);

	                break;
	            case BUTTON_DEHYDRATE:
                    ui.active_function = new_function;

                    set_time(60*8, 0, 30, 60*24);
                    set_temp(135, 90, 170);
                    set_flags(0, 0, 1, 0);
	                break;
	            case BUTTON_PREHEAT:
	                //not sure
	                if(ui.active_function != BUTTON_DEHYDRATE){
	                    if(ui.preheat_time != 0){
	                        ui.preheat_time = 0;
	                    }
	                    else{
	                        ui.preheat_time = 2;
	                    }
	                }
	                break;
	            case BUTTON_GRILL:
	                switch(ui.active_function){
	                case BUTTON_GRILL_LOW:
                        ui.active_function = BUTTON_GRILL_MED;
                        set_temp(450, 450, 450);
	                    break;
	                case BUTTON_GRILL_MED:
                        ui.active_function = BUTTON_GRILL_HIGH;
                        set_temp(500, 500, 500);
	                    break;
	                case BUTTON_GRILL_HIGH:
                        ui.active_function = BUTTON_GRILL_MAX;
                        set_temp(510, 510, 510);
	                    break;
	                case BUTTON_GRILL_MAX:
	                    set_idle_state();
                        break;
	                default:
	                    ui.active_function = BUTTON_GRILL_LOW;
	                    set_temp(400, 400, 400);
	                    set_time(10, 2, 1, 60);
	                    set_flags(1, 1, 1, 1);
	                    break;
	                }
	                break;
	            case BUTTON_TIME_UP:
	                buzzer_beep(BEEP_SHORT);
                    do{
                        ui.time = min(ui.time+1, ui.time_max);
                            display_show_temp_time();
                            display_show(&display);
                            delay_ms(BUTTON_PRESS_DELAY);
                    }
                    while(button_check_for_holding(new_function)==new_function);
	                break;
	            case BUTTON_TIME_DOWN:
	                buzzer_beep(BEEP_SHORT);
                    do{
                        ui.time = max(ui.time-1, ui.time_min);
                            display_show_temp_time();
                            display_show(&display);
                            delay_ms(BUTTON_PRESS_DELAY);
                    }
                    while(button_check_for_holding(new_function)==new_function);
	                break;
	            case BUTTON_TEMP_UP:
	                buzzer_beep(BEEP_SHORT);
                    do{
                        ui.temp = min(ui.temp+5, ui.temp_max);
                            display_show_temp_time();
                            display_show(&display);
                            delay_ms(BUTTON_PRESS_DELAY);
                    }
                    while(button_check_for_holding(new_function)==new_function);
	                break;
	            case BUTTON_TEMP_DOWN:
	                buzzer_beep(BEEP_SHORT);
                    do{
                            ui.temp = max(ui.temp-5, ui.temp_min);
                            display_show_temp_time();
                            display_show(&display);
                            delay_ms(BUTTON_PRESS_DELAY);
                    }
                    while(button_check_for_holding(new_function)==new_function);
	                break;
	            case BUTTON_STOP_CANCEL:
	                break;
	            case BUTTON_START:
	                if(ui.active_function != BUTTON_NULL){
	                    if(ui.preheat_time > 0){
	                        update_state(STATE_PREHEAT);
	                    }
	                    else{
	                        update_state(STATE_ADDFOOD);
	                    }

	                }
	                break;
	            case BUTTON_SMOKE_EXT:
	                if(ui.smoke_edit){
	                    ui.smoke_extract = !ui.smoke_extract;
	                }
	                break;
	            case BUTTON_TURN_REM:
	                if(ui.turn_edit){
	                    ui.turn_reminder = !ui.turn_reminder;
	                }
	                break;
	            case BUTTON_TIME_TEMP_TOGGLE:
	                break;
	            }
	            if(ui.active_function != BUTTON_NULL){
	                buttons_selection_state(ui.active_function, ui.turn_reminder, ui.smoke_extract, ui.preheat_time);
	                if(ui.active_function >= BUTTON_GRILL_LOW){
	                    change_button_state(BUTTON_GRILL, BUTTON_STATE_PRESSED);
	                }
	                display_show_temp_time();
	                show_leds_displays();
	            }
	        }
	        break;
	    case STATE_PREHEAT:
	        if(ui.last_state != STATE_PREHEAT){
	            ui.last_state = STATE_PREHEAT;
	            preheat_entry = g_uptime;
	            buttons_running_state(ui.active_function, ui.turn_reminder, ui.smoke_extract, ui.preheat_time);
	            display_preheat();
	            show_leds_displays();
	        }

	        if((g_uptime - preheat_entry) > (ui.preheat_time*60)){
	            ui.preheat_time = 0;
	            update_state(STATE_ADDFOOD);
	            break;
	        }

	        switch(new_function){
	        case BUTTON_STOP_CANCEL:
	            pause_entry = g_uptime;
	            update_state(STATE_PAUSED);
	            change_button_state(BUTTON_START, BUTTON_STATE_ON);
	            break;
	        case BUTTON_POWER:
	            update_state(STATE_OFF);
	            break;
	        }

	        break;
        case STATE_PAUSED:
            switch(ui.last_state){
            case STATE_COOKING:
                display_show_temp_time();
                g_uptime&BIT0?display_time_remaining(cooking_time_remaining):display_clear(&display);
                break;
            case STATE_PREHEAT:
                g_uptime&BIT0?display_preheat():display_clear(&display);
            }
            show_leds_displays();

            switch(new_function){
            case BUTTON_STOP_CANCEL:
                update_state(STATE_IDLE);
                break;
            case BUTTON_START:
                ui.current_state = ui.last_state;
                change_button_state(BUTTON_START, BUTTON_STATE_OFF);
                show_leds_displays();
                if(ui.last_state == STATE_PREHEAT){
                    preheat_entry += g_uptime - pause_entry;
                }
                else{
                    cook_entry += g_uptime - pause_entry;
                }
                break;
            }
            break;
        case STATE_ADDFOOD:
            if(ui.last_state != STATE_ADDFOOD){
                ui.last_state = STATE_ADDFOOD;
                add_entry = g_uptime;
                buttons_running_state(ui.active_function, ui.turn_reminder, ui.smoke_extract, ui.preheat_time);
                show_leds_displays();
            }
            for(uint8_t i = 0 ; i < 5; i++){
                display_addfood();
                display_show(&display);
                buzzer_beep(BEEP_LONG);
                delay_ms(1000-BEEP_LONG);
                display_clear(&display);
                display_show(&display);
                delay_ms(1000);
            }
            update_state(STATE_COOKING);
            break;
        case STATE_COOKING:
            if(ui.last_state != STATE_COOKING){
                ui.last_state = STATE_COOKING;
                cook_entry = g_uptime;
                cooking_time_total = ui.time*60;
                buttons_running_state(ui.active_function, ui.turn_reminder, ui.smoke_extract, ui.preheat_time);
                display_show_temp_time();
            }
            cooking_time_remaining = cooking_time_total - (g_uptime - cook_entry);

            if(cooking_time_remaining + 1 == (cooking_time_total/2) && ui.turn_reminder){
                ui.turn_reminder = false;
                for(uint8_t i = 0 ; i < 5; i++){
                    display_clear(&display);
                    display_show(&display);
                    delay_ms(1000);
                    display_turnfood();
                    display_show(&display);
                    buzzer_beep(BEEP_LONG);
                    delay_ms(1000-BEEP_LONG);
                }
                display_clear(&display);
                display_show(&display);

                delay_ms(1000);

                display_show_temp_time();
                buttons_running_state(ui.active_function, ui.turn_reminder, ui.smoke_extract, ui.preheat_time);
                cook_entry += 10;
            }

            display_time_remaining(cooking_time_remaining);


            if(cooking_time_remaining <= 0){
                update_state(STATE_END);
            }

            switch(new_function){
            case BUTTON_STOP_CANCEL:
                pause_entry = g_uptime;
                update_state(STATE_PAUSED);
                change_button_state(BUTTON_START, BUTTON_STATE_ON);
                break;
            }
            show_leds_displays();

            break;
        case STATE_END:
            if(ui.last_state != STATE_END){

                buttons_running_state(ui.active_function, ui.turn_reminder, ui.smoke_extract, 0);
                show_leds_displays();
                for(uint8_t i = 0 ; i < 5; i++){
                    display_clear(&display);
                    display_show(&display);
                    delay_ms(1000);
                    display_end();
                    display_show(&display);
                    buzzer_beep(BEEP_LONG);
                    delay_ms(1000-BEEP_LONG);
                }
                buttons_idle_state();
                show_leds_displays();
                ui.last_state = STATE_IDLE;
                ui.current_state = STATE_IDLE;
                ui.active_function = BUTTON_NULL;
            }
            break;
	}
	}
}
