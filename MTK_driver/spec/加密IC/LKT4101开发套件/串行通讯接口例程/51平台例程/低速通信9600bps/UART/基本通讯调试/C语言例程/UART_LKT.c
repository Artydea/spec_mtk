/*��Ƭ��ʵ�ָ�LKT����оƬ��ͨѶ������ȷʵ�����渴λӦ���Լ���ȡ�����������ͨѶ�ͳ����ɹ�*/
  /*��������Ϊ����1�� ʵ��LKT����оƬ�ĸ�λ ��2��ʵ�ֻ�ȡ���ֽڵ������*/
#include<reg51.h>

#define	uchar  unsigned  char
#define	uint   unsigned  int

uchar buf[25];
uchar Sendbuf[5]={0x00,0x84,0x00,0x00,0x08};
sbit	REST = P2^0;
sbit	IO   = P3^1;

void Delay()					
{									
	uchar   i;
	for(i=0;i<27;i++);
}

void Rest()							
{
	IO   = 1;			    //����Ϊ�ߵȴ�����LKT����оƬ���͵���ʼλ
	REST = 0;
	Delay();
	REST = 1; 
}
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
void Send()
{
	uchar i;
	for(i=0;i<5;i++)
	{
		ACC  = Sendbuf[i];
		TB8  = P;				//����żУ��λ����TB8
		SBUF = Sendbuf[i];
		while(!TI);
		TI = 0;
		Delay();
		
	}

}	
void main()
{	
	Uart_init();
	Rest();	   
	Rece(17);
	Delay();
	Send();	
	Rece(11);
	P0 = buf[9];
	while(1);	
}