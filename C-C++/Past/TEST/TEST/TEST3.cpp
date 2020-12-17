#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

#include"CSocketProtocol.h"
#include"CsckFactoryImp.h"
#include"CsckFactoryImp2.h"

#include"CEncDesProtocol.h"
#include"HwEncDec.h"


//class MainOP :public CSocketProtocol, public CEncDesProtocol
//{
//public:
//
//};

class MainOP
{
public:
	MainOP()
	{
		this->sp = NULL;
		this->ed = NULL;
	}
	MainOP(CSocketProtocol*sp, CEncDesProtocol*ed)
	{
		this->sp = sp;
		this->ed = ed;
	}

	void setSP(CSocketProtocol*sp)
	{
		this->sp = sp;
	}
	void setED(CEncDesProtocol*ed)
	{
		this->ed = ed;
	}

	int SckSendAndRec_EncDec(unsigned char *in, int inlen, unsigned char *out, int *outlen)
	{
		int ret = 0;
		unsigned char data[4096];
		int datalen = 0;

		ret = this->sp->cltSocketInit();
		if (ret != 0)
		{
			goto End;
		}

		ret = this->ed->EncData(in, inlen, data, &datalen);
		if (ret != 0)
		{
			goto End;
		}

		ret = this->sp->cltSocketSend(data, datalen);
		if (ret != 0)
		{
			goto End;
		}

		ret = sp->cltSocketRev(data, &datalen);
		if (ret != 0)
		{
			goto End;
		}

		ret = ed->DecData(data, datalen, out, outlen);
		if (ret != 0)
		{
			goto End;
		}


	End:
		ret = sp->cltSocketDestory();
		return 0;
	}



protected:
private:
	CSocketProtocol * sp;
	CEncDesProtocol *ed;
};


int main()
{
	int ret = 0;

	unsigned char in[4096];
	int inlen;
	unsigned char out[4096];
	int outlen = 0;

	strcpy((char*)in, "asdfghjklaaaaaaaaaaaaaaa");
	inlen = 9;

	MainOP *myMainOP = new MainOP;

	CSocketProtocol *sp = NULL;
	CEncDesProtocol *ed = NULL;


	//sp = new CSckFactoryImp1;
	sp = new CSckFactoryImp2;
	ed = new HwEncDec;


	myMainOP->setSP(sp);
	myMainOP->setED(ed);

	myMainOP->SckSendAndRec_EncDec(in, inlen, out, &outlen);
	if (ret != 0)
	{
		printf("myMainOP->SckSendAndRec_EncDec() err %d\n", ret);
	}

	delete sp;
	delete ed;
	delete myMainOP;

	//ret = SckSendAndRec_EncDec(sp, ed, in, inlen, out, &outlen);

	//if (ret != 0)
	//{
	//	printf("func SckSendAndRec() err:%d\n", ret);
	//	return ret;
	//}


	/*delete sp;*/

	system("pause");
	return ret;
}
