#ifndef __QVMEMPOOL_H__
#define __QVMEMPOOL_H__
#include "QVSpacePool.h"
#include "QVString.h"


/***********************************************************************\
class IQVMemPool
\***********************************************************************/
class QVBASEDLL IQVMemPool : public CQVObject
{
public:
	IQVMemPool(const char* name){ m_poolname = CQVString::Clone(name); m_pagenum = 0; m_pagebit = 0; m_pagelen = 0; };
	virtual ~IQVMemPool(void){ QVFree(m_poolname); };
public:
	virtual int		Create(uint pagenum, uint pagebit){ if (pagenum == 0 || pagebit == 0) return QVERR_PARAMETER; m_pagenum = pagenum; m_pagebit = pagebit; m_pagelen = BIT(pagebit); return QV_OK; };
	virtual int		Delete(void) = 0;
	virtual int		CreateBuffer(uint64& memid, uchar*& buffer, uint& size) = 0;
	virtual int		DeleteBuffer(uint64& memid, uchar*& buffer) = 0;
	virtual void	Dump(CQVString* doc){};
protected:
	char*			m_poolname;
	uint			m_pagenum;
	uint			m_pagebit;
	uint			m_pagelen;
};

/***********************************************************************\
class IQVMemPoolFix
\***********************************************************************/
class QVBASEDLL IQVMemPoolFix : public IQVMemPool
{
public:
	IQVMemPoolFix(const char* name);
	virtual ~IQVMemPoolFix(void);
public:
	virtual int		Create(uint pagenum, uint pagebit);
	virtual int		Delete(void);
	virtual int		CreateBuffer(uint64& memid, uchar*& buffer, uint& size);
	virtual int		DeleteBuffer(uint64& memid, uchar*& buffer);
	virtual void	Dump(CQVString* doc);
protected:
	IQVSpacePool*	m_spacepool;	
	uchar*			m_bufferbase;
	uchar*			m_buffer;
};


#if 0
/***********************************************************************\
class IQVMemPoolDyn
\***********************************************************************/
class QVBASEDLL IQVMemPoolDyn : public IQVMemPool
{
public:
	IQVMemPoolDyn(void);
	virtual ~IQVMemPoolDyn(void);
public:
	virtual int Create(uint pagenum, uint pagebit);
	virtual int Delete(void);
};
#endif

#endif//__QVMEMPOOL_H__