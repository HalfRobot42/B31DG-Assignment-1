#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "include/globals.h"

void gpio_isr_data_handler(void* state);
void gpio_isr_alt_handler(void* state);

#endif