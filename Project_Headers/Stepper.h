#ifndef STEPPER_H_
#define STEPPER_H_

#include "Config.h"

#define NUM_PINS    4
#define NUM_MOTORS  2

/* Settings structure for stepper */
typedef struct
{
  GPIO_MemMapPtr Pt;
  PORT_MemMapPtr Port;
  uint8_t Pin[NUM_PINS];
} StepperSettings;

/* Status structure for stepper */
typedef struct
{
  uint8_t enabled;
  uint8_t spinning;
  uint8_t speed;
  uint32_t desired_position;
  uint32_t current_position;
} StepperStatus;

/* Stepper motor structure which has settings and status */
typedef struct
{
  StepperSettings settings;
  StepperStatus status;
} StepperMotor;

/* Stepper motor objects */
StepperMotor Motor[NUM_MOTORS];

/* Pointers to the steppers */
StepperMotor* p_Motor0;
StepperMotor* p_Motor1;

/* Public stepper functions */
void StepperInit();
void StepperSetPosition(StepperMotor* mot, int new_position);
void StepperSetPositionDelta(StepperMotor* mot, int delta);
int StepperGetPosition(StepperMotor* mot);
void StepperUpdate(StepperMotor* mot);

#endif /* STEPPER_H_ */
