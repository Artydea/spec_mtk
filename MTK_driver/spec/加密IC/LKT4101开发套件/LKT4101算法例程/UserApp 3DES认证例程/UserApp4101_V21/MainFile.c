typedef unsigned char BYTE;
typedef unsigned int  WORD;
typedef unsigned long DWORD;


extern void test_fun1(BYTE xdata *inbuf,BYTE xdata *outbuf); // DES Encrypt
extern void test_fun2(BYTE xdata *inbuf,BYTE xdata *outbuf); //д��Կ
extern void test_fun3(BYTE xdata *inbuf,BYTE xdata *outbuf); //����Կ


//####################################################################
//�������Ӻ�  data ���Ĵ�С���ܴ��� 54  (0x0036)
//�������Ӻ� xdata ���Ĵ�С���ܴ��� 640 (0x0280) 
//�������Ӻ�  code ���Ĵ�С���ܴ��� 48K (0xC000)
//####################################################################


//==========================================================
//Fun_UserAppAlg �û��㷨���
//�û����㷨�ڴ�ʵ��
//==========================================================
BYTE UserAppAlg(BYTE xdata *RxComm,BYTE xdata *TxComm)
{
 BYTE cmd;

 cmd = RxComm[1]; 

 if (cmd == 0x01) 
 {
  test_fun1(RxComm  , TxComm);
 }
 
 if (cmd == 0x02) 
  {  
   test_fun2(RxComm, TxComm);
  }

 if (cmd == 0x03) 
 {
  test_fun3(RxComm,TxComm);
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
