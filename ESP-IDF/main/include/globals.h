#ifndef GLOBALS_H
#define GLOBALS_H

#include <stdint.h>
#include "driver/gpio.h"
#include "rom/ets_sys.h" // delay function

// pin definitions and io bit masks
#define EN_IN_PIN     GPIO_NUM_10
#define SELECT_IN_PIN GPIO_NUM_3

#define DATA_OUT_PIN  GPIO_NUM_6
#define SYNC_OUT_PIN  GPIO_NUM_7

#define INPUT_MASK  1ULL<<EN_IN_PIN    | 1ULL<<SELECT_IN_PIN
#define OUTPUT_MASK 1ULL<<DATA_OUT_PIN | 1ULL<<SYNC_OUT_PIN

#endif