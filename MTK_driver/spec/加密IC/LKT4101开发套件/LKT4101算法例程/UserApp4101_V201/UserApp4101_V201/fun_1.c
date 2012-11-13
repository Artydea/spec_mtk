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


  key[0]  = 8;
  for(i=0;i<8;i++)
  {
   key[i+1] = RxComm[i+2];
  }

  in[0] = RxComm[10]; // ���������ݵĳ���

  for(i=0;i<in[0] ;i++)
  {
   in[i+1] = RxComm[i+11];
  }

  DESEncrypt(in,key,out);// in,key ���������������LV��ʽ,�������outҲ��LV��ʽ.

  for(i=0;i<out[0];i++)
  {
   TxComm[i+1] = out[i+1]; //���8�ֽ�DES���ܵĽ��
  }

   TxComm[0]=out[0];  //�������Ϊ out[0]
 }


//========================================
//test_fun3 ������ȡ16�ֽ������
//
//========================================
void test_fun3(unsigned char xdata *TxComm) // get random
{
 GetRandomData( TxComm + 1, 16 );

 TxComm[0] = 16 ;

}
//========================================
//test_fun4 �����ǻ�ȡ8�ֽ�оƬID��
//
//========================================
void test_fun4(unsigned char xdata *TxComm) // get 8 bytes chip ID
{
 GetChipID( TxComm + 1);
 
 TxComm[0] = 8 ;

}

