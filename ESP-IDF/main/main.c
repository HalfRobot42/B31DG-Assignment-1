#include "include/globals.h"
#include "include/waveform.h"
#include "include/interrupt.h"

void app_main(void)
{   
    // variables to keep track of program state
    uint8_t data_state = 1; // whether data output is enabled or not (on by default)
    uint8_t alt_state = 0; // whether the alternative functionality is used or not (off by default)
    
    // gpio setup
    gpio_config_t io_conf = {}; // zero-initialize the config structure.
    
    // configure outputs
    io_conf.intr_type = GPIO_INTR_DISABLE; // disable interrupt
    io_conf.mode = GPIO_MODE_OUTPUT; // set as output mode
    io_conf.pin_bit_mask = OUTPUT_MASK; // bit mask
    io_conf.pull_down_en = 0; // disable pull-down mode
    io_conf.pull_up_en = 0; // disable pull-up mode

    gpio_config(&io_conf); // configure GPIO with the given settings

    // configure inputs
    io_conf.mode = GPIO_MODE_INPUT; // set as input mode
    io_conf.intr_type = GPIO_INTR_POSEDGE; // enable interrupt
    io_conf.pin_bit_mask = INPUT_MASK; // bit mask

    gpio_config(&io_conf); // configure GPIO with the given settings


    // setup interrupts
    gpio_install_isr_service(0);

    gpio_set_intr_type(EN_IN_PIN, GPIO_INTR_POSEDGE);
    gpio_isr_handler_add(EN_IN_PIN, gpio_isr_data_handler, (void*) &data_state);
    
    gpio_set_intr_type(SELECT_IN_PIN, GPIO_INTR_POSEDGE);
    gpio_isr_handler_add(SELECT_IN_PIN, gpio_isr_alt_handler, (void*) &alt_state);


    // main program loop, generate waveforms repeatedly
    while(1) {

        generate_waveform(&data_state, &alt_state);
        
    }
}