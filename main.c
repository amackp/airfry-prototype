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

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;   // Stop WDT


    clock_init();
    neopixel_Init();

    display_init();
    display_off(&display);
    ui.last_state = STATE_NULL;
    ui.current_state = STATE_OFF;

    __bis_SR_register(GIE); //enable global interrupts

	while(1)
	{
	    button_function_t new_function = buttons_check();
	    switch(new_function){
	    case BUTTON_STOP_CANCEL:
	        break;
	    case BUTTON_START:
	        break;
	    case BUTTON_POWER:
	        break;
	    case BUTTON_TIME_UP:
	        break;
	    case BUTTON_TIME_DOWN:
	        break;
	    case BUTTON_TEMP_UP:
	        break;
	    case BUTTON_TEMP_DOWN:
	        break;
	    case BUTTON_SMOKE_EXT:
	        break;
	    case BUTTON_TIME_TEMP_TOGGLE:
	        break;
	    case BUTTON_TURN_REM:
	        break;
	    case BUTTON_AIRFRY:
	        break;
	    case BUTTON_BAKE:
	        break;
	    case BUTTON_ROAST:
	        break;
	    case BUTTON_DEHYDRATE:
	        break;
	    case BUTTON_PREHEAT:
	        break;
	    case BUTTON_GRILL:
	        break;
	    default:
	        break;
	    }

	    switch(ui.current_state){
	    case STATE_OFF:
	        if(ui.last_state != STATE_OFF){
	            display_off(&display);
	            neopixel_Clear();
	            neopixel_Show();
	        }
	        break;
	    case STATE_IDLE:
	        if(ui.last_state != STATE_IDLE){

	        }
	    }

	}
}
