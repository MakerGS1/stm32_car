#include "car.h"
#include "l298n.h"

#define speed  500
#define ds  20

//car_t car;
uint8_t g_ucaHW_Read[8] = {0};//�������Թܵ�ƽ������
int32_t g_cThisState = 0;//���״̬
int32_t g_cLastState = 0; //�ϴ�״̬
float g_fHW_PID_Out;//����Թ�PID��������ٶ�
float g_fHW_PID_Out1;//���1�����ѭ��PID�����ٶ�
float g_fHW_PID_Out2;//���2�����ѭ��PID�����ٶ�
fp32 speed_l = speed;
fp32 speed_r = speed;
car_t car_pid;
void car(void) {
	g_ucaHW_Read[0] = IN1;//��ȡ����Թ�״̬�����������д��if�������Ч
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
        g_cThisState = 0;//ǰ��
    }
    else if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 1&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = -1;//Ӧ����ת
    }
    else if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 1&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = -2;//������ת

    }
    else if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 1&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = -3;//������ת

    }
    else if(g_ucaHW_Read[0] == 1&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = -4;//������ת

    }
	 else if(g_ucaHW_Read[0] == 1&&g_ucaHW_Read[1] == 1&&g_ucaHW_Read[2] == 1&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = -4;//������ת

    }
	else if(g_ucaHW_Read[0] == 1&&g_ucaHW_Read[1] == 1&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = -4;//������ת

    }
	else if(g_ucaHW_Read[0] == 1&&g_ucaHW_Read[1] == 1&&g_ucaHW_Read[2] == 1&&g_ucaHW_Read[3] == 1&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = -4;//������ת

    }
	
	
	
	
    else if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 1&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = 1;//������ת

    }
	
	    else if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 1&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = 2;//������ת

    }
	    else if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 1&&g_ucaHW_Read[7] == 0)
    {
        g_cThisState = 3;//������ת

    }
	    else if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 0&&g_ucaHW_Read[7] == 1)
    {
        g_cThisState = 4;//������ת

    }
	
	else if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 0&&g_ucaHW_Read[6] == 1&&g_ucaHW_Read[7] == 1)
    {
        g_cThisState = 4;//������ת

    }
	else if(g_ucaHW_Read[0] == 0&&g_ucaHW_Read[1] == 0&&g_ucaHW_Read[2] == 0&&g_ucaHW_Read[3] == 0&&
			g_ucaHW_Read[4] == 0&&g_ucaHW_Read[5] == 1&&g_ucaHW_Read[6] == 1&&g_ucaHW_Read[7] == 1)
    {
        g_cThisState = 4;//������ת

    }	

    g_fHW_PID_Out = PID_calc(&car_pid.car_line_pid, g_cThisState, 0); //PID�������Ŀ���ٶ� ����ٶȣ���ͻ����ٶȼӼ�
    g_fHW_PID_Out1 = speed + g_fHW_PID_Out;//���1�ٶ�=�����ٶ�+ѭ��PID����ٶ�
    g_fHW_PID_Out2 = speed - g_fHW_PID_Out;//���1�ٶ�=�����ٶ�-ѭ��PID����ٶ�
//    if(g_fHW_PID_Out1 >5) g_fHW_PID_Out1 =5;//�����޷� �޷��ٶ���0-5֮��
//    if(g_fHW_PID_Out1 <0) g_fHW_PID_Out1 =0;
//    if(g_fHW_PID_Out2 >5) g_fHW_PID_Out2 =5;
//    if(g_fHW_PID_Out2 <0) g_fHW_PID_Out2 =0;
    if(g_cThisState != g_cLastState)//������״̬�������ϴ�״̬���ͽ��иı�Ŀ���ٶȺͿ��Ƶ�����ڶ�ʱ�������ɶ�ʱ���Ƶ��
    {
        Motor_SetSpeed(g_fHW_PID_Out1, g_fHW_PID_Out2);//ͨ��������ٶȿ��Ƶ��
	}
}

void car_init(void) {
	const static fp32 car_line_pid[3] = {CAR_LINE_PID_KP, CAR_LINE_PID_KI, CAR_LINE_PID_KD};
PID_init(&car_pid.car_line_pid, PID_POSITION, car_line_pid, CAR_LINE_PID_MAX_OUT, CAR_LINE_PID_MAX_IOUT);

}
