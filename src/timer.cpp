#include <stdint.h>
#include <avr/interrupt.h>

#include "timer.h"

#define CLEAR_BIT(x, bit) x &= ~(1 << bit)
#define SET_BIT(x, bit) x |= (1 << bit)

// Number of times the counter has timer_overflowed.
volatile uint32_t timer_ticks;
// Number of times the counter must overflow before triggering the
// timer.
volatile uint32_t timer_interval;
// 1 if the counter is currently timer_overflowed, else 0.
volatile uint8_t timer_overflowed;
// Function to call when the timer is triggered.
void (*timer_func)();
// Value we store in the TCNT2 register to overflow at the correct time.
volatile uint8_t tcnt2_init;

void timer_init(uint32_t interval, void (*f)())
{
	timer_ticks = 0;
	timer_overflowed = 0;
	timer_func = f;
	timer_interval = interval;

	// Disable overflow interrupt (until we actually want to start
	// the timer).
	CLEAR_BIT(TIMSK2, TOIE2);
	// Ensure we're in normal counter mode.
	CLEAR_BIT(TCCR2A, WGM21);
	CLEAR_BIT(TCCR2A, WGM20);
	CLEAR_BIT(TCCR2B, WGM22);
	// Use the IO clock rather than an external oscillator.
	CLEAR_BIT(ASSR, AS2);
	// Disable compare match A interrupt.
	CLEAR_BIT(TIMSK2, OCIE2A);

	// XXX: assumes we're running at 16MHz. If not, use a
	// different prescaler.
	
	// Use a prescaler of 64.
	SET_BIT(TCCR2B, CS22);
	CLEAR_BIT(TCCR2B, CS21);
	CLEAR_BIT(TCCR2B, CS20);

	// Timer register gets set to this so it overflows in
	// TIMER_RESOLUTION seconds.
	tcnt2_init = 256 - (int)((float)F_CPU * TIMER_RESOLUTION / 64.0);
}

void timer_start()
{
	timer_ticks = 0;
	timer_overflowed = 0;
	// Set timer register to its initial value; it'll be incremented
	// from this value and trigger an interrupt on overflow.
	TCNT2 = tcnt2_init;
	// Enable overflow interrupts.
	SET_BIT(TIMSK2, TOIE2);
}

void overflow()
{
	timer_ticks++;
	if (timer_ticks >= timer_interval && !timer_overflowed) {
		timer_overflowed = 1;
		// We subtract rather than setting to 0 so that ticks
		// which occur during execution are still counted.
		timer_ticks -= timer_interval;

		// Do the thing.
		(*timer_func)();

		timer_overflowed = 0;
	}
}

ISR(TIMER2_OVF_vect) 
{
	// Reset the timer register for the next tick.
	TCNT2 = tcnt2_init;
	overflow();
}	
