#include "car.h"
#include "l298n.h"

#define speed  500
#define ds  20

//car_t car;
uint8_t g_ucaHW_Read[8] = {0};//保存红外对管电平的数组
int32_t g_cThisState = 0;//这次状态
int32_t g_cLastState = 0; //上次状态
float g_fHW_PID_Out;//红外对管PID计算输出速度
float g_fHW_PID_Out1;//电机1的最后循迹PID控制速度
float g_fHW_PID_Out2;//电机2的最后循迹PID控制速度
fp32 speed_l = speed;
fp32 speed_r = speed;
car_t car_pid;
void car(void) {
	g_ucaHW_Read[0] = IN1;//读取红外对管状态、这样相比于写在if里面更高效
	g_ucaHW_Read[1] = IN2;
	g_ucaHW_Read[2] = IN3;
	g_ucaHW_Read[3] = IN4;
	g_ucaHW_Read[4] = IN5;
	g_ucaHW_Read[5] = IN6;
	g_ucaHW_Read[6] = IN7;
	g_ucaHW_Read[7] = IN8;
	
	if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
	   g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = 0;//前进
    }
    else if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 1&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = -1;//应该右转
    }
    else if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 1&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = -2;//快速右转

    }
    else if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 1&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = -3;//快速右转

    }
    else if(g_ucaHW_Read[0] == 1&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = -4;//快速右转

    }
	 else if(g_ucaHW_Read[0] == 1&&g_ucaHW_Read[1] == 1&&g_ucaHW_Read[2] == 1&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = -4;//快速右转

    }
	else if(g_ucaHW_Read[0] == 1&&g_ucaHW_Read[1] == 1&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = -4;//快速右转

    }
	else if(g_ucaHW_Read[0] == 1&&g_ucaHW_Read[1] == 1&&g_ucaHW_Read[2] == 1&&g_ucaHW_Read[3] == 1&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = -4;//快速右转

    }
	
	
	
	
    else if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 1&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = 1;//快速右转

    }
	
	    else if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 1&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = 2;//快速右转

    }
	    else if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 1&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = 3;//快速右转

    }
	    else if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 1)
    {
        g_cThisState = 4;//快速右转

    }
	
	else if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 1&&g_ucaHW_Read[7] == 1)
    {
        g_cThisState = 4;//快速右转

    }
	else if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 1&&g_ucaHW_Read[6] == 1&&g_ucaHW_Read[7] == 1)
    {
        g_cThisState = 4;//快速右转

    }	

    g_fHW_PID_Out = PID_calc(&car_pid.car_line_pid, g_cThisState, 0); //PID计算输出目标速度 这个速度，会和基础速度加减
    g_fHW_PID_Out1 = speed + g_fHW_PID_Out;//电机1速度=基础速度+循迹PID输出速度
    g_fHW_PID_Out2 = speed - g_fHW_PID_Out;//电机1速度=基础速度-循迹PID输出速度
//    if(g_fHW_PID_Out1 >5) g_fHW_PID_Out1 =5;//进行限幅 限幅速度在0-5之间
//    if(g_fHW_PID_Out1 <0) g_fHW_PID_Out1 =0;
//    if(g_fHW_PID_Out2 >5) g_fHW_PID_Out2 =5;
//    if(g_fHW_PID_Out2 <0) g_fHW_PID_Out2 =0;
    if(g_cThisState != g_cLastState)//如何这次状态不等于上次状态、就进行改变目标速度和控制电机、在定时器中依旧定时控制电机
    {
        Motor_SetSpeed(g_fHW_PID_Out1, g_fHW_PID_Out2);//通过计算的速度控制电机
	}
}

void car_init(void) {
	const static fp32 car_line_pid[3] = {CAR_LINE_PID_KP, CAR_LINE_PID_KI, CAR_LINE_PID_KD};
PID_init(&car_pid.car_line_pid, PID_POSITION, car_line_pid, CAR_LINE_PID_MAX_OUT, CAR_LINE_PID_MAX_IOUT);

}
