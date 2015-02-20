/* Simple clock for sample timing. Uses the timer2 on an ATmega328P
 * microcontroller.
 */
	
#ifndef H_TIMER
#define H_TIMER

#include <stdint.h>

// Resolution of the timer, in seconds.
#define TIMER_RESOLUTION 0.001

// Interval is the length of time after which f will be called, in
// multiples of TIMER_RESOLUTION (if TIMER_RESOLUTION is unchanged,
// interval will be in milliseconds).
void timer_init(uint32_t interval, void(*f)());

void timer_start();

#endif
