#include "include/waveform.h"


// determine the duration of a waveform pulse, depending on its order
uint32_t get_data_pulse_delay(uint32_t n) { 
    uint32_t delay = 0;

    if (n >= 2) {
        //delay = ((650 + (50*n)) * TIMING_MULTIPLIER); // use provided formula
        delay = PULSE_FORMULA_CONST + (PUSLE_FORMULA_COEFF*n) ; // use provided formula
    }
    else { 
        delay = A_DELAY; // first pulse uses A_DELAY
    }

    return delay;
}


// create the specific waveform that depends on the program state
void generate_waveform(uint8_t* data_state, uint8_t* alt_state) {

    uint8_t pulses = C_PULSES;
    uint32_t delay = 0;

    if (*alt_state) { // use alternative behaviour
        pulses = pulses - ALT_PULSE_REDUCTION;
    }

    // pulse SYNC LED before starting the DATA waveform
    gpio_set_level(SYNC_OUT_PIN, 1); 
    ets_delay_us(SYNC_DELAY);
    gpio_set_level(SYNC_OUT_PIN, 0); 

    // generate set number of pulses, i starts at 1
    for (int i=1; i<=pulses; i++) {

        delay = get_data_pulse_delay(i); // generate appriopriate length pulse duration depending on its order
        
        if (*data_state) { // if the data output is enabled, actually toggle the LED
            gpio_set_level(DATA_OUT_PIN, 1);
            ets_delay_us(delay);
            gpio_set_level(DATA_OUT_PIN, 0); 
            ets_delay_us(B_DELAY); // all pulses are seperated by B_DELAY
        }
        else { // if output is disabled, still delay just don't toggle
            ets_delay_us(delay); 
            ets_delay_us(B_DELAY);
        }

    }

    ets_delay_us(D_DELAY); // generate delay at the end of the waveform
}