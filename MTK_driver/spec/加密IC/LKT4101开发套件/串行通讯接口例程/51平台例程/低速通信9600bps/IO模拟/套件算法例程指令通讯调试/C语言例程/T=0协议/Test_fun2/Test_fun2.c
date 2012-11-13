#include<reg51.h>

#define	uchar  unsigned  char
#define	uint   unsigned  int
sbit	REST = P2^2;
sbit	IO   = P2^0;

uchar	buf[25];										//���ݻ�����
uchar	SendBuf_1[22]={0x80,0x08,0x00,0x00,0x11,0x02,0xAA,
						0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
						0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff	};
				

uchar	SendBuf_2[5]={0x00,0xc0,0x00,0x00,0x08}	;

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
		SendChar = 	Send[n];	 
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
	uchar  temp;
	temp = SendBuf_1[1];			  //���������͵ڶ��ֽ�
	Rest();
	ReceArt(17); 					  //������������ʱ�㹻��������LKT����оƬ��MCU���ͷ�����Ϣ��ʱ�䣩������LKT����оƬ��������
	Delay_100us();	
	SendChar(5,SendBuf_1)	;		 //����T=0Э������LKT����оƬ����ǰ5�ֽڣ�LKT����оƬӦ���صڶ��ֽ�
	ReceArt(1);	
	if(buf[0] == temp)				 //�ж��Ƿ񷵻صڶ��ֽڣ�������ȷ����ʣ�µ��ֽ�
	{	
		
		SendChar(17,&SendBuf_1[5]);
		ReceArt(2);	
		  									
	}			  
	if(buf[0]==0x61 && buf[1] ==0x08 );	  //�ж�Ӧ��λ�Ƿ���ȷ
	SendChar(5,SendBuf_2) ;				  //Ӧ����ȷ���Ͷ�ȡ������Ϣ
	ReceArt(10);	
	while(1);
}