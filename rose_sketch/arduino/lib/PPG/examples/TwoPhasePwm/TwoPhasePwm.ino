#include <Arduino.h>
#include <PPG.h>

uint32_t	motor_speed[2];
uint32_t	motor_pwm_cycle = 500;	// 500[micro-second]
void    calc_speed();

void    setup()
{
  PPG.begin(true, true, true, true, motor_pwm_cycle, 0b0101);
  PPG.setTrigger(0, 0, motor_pwm_cycle / 2);
  PPG.setTrigger(1, 0, motor_pwm_cycle / 2);
  PPG.setTrigger(2, 0, motor_pwm_cycle / 2);
  PPG.setTrigger(3, 0, motor_pwm_cycle / 2);
  PPG.start();
}

void	loop()
{
  calc_speed();
  PPG.setTrigger(0, 0, motor_speed[0]);
  PPG.setTrigger(1, 0, motor_speed[0]);
  PPG.setTrigger(2, 0, motor_speed[1]);
  PPG.setTrigger(3, 0, motor_speed[1]);
  PPG.enableTrigger();
  delay(100);
}

void    calc_speed()
{
  // Set spped according to A0, A1
  motor_speed[0] = map(analogRead(A0), 0, (1U<<12), 0, motor_pwm_cycle);
  motor_speed[1] = map(analogRead(A1), 0, (1U<<12), 0, motor_pwm_cycle);
}

