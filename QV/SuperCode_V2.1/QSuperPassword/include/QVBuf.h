#ifndef __QVBUF_H__
#define __QVBUF_H__
#include "QVObject.h"
#include "QVPacket.h"

class QVBASEDLL CQVPageBuffer : public CQVObject
{
public:
	CQVPageBuffer(void);
	virtual ~CQVPageBuffer(void);

public:
	virtual int CreatePages(uint pagenum, uint pagebit);
	int CreatePages(char* buffer, uint pagenum, uint pagebit);
	int	Create(uint size, uint pagebit);
	int Create(char* buffer, uint size, uint pagebit);
	virtual int		Destroy(void);
	virtual void	Clear(uint pageidx=0, uint pagenum=0);
public:
	char*	GetBuffer(uint pageidx=0);

	uint	GetPageNum(void) { return m_pagenum;}
	uint	GetPageBit(void) { return m_pagebit;}
	uint	GetSize(void)	{ return m_pagenum<<m_pagebit;}

public:
	virtual void Dump(void);

public:
	bool	IsAligned(size_t ptr);

public:
	static	bool IsAligned(size_t ptr, uint pagebit);

protected:
	char*	m_base;		//缓冲区基础地址
	char*	m_buffer;	//实际使用缓冲区地址
	uint	m_pagebit;	//每个页面长度的BIT数
	uint	m_pagenum;	//页面数
};



////////////////////////////////////////////////////////////////////
//class CQVPageBufferExt
class  QVBASEDLL CQVPageBufferExt : public CQVPageBuffer
{
public:
    CQVPageBufferExt(void);
    virtual ~CQVPageBufferExt(void);
public:
	virtual int CreatePages(uint pagenum, uint pagebit);
	virtual int Create(uint pagenum,  uint pagebit, CPacket*& packet);
	virtual int	Destroy(void);
protected:
    CPacket*    m_packet;
};
#endif//__QVBUF_H__
