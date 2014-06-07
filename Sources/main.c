#include "Config.h"

/*
 * Future main method for Pythagorian Plotter
 */
int main(void)
{
  int i = 0;
  Initialize();
  StepperSetPosition(p_Motor0, 400);
  StepperSetPosition(p_Motor1, 400);
  while(i++ < 600)
  {
    Delay_mS(10);
    StepperUpdate(p_Motor0);
    StepperUpdate(p_Motor1);
  }
  StepperSetPosition(p_Motor0, 0);
  StepperSetPosition(p_Motor1, 0);
  while(1)
  {
    Delay_mS(10);
    StepperUpdate(p_Motor0);
    StepperUpdate(p_Motor1);
  }
  return 0;
}
