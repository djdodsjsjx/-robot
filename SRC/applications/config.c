#include "config.h"

float prep_time,launch_time,fall_time,stance_height,jump_extension,fall_extension,x_jump;
float IMU_ROL_Kp_G,IMU_PIT_Kp_G,IMU_POSX_12_Kp_G,IMU_POSX_34_Kp_G,OPENMV_Angle_Kp_G,OPENMV_Deviation_Kp_G;
float init_head_servo;
u8 pit_max_ang,rol_max_ang;
u8 PA_PO_FLAG,PA_PO_Status_TIMES,Turn_Left_FLAG,Turn_Left_Status_TIMES,Turn_Right_FLAG,Turn_Right_Status_TIMES;
leg_XYZ pos_leg_XYZ;
leg_XYZ trot_leg_XYZ;
leg_XYZ mix_leg_XYZ;
leg_angle angle_output;
leg_angle leg_rotation_Angle;
leg_angle init_leg_angle;
leg_angle Last_leg_rotation_Angle;
Body_parameters Body;
Motion_parameters Motion;

void data_config()
{
	Motion.start=0;   // 1->У׼     0->����
	Motion.faai=0.5;  	//0.25->walk��̬     0.5->trot��̬
	
	Body.l1_12 = 70;
	Body.l1_34 = 80;
	Body.l2_12=57;
	Body.l2_34=80;
	Body.l3=35;
	Body.b=85;     //��ǰ�����ԭ��֮��ľ���
	Body.l=183;    //����ڳ��ȷ������
	Body.h=85;
	Body.w=Body.b+2*Body.l3;    //����ڿ�ȷ������
	
	
	Motion.trot_speed=0.014;   //��Ƶ  
	Motion.turn_speed=0.01;
	Motion.t=0;           //ʱ��
	Motion.Ts=1;        //����
	Motion.h=45;
	// Motion.h_12=10;       //̧�ȸ߶�
	// Motion.h_34=40;
	
	IMU_ROL_Kp_G=1;         //��̬���Ʊ���ϵ��
	IMU_PIT_Kp_G=0;
	IMU_POSX_12_Kp_G=1.5;
	IMU_POSX_34_Kp_G=1.2;
	OPENMV_Angle_Kp_G=0.3;
	OPENMV_Deviation_Kp_G=0.1;

	pit_max_ang=15;    //����Ǽ���ֵ
	rol_max_ang=25;    //�����Ǽ���ֵ
	
	init_head_servo=90;   //ͷ�������ʼֵ
	
	init_leg_angle.gamma[0]=65;      // ��->��   С->��
	init_leg_angle.alfa[0]=160;      //	С->��   ��->��
	init_leg_angle.beta[0]=80;       // С->��   ��->�� 
	
	init_leg_angle.gamma[1]=60;	    //   ��->��  С->��
	init_leg_angle.alfa[1]=10;      //   С->��  ��->��
	init_leg_angle.beta[1]=100;      //   С->��  ��->��	

	init_leg_angle.gamma[2]=53;     //   ��->��  С->��
	init_leg_angle.alfa[2]=18;			//   С->��  ��->��
	init_leg_angle.beta[2]=90;		  //   С->��  ��->��	

	init_leg_angle.gamma[3]=50;     //   ��->��  С->��
	init_leg_angle.alfa[3]=168;			//   С->��  ��->��
	init_leg_angle.beta[3]=88;			//   С->��  ��->��			
	

	//��Ծ��������
	prep_time = 0.3;      //��Ծ׼��ʱ��
	launch_time = 0.5;    //��Ծ����ʱ��
	fall_time = 0.4;      //�½�����ʱ��
	stance_height = -60;   //��ǰ���ȳ���(mm)
	jump_extension = -140; //��ʱ�����ų���(mm)
	fall_extension = -60;  //�½�ʱ�ȳ���(mm)
	x_jump=-10;           //x��ʼ����λ��

}

void init_config(void)
{  
	SysTick_Configuration();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(500000); 	
	Usart3_Init(500000);
	Scheduler_Setup();
	pwm_servo_init();	
	LED_Init();	
	OLED_Init();
	MPU6050_initialize();
	TIM_INIT();
//	
//	MPU9250_INIT();
	Dog_Start();
}
