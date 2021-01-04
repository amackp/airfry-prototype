/*
 * clock.c
 *
 *  Created on: Oct 24, 2017
 *      Author: mark
 */



#include "clock.h"
#include "config.h"
#include <msp430.h>
#include <stdint.h>

// If calibration constant erased do not load, trap CPU!!
#define CLOCK_CHECK(c) if (c==0xFF) {while(1);}

void clock_init() {

    switch (CONFIG_CLOCK_FREQUENCY) {

    case CLOCK_1MHZ:
        CLOCK_CHECK(CALBC1_1MHZ);
        BCSCTL1 = CALBC1_1MHZ;
        DCOCTL = CALDCO_1MHZ;
        break;

    case CLOCK_8MHZ:
        CLOCK_CHECK(CALBC1_8MHZ);
        BCSCTL1 = CALBC1_8MHZ;
        DCOCTL = CALDCO_8MHZ;
        break;

    case CLOCK_12MHZ:
        CLOCK_CHECK(CALBC1_12MHZ);
        BCSCTL1 = CALBC1_12MHZ;
        DCOCTL = CALDCO_12MHZ;
        break;

    case CLOCK_16MHZ:
        CLOCK_CHECK(CALBC1_16MHZ);
        BCSCTL1 &= BIT1; //ensure bit 1 is cleared
        BCSCTL1 |= 0x0d; //set RSELx to 13
        __delay_cycles(4);  //wait for new clock to settle
        BCSCTL1 = CALBC1_16MHZ |
                XTS * 0     |
                DIVA1 * 1  + DIVA0 * 1; //sets Divider for ACLK to 1/8 of the DCOCLT
        BCSCTL3 = LFXT1S1 * 1 | //enable VLOCLK when XTS == 0
                  LFXT1S0 * 0 ; //enable VLOCLK when XTS == 0
        DCOCTL  = CALDCO_16MHZ; //sets DCOCLT to 16MHZ
        __delay_cycles(4);  //wait for new clock to settle
        break;
    }


    //init timer for RTC
    //set timer 0 interrupt
    CCTL0 = CCIE;
    TACTL = TASSEL_2 + MC_1 + ID_3;           // SMCLK/8, upmode
    CCR0 =  62500;                            // T = 0.5 Hz. Finterrupt = FCD0/Divider /  CCR0 value
                                              //             Finterrupt =  1E6/8 / 62500 = 2 Hz
}

uint16_t rtc_miliseconds = 0;
inline void rtc_tick(){
    //check if the processor is running at 16MHz

    rtc_miliseconds+= 31;  //500/16.

    if (rtc_miliseconds >=1000){
        rtc_miliseconds = (rtc_miliseconds % 1000);
        g_uptime ++;
    }
}


//waits for x amount of miliseconds, calculated on the RTC clock source
void rtc_timer_ms( uint16_t ms){
    uint32_t end_time_s;
    uint32_t end_time_ms;

    end_time_ms = rtc_miliseconds + ms;
    if (end_time_ms > 1000){
        end_time_s = g_uptime + end_time_ms % 1000;
        end_time_ms = end_time_ms / 1000;
    }
    while (g_uptime < end_time_s &&
            rtc_miliseconds < end_time_ms );
}

extern void update_press_from_interrupt(uint8_t port, uint8_t int_mask);

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    //rtc_increment_half_second();
    rtc_tick();

    //check inputs on port3, bc we have no interrupt vector there
    if(P3IN != 0xff){
        update_press_from_interrupt(3, ~P3IN);
    }

    //LPM4_EXIT;
}
