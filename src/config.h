/* Compile-time configuration options. Tweak these according to your
 * hardware setup or whim. */

#ifndef H_CONFIG
#define H_CONFIG

/* Set this to the number of ECG channels your hardware provides; this
 * will almost always be equal to the number of EKG-EMG shield boards
 * you're using. */
#define CHANNELS 1

/* Uncomment this to print debugging information to the serial 
 * console. */
//#define DEBUG 1

/* Sample rate in hertz - can be adjusted as desired, the maximum I've
 * successfully used is 256 (on an atmega328p). */
#define SAMPLE_RATE 32

#endif
