/****************************************Copyright (c)****************************************************
**                                 http://www.PowerAVR.com
**								   http://www.PowerMCU.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           uart.c
** Last modified Date:  2010-05-12
** Last Version:        V1.00
** Descriptions:        
**
**--------------------------------------------------------------------------------------------------------
** Created by:          PowerAVR
** Created date:        2010-05-10
** Version:             V1.00
** Descriptions:        ��дʾ������
**
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/
#include "lpc17xx.h"                              /* LPC17xx definitions    */
#include "uart.h"

#define FOSC                       11059200                           /*  ����Ƶ��                  */

#define FCCLK                      (FOSC  * 8)                          /*  ��ʱ��Ƶ��<=100Mhz          */
                                                                        /*  FOSC��������                */
#define FCCO                       (FCCLK * 3)                          /*  PLLƵ��(275Mhz~550Mhz)      */
                                                                        /*  ��FCCLK��ͬ���������ż���� */
#define FPCLK                      (FCCLK / 4)                          /*  ����ʱ��Ƶ��,FCCLK��1/2��1/4*/
                                                                        /*  ����FCCLK��ͬ               */

#define UART0_BPS     16129                                           /* ����0ͨ�Ų�����             */
/*********************************************************************************************************
** Function name:       UART0_Init
** Descriptions:        ��Ĭ��ֵ��ʼ������0�����ź�ͨѶ����������Ϊ8λ����λ��2λֹͣλ��żУ��
** input parameters:    ��
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void UART0_Init (void)
{
	uint16_t usFdiv;
    /* UART0 */
    LPC_PINCON->PINSEL0 |= (1 << 4);             /* Pin P0.2 used as TXD0 (Com0) */
    LPC_PINCON->PINSEL0 |= (1 << 6);             /* Pin P0.3 used as RXD0 (Com0) */
  
  	LPC_UART0->LCR  = 0x83;                      /* �������ò�����               */
    usFdiv = (FPCLK / 16) / UART0_BPS;           /* ���ò�����                   */
    LPC_UART0->DLM  = usFdiv / 256;
    LPC_UART0->DLL  = usFdiv % 256; 
    LPC_UART0->LCR  = 0x1F;                      /* ����������                   */
    LPC_UART0->FCR  = 0x87; 				   
}

/*********************************************************************************************************
** Function name:       UART0_SendByte
** Descriptions:        �Ӵ���0��������
** input parameters:    data: ���͵�����
** output parameters:   ��
** Returned value:      ��
*********************************************************************************************************/
void UART0_SendByte (char m, char Send[])
{
	 char i;	
	 for(i=0;i<m;i++)
	 {
     	LPC_UART0->THR = Send[i];
	 	while (!(LPC_UART0->LSR & 0x20));
	}
}

/*----------------------------------------------------------------------------
  Read character from Serial Port   (blocking read)
 *----------------------------------------------------------------------------*/
char buf[25];
void UART0_GetChar (char m) 
{
	char i;
	for(i=0;i<m;i++)
	{
  		while (!(LPC_UART0->LSR & 0x01));
  		buf[i] = LPC_UART0->RBR;
	}
}


