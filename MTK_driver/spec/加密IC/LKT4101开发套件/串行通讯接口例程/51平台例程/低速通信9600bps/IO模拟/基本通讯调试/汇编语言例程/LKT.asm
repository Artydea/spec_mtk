/*��Ƭ��ʵ�ָ�LKT����оƬ��ͨѶ������ȷʵ�����渴λӦ���Լ���ȡ�����������ͨѶ�ͳ����ɹ�*/ 
/*��������Ϊ����1�� ʵ��LKT����оƬ�ĸ�λ ��2��ʵ�ֻ�ȡ���ֽڵ������*/
 
  	RSET	EQU		P2.2
	IO		EQU		P2.0
	flag	EQU		20H.0		   //���ָ�λ��Ϣ���������Ϣ�ĳ���	:0Ϊ17�ֽڵĸ�λ��Ϣ��1Ϊȡ���ֽ�������ĸ�λ��Ϣ��11���ֽڣ�
	buf 	EQU		30H			   //���ݻ�����
	ORG 	0000H

	
	LCALL	SamPowerOn				//�ϵ緢�͸�λ����
	LCALL   putdata1  				//��00 84 00 00 08 ��ȡ���������д�����ݻ�����
	LCALL   ICCcommand				//���������LKT����оƬ���ص����ݴ������ݻ�����		
	JMP		ED

putdata1: 							// ��00 84 00 00 08 ��ȡ���������д�����ݻ�����
	 MOV	R0,#buf
	 CLR	A
	 MOV	buf,A
	 MOV	buf+1,#84H
	 MOV	buf+2,A
	 MOV	buf+3,A
	 MOV	buf+4,#8
	 RET	  
	  
SamPowerOn:						    //�ϵ緢�͸�λ����
	LCALL	DelayEtu
	SETB	IO					    //����Ϊ�ߵȴ�����LKT����оƬ���͵���ʼλ
	CLR		RSET				 
	LCALL	Delay
	SETB	RSET
	CLR     flag					
	MOV		R0,#buf

Readchar:							//��ȡLTK����оƬ�ķ�����Ϣ
	LCALL	ReceChar
	MOV		@R0,A
	INC		R0	
	JB		flag,Icc
	CJNE	R0,#buf+17,Readchar	    //��λ��Ϣ�Ƿ����
	RET
Icc:			
	CJNE	R0,#buf+11,Readchar		//�������Ϣ�Ƿ���� 
	RET		 

ReceChar:							//��һ���ֽں��� 
	JB		IO,$                 		
	MOV		R7,#9				  
	CLR 	A
	CLR		C
ReceChar1:			
	NOP
	LCALL	DelayEtu
	MOV		C,IO 
	RRC		A
	DJNZ	R7,ReceChar1
	LCALL	DelayEtu
	LCALL	Delay		
	NOP
	NOP
	MOV		C,IO 				    //����żУ��λ	 CY�е�����Ҫ��PSW.0��ͬ
	JC		Rececharodd	
	JNB		PSW.0,Rececharok

Rececharerr:						//������	   
	RET		
Rececharodd: 
	JNB		PSW.0,Rececharerr	 
	
Rececharok:							 //����һ���ֽڳɹ� �ȴ�����ֹͣλ
	LCALL	DelayEtu
	LCALL	DelayEtu
	RET	 	 
 
SendChar:							 //����һ���ֽ�
 	MOV		R7,#9
	MOV		C,PSW.0	   				 //��PSW.0���浽CY�� ��żУ��λ��
	CLR		IO						 //������ʼλ
SendChar1:
	RRC		A
	LCALL	DelayEtu
	LCALL   Delay
   	MOV		IO,C					 
	DJNZ	R7,SendChar1

	NOP
	NOP
	LCALL	DelayEtu
	SETB	IO						 //����ֹͣλ
	LCALL	DelayEtu
	LCALL	DelayEtu
	LCALL	Delay
	RET

ICCcommand:							 //����������Ϣ
   	
	MOV		A,@R0 
	LCALL	SendChar
	INC		R0
	CJNE	R0,#buf+5,icccommand	
	MOV		R0,#buf
	SETB    flag					 //����11���ֽڵ��������Ϣ
	LCALL	Readchar		
	RET   
	           	                                                                                                                               
DelayEtu:							 //���ͽ���һλ��ʱ�� etu=372/3.579 = 104us
	MOV		R1,#42					 //���ͽ�������ָ��ҲҪռ��ʱ�������	DelayEtu = 90us
	DJNZ	R1,$
	RET

Delay:								 //����΢�����ͽ��յ�ʱ��
	MOV		R1,#4
	DJNZ	R1,$
	RET	  

ED:	   
	END	