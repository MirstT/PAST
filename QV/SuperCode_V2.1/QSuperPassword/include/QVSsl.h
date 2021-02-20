#ifndef __QVSSL_H_
#define __QVSSL_H_

#include "QVType.h"
#include "QVObject.h"
#include "QVString.h"

class QVBASEDLL CQVSsl
{
public:
	CQVSsl();
	virtual ~CQVSsl();
	
public:
	virtual void SetUseSsl(bool bEnable);
	virtual bool GetUseSsl(){ return m_bEnable; }
	virtual void SetSocket(int fd);
	virtual bool BindSsl();
	virtual void FreeSsl();
	virtual int  SendData(const void *buf, size_t len, int flags);
	virtual int  RecvData(void *buf, size_t len, int flags);

	virtual	int SetCertsPathName(const char *pCaPathName, const char *pCertPathName, const char *pKeyPathName);

public:
	static void InitSsl();

protected:
	bool	CheckCerts();

protected:
	bool m_bEnable;
	int  m_nMode;
	int  m_nNeedCert;
#ifdef QV_USED_OPENSSL
	void*	m_sslctx;
	void*	m_sslobj;
#endif
	int  m_fd;
	bool m_bBind;

	CQVString	m_strCaPathName;
	CQVString	m_strCertPathName;
	CQVString	m_strKeyPathName;
};

#endif //__QVSSL_H_
