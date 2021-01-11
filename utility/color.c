/*
 * color.c
 *
 *  Created on: Jan 6, 2021
 *      Author: abema
 */

#include "color.h"

color_t color_Interp(color_t color_start, color_t color_stop, uint16_t step){
    color_t color_out;
    if(step >= 250){
        return color_stop;
    }
    color_out.red = (color_start.red&(255-step)) | (color_stop.red&step);
    color_out.green = (color_start.green&(255-step)) | (color_stop.green&step);
    color_out.blue = (color_start.blue&(255-step)) | (color_stop.blue&step);
    return color_out;
}


