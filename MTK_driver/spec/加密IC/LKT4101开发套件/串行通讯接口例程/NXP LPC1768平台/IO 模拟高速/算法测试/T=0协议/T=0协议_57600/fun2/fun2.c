/**************LPC1768 ʹ��12MHZ����    ����оƬʹ��3.6864MHZ�ľ���*******************/
#include <LPC17xx.h>

/*1us��ʱ����*/
void Delay_1us(char Sec)
{
	char i,k;
	for(k=0;k<Sec;k++)
	{
		for(i=0;i<18;i++);
	}
}
unsigned char buf[30];			 //���ݴ洢��

/*���������������H = 1 Ϊ���٣�H = 0 Ϊ���� ; m Ϊ�����ֽڵĸ���*/
void ReceArt(char H,char m)	   		   
{
	unsigned char i,n;
	unsigned char cIO;
	LPC_GPIO2->FIODIR = 0x0000007f;// io��Ϊ����
	for(n=0;n<m;n++)
	{	
		while(LPC_GPIO2->FIOPIN & (1<<7));
		cIO = 0x00;
		if(H == 1)				 //H = 1 ʱΪ����ͨѶ
		{
			Delay_1us(8);	
		}
		else if(H == 0)			  //H = 0 ʱΪ����ͨѶ
		{
			Delay_1us(30);
		}
		for(i=0;i<8;i++)   		   //��һ���ֽں��� 
		{
			if(H == 1)
			{
				Delay_1us(17);
			}
			else if(H == 0)
			{
				Delay_1us(100);
			} 
			cIO >>= 1;
			if(LPC_GPIO2->FIOPIN & (1<<7))
			{
				cIO |= 0x80;
			}
		}
		buf[n] =cIO;
		if(H == 1)
		{
			Delay_1us(51);	
		}
		else if(H == 0)
		{
			Delay_1us(100);
			Delay_1us(200);
		}	
	}
}

char	Send_1[4]={0xFF,0x10,0x94,0x7B} ;	  //������������
char	Send_2[22]={0x80,0x08,0x00,0x00,0x11,0x02,0xAA,
						0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,
						0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff	};

char	Send_3[5]={0x00,0xc0,0x00,0x00,0x08};

/*���������������H = 1 Ϊ���٣�H = 0 Ϊ���� ; m Ϊ�����ֽڵĸ��� ; SendBuf[]������������*/
void SendChar(char H,char m,char SendBuf[])
{
    char i,n,flag,uChar;

	 LPC_GPIO2->FIODIR = 0x000000ff;	 //���ó����
	 
	for(n = 0 ;n<m ; n++)
	{	
		uChar  = SendBuf[n] ;
		flag = 0; 
		LPC_GPIO2->FIOPIN &= ~(1<<7);
		for(i=0;i<8;i++)			   //����һ���ֽ�
		{
			if(H == 1)
			{
				Delay_1us(17);	
			}
			else if(H == 0)
			{
				Delay_1us(103);
			}	
			
			if(uChar & 0x01)
			{
				LPC_GPIO2->FIOPIN |= (1<<7);
			    flag++;				 //�����ж�żУ��λ
			}
			else
			{
				LPC_GPIO2->FIOPIN &= ~(1<<7);
			}
			uChar >>=1;
		}

		if(H == 1)
		{
			Delay_1us(17);		
		}
		else if(H == 0)
		{
				Delay_1us(100);
		}

		if(flag%2 == 1)			   //�ж�У��λ
		{
			LPC_GPIO2->FIOPIN |= (1<<7);
		}
		else
		{
			LPC_GPIO2->FIOPIN &= ~(1<<7);
		}
		if(H == 1)					//��ʱһ��У��λ
		{
			Delay_1us(17);	
		}
		else if(H == 0)
		{
			Delay_1us(100);
		}	
		LPC_GPIO2->FIOPIN |= (1<<7);
		if(H == 1)				  //��ʱ����ֹͣλ
		{
			Delay_1us(34);	
		}
		else if(H == 0)
		{
			Delay_1us(200);
		}		   		
	}
}

/*���ų�ʼ��*/
void Rest(void)
{
	LPC_GPIO2->FIODIR |= (1<<0);			//��λ�����ó����
	LPC_GPIO2->FIODIR |= (1<<7);  			//���ݽ����ó����
	LPC_GPIO2->FIOPIN &= ~(1<<0); 			//��λ������
 
	Delay_1us(100); 
	LPC_GPIO2->FIOPIN |= (1<<7);			 //���ݽϱ��ָߵ�ƽ 
	LPC_GPIO2->FIOPIN |= (1<<0);			 //��λ������
}



/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int main (void)
{  
	char  temp;
	temp = Send_2[1];			//����ڶ����ֽ�
	Rest();						//��λ
	ReceArt(0,17);				//���ո�λ��Ϣ
	SendChar(0,4,Send_1);		//������������
	ReceArt(0,4);

	SendChar(1,5,Send_2);		//����T=0Э���ȷ���ǰ����ֽ�
	ReceArt(1,1);

	if(buf[0] == temp)			//�жϽ��յ��ǲ��ǵڶ����ֽ�		
	{	
		
		SendChar(1,17,&Send_2[5]); //����ʣ�µ��ֽ�
		ReceArt(1,2);	
		  									
	}	
			  
	if(buf[0]==0x61 && buf[1] ==0x08 )	  //�жϷ�����Ϣ
	{
		SendChar(1,5,Send_3) ;				//���ͻ�ȡ��������		 
		ReceArt(1,11);
	}  	
	while(1)  ;
}

