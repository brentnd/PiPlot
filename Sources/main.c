#include "Config.h"

void DrawSquare()
{
  MovementGoto(2500,2000);
  MovementGoto(2500,2500);
  MovementGoto(2000,2500);
  MovementGoto(2000,2000);
}

/*
 * Future main method for Pythagorian Plotter
 */
int main(void)
{
  ConfigInitialize();
  ConfigStart();
  
  StepperSetZero(p_Motor0);
  StepperSetZero(p_Motor1);
  
  DrawSquare();
  
  while(1){}
  
  return 0;
}
