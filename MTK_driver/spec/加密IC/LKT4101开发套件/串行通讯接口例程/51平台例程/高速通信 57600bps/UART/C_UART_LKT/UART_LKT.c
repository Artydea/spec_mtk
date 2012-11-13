  /*��������Ϊ����1�� ʵ��LKT����оƬ�ĸ�λ ��2��ʵ�ֻ�ȡ���ֽڵ������
  *********************��Ƭ������Ϊ11.0592MHZ��   ����оƬʹ��3.6864MHZ *******************************/
#include<reg51.h>

#define	uchar  unsigned  char
#define	uint   unsigned  int

uchar buf[25]=0;
uchar Sendbuf[4]={0xFF,0x10,0x94,0x7B};			 //	���͸���ͨѶ����������ͨѶ�ٶ�Ϊ��fosc/64��  
uchar Sendbuf_1[5]={0x00,0x84,0x00,0x00,0x08};	 //��ȡ���ֽ����������

sbit	REST = P2^0;							 //��λ��

void Delay()					
{									
	uchar   i;
	for(i=0;i<26;i++);
}						

/*UART��ʼ��������1��ʼλ��8����λ��żУ�顢2ֹͣλ */
void Uart_init()
{
	TMOD = 0x20;			// ��ʱ��1������8λ�Զ�����ģʽ, ���ڲ���������
	TH1 = 0xFD;				// ������9600
	TL1 = 0xFD;
	SCON = 0xD0;			// �趨���пڹ�����ʽ
	PCON &= 0xef;			// �����ʲ�����	
	TR1 = 1;				// ������ʱ��1
	IE = 0x0;				// ��ֹ�κ��ж�
}

/*9600Kbps�µĽ��պ���*/
void Rest()							
{
	REST = 0;
	Delay();
	REST = 1; 
}
	
/*57600Kbps�µĽ��պ���*/
void Rece(uchar m)
{
	   uchar i;
	   for(i=0; i<m;i++)
	   {
			while(!RI);			// �Ƿ������ݵ���				
			buf[i] = SBUF;		// �ݴ���յ�������	  		
			RI = 0;	
		}

}
/*9600Kbps�µķ��ͺ���*/

void Send()
{
	uchar i;
	for(i=0;i<4;i++)
	{
		ACC  = Sendbuf[i];
		TB8  = P;				//����żУ��λ����TB8
		SBUF = Sendbuf[i];
		while(!TI);				// �Ƿ����ݴ������
		TI = 0;
		Delay(); 				//��ʱ1��etu ��Ϊ51��Ƭ��ֻ�ܷ���1��ֹͣλ��
								//���Լ�һ����ʱ�ӳ�ֹͣΪʱ��
	}

}

/*57600Kbps�µķ��ͺ���*/

void Send_1()
{
	uchar i,sec;
	for(i=0;i<5;i++)
	{
		ACC  = Sendbuf_1[i];
		TB8  = P;				 //����żУ��λ����TB8
		SBUF = Sendbuf_1[i];
		while(!TI);
		TI = 0;					  //��ʱ1��etu ��Ϊ51��Ƭ��ֻ�ܷ���1��ֹͣλ��
		for(sec=0;sec<4;sec++);   //���Լ�һ����ʱ�ӳ�ֹͣΪʱ��		
	}

}	

void main()
{	
	Uart_init();			 //UART��ʼ��
	Rest();	   				 //��λ����оƬ
	Rece(17);				 //���ո�λ��Ϣ
	Delay();

	Send();					 //���͸�������
	Rece(4);   				 //���ٳɹ��Ļ�оƬ���ص����ݺͷ���������ͬ

	Delay();
	TL1 = 0xFF;				 //����57600kbps�ĳ�ֵ
	TH1 = 0xFF;			
	PCON |= (1<<7);	 		// �����ʱ������ﵽ57600kbps
	
			   	
	Send_1();  				 //��57600kbps���ͻ�ȡ���������
	Rece(11);				 //���շ������ݣ�84 + 8�ֽ������ + 90 00��
	while(1);	 
}