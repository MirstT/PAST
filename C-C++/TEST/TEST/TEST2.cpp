//#define _CRT_SECURE_NO_WARNINGS
//#include<iostream>
//using namespace std;
//
//#include"CSocketProtocol.h"
//#include"CsckFactoryImp.h"
//#include"CsckFactoryImp2.h"
//
//#include"CEncDesProtocol.h"
//#include"HwEncDec.h"
//
//
//int SckSendAndRec_EncDec(CSocketProtocol *sp,CEncDesProtocol*ed, unsigned char *in, int inlen, unsigned char *out, int *outlen)
//{
//	int ret = 0;
//	unsigned char data[4096];
//	int datalen = 0;
//
//	ret = sp->cltSocketInit();
//	if (ret != 0)
//	{
//		goto End;
//	}
//
//	ret = ed->EncData(in, inlen,data,&datalen);
//	if (ret != 0)
//	{
//		goto End;
//	}
//
//	ret = sp->cltSocketSend(data, datalen);
//	if (ret != 0)
//	{
//		goto End;
//	}
//
//	ret = sp->cltSocketRev(data, &datalen);
//	if (ret != 0)
//	{
//		goto End;
//	}
//
//	ret = ed->DecData(data, datalen,out, outlen);
//	if (ret != 0)
//	{
//		goto End;
//	}
//
//
//End:
//	ret = sp->cltSocketDestory();
//	return 0;
//}
//int main()
//{
//	int ret = 0;
//
//	unsigned char in[4096];
//	int inlen;
//	unsigned char out[4096];
//	int outlen = 0;
//
//	strcpy((char*)in, "asdfghjklaaaaaaaaaaaaaaa");
//	inlen = 9;
//
//	CSocketProtocol *sp = NULL;
//	CEncDesProtocol *ed = NULL;
//
//
//	//sp = new CSckFactoryImp1;
//	sp = new CSckFactoryImp2;
//	ed = new HwEncDec;
//
//
//
//	ret = SckSendAndRec_EncDec(sp,ed, in, inlen, out, &outlen);
//
//	if (ret != 0)
//	{
//		printf("func SckSendAndRec() err:%d\n", ret);
//		return ret;
//	}
//
//
//	delete sp;
//
//	system("pause");
//	return ret;
//}
