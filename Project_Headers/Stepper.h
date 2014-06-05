#ifndef STEPPER_H_
#define STEPPER_H_

#include "Config.h"

typedef struct
{
  uint8 Coil[4] =
  { 1, 2, 3, 4 };
  uint8 Enable = 0;
  int HalfStep = 0;

} StepperSettings;

typedef struct
{
  uint8 spinning = 0;
  uint8 speed = 0;
  int32 desired_position = 0;
  int32 current_position = 0;
} StepperStatus;

typedef struct
{
  StepperSettings settings;
  StepperStatus status;
} StepperMotor;

/* Stepper motor objects */
StepperMotor Motor[2];

/* Pointers to the steppers */
StepperMotor* p_Motor0 = &Motor[0];
StepperMotor* p_Motor1 = &Motor[1];

/* Public stepper functions */
void StepperInit();
void StepperSetPosition(StepperMotor* mot, int new_position);
void StepperSetPositionDelta(StepperMotor* mot, int delta);
in32t StepperGetPosition(StepperMotor* mot);

#endif /* STEPPER_H_ */
