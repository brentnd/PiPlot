#include "Config.h"

#define HOME_POS            (uint32_t)((0.7071*CANVAS_WIDTH) / LENGTH_PER_STEP)

/*
 * Internal function prototypes
 */
void StepperSetSettings();
void StepperActivateCoil(StepperMotor* mot, uint8 stage);
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
  int i;
  
  p_Motor0 = &Motor[0];
  p_Motor1 = &Motor[1];
  
  StepperSetSettings();

  // Enable Clocks to all ports
  SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK
      | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;

  // Setup GPIO ports as outputs with drive strength enabled
  GPIO_PDDR_REG(p_Motor0->settings.Pt) = 0;
  GPIO_PDDR_REG(p_Motor1->settings.Pt) = 0;
  for (i = 0; i < NUM_PINS; i++)
  {
    PORTE_PCR1 = 0;
    // Motor 1
    GPIO_PDDR_REG(p_Motor0->settings.Pt) |= (1 << p_Motor0->settings.Pin[i]);
    PORT_PCR_REG(p_Motor0->settings.Port, p_Motor0->settings.Pin[i])= PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;
    // Motor 2
    GPIO_PDDR_REG(p_Motor1->settings.Pt) |= (1 << p_Motor1->settings.Pin[i]);
    PORT_PCR_REG(p_Motor1->settings.Port, p_Motor1->settings.Pin[i])= PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK;
  }
}

/*
 * Activate settings for both stepper motors
 */
void StepperSetSettings()
{
  /* Reset both motor statuses */
  StepperReset(p_Motor0);
  StepperReset(p_Motor1);

  /* Assign PINs for each coil, hardcoded to PORTC */
  p_Motor0->settings.Pt = PTC_BASE_PTR; // TODO: PORT as param
  p_Motor0->settings.Port = PORTC_BASE_PTR;
  p_Motor0->settings.Pin[0] = 17;
  p_Motor0->settings.Pin[1] = 16;
  p_Motor0->settings.Pin[2] = 13;
  p_Motor0->settings.Pin[3] = 12;

  /* Assign PINs for each coil, hardcoded to PORTE */
  p_Motor1->settings.Pt = PTE_BASE_PTR; // TODO: PORT as param
  p_Motor1->settings.Port = PORTE_BASE_PTR;
  p_Motor1->settings.Pin[0] = 23;
  p_Motor1->settings.Pin[1] = 22;
  p_Motor1->settings.Pin[2] = 21;
  p_Motor1->settings.Pin[3] = 20;
}

/* 
 * Update the absolute position of the stepper motor
 *  @param *mot - pointer to motor structure
 *  @param new_position - absolute desired position
 */
void StepperSetPosition(StepperMotor* mot, uint32_t new_position)
{
  mot->status.spinning = 1;
  mot->status.desired_position = new_position;
}

/* 
 * Update the difference in position of the stepper motor
 *  @param *mot - pointer to motor structure
 *  @param delta - change in position, positive for Clock-wise,
 *                                     negative for Counter clock-wise
 */
void StepperSetPositionDelta(StepperMotor* mot, uint16_t delta)
{
  mot->status.spinning = 1;
  mot->status.desired_position += delta;
}

void StepperSetZero(StepperMotor* mot)
{
  mot->status.desired_position = HOME_POS;
  mot->status.current_position = HOME_POS;
}


uint8_t StepperMoving()
{
  return (p_Motor0->status.spinning || p_Motor1->status.spinning);
}

/*
 * Get the position the stepper motor is currently at
 */
uint32 StepperGetPosition(StepperMotor* mot)
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
  mot->status.current_position = HOME_POS;
  mot->status.desired_position = HOME_POS;
  mot->status.speed = 0;
  mot->status.spinning = 0;
  /* Re-enable the motor */
  mot->status.enabled = 1;
  mot->status.enabled = 1;
  
  /* Set to default speed */
  mot->status.speed = 10;
}

/*
 * Update the stepper motor based on the desired and current position.
 * Should be called by a periodic interrupt timer to produce smooth
 * movement.
 */
void StepperUpdate(StepperMotor* mot)
{
  if (mot->status.enabled)
  {
    // State change CW
    if (mot->status.desired_position > mot->status.current_position)
      mot->status.current_position++;
    // State changed CCW
    else if (mot->status.desired_position < mot->status.current_position)
      mot->status.current_position--;
    else
      mot->status.spinning = 0;
    
    if(mot->status.current_position > 0)
      StepperActivateCoil(mot, mot->status.current_position % NUM_PINS);
    else
      StepperActivateCoil(mot, (-mot->status.current_position) % NUM_PINS);
  }
}

/*
 * Activates a given coil in the stepper motor by setting the
 * GPIO pin associated with the H-Bridge
 */
void StepperActivateCoil(StepperMotor* mot, uint8 stage)
{
  switch(stage)
  {
  case 0:
    GPIO_PSOR_REG(mot->settings.Pt) = (1 << mot->settings.Pin[0]); // A1
    GPIO_PCOR_REG(mot->settings.Pt) = (1 << mot->settings.Pin[1]); // A2
    GPIO_PSOR_REG(mot->settings.Pt) = (1 << mot->settings.Pin[2]); // B1
    GPIO_PCOR_REG(mot->settings.Pt) = (1 << mot->settings.Pin[3]); // B2
    break;
  case 1:
    GPIO_PCOR_REG(mot->settings.Pt) = (1 << mot->settings.Pin[0]);
    GPIO_PSOR_REG(mot->settings.Pt) = (1 << mot->settings.Pin[1]);
    GPIO_PSOR_REG(mot->settings.Pt) = (1 << mot->settings.Pin[2]);
    GPIO_PCOR_REG(mot->settings.Pt) = (1 << mot->settings.Pin[3]);
    break;
  case 2:
    GPIO_PCOR_REG(mot->settings.Pt) = (1 << mot->settings.Pin[0]);
    GPIO_PSOR_REG(mot->settings.Pt) = (1 << mot->settings.Pin[1]);
    GPIO_PCOR_REG(mot->settings.Pt) = (1 << mot->settings.Pin[2]);
    GPIO_PSOR_REG(mot->settings.Pt) = (1 << mot->settings.Pin[3]);
    break;
  case 3:
    GPIO_PSOR_REG(mot->settings.Pt) = (1 << mot->settings.Pin[0]);
    GPIO_PCOR_REG(mot->settings.Pt) = (1 << mot->settings.Pin[1]);
    GPIO_PCOR_REG(mot->settings.Pt) = (1 << mot->settings.Pin[2]);
    GPIO_PSOR_REG(mot->settings.Pt) = (1 << mot->settings.Pin[3]);
    break;
  }
}
