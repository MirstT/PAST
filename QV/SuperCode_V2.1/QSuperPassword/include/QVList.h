#ifndef __QVFSLIST_H__
#define __QVFSLIST_H__
#include "QVListT.h"
#include "QVArrayT.h"
class QVBASEDLL CQVList : public CQVObject
{
public:
	CQVList(uint blocksize=10);
	virtual ~CQVList(void);
protected:
	typedef struct LISTNode
	{
		struct LISTNode*	next;
		struct LISTNode*	prev;
		void*				data;
	}LISTNODE, *PLISTNODE;
	typedef struct LISTBlock
	{
		struct LISTBlock*	next;
	}LISTBLOCK, *PLISTBLOCK;

protected:
	PLISTNODE	m_head;
	PLISTNODE	m_tail;
	PLISTNODE	m_free;
	PLISTBLOCK	m_block;
	uint		m_blocksize;
	uint		m_count;
	bool		m_autodel;	//是否自动删除队列数据

protected:
	virtual void OnDataFree(void* data);
	int			AllocFreeNode(void);
	PLISTNODE	NewNode(PLISTNODE prev, PLISTNODE next);
	void		FreeNode(PLISTNODE node);

public:
	void		SetAutoDel(bool enable) { m_autodel = enable;}
	bool		IsAutoDel(void) { return m_autodel;}
	bool		IsEmpty(void) const { return m_count == 0;}
	uint		GetCount(void) const { return m_count;}
	void*		GetAtHead(void) const { if( m_head == NULL) return NULL; return m_head->data;}
	void*		GetAtTail(void) const { if( m_tail == NULL) return NULL; return m_tail->data;}
	void*		GetAt(QVLISTPOS pos) const { PLISTNODE node = (PLISTNODE)pos; if( node==NULL) return NULL; return node->data;}
	bool		SetAt(QVLISTPOS pos, void* data) { PLISTNODE node = (PLISTNODE)pos; if (node == NULL) return false; node->data = data; return true; };
	QVLISTPOS	GetHead(void) const{ return m_head;}
	QVLISTPOS	GetTail(void) const{ return m_tail;}
	QVLISTPOS	GetNext(QVLISTPOS pos) const{ PLISTNODE node = (PLISTNODE)pos; if( node==NULL ) return NULL; return node->next;}
	QVLISTPOS	GetPrev(QVLISTPOS pos) const{ PLISTNODE node = (PLISTNODE)pos; if( node==NULL ) return NULL; return node->prev;}

public:
	void		RemoveAll(void);
	QVLISTPOS	AddHead(void* data);
	QVLISTPOS	AddTail(void* data);
	QVLISTPOS	InsertNext(QVLISTPOS pos, void* data);
	QVLISTPOS	InsertPrev(QVLISTPOS pos, void* data);
	QVLISTPOS	Find(void* data);
	void*		RemoveHead(void);
	void*		RemoveTail(void);
	void*		RemoveAt(QVLISTPOS pos);
	uint 		RemoveFromTailNum(uint num);

public:
	int			GetIDX(void* data) const;
	void*		operator[](int idx) const;

};

class QVBASEDLL CQVListOBJ : public CQVList
{
public:
	CQVListOBJ(uint blocksize=10);
	virtual ~CQVListOBJ(void);
protected:
	virtual void OnDataFree(void* data);
};


///////////////////////////////////////////////////////////
//class CQVQueue
class QVBASEDLL CQVQueue : public CQVObject
{
public:
	CQVQueue(uint maxnum = 0);
	virtual ~CQVQueue(void);

public:
	int		Put(void* data);
	int		Get(void*& data, uint timeout = INFINITE);
	BOOL	IsEmpty(void);
	uint	GetCount(void);

protected:
	uint			m_maxnum;
	CQVList			m_list;
#if( defined(QVOS_WIN32) | defined(QVOS_WIN64) )
	HANDLE			m_mutex;
	HANDLE			m_event;
#else
	pthread_mutex_t	m_mutex;
	pthread_cond_t	m_event;
#endif
};


#endif//__QVFSLIST_H__
