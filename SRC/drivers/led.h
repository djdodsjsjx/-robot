#ifndef __LED_H
#define __LED_H	 
#include "config.h"
 

#define Air_pump_on   PBout(12) = 1;   //���ÿ�
#define Air_pump_off  PBout(12) = 0;   //���ù�

//��λ��ͨ
#define Electromagnetic_valve1_Inhale   PBout(14) = 0;   //����->����
#define Electromagnetic_valve1_Deflation   PBout(14) = 1;   //����->����

#define Electromagnetic_valve2_Inhale   PAout(12) = 0;   //����->����
#define Electromagnetic_valve2_Deflation   PAout(12) = 1;   //����->����

#define Electromagnetic_valve3_Inhale   PAout(15) = 0;   //����->����
#define Electromagnetic_valve3_Deflation   PAout(15) = 1;   //����->����

//��λ��ͨ  ����
//���ýӿ���
#define Electromagnetic_valve2_connect   PBout(14) = 0;   //��ŷ���ͨ   
#define Electromagnetic_valve2_disconnect   PBout(14) = 1;   //��ŷ��Ͽ�

#define Electromagnetic_valve3_connect   PBout(15) = 0;   //��ŷ���ͨ   
#define Electromagnetic_valve3_disconnect   PBout(15) = 1;   //��ŷ��Ͽ�   

void LED_Init(void);//��ʼ��
void LED_demo(void);
void Sucker13_on(void);
void Sucker13_off(void);
void Sucker24_on(void);
void Sucker24_off(void);	
void Sucker1234_on(void);	 				    
#endif
