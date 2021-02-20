#ifndef __QVMUTEX_H__
#define __QVMUTEX_H__
#include "QVObject.h"

/////////////////////////////////////////////////////////
//class CQVMutex
class QVBASEDLL CQVMutex : public CQVObject
{
public:
	CQVMutex(void);
	virtual ~CQVMutex(void);
public:
	BOOL	Enter(uint timeout = INFINITE);
	BOOL	Leave(void);

private:
#if( defined(QVOS_WIN32) | defined(QVOS_WIN64) )
	HANDLE	m_mutex;
#else
	pthread_mutex_t m_mutex;
#endif
};

/////////////////////////////////////////////////////////
//class CQVGuard
class QVBASEDLL CQVGuard : public CQVObject
{
public:
	CQVGuard(CQVMutex& mutex) :m_mutex(mutex){ m_mutex.Enter(); }
	virtual ~CQVGuard(void){ m_mutex.Leave(); }
private:
	CQVMutex&	m_mutex;
};


///////////////////////////////////////////////////////////
//class CQVEvent
class QVBASEDLL CQVEvent : public CQVObject
{
public:
	CQVEvent(bool autoreset = false);
	virtual ~CQVEvent(void);
public:
	BOOL	Set(void);
	BOOL	Reset(void);
	BOOL	Check(void);
	int		Wait(uint timeout = INFINITE);
private:
	bool	m_autoreset;
#if( defined(QVOS_WIN32) | defined(QVOS_WIN64) )
	HANDLE	m_event;
#else
	BOOL			m_signal;
	pthread_mutex_t	m_mutex;
	pthread_cond_t	m_event;
#endif
};

#endif//__QVMUTEX_H__
