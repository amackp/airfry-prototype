#include <msp430.h>				
#include "drivers/inc/MAX7219.h"
#include "drivers/inc/neopixel.h"
#include "drivers/inc/cap_buttons.h"
#include "utility/clock.h"
#include "utility/delay.h"

display_t display;

typedef enum{
    STATE_OFF = 0x00,
    STATE_IDLE,
    STATE_AIRFRY,
    STATE_BAKE,
    STATE_ROAST,
    STATE_DEHYDRATE,
    STATE_GRILL_LOW,
    STATE_GRILL_MED,
    STATE_GRILL_HIGH,
    STATE_GRILL_MAX,

    STATE_NULL
}ui_state_t;

typedef struct{
    ui_state_t current_state;
    ui_state_t last_state;

    //display info
    uint16_t temp;
    uint16_t time;
    uint16_t preheat_time;

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

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT

    clock_init();
    neopixel_Init();
    button_io_init();
    display_init();
    display_off(&display);
    ui.last_state = STATE_NULL;
    ui.current_state = STATE_OFF;

    P1DIR |= BIT1;
    P1OUT &= ~BIT1;

    P3DIR |= BIT7;
    P3OUT |= BIT7;
    P3REN &= ~BIT7;

    P2IFG = 0;
    __bis_SR_register(GIE); //enable global interrupts
    volatile int i = 0;

    for(uint8_t j = 0; j < 8; j++){
        display_set_digit(&display, j, DIG_8 | DOTS);
    }
    display_show_all_digits(&display);
    update_button_leds();
    neopixel_Show();

//    while(1){
//
//        if(i == 0){
//            neopixel_Clear();
//            neopixel_Show();
//        }
//        //buzzer_beep(1000);
//        P3OUT ^= BIT7;
//        display_off(&display);
//        display_show_all_digits(&display);
//
//        neopixel_SetColorAndShow(i, COLOR_RGB(50,50,50));
//        i = (i+1) % NEOPIXEL_LED_COUNT;
//
//        delay_ms(1000);
//        for(uint8_t j = 0; j < 8; j++){
//            display_set_digit(&display, j, DIG_8);
//        }
//        display_show_all_digits(&display);
//        P3OUT ^= BIT7;
//        delay_ms(1000);
//    }

	while(1)
	{
	    button_function_t new_function = buttons_check();
	    if(new_function != BUTTON_NULL){
	        change_button_state(new_function,(get_button_state(new_function)+1)%BUTTON_STATE_NULL);
	        update_button_leds();
	        neopixel_Show();
	        buzzer_beep(50);


	        display_off(&display);
	        display_set_digit(&display, i, DIG_8 | DOTS);
	        i = (i+1)%8;
	        display_show_all_digits(&display);

	    }
	    button_decrement_debounce();

//	    switch(new_function){
//	    case BUTTON_STOP_CANCEL:
//	        break;
//	    case BUTTON_START:
//	        break;
//	    case BUTTON_POWER:
//	        break;
//	    case BUTTON_TIME_UP:
//	        break;
//	    case BUTTON_TIME_DOWN:
//	        break;
//	    case BUTTON_TEMP_UP:
//	        break;
//	    case BUTTON_TEMP_DOWN:
//	        break;
//	    case BUTTON_SMOKE_EXT:
//	        break;
//	    case BUTTON_TIME_TEMP_TOGGLE:
//	        break;
//	    case BUTTON_TURN_REM:
//	        break;
//	    case BUTTON_AIRFRY:
//	        break;
//	    case BUTTON_BAKE:
//	        break;
//	    case BUTTON_ROAST:
//	        break;
//	    case BUTTON_DEHYDRATE:
//	        break;
//	    case BUTTON_PREHEAT:
//	        break;
//	    case BUTTON_GRILL:
//	        break;
//	    default:
//	        break;
//	    }

//	    switch(ui.current_state){
//	    case STATE_OFF:
//	        if(ui.last_state != STATE_OFF){
//	            display_off(&display);
//	            neopixel_Clear();
//	            neopixel_Show();
//	        }
//	        break;
//	    case STATE_IDLE:
//	        if(ui.last_state != STATE_IDLE){
//
//	        }
//	    }

	}
}
