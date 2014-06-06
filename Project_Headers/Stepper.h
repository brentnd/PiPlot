#ifndef STEPPER_H_
#define STEPPER_H_

#include "Config.h"

#define PT1  (1<<1)
#define PT2  (1<<2)
#define PT3  (1<<3)
#define PT4  (1<<4)

/* Settings structure for stepper */
typedef struct
{
  GPIO_MemMapPtr Port;
  uint8_t Pin[4];
} StepperSettings;

/* Status structure for stepper */
typedef struct
{
  uint8_t enabled;
  uint8_t spinning;
  uint8_t speed;
  int32_t desired_position;
  int32_t current_position;
} StepperStatus;

/* Stepper motor structure which has settings and status */
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
int StepperGetPosition(StepperMotor* mot);
void StepperUpdate(StepperMotor* mot);

#endif /* STEPPER_H_ */
