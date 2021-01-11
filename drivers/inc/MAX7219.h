/*
 * MAX7219.h
 *
 *  Created on: Jan 3, 2021
 *      Author: abema
 */

#ifndef DRIVERS_INC_MAX7219_H_
#define DRIVERS_INC_MAX7219_H_

#include <msp430.h>
#include <stdint.h>

#define MAX_REG_DIGIT0      0x01
#define MAX_REG_DIGIT1      0x02
#define MAX_REG_DIGIT2      0x03
#define MAX_REG_DIGIT3      0x04
#define MAX_REG_DIGIT4      0x05
#define MAX_REG_DIGIT5      0x06
#define MAX_REG_DIGIT6      0x07
#define MAX_REG_DIGIT7      0x08
#define MAX_REG_DECODEMODE  0x09
#define MAX_REG_INTENSITY   0x0A
#define MAX_REG_SCANLIMIT   0x0B
#define MAX_REG_SHUTDOWN    0x0C
#define MAX_REG_DISPLAYTEST 0x0F

#define SCAN_LIMIT_ALL 0x07

#define DISPLAY_NUM_DIGITS  8

typedef enum{
    NO_DECODE = 0,
    ALL_DECODE = 0xff
}display_decode_t;

typedef enum{
    CHAR_NULL = 0x00,

    DIG_0 = 0b01111110,
    DIG_1 = 0b00110000,
    DIG_2 = 0b01101101,
    DIG_3 = 0b01111001,
    DIG_4 = 0b00110011,
    DIG_5 = 0b01011011,
    DIG_6 = 0b01011111,
    DIG_7 = 0b01110000,
    DIG_8 = 0b01111111,
    DIG_9 = 0b01111011,

    CHAR_F = 0b01000111,
    CHAR_N = 0b01110110,
    CHAR_P = 0b01100111,
    CHAR_R = 0b00000101,
    CHAR_E = 0b01001111,
    CHAR_H = 0b00110111,
    CHAR_A = 0b01110111,
    CHAR_T = 0b00001111,
    CHAR_D = 0b00111101,
    CHAR_U = 0b00011100,
    CHAR_O_LOWER = 0b00011110,

    CHAR_DASH = 0b00000001,

    DOTS = 0b10000000
}display_character_t;


typedef enum{
    DUTY_1 = 0,
    DUTY_2,
    DUTY_3,
    DUTY_4,
    DUTY_5,
    DUTY_6,
    DUTY_7,
    DUTY_8,
    DUTY_9,
    DUTY_10,
    DUTY_11,
    DUTY_12,
    DUTY_13,
    DUTY_14,
    DUTY_15,
    DUTY_MAX
}display_intensity_t;

typedef struct{
    display_character_t digit[DISPLAY_NUM_DIGITS];
}display_t;


#define MAX_REG_DECODEMODE  0x09
#define MAX_REG_INTENSITY   0x0A
#define MAX_REG_SCANLIMIT   0x0B
#define MAX_REG_SHUTDOWN    0x0C
typedef struct{
    display_decode_t decode_mode;
    display_intensity_t intensity;
    uint8_t scan_limit;
    uint8_t shutdown;
}display_config_t;

display_config_t g_display_config;

void display_init();

void display_write_config(display_config_t config);
void display_show_all_digits(display_t * disp);
void display_set_digit(display_t * disp, uint8_t index, display_character_t value);
void display_off(display_t * disp);
void display_test_mode(uint8_t on);

#endif /* DRIVERS_INC_MAX7219_H_ */
