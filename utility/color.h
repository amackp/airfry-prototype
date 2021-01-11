/*
 * color.h
 *
 *  Created on: Nov 28, 2016
 *      Author: mark
 */

#ifndef COLOR_H_
#define COLOR_H_


#include <stdint.h>

typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} color_t;

#define COLOR_RGB(r,g,b)   ((color_t){g, r, b })      // adjust component order
#define COLOR_HEX(value)   ((color_t){ ((value & 0x00FF00) >> 8), ((value & 0xFF0000) >> 16), (value & 0x0000FF) })


#define COLOR_RED           COLOR_HEX(0xFF0000)
#define COLOR_GREEN         COLOR_HEX(0x00FF00)
#define COLOR_BLUE          COLOR_HEX(0x0000FF)
#define COLOR_PURPLE        COLOR_HEX(0xFF00FF)
#define COLOR_ORANGE        COLOR_HEX(0xFF3000)
#define COLOR_YELLOW        COLOR_HEX(0xFFB000)
#define COLOR_CYAN          COLOR_HEX(0x42F4BF)
#define COLOR_CYAN_TRUE     COLOR_HEX(0x00FFFF)
#define COLOR_PINK          COLOR_HEX(0x99140C)                                                                                           `


#define COLOR_PASTEL_RED        COLOR_HEX(0xFF1010)
#define COLOR_PASTEL_GREEN      COLOR_HEX(0x00FF10)
#define COLOR_PASTEL_BLUE       COLOR_HEX(0x1000FF)

#define COLOR_WHITE         COLOR_HEX(0xFFFFFF)
#define COLOR_BLACK         COLOR_HEX(0x000000)


#endif /* COLOR_H_ */
