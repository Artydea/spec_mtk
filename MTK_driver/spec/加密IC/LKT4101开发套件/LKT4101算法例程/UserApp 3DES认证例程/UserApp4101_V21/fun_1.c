#include "cos_fun.h"


//========================================
// test_fun1 �����Ǽ���DES����
// RxComm[1]:
// RxComm[2..9]: 8�ֽ���Կ
// RxComm[10] : ���������ݵĳ���
// RxComm[11....N]: ����������
//========================================
void test_fun1(unsigned char xdata *RxComm,unsigned char xdata *TxComm)
 {
  unsigned char i;
  unsigned char xdata in[129];  //�����ܵ����ݳ��� ������128�ֽ�
  unsigned char xdata out[128];
  unsigned char xdata key[9];
  unsigned char xdata *BUFF;

  key[0]  = 16;
  
  
  ReadNVM(0x0000,&BUFF[0],0x10);
  for(i=0;i<16;i++)
  {
   key[i+1] = BUFF[i];          
  }

  in[0] = RxComm[2]; // ���������ݵĳ���

  for(i=0;i<in[0] ;i++)
  {
   in[i+1] = RxComm[i+3];
  }

  DESEncrypt(in,key,out);// in,key ���������������LV��ʽ,�������outҲ��LV��ʽ.

  for(i=0;i<out[0];i++)
  {
   TxComm[i+1] = out[i+1]; //���8�ֽ�DES���ܵĽ��
  }

   TxComm[0]=out[0];  //�������Ϊ out[0]
 }





