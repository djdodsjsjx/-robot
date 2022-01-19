#include "usart3.h"	  

u8 OPENMV_com_data;

//===========P4->RX, P5->TX==========
void Usart3_Init(u32 bound)
{
	GPIO_InitTypeDef   GPIO_InitStructure;
	USART_InitTypeDef  USART_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);
	
	//USART3_TX		PB.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;					//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//USART3_RX		PB.11
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;			//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//�Դ���3ͨ��Э����г�ʼ������
	USART_InitStructure.USART_BaudRate = bound;						//���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//1λֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;				//����żЧ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	//��Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;	//˫��ͨ��
	USART_Init(USART3, &USART_InitStructure);
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);					//���������ж�	
	USART_Cmd(USART3, ENABLE);

	//�Դ���3�շ��ж�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);					//�ж���ѡ�ڶ���
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;  				
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_USART3_P;  		//��ռ���ȼ�2��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_USART3_S;  			//�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 				//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);
}


static u8 Tx3Buffer[256];
static u8 Tx3Counter=0;
static u8 Tx3count=0;


void Uart3_Put_Char(unsigned char DataToSend)
{
	Tx3Buffer[Tx3count++] = DataToSend;
	USART_ITConfig(USART3, USART_IT_TXE,ENABLE);
}
	
void Uart3_Put_Buf(unsigned char *DateToSend, u8 data_num)
{
	u8 i;
	for(i=0;i<data_num;i++)
		Tx3Buffer[Tx3count++] = *(DateToSend+i);
	if(!(USART3->CR1 & USART_CR1_TXEIE))
	{
		USART_ITConfig(USART3, USART_IT_TXE,ENABLE);
	}
}



void USART3_IRQHandler(void)  
{
	if(USART_GetITStatus(USART3,USART_IT_ORE)!=RESET)
	{
		USART_ReceiveData(USART3);
	}
	
	//�����ж�
  if(USART3->SR &(3<<7)&&(USART3->CR1&USART_CR1_TXEIE))
	{
		USART3->DR=Tx3Buffer[Tx3Counter++];
		if(Tx3Counter==Tx3count)
		{
			USART3->CR1&=~USART_CR1_TXEIE;
			
		}
	}
	//�����ж�
	if(USART3->SR &(1<<5))
	{
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
		OPENMV_com_data = USART3->DR;
		OpenMV_Byte_Get(OPENMV_com_data);
		
	}
}


