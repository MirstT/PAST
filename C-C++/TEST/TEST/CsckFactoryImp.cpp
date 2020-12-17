
#include<iostream>
using namespace std;
#include"CsckFactoryImp.h"




int CSckFactoryImp1::cltSocketInit()
{
	p = NULL;
	len = 0;
	return 0;
}

int CSckFactoryImp1::cltSocketSend(unsigned char *buf, int buflen)
{
	p = new unsigned char [sizeof(unsigned char)*buflen];
	if (p == NULL)
	{
		return -1;
	}

	memcpy(p, buf, buflen);
	len = buflen;
	return 0;
}

int CSckFactoryImp1::cltSocketRev(unsigned char *buf, int *buflen)
{
	if (buf == NULL || buflen == NULL)
	{
		return -1;
	}

	*buflen = this->len;
	memcpy(buf, this->p, this->len);
	return 0;
}

int CSckFactoryImp1::cltSocketDestory()
{
	if (p != NULL)
	{
		free(p);
		p = NULL;
		len = 0;
	}
	return 0;
}