typedef unsigned char BYTE;
typedef unsigned int  WORD;
typedef unsigned long DWORD;


extern void test_fun1(BYTE xdata *inbuf,BYTE xdata *outbuf); // DES Encrypt
extern void test_fun2(BYTE xdata *inbuf,BYTE xdata *outbuf); // XOR
extern void test_fun3(BYTE xdata *outbuf); // get random
extern void test_fun4(BYTE xdata *TxComm); 

//####################################################################
//�������Ӻ�  data ���Ĵ�С���ܴ��� 54  (0x0036)
//�������Ӻ� xdata ���Ĵ�С���ܴ��� 640 (0x0280) 
//�������Ӻ�  code ���Ĵ�С���ܴ��� 48K (0xC000)
//####################################################################


//ȫ�ֱ����Ķ���ʾ����
BYTE xdata g_test_var1,g_test_var2;
WORD xdata g_test_Wvar;

//�����ҪΪȫ�ֱ�����ʼ����������ڵ����㷨�Ĺ���������ɳ�ʼ��
void GlobalVar_Init() 
{//���˺��������㷨���õ�ʱ����ɡ�
 g_test_var1 = 0x12;
 g_test_var1 = 0x34;
 g_test_Wvar = 0x7788;
}


// ע�⣺��Ҫʹ����������ע���еķ��������ȫ�ֱ����ĳ�ʼ��
/*
BYTE xdata g_test_var1 = 0x12;
WORD xdata g_test_Wvar = 0x7788;
*/





//==========================================================
//Fun_UserAppAlg �û��㷨���
//�û����㷨�ڴ�ʵ��
//==========================================================
BYTE UserAppAlg(BYTE xdata *RxComm,BYTE xdata *TxComm)
{
 BYTE cmd;

 cmd = RxComm[1]; 

 if (cmd == 0x00) 
 {
  GlobalVar_Init(); //ȫ�ֱ����ĳ�ʼ�� 
 }

 if (cmd == 0x01) 
 {
  test_fun1(RxComm  , TxComm);
 }
 
 if (cmd == 0x02) 
  {  
   test_fun2(RxComm,TxComm);
  }

 if (cmd == 0x03) 
 {
  test_fun3(TxComm);
 }

 if (cmd == 0x04) 
 {
  test_fun4(TxComm);
 }

 return 1;

}

//=====================����main ������Ҫ�޸�===========================
void main()
{
 BYTE xdata inbuf[1],outbuf[1];
 UserAppAlg(inbuf,outbuf);
 for(;;);
}
//=====================================================================
