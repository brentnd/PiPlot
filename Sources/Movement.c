#include "Config.h"

#define LENGTH_PER_STEP   (2*3.14159265358979323846*MOTOR_RADIUS / 200)

void SetLengths(uint32_t l0, uint32_t l1);

void MovementGoto(uint32_t x, uint32_t y)
{
  uint32_t l0, l1;
  // Translate X, Y coords into lengths 
  // for each stepper motor.
  l0 = (uint32_t) (sqrt(x*x + y*y));
  l1 = (uint32_t) (sqrt(x*x + (CANVAS_WIDTH-y)*(CANVAS_WIDTH-y)));
  
  // Update stepper motors to those lengths
  SetLengths(l0, l1);
 
  while(StepperMoving());
}

void SetLengths(uint32_t l0, uint32_t l1)
{
  uint32_t steps0, steps1;
  
  steps0 = (uint32_t) (l0 / LENGTH_PER_STEP);
  steps1 = (uint32_t) (l1 / LENGTH_PER_STEP);
  
  StepperSetPosition(p_Motor0, steps0);
  StepperSetPosition(p_Motor1, steps1);
}
