#include "l298n.h"

/// @brief L298N初始化
/// @param  无
void L298N_init(void) {
    HAL_TIM_PWM_Start(&MOTOR_TIM, MOTOR_1_CHANNEL);
    HAL_TIM_PWM_Start(&MOTOR_TIM, MOTOR_2_CHANNEL);
    HAL_TIM_PWM_Start(&MOTOR_TIM, MOTOR_3_CHANNEL);
    HAL_TIM_PWM_Start(&MOTOR_TIM, MOTOR_4_CHANNEL);
}

/// @brief 设置电机速度方向
/// @param motor 电机地址
/// @param speed 速度
void Motor_SetSpeedAndDirection(uint8_t motor, int16_t speed) {
    uint16_t abs_speed = (speed < 0) ? -speed : speed; // 取绝对值
    uint8_t direction = (speed < 0) ? 0 : 1; // 方向：0为反转，1为正转

    if (motor == 0) {
        if (direction == 1) {
            __HAL_TIM_SET_COMPARE(&MOTOR_TIM, MOTOR_1_CHANNEL, 0); // 设置速度
            __HAL_TIM_SET_COMPARE(&MOTOR_TIM, MOTOR_2_CHANNEL, abs_speed); // 设置速度
        } else {
            __HAL_TIM_SET_COMPARE(&MOTOR_TIM, MOTOR_1_CHANNEL, abs_speed); // 设置速度
            __HAL_TIM_SET_COMPARE(&MOTOR_TIM, MOTOR_2_CHANNEL, 0); // 设置速度
        }
        
    } else if (motor == 1) {
        if (direction == 1) {
            __HAL_TIM_SET_COMPARE(&MOTOR_TIM, MOTOR_3_CHANNEL, abs_speed); // 设置速度
            __HAL_TIM_SET_COMPARE(&MOTOR_TIM, MOTOR_4_CHANNEL, 0); // 设置速度
        } else {
            __HAL_TIM_SET_COMPARE(&MOTOR_TIM, MOTOR_3_CHANNEL, 0); // 设置速度
            __HAL_TIM_SET_COMPARE(&MOTOR_TIM, MOTOR_4_CHANNEL, abs_speed); // 设置速度
        }
    }
}

void Motor_SetSpeed(int16_t speed_l, int16_t speed_r) {
	Motor_SetSpeedAndDirection(0, speed_l);
	Motor_SetSpeedAndDirection(1, speed_r);
}
