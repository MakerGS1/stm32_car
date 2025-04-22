#ifndef L298N_H
#define L298N_H

#include "main.h"
#include "tim.h"

// 定义PWM定时器
#define MOTOR_TIM htim3
#define MOTOR_1_CHANNEL TIM_CHANNEL_1
#define MOTOR_2_CHANNEL TIM_CHANNEL_2
#define MOTOR_3_CHANNEL TIM_CHANNEL_3
#define MOTOR_4_CHANNEL TIM_CHANNEL_4

void L298N_init(void);
void Motor_SetSpeedAndDirection(uint8_t motor, int16_t speed);
void Motor_SetSpeed(int16_t speed_l, int16_t speed_r);
extern void Motor_SetSpeedAndDirection(uint8_t motor, int16_t speed);
extern void L298N_init(void);

#endif
