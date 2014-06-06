#include "Config.h"

/*
 * Internal function prototypes
 */
void StepperActivateCoil(StepperMotor* mot, uint8 coil);
void StepperReset(StepperMotor* mot);

/*
 * Function implementations
 */

/* 
 * Update the absolute position of the stepper motor
 *  @param none
 */
void StepperInit()
{
  /* Reset both motor statuses */
  StepperReset(p_Motor0);
  StepperReset(p_Motor1);
  
  /* Assign PINs for each coil, hardcoded to PORTC */
  p_Motor0->settings.Port = PTC_BASE_PTR; // TODO: PORT as param
  p_Motor0->settings.Pin[0] = 12;
  p_Motor0->settings.Pin[1] = 13;
  p_Motor0->settings.Pin[2] = 16;
  p_Motor0->settings.Pin[3] = 17;

  /* Assign PINs for each coil, hardcoded to PORTE */
  p_Motor0->settings.Port = PTE_BASE_PTR; // TODO: PORT as param
  p_Motor0->settings.Pin[0] = 23;
  p_Motor0->settings.Pin[1] = 22;
  p_Motor0->settings.Pin[2] = 21;
  p_Motor0->settings.Pin[3] = 20;
}

/* 
 * Update the absolute position of the stepper motor
 *  @param *mot - pointer to motor structure
 *  @param new_position - absolute desired position
 */
void StepperSetPosition(StepperMotor* mot, int new_position)
{
  mot->status.desired_position = new_position;
}

/* 
 * Update the difference in position of the stepper motor
 *  @param *mot - pointer to motor structure
 *  @param delta - change in position, positive for Clock-wise,
 *                                     negative for Counter clock-wise
 */
void StepperSetPositionDelta(StepperMotor* mot, int delta)
{
  mot->status.desired_position += delta;
}

/*
 * Get the position the stepper motor is currently at
 */
int32 StepperGetPosition(StepperMotor* mot)
{
  return mot->status.current_position;
}

/*
 * Reset the stepper motor to 0 and stop
 */
void StepperReset(StepperMotor* mot)
{
  /* Enable both stepper motors */
  mot->status.enabled = 0;
  mot->status.enabled = 0;
  mot->status.current_position = 0;
  mot->status.desired_position = 0;
  mot->status.speed = 0;
  mot->status.spinning = 0;
  /* Re-enable the motor */
  mot->status.enabled = 1;
  mot->status.enabled = 1;
}

/*
 * Update the stepper motor based on the desired and current position.
 * Should be called by a periodic interrupt timer to produce smooth
 * movement.
 */
void StepperUpdate(StepperMotor* mot)
{
  if(mot->status.enabled)
  {
    // State change CW
    if(mot->status.desired_position > mot->status.current_position)
      mot->status.current_position++;
    // State changed CCW
    else if(mot->status.desired_position < mot->status.current_position)
      mot->status.current_position--;
    
    StepperActiveCoil(mot, mot->status.current_position%4);
  }
}

/*
 * Activates a given coil in the stepper motor by setting the
 * GPIO pin associated with the H-Bridge
 */
void StepperActivateCoil(StepperMotor* mot, uint8 coil)
{
  GPIO_PSOR_REG(mot->settings.Port) = (1 << mot->settings.Pin[coil]);
}
