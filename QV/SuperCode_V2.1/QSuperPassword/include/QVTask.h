#ifndef __QVTASK_H__
#define __QVTASK_H__
#include "QVThread.h"
#include "QVSignal.h"
#define		QVTASK_ASYNC_RUN	(QVMSG_BASE + 101)
#define		QVTASK_ASYNC_STOP	(QVMSG_BASE + 102)
QVBASEAPI int QVASYNCExecInitialize(void);
QVBASEAPI int QVASYNCExecInvalidate(void);
QVBASEAPI int QVASYNCExecCreate(HANDLE& hExec, int prority = 30);
QVBASEAPI int QVASYNCExecDelete(HANDLE hExec, bool sync);
QVBASEAPI int QVASYNCExecCommit(HANDLE hExec, CQVObject* obj, QVSIGAPI api);


#if 0
////////////////////////////////////////////////////////////////
// class IQVTaskManager
//		任务管理器
class IQVTaskManager : public CQVThread
{
public:
	IQVTaskManager(const char* name, uint taskmax, int priority = 30);
	virtual ~IQVTaskManager(void);
};

class IQVTask : public CQVObject
{
protected:
	IQVTask(void);
	virtual ~IQVTask(void);
public:
	virtual int AddRef(void);
	virtual int Release(void);
public:
	BOOL	Set(void) { return m_event.Set(); };
	BOOL	Reset(void) { return m_event.Reset(); };
	int		Wait(uint ms = INFINITE) { return m_event.Wait(); };
	int		GetError(void) { CQVGuard guard(m_mutex); return m_error; };
	int		SetError(int error = QV_OK) { CQVGuard guard(m_mutex); m_error = error; return m_error; };
protected:
	CQVMutex	m_mutex;
	CQVEvent	m_event;
	int			m_ref;
	int			m_error;
	uint		m_state;
};
#endif

#endif//__QVTASK_H__