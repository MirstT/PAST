#ifndef __QVCALLBACK_H__
#define __QVCALLBACK_H__
#include "QVObject.h"

class QVBASEDLL IQVCallback : public CQVObject
{
public:
	IQVCallback(void* context, QVCALLBACK callback);
	virtual ~IQVCallback(void);
public:
	int		OnSignal(CQVObject* object, uint cmd, void* p0, void* p1);
protected:
	void*		m_context;
	QVCALLBACK	m_callback;

};

#endif//__QVCALLBACK_H__