#ifndef __QVTHREAD_H__
#define __QVTHREAD_H__

#if( defined( QVPLATFORM_XVRV10 ) )
#include "Foundation/CppThread.h"
#endif

#include "QVMutex.h"
#include "QVList.h"
#include "QVString.h"
#define	QVMSG_NONE		0
#define	QVMSG_QUIT		1
#define	QVMSG_START		2
#define	QVMSG_BASE		(100)

////////////////////////////////////////////////////////////////////////////
//class IQVMessage 
//	通用消息类
class QVBASEDLL IQVMessage : public IQVRef
{
public:
	IQVMessage(void){ m_cmd = 0; m_object = NULL; m_param[0] = NULL; m_param[1] = NULL; };
protected:
	virtual ~IQVMessage(void){};
public:
	virtual int Release(void) { int ret = IQVRef::Release(); if (ret > 0) return ret; delete this; return 0; };
public:
	virtual int			Setup(uint cmd, CQVObject* obj = NULL, void* p0 = NULL, void* p1 = NULL){ m_object = obj; m_cmd = cmd; m_param[0] = p0; m_param[1] = p1; return QV_OK; };
	virtual uint		GetCommand(void) const { return m_cmd; };
	virtual CQVObject*	GetObject(void) const { return m_object; };
	virtual void*		GetParam(int idx) const { if (idx < 0 || idx >= 2) return NULL; return m_param[idx]; }
	virtual int			SetParam(int idx, void* p){ if (idx < 0 || idx >= 2) return QVERR_SUPPORT; m_param[idx] = p; return QV_OK; };
	virtual void		SetCommand(uint cmd) { m_cmd = cmd; };
	virtual void		SetObject(CQVObject* object){ m_object = object; };
protected:
	uint		m_cmd;
	CQVObject*	m_object;
	void*		m_param[2];
};

////////////////////////////////////////////////////////////////////////////
//class CQVMessageT
//	线程消息类
class QVBASEDLL CQVMessageT : public CQVObject
{
public:
	CQVMessageT(void);
	CQVMessageT(const CQVMessageT& msg);
	CQVMessageT(uint cmd, void* p0 = NULL, void* p1 = NULL, uint timestamp = 0);
	virtual ~CQVMessageT(void){};

public:
	uint&	Command(void){ return m_command; }
	void*&	Param0(void){ return m_param0; }
	void*&	Param1(void){ return m_param1; }
	uint&	TimeStamp(void){ return m_timestamp; }
	void	operator=(const CQVMessageT& msg);

protected:
	uint	m_command;
	void*	m_param0;
	void*	m_param1;
	uint	m_timestamp;
};


////////////////////////////////////////////////////////////////////////////
//class CQVThread:
//	线程基类
#define	QVT_STATE_IDLE		(0)
#define	QVT_STATE_START		(1)
#define	QVT_STATE_RUN		(2)
#define	QVT_STATE_STOP		(3)

#if(defined(QVOS_LINUX)|defined(QVOS_MAC)|defined(QVOS_LITEOS) )
#include <sys/prctl.h>
typedef void* (*LPTHREAD_START_ROUTINE)(void* param);
#endif
class QVBASEDLL CQVThread : public CQVObject
{
public:
	CQVThread(const char* name = NULL, size_t stacksize = 0, int priority = 30);
	virtual ~CQVThread(void);
public:
	static QVTID	GetCurrentThreadID(void);
    
public:
	int	ThreadStart(void);
	int	ThreadStop(void);
public:
	QVTID	GetThreadID(void) const { return m_threadid; };

public:
	int		PostMessage(uint cmd, void* p0 = NULL, void* p1 = NULL, uint timestamp = 0);
	int		GetMessage(CQVMessageT*& msg, uint timeout = INFINITE);
	int		GetMessage(CQVMessageT& msg, uint timeout = INFINITE);
	uint	GetMessageCount();


