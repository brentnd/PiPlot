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
void StepperSetZero(StepperMotor* mot);
void StepperSetPosition(StepperMotor* mot, uint32_t new_position);
void StepperSetPositionDelta(StepperMotor* mot, uint16_t delta);
uint32_t StepperGetPosition(StepperMotor* mot);
uint8_t StepperMoving();
void StepperUpdate(StepperMotor* mot);

#endif /* STEPPER_H_ */
