/*
 * color.h
 *
 *  Created on: Nov 28, 2016
 *      Author: mark
 */

#ifndef COLOR_H_
#define COLOR_H_


typedef struct {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} COLOR;


#define BLACK       ((COLOR){0x00,0x00,0x00})
#define COLOR_OFF   BLACK

#define RED         ((COLOR){0xFF,0x00,0x00})
#define RED_50      ((COLOR){0x7F,0x00,0x00})
#define RED_10      ((COLOR){0x19,0x00,0x00})

#define GREEN       ((COLOR){0x00,0xFF,0x00})
#define GREEN_50    ((COLOR){0x00,0x7F,0x00})
#define GREEN_10    ((COLOR){0x00,0x19,0x00})

#define BLUE        ((COLOR){0x00,0x00,0xFF})
#define BLUE_50     ((COLOR){0x00,0x00,0x7F})
#define BLUE_10     ((COLOR){0x00,0x00,0x19})
#define BLUE_01     ((COLOR){0x00,0x00,0x03})


#define PURPLE      ((COLOR){0xFF,0x00,0xFF})
#define ORANGE      ((COLOR){0xFF,0x7F,0x00})

#define WHITE       ((COLOR){0xFF,0xFF,0xFF})



#endif /* COLOR_H_ */
