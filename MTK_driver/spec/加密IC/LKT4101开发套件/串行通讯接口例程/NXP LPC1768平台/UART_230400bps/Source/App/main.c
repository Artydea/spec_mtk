/****************************************Copyright (c)****************************************************
**                                 http://www.PowerAVR.com
**								   http://www.PowerMCU.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           main.c
** Last modified Date:  2010-05-12
** Last Version:        V1.00
** Descriptions:        The main() function example template
**
**--------------------------------------------------------------------------------------------------------
** Created by:          PowerAVR
** Created date:        2010-05-10
** Version:             V1.00
** Descriptions:        ��дʾ������
**
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#include "LPC17xx.h"
#include "uart.h"

/*********************************************************************************************************
** Function name:       Delay
** Descriptions:        �����ʱ
** input parameters:    ulTime
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/


/*���ų�ʼ��*/
void Rest(void)
{
	char i;
	LPC_GPIO2->FIODIR |= (1<<0);			//��λ�����ó����
	LPC_GPIO2->FIODIR |= (1<<7);  			//���ݽ����ó����
	LPC_GPIO2->FIOPIN &= ~(1<<0); 			//��λ������
 
	for(i=0;i<108;i++); 
	LPC_GPIO2->FIOPIN |= (1<<7);			 //���ݽϱ��ָߵ�ƽ 
	LPC_GPIO2->FIOPIN |= (1<<0);			 //��λ������
}


char SendBuf_0[4]={0xff,0x10,0x96,0x79};		 //������������
char SendBuf_1[5]={0x00,0x84,0x00,0x00,0x08} ;	 //���ͻ�ȡ���������
int main(void)
{
	char usFdiv;
	SystemInit();
	UART0_Init();								 //��ʼ������
	Rest();										 //��λ
	UART0_GetChar(17);							 //���ո�λ��Ϣ
		  
	UART0_SendByte(4,SendBuf_0); 				 //������������
	UART0_GetChar(4);

	LPC_UART0->LCR  = 0x83;                      /* �������ò�����               */
    usFdiv = (11059200*2 / 16) / 230400;         /* ���ò�����                   */
    LPC_UART0->DLM  = usFdiv / 256;
    LPC_UART0->DLL  = usFdiv % 256; 
	
    LPC_UART0->LCR  = 0x1F;                      /* ����������                   */
    LPC_UART0->FCR  = 0x87; 					  //��ս��շ��ͼĴ���

	UART0_SendByte(5,SendBuf_1);				  //���ͻ�ȡ���������
	UART0_GetChar(11);							  //��ȡ�����
	while(1);
}
