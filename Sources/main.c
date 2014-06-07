#include "Config.h"

/*
 * Future main method for Pythagorian Plotter
 */
int main(void)
{
  ConfigInitialize();
  StepperSetPosition(p_Motor0, 400);
  StepperSetPosition(p_Motor1, 400);
  
  ConfigStart();
  
  while(1){}
  
  return 0;
}
