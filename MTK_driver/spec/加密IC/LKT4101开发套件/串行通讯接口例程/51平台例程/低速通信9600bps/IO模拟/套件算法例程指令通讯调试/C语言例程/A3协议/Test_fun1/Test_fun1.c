#include<reg51.h>

#define	uchar  unsigned  char
#define	uint   unsigned  int
sbit	REST = P2^2;
sbit	IO   = P2^0;

uchar	buf[25];										//���ݻ�����
uchar	SendBuf_1[20]={0xA3,0x12,0x01,0x01,0x02,0x03,0x04,0x05,
						0x06,0x07,0x08,0x08,0x11,0x22,0x33,0x44,
						0x55,0x66,0x77,0x88};


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

void SendChar(uchar m,uchar Send[])
{
    uchar i,n,flag,SendChar;
	
	for(n = 0 ;n<m ; n++)
	{	
		ACC  = Send[n] ;
		flag = P;
		SendChar = 	Send[n];	 		//�����͵��ֽڷ���SendChar
		IO  = 0;
		for(i=0;i<8;i++)			   //����һ���ֽ�
		{
			Delay_100us();
			if(SendChar & 0x01)
				IO = 1;
			else
				IO = 0;
			SendChar >>=1;
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
	ReceArt(17); 						 //������������ʱ�㹻��������LKT����оƬ��MCU���ͷ�����Ϣ��ʱ�䣩������LKT����оƬ��������
	Delay_100us();	
	SendChar(20,SendBuf_1)	;		 	//��SendBuf�ĳ��Ⱥ��׵�ַ����SendChar(uchar m,uchar Send[])
	ReceArt(10);	
	while(1);
}
