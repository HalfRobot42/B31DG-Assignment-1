#include <stdint.h>

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

// pin definitions and io bit masks
#define EN_IN_PIN     10
#define SELECT_IN_PIN 3

#define DATA_OUT_PIN  6
#define SYNC_OUT_PIN  7


// global variables to keep track of program state (must be global as arduino ISRs cannot have parameters)
volatile uint8_t data_state = 1; // whether data output is enabled or not (on by default)
volatile uint8_t alt_state = 0; // whether the alternative functionality is used or not (off by default)



// determine the duration of a waveform pulse, depending on its order
uint32_t get_data_pulse_delay(uint32_t n) {

    uint32_t delay_ = 0;

    if (n >= 2) {
        //delay_ = ((650 + (50*n)) * TIMING_MULTIPLIER); // use provided formula
        delay_ = PULSE_FORMULA_CONST + (PUSLE_FORMULA_COEFF*n) ; // use provided formula
    }
    else {
        delay_ = A_DELAY; // first pulse uses A_DELAY
    }

    return delay_;
}


// create the specific waveform that depends on the program state
void generate_waveform() {

    int pulses = C_PULSES;
    uint32_t delay_ = 0;

    if (alt_state) { // use alternative behaviour
        pulses = pulses - ALT_PULSE_REDUCTION;
    }

    // pulse sync LED before starting the data waveform
    digitalWrite(SYNC_OUT_PIN, HIGH); 
    delayMicroseconds(SYNC_DELAY);
    digitalWrite(SYNC_OUT_PIN, LOW);

    // generate set number of pulses, i starts at 1
    for (int i=1; i<=pulses; i++) {
        
        delay_ = get_data_pulse_delay(i); // generate appriopriate length pulse duration depending on its order

        if (data_state) { // if the data output is enabled, actually toggle the LED
            digitalWrite(DATA_OUT_PIN, HIGH); 
            delayMicroseconds(delay_);
            digitalWrite(DATA_OUT_PIN, LOW); 
            delayMicroseconds(B_DELAY); // all pulses are seperated by B_DELAY
        }
        else { // if output is disabled, still delay just don't toggle
            delayMicroseconds(delay_);
            delayMicroseconds(B_DELAY);
        }

    }

    delayMicroseconds(D_DELAY); // generate delay at the end of the waveform
}


// ISR for when the enable button is pressed, to toggle the data output state
void gpio_isr_data_handler() {   
    data_state = !data_state;

    if (!data_state) { // if data_state is 0, immediately turn the LED off for faster responiveness
        digitalWrite(DATA_OUT_PIN, LOW); 
    }
}

// ISR for when the select button is pressed, to toggle the alternative behaviour
void gpio_isr_alt_handler() {   
    alt_state = !alt_state;
}



void setup() {

  // pin setup
  pinMode(EN_IN_PIN,     INPUT);
  pinMode(SELECT_IN_PIN, INPUT);
  pinMode(DATA_OUT_PIN,  OUTPUT);
  pinMode(SYNC_OUT_PIN,  OUTPUT);

  // setup interrupts
  attachInterrupt(digitalPinToInterrupt(EN_IN_PIN), gpio_isr_data_handler, RISING);
  attachInterrupt(digitalPinToInterrupt(SELECT_IN_PIN), gpio_isr_alt_handler, RISING);
}

void loop() {
  generate_waveform(); // generate waveforms repeatedly
}
