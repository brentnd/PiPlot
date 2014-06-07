#ifndef CONFIG_H_
#define CONFIG_H_

#include <MKL25Z4.h>
#include "System.h"
#include "UART.h"
#include "Stepper.h"
#include "PIT.h"

void ConfigInitialize();
void ConfigStart();

#endif /* CONFIG_H_ */
