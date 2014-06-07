#ifndef PIT_H_
#define PIT_H_

#include "Config.h"

void PIT_init();
void PIT_setSpeed(uint16_t speed);
void PIT_enable();
void PIT_disable();
void PIT_IRQ();

#endif /* PIT_H_ */
