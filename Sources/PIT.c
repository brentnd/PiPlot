#include "Config.h"

void PIT_init()
{
  //Enable clock to the PIT
  SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;

  //enable PIT0 and its interrupt
  PIT_TCTRL0 = PIT_TCTRL_TEN_MASK | PIT_TCTRL_TIE_MASK;

  // stop the pit when in debug mode
  PIT_MCR |= PIT_MCR_FRZ_MASK;

  //Enable the PIT module
  PIT_MCR &= ~PIT_MCR_MDIS_MASK;
}

/*
 * Enable the Interrupt for the PIT
 */
void PIT_enable()
{
  enable_irq(INT_PIT - 16);
}

/*
 * Disable the interrupt for the PIT
 */
void PIT_disable()
{
  disable_irq(INT_PIT - 16);
}

void PIT_IRQ()
{
  // Turn off the Pit 0 Irq flag
  PIT_TFLG0 = PIT_TFLG_TIF_MASK;

  // Update stepper motors
  StepperUpdate(p_Motor0);
  StepperUpdate(p_Motor1);
}
