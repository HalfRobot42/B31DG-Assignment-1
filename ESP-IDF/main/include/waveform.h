#ifndef WAVEFORM_H
#define WAVEFORM_H

#include "include/globals.h"

// production vs debug timing
#define PRODUCTION_TIMING 1
#define DEBUG_TIMING 1000
#define TIMING_MULTIPLIER DEBUG_TIMING//PRODUCTION_TIMING

// delay constants
#define A_DELAY             700  * TIMING_MULTIPLIER // us
#define B_DELAY             1200 * TIMING_MULTIPLIER // us
#define C_PULSES            9
#define D_DELAY             6500 * TIMING_MULTIPLIER // us
#define SYNC_DELAY          50   * TIMING_MULTIPLIER // us   
#define PULSE_FORMULA_CONST 650  * TIMING_MULTIPLIER // us
#define PUSLE_FORMULA_COEFF 50   * TIMING_MULTIPLIER // us
#define ALT_PULSE_REDUCTION 3

uint32_t get_data_pulse_delay(uint32_t n);
void generate_waveform(uint8_t* data_state, uint8_t* alt_state);

#endif