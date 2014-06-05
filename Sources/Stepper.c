#include "Config.h"


void StepperInit()
{
  /* Reset both motor statuses */
  StepperReset(p_Motor0);
  StepperReset(p_Motor1);
  
  /* Assign PINs for each coil */
  p_Motor0->settings.Coil[0] = 1;
  p_Motor0->settings.Coil[1] = 1;
  p_Motor0->settings.Coil[2] = 1;
  p_Motor0->settings.Coil[3] = 1;

  /* Assign PINs for each coil */
  p_Motor1->settings.Coil[0] = 1;
  p_Motor1->settings.Coil[1] = 1;
  p_Motor1->settings.Coil[2] = 1;
  p_Motor1->settings.Coil[3] = 1; 
  
  /* Stepper motors in full-step mode */
  p_Motor0->settings.HalfStep = 0;
  p_Motor1->settings.HalfStep = 0;
  
  /* Enable both stepper motors */
  p_Motor0->settings.Enable = 1;
  p_Motor1->settings.Enable = 1;
}

void StepperSetPosition(StepperMotor* mot, int new_position)
{
  mot->status.desired_position = new_position;
}

// Positive, CW
// Negative, CCW
void StepperSetPositionDelta(StepperMotor* mot, int delta)
{
  mot->status.desired_position = desired_position + delta;
}

in32t StepperGetPosition(StepperMotor* mot)
{
  return mot->status.current_position;
}

void StepperReset(StepperMotor* mot)
{
  mot->status.current_position = 0;
  mot->status.desired_position = 0;
  mot->status.speed = 0;
  mot->status.spinning = 0;
}

void StepperUpdate(StepperMotor* mot)
{
  // State change CW
  if(mot->status.desired_position > mot->status.current_position)
    current_position++;
  // State changed CCW
  else if(mot->status.desired_position < mot->status.current_position)
    current_position--;
  
  StepperActiveCoil(mot, current_position%4);
}

void StepperActivateCoil(StepperMotor* mot, uint8 coil)
{
  //Not implemented
}
