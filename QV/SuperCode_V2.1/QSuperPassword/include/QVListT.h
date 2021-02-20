#ifndef __QVLIST_T_H__
#define __QVLIST_T_H__
#include "QVObject.h"
typedef void*	QVLISTPOS;
#if( defined(QVOS_LINUX) | defined(QVOS_MAC) | defined(QVOS_LITEOS) )
typedef QVLISTPOS	POSITION;
#endif
template<class T> class CQVListT : public CQVObject
{
public:
	CQVListT(uint block = 16)
	{
		if (block == 0)
			block = 16;
		m_blocksize = block;
		m_head		= NULL;
		m_tail		= NULL;
		m_free		= NULL;
		m_block		= NULL;
		m_count		= 0;
		m_autodel	= false;
	};
	virtual ~CQVListT(void){ RemoveAll(); };
protected:
	typedef struct LISTNode
	{
		struct LISTNode*	next;
		struct LISTNode*	prev;
		T					data;
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
public:
	void		SetAutoDel(bool enable) { m_autodel = enable; }
	bool		IsAutoDel(void) { return m_autodel; }
	bool		IsEmpty(void) const { return m_count == 0; }
	uint		GetCount(void) const { return m_count; }
	int			GetAtHead(T& data) const { if (m_head == NULL) return QVERR_EMPTY; data = m_head->data; return QV_OK; };
	int			GetAtTail(T& data) const { if (m_tail == NULL) return QVERR_EMPTY; data = m_tail->data; return QV_OK; };
	int			GetAt(QVLISTPOS pos, T& data) const { PLISTNODE node = (PLISTNODE)pos; if (node == NULL) return QVERR_PARAMETER; data = node->data; return QV_OK; };
	QVLISTPOS	GetHead(void) const{ return m_head; }
	QVLISTPOS	GetTail(void) const{ return m_tail; }
	QVLISTPOS	GetNext(QVLISTPOS pos) const{ PLISTNODE node = (PLISTNODE)pos; if (node == NULL) return NULL; return node->next; }
	QVLISTPOS	GetPrev(QVLISTPOS pos) const{ PLISTNODE node = (PLISTNODE)pos; if (node == NULL) return NULL; return node->prev; }
public:	
	QVLISTPOS	AddHead(T& data);
	QVLISTPOS	AddTail(T& data);
	QVLISTPOS	InsertNext(QVLISTPOS pos, T& data);
	QVLISTPOS	InsertPrev(QVLISTPOS pos, T& data);
	QVLISTPOS	Find(T& data);
	QVLISTPOS	FindIndex(int idx);
	int			Remove(QVLISTPOS pos);
	int			Remove(T& data);
	int			RemoveHead(T& data);
	int			RemoveTail(T& data);
	int			RemoveAt(QVLISTPOS pos, T& data);
	int			GetIDX(T& data) const;
	T&			operator[](int idx) const;
public:
	virtual void RemoveAll(void);
protected:
	virtual void OnDataFree(T& data){};
	int			AllocFreeNode(void);
	void		FreeNode(PLISTNODE node, BOOL del);
	PLISTNODE	NewNode(PLISTNODE prev, PLISTNODE next)
	{
		PLISTNODE node = NULL;
		AllocFreeNode();
		QVASSERT(m_free != NULL);
		node = m_free;
		m_free = node->next;
		//node->data = NULL;
		node->prev = prev;
		node->next = next;
		m_count++;
		return node;
	}
};


template<class T>
int CQVListT<T>::AllocFreeNode(void)
{
	PLISTBLOCK	block;
	PLISTNODE	node;
	uint		idx;
	if (m_free != NULL)
		return 0;

	block = (LISTBLOCK*)QVMalloc(sizeof(LISTBLOCK)+m_blocksize* sizeof(LISTNODE));
	QVASSERT(block != NULL);

	node = (PLISTNODE)(block + 1);
	node += (m_blocksize - 1);
	for (idx = 0; idx < m_blocksize; idx++)
	{
		node->next = m_free;
		node->prev = NULL;
		//node->data = NULL;
		m_free = node;
		node--;
	}
	block->next = m_block;
	m_block = block;
	return 0;
}
template<class T>
void CQVListT<T>::FreeNode(PLISTNODE node, BOOL del)
{
	if (node == NULL)
		return;
	if ( del )
		OnDataFree(node->data);
	node->next = m_free;
	m_free = node;
	m_count--;
	if (m_count == 0)
		RemoveAll();
}

template<class T>
void CQVListT<T>::RemoveAll(void)
{
	PLISTNODE	node;
	PLISTBLOCK	block;
	for (node = m_head; node != NULL; node = node->next)
		OnDataFree(node->data);
	m_count = 0;
	m_head = NULL;
	m_tail = NULL;
	m_free = NULL;
	while (m_block != NULL)
	{
		block = m_block;
		m_block = m_block->next;
		QVFree(block);
	}
}

template<class T>
QVLISTPOS CQVListT<T>::AddHead(T& data)
{
	PLISTNODE node = NewNode(NULL, m_head);
	node->data = data;
	if (m_head != NULL)
		m_head->prev = node;
	else
		m_tail = node;
	m_head = node;
	return node;
}
template<class T>
QVLISTPOS CQVListT<T>::AddTail(T& data)
{
	PLISTNODE node = NewNode(m_tail, NULL);
	node->data = data;
	if (m_tail != NULL)
		m_tail->next = node;
	else
		m_head = node;
	m_tail = node;
	return node;
}
template<class T>
QVLISTPOS CQVListT<T>::InsertNext(QVLISTPOS pos, T& data)
{
	PLISTNODE prev = (PLISTNODE)pos;
	PLISTNODE node = NULL;
	if (prev == NULL)
		return AddTail(data);
	node = NewNode(prev, prev->next);
	node->data = data;
	if (prev->next != NULL)
		prev->next->prev = node;
	else
		m_tail = node;
	prev->next = node;
	return node;
}

template<class T>
QVLISTPOS CQVListT<T>::InsertPrev(QVLISTPOS pos, T& data)
{
	PLISTNODE next = (PLISTNODE)pos;
	PLISTNODE node = NULL;
	if (next == NULL)
		return AddHead(data);
	node = NewNode(next->prev, next);
	node->data = data;

	if (next->prev != NULL)
		next->prev->next = node;
	else
		m_head = node;
	next->prev = node;
	return node;
}
template<class T>
QVLISTPOS CQVListT<T>::Find(T& data)
{
	PLISTNODE node = m_head;
	while (node != NULL)
	{
		if (node->data == data)
			return node;
		node = node->next;
	}
	return NULL;
}

template<class T>
QVLISTPOS CQVListT<T>::FindIndex(int idx)
{
	if (idx < 0 || idx >= (int) m_count)
	{
		return NULL;
	}

	PLISTNODE 	node = m_head;
	while (node != NULL)
	{
		if (idx == 0)
			break;
		idx--;
		node = node->next;
	}
	return node;
}

template<class T>
int CQVListT<T>::RemoveHead(T& data)
{
	PLISTNODE	node = m_head;
	if (m_head == NULL)
		return QVERR_EMPTY;
	data = node->data;
	node->data = NULL;
	m_head = node->next;
	if (m_head != NULL)
		m_head->prev = NULL;
	else
		m_tail = NULL;
	FreeNode(node, FALSE);
	return QV_OK;
}

template<class T>
int CQVListT<T>::RemoveTail(T& data)
{	
	PLISTNODE	node = m_tail;
	if (m_tail == NULL)
		return QVERR_EMPTY;
	data = node->data;
	m_tail = node->prev;
	if (m_tail != NULL)
		m_tail->next = NULL;
	else
		m_head = NULL;
	FreeNode(node, FALSE);	
	return QV_OK;
}
template<class T>
int CQVListT<T>::Remove(QVLISTPOS pos)
{
	PLISTNODE	node = (PLISTNODE)pos;
	if (node == NULL)
		return QV_FAIL;	
	if (node == m_head)
		m_head = node->next;
	else
		node->prev->next = node->next;
	if (node == m_tail)
		m_tail = node->prev;
	else
		node->next->prev = node->prev;
	FreeNode(node, TRUE);
	return QV_OK;
}

template<class T>
int CQVListT<T>::Remove(T& data)
{
	PLISTNODE	node = (PLISTNODE)Find(data);
	if (node == NULL)
		return QVERR_FOUND;
	if (node == m_head)
		m_head = node->next;
	else
		node->prev->next = node->next;
	if (node == m_tail)
		m_tail = node->prev;
	else
		node->next->prev = node->prev;
	FreeNode(node, FALSE);
	return QV_OK;
}

template<class T>
int CQVListT<T>::RemoveAt(QVLISTPOS pos, T& data)
{	
	PLISTNODE	node = (PLISTNODE)pos;
	if (node == NULL)
		return QV_FAIL;	
	data = node->data;	
	if (node == m_head)
		m_head = node->next;
	else
		node->prev->next = node->next;
	if (node == m_tail)
		m_tail = node->prev;
	else
		node->next->prev = node->prev;
	FreeNode(node, FALSE);
	return QV_OK;
}
template<class T>
int	CQVListT<T>::GetIDX(T& data) const
{
	int			idx = -1;
	PLISTNODE 	node = m_head;
	while (node != NULL)
	{
		idx++;
		if (node->data == data)
			return idx;
		node = node->next;
	}
	return -1;
}

template<class T>
T& CQVListT<T>::operator[](int idx) const
{
	PLISTNODE 	node = m_head;
	QVASSERT(idx >= 0 && idx < (int)m_count);
	while (node != NULL)
	{
		if (idx == 0)
			break;			
		idx--;
		node = node->next;
	}
	return node->data;
}

#define	AUTODEL_NONE	0
#define AUTODEL_DEL		1
#define AUTODEL_FREE	2
#define AUTODEL_REF		3
#define AUTODEL_USER	4
template<class T> class CQVListP : public CQVListT<T*>
{
public:
    CQVListP(uint type = AUTODEL_NONE, uint block = 16) : CQVListT<T*>(block)
	{
		m_type = type;
		if (type == AUTODEL_NONE)
            this->m_autodel = false;
		else
            this->m_autodel = true;
	};
	virtual ~CQVListP(void)
	{
		RemoveAll();
	};
public:
	virtual void RemoveAll(void) { CQVListT<T*>::RemoveAll(); }
protected:
	virtual void OnDataFree(T*& data)
	{
        if (!this->m_autodel)
			return;
		if (m_type == AUTODEL_DEL)
			QVDel(data);
		else if (m_type == AUTODEL_FREE)
			QVFree(data);
	}
private:
	uint	m_type;
};


//////////////////////////////////////////////////////////////////
//Sortable list
#define	LIST_SORT_NONE		0
#define	LIST_SORT_ASCEND	1
#define	LIST_SORT_DESCEND	2
template<class T> class CQVListSortT : public CQVListT<T>
{
public:
	CQVListSortT(uint order = LIST_SORT_NONE, uint block = 16) :CQVListT<T>(block){ m_order = order; };
	virtual ~CQVListSortT(void) { };
public:
	int		SetOrder(uint order) { if (order > LIST_SORT_DESCEND) return QVERR_PARAMETER; m_order = order; return QV_OK; }
	uint	GetOrder(void) const { return m_order; };
public:
	QVLISTPOS Add(T data)
	{
		QVLISTPOS		pos;
        if (m_order == LIST_SORT_NONE)
			return AddTail(data);
		if (m_order == LIST_SORT_ASCEND)
		{
            pos = this->GetTail();
			while (pos != NULL)
			{
                if (Compare(CQVListSortT::PLISTNODE(pos)->data, data) >= 0)
				{
                    return this->InsertNext(pos);
				}
                pos = this->GetPrev(pos);
			}
			return AddHead(data);
		}
		if (m_order == LIST_SORT_DESCEND)
		{
            pos = this->GetHead();
			while (pos != NULL)
			{
                if (Compare(CQVListSortT::PLISTNODE(pos)->data, data) <= 0)
				{
                    return this->InsertPrev(pos);
				}
                pos = this->GetNext(pos);
			}
            return this->AddHead(data);
		}
		return NULL;
	}
protected:
	virtual int Compare(T t0, T t1){ return 0; }
protected:
	uint	m_order;
};

#endif//__QVLIST_T_H__
