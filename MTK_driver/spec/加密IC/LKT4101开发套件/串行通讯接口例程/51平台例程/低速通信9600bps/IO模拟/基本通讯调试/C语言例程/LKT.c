/*��Ƭ��ʵ�ָ�LKT����оƬ��ͨѶ������ȷʵ�����渴λӦ���Լ���ȡ�����������ͨѶ�ͳ����ɹ�*/

/*��������Ϊ����1�� ʵ��LKT����оƬ�ĸ�λ ��2��ʵ�ֻ�ȡ���ֽڵ������*/

#include<reg51.h>

#define	uchar  unsigned  char
#define	uint   unsigned  int
sbit	REST = P2^2;
sbit	IO   = P2^0;

uchar	buf[25];										//���ݻ�����
uchar	SendBuf[5]={0x00,0x84,0x00,0x00,0x10} ;			//��ȡ���ֽ����������

/*****************����΢�����ͽ��յ�ʱ��**************/
void Delay()				 		
{
	uchar	i;
	for(i=0;i<3;i++);
}	
	
/*********************���ͽ���һλ��ʱ�� etu=372/3.579 = 104us*************
***************���ͽ�������ָ��ҲҪռ��ʱ�������	DelayEtu = 90us********/
void Delay_100us()					
{									
	uchar   i;
	for(i=0;i<28;i++);
}

/*****************�ϵ緢�͸�λ����******************/
void Rest()							
{
	Delay() ;
	IO   = 1;			    		//����Ϊ�ߵȴ�����LKT����оƬ���͵���ʼλ
	REST = 0;
	Delay_100us();
	REST = 1; 
} 

/****************��ȡLTK4101�ķ�����Ϣ������������ݻ�����****************/
void ReceArt(char m)	   		   
{
	uchar i,n;
	
	for(n=0;n<m;n++)
	{	
		while(IO);
		for(i=0;i<8;i++)   		   //��һ���ֽں��� 
		{
			Delay_100us();
			buf[n] >>= 1;
			if(1 == IO)
				buf[n] |= 0x80;
		}
		Delay_100us();
		ACC = buf[n];							   
		if(IO == P)				    //�ж�żУ��λ
		{
		   Delay_100us();
		   Delay_100us();
		}  	
	}

}

/****************���������������Ϣ***************/

void SendChar()
{
    uchar i,n,flag;
	
	for(n = 0 ;n<5 ; n++)
	{	
		ACC  = SendBuf[n] ;
		flag = P; 
		IO  = 0;
		for(i=0;i<8;i++)			   //����һ���ֽ�
		{
			Delay_100us();
			if(SendBuf[n] & 0x01)
				IO = 1;
			else
				IO = 0;
			SendBuf[n] >>=1;
		}
		Delay_100us();
		IO = flag;					   //���ͱ������żλ
		Delay_100us();	
		IO = 1;						   //����ֹͣλ
		Delay_100us();	
		Delay_100us();   		
	}
}	 

void main()
{
	Rest();	
	ReceArt(17); 	 	   //���ո�λ��Ϣ
	Delay_100us();
	SendChar()	;
	ReceArt(19);		  //�����������Ϣ
	P0 = buf[17];
	while(1);
}
