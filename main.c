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
    STATE_SELECTION,
    STATE_ACTIVE
}ui_state_t;

typedef enum{
    CYCLE_NULL,
    CYCLE_AIRFRY,
    CYCLE_BAKE,
    CYCLE_ROAST,
    CYCLE_DEHYDRATE,
    CYCLE_GRILL_LOW,
    CYCLE_GRILL_MED,
    CYCLE_GRILL_MAX
}cycle_state_t;

typedef struct{
    ui_state_t current_state;
    ui_state_t last_state;

    button_function_t active_function;

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
    display_show(&display);
    update_button_leds();
    neopixel_Show();

	while(1)
	{
	    button_function_t new_function = buttons_check();
	    button_decrement_debounce();

	    switch(ui.current_state){
	    case STATE_OFF:
	        if(ui.last_state != STATE_OFF){
	            display_clear(&display);
	            display_show(&display);
	            neopixel_Clear();
	            neopixel_Show();
	        }
	        switch(new_function){
                case BUTTON_POWER:
                    buttons_idle_state();
                    display_set_digit(&display, 2, DIG_0);
                    display_set_digit(&display, 3, CHAR_N);
                    display_show(&display);
                    neopixel_Show();
                    ui.current_state = STATE_IDLE;
                    ui.active_cycle = CYCLE_NULL;
                    break;
	        }
	        break;
	    case STATE_IDLE:
	        if(ui.last_state != STATE_IDLE){

	        }

	        switch(new_function){
	        case BUTTON_POWER:
	            ui.current_state = STATE_OFF;
	            break;
	        case BUTTON_AIRFRY:
	            ui.active_cycle = new_function;
	            buttons_idle_state();
	            change_button_state(BUTTON_AIRFRY, BUTTON_STATE_PRESSED);
	            ui.current_state = STATE_SELECTION;

	        }
	    }

	    ui.last_state = ui.current_state;

	}
}
