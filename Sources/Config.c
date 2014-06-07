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
  PIT_init();
}

void ConfigStart()
{
  PIT_enable();
}
