#ifndef __QVOBJECT_H__
#define __QVOBJECT_H__
#include "QVBaseAPI.h"


//////////////////////////////////////////////////////////////////////////
//class CQVObject
//
//#ifdef QVPLATFORM_XVRV10
//class QVBASEDLL CQVObject : public CObject
//#else
class QVBASEDLL CQVObject
//#endif
{
public:
    CQVObject(void){}
    virtual ~CQVObject(void){}
};

class CQVMutex;
class QVBASEDLL IQVRef
{
public:
	IQVRef(void);
	virtual ~IQVRef(void);
public:
	virtual	int AddRef(void);
	virtual int Release(void);
	virtual int GetRef(void);
private:	
	int			m_ref;
};

class QVBASEDLL IQVState
{
public:
	IQVState(void);
	virtual ~IQVState(void);
public:
	virtual int		SetError(int error);
	virtual int		GetError(void);
	virtual uint	GetState(void);
	virtual bool	CheckState(uint statemask);
	virtual uint	SetState(uint statemask);
	virtual uint	ClearState(uint statemask);
	virtual uint	ResetState(uint state);
private:	
	uint		m_objectstate;
	int			m_objecterror;
};

class  QVBASEDLL IQVStateRef
{
public:
	IQVStateRef(void);
	virtual ~IQVStateRef(void);
public:
	virtual	int		AddRef(void);
	virtual int		Release(void);
	virtual int		GetRef(void);
public:
	virtual int		SetError(int error);
	virtual int		GetError(void);
	virtual uint	GetState(void);
	virtual bool	CheckState(uint statemask);
	virtual uint	SetState(uint statemask);
	virtual uint	ClearState(uint statemask);
	virtual uint	ResetState(uint state);
private:
	int			m_objectref;
	uint		m_objectstate;
	int			m_objecterror;
};

/////////////////////////////////////////////////
///////////////// 单件模式
#define PATTERN_SINGLETON_DECLARECBB(classname)	\
static classname * instance();

#define PATTERN_SINGLETON_IMPLEMENTCBB(classname)	\
classname * classname::instance()		\
{												\
	static classname * _instance = NULL;		\
	if( NULL == _instance)						\
	{											\
		_instance = new classname;				\
	}											\
	return _instance;							\
}
/////////////////////////////////////////////////
#endif//__QVOBJECT_H__