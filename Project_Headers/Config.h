#ifndef CONFIG_H_
#define CONFIG_H_

#include <MKL25Z4.h>
#include "System.h"
#include "UART.h"
#include "Stepper.h"

void Initialize();

// Initialize the GPIO pins
void InitGPIO();

#endif /* CONFIG_H_ */
