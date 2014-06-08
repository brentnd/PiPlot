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
}

void ConfigStart()
{
  PIT_enable();
}
