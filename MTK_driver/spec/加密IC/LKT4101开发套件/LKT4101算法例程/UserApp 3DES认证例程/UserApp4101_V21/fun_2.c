#include "cos_fun.h"

//========================================
//test_fun2 ������д���ݵ�NVM

//========================================
 void test_fun2(unsigned char xdata *RxComm,unsigned char xdata *TxComm)
 {
 
    WriteNVM(RxComm[2]*0x100 + RxComm[3],&RxComm[5],RxComm[4]); // �洢��д:RxComm[2]RxComm[3]��ʾƫ�Ƶ�ַ��RxComm[4]д�����ݵĳ��ȣ�RxComm[5].������֮����д�������
    TxComm[0] = 0;
	
 }


//========================================
//test_fun3 �����Ƕ�ȡNVM����
��ע�⣺ʵ��Ӧ���У������ڲ�����ʹ�ã���Ҫʹ�������ȡ���������ⲿ��ȡNVM�����������NVM���洢�����ݾͻᱻ����������������ɾ����������д�����Կ���޷�������������Կ�İ�ȫ��
//
//========================================
void test_fun3(unsigned char xdata *RxComm,unsigned char xdata *TxComm) 
{

   ReadNVM(RxComm[2]*0x100 + RxComm[3],&TxComm[1],RxComm[4]); // �洢���� ����RxComm[2]RxComm[3]�Ƕ����ݵ���ʼ��ַ; TxComm[1]�Ƕ��������ݣ�RxComm[4]�����Ҫ��ȡ�����ݳ���
   TxComm[0] = RxComm[4];                                       //
   
 }


