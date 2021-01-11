/*
 * spi.c
 *
 *  Created on: Jan 2, 2021
 *      Author: abema
 */

#include "../inc/MAX7219.h"
#include "../../utility/delay.h"

void display_init()
{
    //Configuration of USCI for SPI
    P1SEL |= BIT2 + BIT4;                 //Uset pins MOSI and MISO SCA0CLK to USCI control
    P1SEL2 |= BIT2 + BIT4;                //Uset pins MOSI and MISO SCA0CLK to USCI control

    UCA0CTL1 = UCSWRST;                          // USCI logic held in reset state
    UCA0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC; // 3-pin, 8-bit SPI master, MSB
    UCA0CTL1 |= UCSSEL_3;                        // BRCLK (source of SPI clock) is set to be the  SMCLK
    UCA0BR0 |= 0x40;                             // Divide clock by 64.  SPI transmission = 0.125Mhz, when operating at 8MHZ
    UCA0BR1 = 0;                                 //
    UCA0MCTL = 0;                                // No modulation
    UCA0CTL1 &= ~UCSWRST;                        // Software reset  Disabled. USCI reset released for operation.

    //LOAD pin config, uses rising edge to load data into max7219
    P1SEL &= ~BIT3;
    P1SEL2 &= ~BIT3;
    P1DIR |= BIT3;
    P1OUT &= ~BIT3;

    //set initial config
    g_display_config.decode_mode = NO_DECODE;
    g_display_config.intensity = DUTY_4;
    g_display_config.scan_limit = SCAN_LIMIT_ALL;
    g_display_config.shutdown = 0x01;

    display_write_config(g_display_config);
    display_test_mode(0);

}


void spi_Write_Reg(uint8_t addr, uint8_t data)
{
    while (!(IFG2 & UCA0TXIFG));            // wait for TX buff
    UCA0TXBUF = addr;                      // send data byte over MOSI

    while (!(IFG2 & UCA0TXIFG));            // wait for TX buff
    UCA0TXBUF = data;                      // send data byte over MOSI

    while (UCA0STAT & UCBUSY);              // wait for TX to finish

    //trigger LOAD pin to ingest data
    P1OUT |= BIT3;
    delay_us(100);
    P1OUT &= ~BIT3;
}

void display_write_config(display_config_t config){
    spi_Write_Reg(MAX_REG_DECODEMODE, config.decode_mode);
    spi_Write_Reg(MAX_REG_INTENSITY, config.intensity);
    spi_Write_Reg(MAX_REG_SCANLIMIT, config.scan_limit);
    spi_Write_Reg(MAX_REG_SHUTDOWN, config.shutdown);
}

void display_show_all_digits(display_t * disp){

    for(uint8_t i = 0; i < DISPLAY_NUM_DIGITS; i++){
        spi_Write_Reg(MAX_REG_DIGIT0+i, disp->digit[i]);
    }
}

void display_set_digit(display_t * disp, uint8_t index, display_character_t value){
    disp->digit[index] = value;
}

void display_off(display_t * disp){
    for(uint8_t i = 0; i < DISPLAY_NUM_DIGITS; i++){
        disp->digit[i] = CHAR_NULL;
    }

    display_show_all_digits(disp);
}

void display_test_mode(uint8_t on){
    if(on){
        spi_Write_Reg(MAX_REG_DISPLAYTEST, 0x01);
    }
    else{
        spi_Write_Reg(MAX_REG_DISPLAYTEST,0x00);
    }
}

