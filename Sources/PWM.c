#include "Config.h"

/*
 * Set the PWM position
 * @param position - The position (-100 to 100) of the turning PWM
 */
void PWM_setPosition(int position)
{
  position -= 4;
  PWM_setDuty(((PWM_DUTY_RANGE * (position + 100)) / 200) + PWM_DUTY_LEFT);
}

/* 
 * Sets the duty cycle for the forward turning PWM
 * Note: Duty cycle should not be outside of valid PWM range
 * @param DutyCycle - Float (0.0 to 1.0) Duty Cycle to control PWM
 */
void PWM_setDuty(float DutyCycle)
{
  TPM1_C0V = TPM1_MOD * DutyCycle;
}

volatile unsigned char PWMTickVar;

/* Interrupt handler for the PWM */
void PWM_IRQHandler()
{
  //Clear the overflow mask if set.
  if (TPM1_SC & TPM_SC_TOF_MASK)
    TPM1_SC |= TPM_SC_TOF_MASK;
  if (PWMTickVar < 0xff)
    PWMTickVar++;
}

/* Initialize the turning PWM with the TPM module.
 * Sets up the timer clock and aligns PWM to center
 */
void PWM_init()
{
  SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;
  SIM_SOPT2 &= ~(SIM_SOPT2_TPMSRC_MASK);
  SIM_SOPT2 |= SIM_SOPT2_TPMSRC(1);

  SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;

  TPM1_SC = 0;
  TPM1_CONF = 0;

  TPM1_SC = TPM_SC_PS(PWM_CLK_PRESCALE);
  TPM1_SC |= TPM_SC_TOIE_MASK;

  TPM1_MOD = PWM_CLK / (1 << (PWM_CLK_PRESCALE + 1)) / PWM_FREQ;

  TPM1_C0SC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;
  TPM1_C1SC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK;

  PWM_setPosition(0.0);

  TPM1_SC |= TPM_SC_CMOD(1);

  enable_irq(INT_TPM1 - 16);

  PORTB_PCR0 = PORT_PCR_MUX(3);
}
