#ifndef __QVTIMER_H__
#define __QVTIMER_H__
#include "QVMutex.h"
#include "QVSignal.h"
#include "QVList.h"

class IQVTimerManager;
class QVBASEDLL IQVTimer : public CQVObject, public IQVRef
{
	friend class IQVTimerThread;
	friend class IQVTimerManager;
	friend class CQVListP<IQVTimer>;

private:
	IQVTimer(void);
	virtual ~IQVTimer(void);
public:
	static	IQVTimer* AcquireTimer(void);

public:
	virtual int	Release(void);

public:		
	int		Start(CQVObject* obj, QVSIGAPI api, uint duration = 1000, uint calledmax = 0, bool callednow = false);
	int		Stop(void);

private:
	void	Run(void);
	bool	Check(uint64 ticks);

private:
	IQVSignal	m_signal;
	uint		m_duration;		//	ms
	uint		m_calledmax;	//	to be called number
	uint		m_callednum;	//	called number
	uint64		m_callednext;	//	the timestamp to be called
	CQVMutex	m_mutexwork;	//	the timer mutex	
	uint		m_workstate;

public:
	static	int		QVTimerInitialize(void);
	static	int		QVTimerInvalidate(void);
private:
	static	int					s_timerref;
	static	CQVMutex			s_timermutex;
	static	IQVTimerManager*	s_pTimerManager;
};

#endif//__QVTIMER_H__