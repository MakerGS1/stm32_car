#ifndef CAR_H
#define CAR_H

#include "main.h"
#include "pid.h"


#define	IN1 HAL_GPIO_ReadPin(IN1_GPIO_Port,IN1_Pin)
#define	IN2 HAL_GPIO_ReadPin(IN2_GPIO_Port,IN2_Pin)
#define	IN3 HAL_GPIO_ReadPin(IN3_GPIO_Port,IN3_Pin)
#define	IN4 HAL_GPIO_ReadPin(IN4_GPIO_Port,IN4_Pin)
#define	IN5 HAL_GPIO_ReadPin(IN5_GPIO_Port,IN5_Pin)
#define	IN6 HAL_GPIO_ReadPin(IN6_GPIO_Port,IN6_Pin)
#define	IN7 HAL_GPIO_ReadPin(IN7_GPIO_Port,IN7_Pin)
#define	IN8 HAL_GPIO_ReadPin(IN8_GPIO_Port,IN8_Pin)

/*直线pid参数*/
#define CAR_LINE_PID_KP          250.0f    
#define CAR_LINE_PID_KI          0.0f
#define CAR_LINE_PID_KD          0.0f 
#define CAR_LINE_PID_MAX_OUT     1000.0f 
#define CAR_LINE_PID_MAX_IOUT    0.0f 

typedef struct
{
   pid_type_def car_line_pid;                  //直线pid
}car_t;

// 定义PWM定时器
void car(void);
void car_init(void);

#endif
