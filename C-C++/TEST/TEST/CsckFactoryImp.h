#pragma once


#include<iostream>
using namespace std;
#include"CSocketProtocol.h";

class CSckFactoryImp1:public CSocketProtocol
{
public:

	virtual int cltSocketInit();

	virtual int cltSocketSend(unsigned char *buf, int buflen);

	virtual int cltSocketRev(unsigned char *buf, int *buflen);

	virtual int cltSocketDestory();

private:
	unsigned char *p;
	int len;

};