#include "Config.h"

/*
 * Initialize clock, system, GPIO
 */
void ConfigInitialize()
{
  ClockInit();
  SysTickInit();
  UART_init();
  StepperInit();
  MoveInit();
  PIT_init();
  PWM_init();
}

void ConfigStart()
{
  PIT_enable();
}
