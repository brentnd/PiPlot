#ifndef PWM_H_
#define PWM_H_

// PWM Clock
#define PWM_CLK				      (CORE_CLOCK)
#define PWM_CLK_PRESCALE		6
#define PWM_FREQ				    50

// PWM Limits
//0.065
#define PWM_DUTY_RIGHT		0.067
#define PWM_DUTY_LEFT			0.029
#define PWM_DUTY_RANGE		(PWM_DUTY_RIGHT-PWM_DUTY_LEFT)
#define PWM_DUTY_CENTER		((PWM_DUTY_RANGE)/2)+PWM_DUTY_LEFT

void PWM_init();
void PWM_setPosition(int Position);
void PWM_setDuty(float DutyCycle);
void PWM_IRQHandler();

#endif /* PWM_H_ */