	int		QVPostMessage(uint cmd, void* p0 = NULL, void* p1 = NULL, uint timestamp = 0);
	int		QVGetMessage(CQVMessageT*& msg, uint timeout = INFINITE);
	int		QVGetMessage(CQVMessageT& msg, uint timeout = INFINITE);

protected:
	int		OnPostMessage(uint cmd, void* p0 = NULL, void* p1 = NULL, uint timestamp = 0);

public:
	virtual BOOL IsRunning(void);

protected:
	virtual int	 OnMessageCancel(CQVMessageT* msg);
	virtual int	 OnThreadStart(void);
	virtual int	 OnThreadStop(void);
	virtual int  OnThreadClose(void);

protected:
	virtual uint OnThread(void) = 0;
	
private:
	char*			m_threadname;		//线程名
	size_t			m_stacksize;		//线程栈大小
	int				m_threadprio;		//线程优先级

	CQVMutex		m_threadmutex;		//线程锁
	uint			m_threadstate;		//线程状态
	CQVEvent		m_eventwait;
	
	HANDLE			m_thread;			//线程句柄
	QVTID			m_threadid;			//线程ID
	CQVQueue		m_msgque;			//线程消息队列

private:
	static	void* ThreadProc(void* param);

public:
	static	HANDLE	QVThreadCreate(LPTHREAD_START_ROUTINE startaddress, void* param, size_t stacksize, int priority, QVTID& id);
	static	int		QVThreadDestroy(HANDLE& hThread);

	////////////////////////////////////////////////////////////////////
	//有关线程统计的变量和函数
public:
	void	Dump(CQVString& doc);

private:
	int		m_ThdID;
public:
	static	void	THDDump(int id = -1);
private:
	static	int		THDInsert(CQVThread* thread);
	static	int		THDRemove(CQVThread* thread);
private:
	static	CQVMutex	s_THDMutex;
	static	uint		s_THDSlot;
	static	uint		s_THDNum;
	static	CQVThread**	s_THDObj;
};


//////////////////////////////////////////////////////////////////////////////////////
//class CQVThreadWorker
typedef int(CQVObject::*QVTHREADAPI)(CQVMessageT* msg, uint timestamp, uint& timeout);
class CThreadObject;
class QVBASEDLL CQVThreadWorker : public CQVThread
{
public:
	CQVThreadWorker(uint slotmax = 0, const char* name = NULL, size_t stacksize = 0, int priority = 32);
	virtual ~CQVThreadWorker(void);
public:
	uint	GetObjectNum(void);
	bool	Check(uint& num, CQVObject* obj, QVTHREADAPI api);
	int		Attach(CQVObject* obj, QVTHREADAPI api);
	int		Detach(CQVObject* obj, QVTHREADAPI api);
	int		PostWorkerMessage(CQVObject* obj, uint cmd, void* param);
protected:
	virtual uint	OnThread(void);
	virtual int		OnMessage(CQVMessageT& msg);
	virtual int		OnPolling(uint& timeout);
protected:
	int		Clear(void);
protected:
	CQVMutex		m_mutex;
	uint			m_slotnum;			//The maximum slot number of the thread object table	
	CThreadObject**	m_object;			//The thread object table
	CThreadObject*	m_objectwork;		//The pointer of the current working thread object	
};


//////////////////////////////////////////////////////////////////////////////////////
//class CQVThreadPool
//	

class QVBASEDLL CQVThreadPool : public CQVObject
{
public:
	CQVThreadPool(uint maxnum = 4, const char* name = NULL, size_t stacksize = 0, int priority = 30);
	virtual ~CQVThreadPool(void);
public:
	int		Clear(void);
	virtual int		Attach(CQVObject* obj, QVTHREADAPI api);
	virtual int		Detach(CQVObject* obj, QVTHREADAPI api);
	uint	GetObjectNum(void);

public:
	virtual int	PostPoolMessage(CQVObject* obj, uint cmd, void* param);

protected:
	CQVMutex		m_mutex;
	uint			m_maxnum;
	char*			m_name;
	size_t			m_stacksize;
	int				m_priority;
	CQVThreadWorker**	m_threadworker;
};

//////////////////////////////////////////////////////////////////////////////////////
//class CQVThreadPoolEx
//	
class QVBASEDLL CQVThreadPoolEx : public CQVThreadPool
{
public:
	CQVThreadPoolEx(uint maxnum = 4, const char* name = NULL, size_t stacksize = 0, int priority = 30);
	virtual ~CQVThreadPoolEx(void);
public:
	virtual int		Attach(CQVObject* obj, QVTHREADAPI api);
	virtual int		Detach(CQVObject* obj, QVTHREADAPI api);
};
#endif//__QVTHREAD_H__
