#ifndef __QVSIGNAL_H__
#define __QVSIGNAL_H__
#include "QVMutex.h"
#include "QVCallback.h"

typedef int(CQVObject::*QVSIGAPI)(CQVObject* object, uint cmd, void* p0, void* p1);

class ISignalNode;
class QVBASEDLL IQVSignal : public CQVObject
{
public:
	IQVSignal(uint maxnum = 0);
	virtual ~IQVSignal(void);
public:
	int Attach(IQVCallback* pCallback);
	int Detach(IQVCallback* pCallback);
	int	Attach(CQVObject* obj, QVSIGAPI api);
	int Detach(CQVObject* obj, QVSIGAPI api);
	int Commit(CQVObject* obj, uint cmd, void* p0, void* p1);
	uint GetCount(void);
public:
	int Clear(void);
private:
	CQVMutex		m_mutex;		//The mutex object
	uint			m_maxnum;		//The maximum node number
	uint			m_slotnum;		//The current node number
	ISignalNode**	m_node;			//The node objects
	CQVMutex		m_commitmutex;	//The mutex object that used to committing routine
	QVTID			m_committhread;	//The thread ID of current committing.
	ISignalNode*	m_commitnode;	//The signal node of current committing.
public:
	static	void Test(void);
};

#endif//__QVSIGNAL_H__
