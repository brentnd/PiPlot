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

void InitPWM();
void SetPWM(int Position);
void SetPWMDutyCycle(float DutyCycle);

#endif /* PWM_H_ */
