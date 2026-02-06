#include "include/interrupt.h"


// ISR for when the enable button is pressed, to toggle the data output state
void gpio_isr_data_handler(void* state)
{   
    uint8_t* data_state = state;
    *data_state = !*data_state;

    if (!*data_state) { // if data_state is 0, immediately turn the LED off for faster responiveness
        gpio_set_level(DATA_OUT_PIN, 0); 
    }
}


// ISR for when the select button is pressed, to toggle the alternative behaviour
void gpio_isr_alt_handler(void* state)
{   
    uint8_t* alt_state = state;
    *alt_state = !*alt_state;
}