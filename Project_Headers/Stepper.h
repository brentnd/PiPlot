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
  FGPIO_MemMapPtr Port = PTE_BASE_PTR;
  uint8 Pin[4] =  { (1<<0), (1<<0), (1<<0), (1<<0) };

} StepperSettings;

/* Status structure for stepper */
typedef struct
{
  uint8 enabled = 0;
  uint8 spinning = 0;
  uint8 speed = 0;
  int32 desired_position = 0;
  int32 current_position = 0;
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
int32 StepperGetPosition(StepperMotor* mot);

#endif /* STEPPER_H_ */
