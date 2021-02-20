#ifndef __QVARRAY_T_H__
#define __QVARRAY_T_H__
#include "QVMutex.h"

//////////////////////////////////////////////////////////////////
// Array
template<class T> class CQVArrayT : public CQVObject
{
public:
	CQVArrayT(uint slotmax = 0){ m_slotnum = 0; m_slotmax = slotmax; m_array = NULL; };
	virtual ~CQVArrayT(void){ Clear(); };
protected:
	CQVMutex	m_mutex;
	T*			m_array;
	uint		m_slotmax;
	uint		m_slotnum;
public:
	BOOL	Enter(void) { return m_mutex.Enter(); };
	BOOL	Leave(void) {	return m_mutex.Leave();	};
	virtual void Clear(bool lock = false)
	{
		if (lock) m_mutex.Enter();
		QVFree(m_array);
		m_slotnum = 0;
		if (lock) m_mutex.Leave();
	};
	uint	GetSlotNum(bool lock = false)
	{
		uint slotnum;
		if (lock) m_mutex.Enter();
		slotnum = m_slotnum;
		if (lock) m_mutex.Leave();
		return slotnum;
	}
	uint	GetSlotMax(bool lock = false)
	{
		uint slotnum;
		if (lock) m_mutex.Enter();
		slotnum = m_slotmax;
		if (lock) m_mutex.Leave();
		return slotnum;
	}

public:
	T&	operator[](uint idx)
	{
		if (idx >= m_slotnum || m_array == NULL)
		{
			T*		temp	= NULL;
			uint	slotnum = idx + 8;
			if (m_slotmax != 0 && slotnum > m_slotmax)
			{
				QVASSERT(m_slotnum < m_slotmax);
				slotnum = m_slotmax;
			}
			temp = (T*)QVMalloc0(slotnum * sizeof(T));
			QVASSERT(temp != NULL);
			if (m_slotnum > 0 && m_array != NULL)
				memcpy(temp, m_array, m_slotnum * sizeof(T));
			QVFree(m_array);
			m_array		= temp;
			m_slotnum	= slotnum;
		}
		return m_array[idx];
	};
};

template<class T> class CQVArrayP : public CQVArrayT<T*>
{
public:
	CQVArrayP(uint slotmax = 0, uint autodel = AUTODEL_NONE) :CQVArrayT<T*>(slotmax){ m_autodel = autodel; };
	virtual ~CQVArrayP(void){ Clear(); };
protected:
	uint	m_autodel;
public:
	virtual void Clear(bool lock = false)
	{		
		if (m_autodel == AUTODEL_NONE)
		{
			CQVArrayT<T*>::Clear(lock);
			return;
		}
        if (lock) this->m_mutex.Enter();
        if (this->m_array != NULL)
		{
			uint	idx;
            for (idx = 0; idx < this->m_slotnum; idx++)
			{
                if (this->m_array[idx] == NULL)
					continue;
                if (this->m_autodel == AUTODEL_DEL)
                    QVDel(this->m_array[idx]);
                else if (this->m_autodel == AUTODEL_FREE)
                    QVFree(this->m_array[idx]);
			}
            QVFree(this->m_array);
		}
        this->m_slotnum = 0;
        if (lock) this->m_mutex.Leave();
	};

	int	GetIdleSlot(bool lock = false)
	{
		int idx = -1;
        if (lock) this->m_mutex.Enter();
        for (idx = 0; idx < (int)this->m_slotnum && this->m_array != NULL; idx++)
		{
            if (this->m_array[idx] == NULL)
			{
                if (lock) this->m_mutex.Leave();
				return idx;
			}
		}
        if (this->m_slotmax != 0 && this->m_slotnum >= this->m_slotmax)
			idx = -1;
		else
            idx = this->m_slotnum;
        if (lock) this->m_mutex.Leave();
		return idx;
	};

	int GetIndex(T* data, bool lock = false)
	{
		uint idx;
		if (data == NULL)
			return -1;
        if (lock) this->m_mutex.Enter();
        for (idx = 0; idx < this->m_slotnum && this->m_array != NULL; idx++)
		{
            if (data == this->m_array[idx])
			{
                if (lock) this->m_mutex.Leave();
				return idx;
			}
		}
        if (lock) this->m_mutex.Leave();
		return -1;
	};
	uint GetItemNum(bool lock = false)
	{
		uint num = 0;
		uint idx;
        if (lock) this->m_mutex.Enter();
        for( idx = 0; idx < this->m_slotnum && this->m_array != NULL; idx++)
		{
            if (this->m_array[idx] != NULL)
				num++;
		}
        if (lock) this->m_mutex.Leave();
		return num;
	};
};
template<class T> class CQVArrayR : public CQVArrayP<T>
{
public:
	CQVArrayR(uint slotmax = 0, uint autodel = AUTODEL_REF) :CQVArrayP<T>(slotmax, autodel){};
	virtual ~CQVArrayR(void){ Clear(); }
public:
	virtual void Clear(bool lock = false)
	{
        if (this->m_autodel != AUTODEL_REF)
		{
			CQVArrayP<T>::Clear(lock);
			return;
		}
        if (lock) this->m_mutex.Enter();
        if (this->m_array != NULL)
		{
			uint	idx;
            for (idx = 0; idx < this->m_slotnum; idx++)
			{
                if (this->m_array[idx] == NULL)
					continue;
                QVRelease(this->m_array[idx]);
			}
            QVFree(this->m_array);
		}
        this->m_slotnum = 0;
        if (lock) this->m_mutex.Leave();
	};
};

#endif//__QVARRAY_T_H__
