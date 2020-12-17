
#include<iostream>
using namespace std;

#include"HwEncDec.h"
#include"des.h"



int HwEncDec::EncData(unsigned char*plain, int plainlen, unsigned char*cryptdata, int *cryptlen)
{
	int ret = 0;
	ret = DesEnc(plain, plainlen, cryptdata, cryptlen);
	if (ret != 0)
	{
		printf("func DesEnc() err%d\n", ret);
		return ret;
	}
	return ret;
}


int HwEncDec::DecData(unsigned char*cryptdata, int cryptlen, unsigned char*plain, int *plainlen)
{
	int ret = 0;
	ret = DesDec(cryptdata, cryptlen,plain, plainlen);
	if (ret != 0)
	{
		printf("func DesEnc() err%d\n", ret);
		return ret;
	}
	return ret;
	return 0;
}