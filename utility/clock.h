/*
 * clock.h
 *
 *  Created on: Dec 14, 2016
 *      Author: mark
 */

#ifndef SYSTEM_CLOCK_H_
#define SYSTEM_CLOCK_H_

#include <msp430.h>
#include <stdint.h>

#define CLOCK_1MHZ      1
#define CLOCK_8MHZ      8
#define CLOCK_12MHZ     12
#define CLOCK_16MHZ     16

uint32_t g_uptime;

/**@brief Function selecting the clock frequency.
 *
 */
void clock_init();


#endif /* SYSTEM_CLOCK_H_ */
