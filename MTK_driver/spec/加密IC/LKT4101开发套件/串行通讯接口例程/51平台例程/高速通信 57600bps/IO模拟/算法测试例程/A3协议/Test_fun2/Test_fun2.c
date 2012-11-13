
/*********************��Ƭ������Ϊ24MHZ    ����оƬʹ��3.6864MHZ *******************************/

#include<reg51.h>

#define	uchar  unsigned  char
#define	uint   unsigned  int

sbit	REST = P2^2;			  //���帴λ��
sbit	IO   = P2^0;			  //�������ݽ�


uchar	buf[25];								//���ݻ�����
uchar	SendBuf[4]={0xFF,0x10,0x94,0x7B} ;		//	���͸���ͨѶ����������ͨѶ�ٶ�Ϊ��fosc/64��
uchar	SendBuf_1[19]={0xA3,0x11,0x02,0xAA,0xAA,0xAA,0xAA,
						0xAA,0xAA,0xAA,0xAA,0xFF,0xFF,0xFF,0xFF,
						0xFF,0xFF,0xFF,0xFF};  

/*��������ʵ��DES������ʾ����Ӧ���� A3 08 5555555555555555  */


/*****************����΢�����ͽ��յ�ʱ��**************/
void Delay_33us()				 		
{
	uchar	i;
	for(i=0;i<19;i++);
}	
	
/*********************���ͽ���һλ��ʱ�� etu=372/3.6864 = 100us*************
***************���ͽ�������ָ��ҲҪռ��ʱ�������	DelayEtu = 90us********/
void Delay_90us()					
{									
	uchar   i;
	for(i=0;i<58;i++);
}

/*****************�ϵ緢�͸�λ����******************/
void Rest()							
{
	IO   = 1;			    		//����Ϊ�ߵȴ�����LKT����оƬ���͵���ʼλ
	REST = 0;
	Delay_90us();
	REST = 1; 
} 

/****************��ȡLTK4101�ķ�����Ϣ������������ݻ�����****************/
void ReceArt(char m)	   		   
{
	uchar i,n,sec;
	
	for(n=0;n<m;n++)
	{	
		while(IO);
		Delay_33us();				 //����ʱ��Ŀ����ʹIO�ڽ������ݵ�ʱ����оƬ����ÿλ���ݵĽ����м�λ��
		for(i=0;i<8;i++)   		    //��һ���ֽں��� ��ѭ��һ�ε�ʱ���Լ100us  ���� 
		{
			Delay_90us();
			for(sec=0;sec<3;sec++);	  //΢��ʱ��
			buf[n] >>= 1;
			if(1 == IO)
				buf[n] |= 0x80;
		}
		Delay_90us(); 
		ACC = buf[n];								   
		if(IO == P)				    //�ж�żУ��λ
		{
		    Delay_90us();			//��ʱ����ֹͣλ
		  	Delay_90us();
		}  	
	}
}

/****************���ռ���оƬ��57600kbps�µķ�����Ϣ������������ݻ�����****************/
void ReceArt_1(char m)	   		   
{
	uchar i,n,sec;
	for(n=0;n<m;n++)
	{	
		while(IO);
		for(sec=0;sec<5;sec++);		 //����ʱ��Ŀ����ʹIO�ڽ������ݵ�ʱ����оƬ����ÿλ���ݵĽ����м�λ��
		for(i=0;i<8;i++)   		     //��һ���ֽں��� ��ѭ��һ�ε�ʱ���Լ17us ���� 
		{
			for(sec=0;sec<5;sec++);
			buf[n] >>= 1;
			if(1 == IO)
				buf[n] |= 0x80;
		}
		for(sec=0;sec<10;sec++); 
		ACC = buf[n];								   
		if(IO == P)				    //�ж�żУ��λ
		{
			Delay_33us();		    //��ʱ����ֹͣλ
		}  	
	}
}

/****************���������������Ϣ***************/

void SendChar(uchar m,uchar Send[])
{
    uchar i,n,flag,sec,SendChar;
	
	for(n = 0 ;n<m ; n++)
		{	 
			
			ACC  = Send[n] ;
			flag = P;
			SendChar = 	Send[n];	 		//�����͵��ֽڷ���SendChar		
			IO  = 0;	
			for(i=0;i<8;i++)			   //����һ���ֽ�
			{
				Delay_90us();	
				for(sec=0;sec<5;sec++);	
				if(SendChar & 0x01)
					IO = 1;
				else
					IO = 0;
				SendChar >>=1;
			}
			Delay_90us();
			IO = flag;					   //���ͱ������żλ
			Delay_90us();	
			IO = 1;						   //����ֹͣλ
			Delay_90us();				   //��ʱ����ֹͣλ
			Delay_90us();	
		}	
}	 

void SendChar_1(uchar m,uchar Send[])
{
    uchar i,n,flag,sec,SendChar;
	
		for(n = 0 ;n<m ; n++)
		{	
			
			ACC  = Send[n] ;
			flag = P;  
			SendChar = 	Send[n];	 		//�����͵��ֽڷ���SendChar	 
		   	IO  = 0;
			for(i=0;i<8;i++)			   //����һ���ֽ�
			{
				for(sec=0;sec<7;sec++);
				if(SendChar & 0x01)
					IO = 1;
				else
					IO = 0;
				SendChar >>=1;
			}
			for(sec=0;sec<9;sec++);
			IO = flag;					   //���ͱ������żλ
			for(sec=0;sec<9;sec++);	
			IO = 1;						   //����ֹͣλ
			for(sec=0;sec<11;sec++);		
		}
}
void main()
{
	Rest();							   //������������ʱ�㹻��������LKT����оƬ��MCU���ͷ�����Ϣ��ʱ�䣩������LKT����оƬ��������
	ReceArt(17); 					  
	Delay_90us();					  

	SendChar(4,SendBuf)	;		 	  //��SendBuf�ĳ��Ⱥ��׵�ַ����SendChar(uchar m,uchar Send[])
	ReceArt(4);						  //��������ӦΪ0xFF,0x10,0x94,0x7B

	SendChar_1(19,SendBuf_1)	;	  //��SendBuf_1�ĳ��Ⱥ��׵�ַ����SendChar_1(uchar m,uchar Send[])
	ReceArt_1(10);					  //��������ӦΪA3  08 5555555555555555
	while(1);
}