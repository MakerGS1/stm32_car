#include <sensor.h>
uint8_t sensor(void)																																							//读取各个引脚状态，来判断灰度传感器的状态
{
	GPIO_PinState IN1= HAL_GPIO_ReadPin(IN1_GPIO_Port,IN1_Pin);																			//读取IN1的状态值
	GPIO_PinState IN2= HAL_GPIO_ReadPin(IN2_GPIO_Port,IN2_Pin);																			//读取IN2的状态值
	GPIO_PinState IN3= HAL_GPIO_ReadPin(IN3_GPIO_Port,IN3_Pin);																			//读取IN2的状态值
	GPIO_PinState IN4= HAL_GPIO_ReadPin(IN4_GPIO_Port,IN4_Pin);																			//读取IN2的状态值
	
	if((IN1==GPIO_PIN_RESET)&&(IN2==GPIO_PIN_RESET)&&(IN3==GPIO_PIN_RESET)&&(IN4==GPIO_PIN_RESET))
		return 0;  //0000
	if((IN1==GPIO_PIN_RESET)&&(IN2==GPIO_PIN_RESET)&&(IN3==GPIO_PIN_RESET)&&(IN4==GPIO_PIN_SET))
		return 1;  //0001
	if((IN1==GPIO_PIN_RESET)&&(IN2==GPIO_PIN_RESET)&&(IN3==GPIO_PIN_SET)&&(IN4==GPIO_PIN_RESET))
		return 2;  //0010	
	if((IN1==GPIO_PIN_RESET)&&(IN2==GPIO_PIN_RESET)&&(IN3==GPIO_PIN_SET)&&(IN4==GPIO_PIN_RESET))
		return 3;  //0011	
	else if((IN1==GPIO_PIN_RESET)&&(IN2==GPIO_PIN_SET)&&(IN3==GPIO_PIN_RESET)&&(IN4==GPIO_PIN_RESET))
		return 4;  //0100
	else if((IN1==GPIO_PIN_RESET)&&(IN2==GPIO_PIN_SET)&&(IN3==GPIO_PIN_RESET)&&(IN4==GPIO_PIN_SET))
		return 5;  //0101
	else if((IN1==GPIO_PIN_RESET)&&(IN2==GPIO_PIN_SET)&&(IN3==GPIO_PIN_SET)&&(IN4==GPIO_PIN_RESET))
		return 6;  //0110
	else if((IN1==GPIO_PIN_RESET)&&(IN2==GPIO_PIN_SET)&&(IN3==GPIO_PIN_SET)&&(IN4==GPIO_PIN_SET))
		return 7;  //0111
	else if((IN1==GPIO_PIN_SET)&&(IN2==GPIO_PIN_RESET)&&(IN3==GPIO_PIN_RESET)&&(IN4==GPIO_PIN_RESET))
		return 8;  //1000
	else if((IN1==GPIO_PIN_SET)&&(IN2==GPIO_PIN_RESET)&&(IN3==GPIO_PIN_RESET)&&(IN4==GPIO_PIN_SET))
		return 9;  //1001
	else if((IN1==GPIO_PIN_SET)&&(IN2==GPIO_PIN_RESET)&&(IN3==GPIO_PIN_SET)&&(IN4==GPIO_PIN_RESET))
		return 10; //1010
	else if((IN1==GPIO_PIN_SET)&&(IN2==GPIO_PIN_RESET)&&(IN3==GPIO_PIN_SET)&&(IN4==GPIO_PIN_SET))
		return 11; //1011
	else if((IN1==GPIO_PIN_SET)&&(IN2==GPIO_PIN_SET)&&(IN3==GPIO_PIN_RESET)&&(IN4==GPIO_PIN_RESET))
		return 12; //1100
	else if((IN1==GPIO_PIN_SET)&&(IN2==GPIO_PIN_SET)&&(IN3==GPIO_PIN_RESET)&&(IN4==GPIO_PIN_SET))
		return 13; //1101
	else if((IN1==GPIO_PIN_SET)&&(IN2==GPIO_PIN_SET)&&(IN3==GPIO_PIN_SET)&&(IN4==GPIO_PIN_RESET))
		return 14; //1110
	else if((IN1==GPIO_PIN_SET)&&(IN2==GPIO_PIN_SET)&&(IN3==GPIO_PIN_SET)&&(IN4==GPIO_PIN_SET))
		return 15; //1111
	else
		return 16;	
	
}

