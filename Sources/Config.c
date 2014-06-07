#include "Config.h"

/*
 * Initialize clock, system, GPIO
 */
void Initialize()
{
  ClockInit();
  SysTickInit();
  UART_init();
  StepperInit();
  //PIT_init(100);
}
