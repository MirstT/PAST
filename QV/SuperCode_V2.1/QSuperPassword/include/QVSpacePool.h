#ifndef __DFSPACEPOOL_H__
#define __DFSPACEPOOL_H__
#include "QVObject.h"

class CQVString;
/***********************************************************************\
				class IQVSpacePool
\***********************************************************************/
class QVBASEDLL IQVSpacePool : public CQVObject
{
public:
	IQVSpacePool(const char* name);
	virtual ~IQVSpacePool(void);
public:
	virtual int Create(uint pagenum);
	virtual int Delete(void);
public:
	uint64		PageAlloc(uint pagenum);
	uint64		PageFree(uint64 pd);
	const char*	GetName(void) const { return m_spacename; };
	uint		GetPageNum(void) const { return m_pagenum; };
	uint		GetPageUse(void) const { return m_pageuse; };
public:
	static	uint Log2X(uint val);

protected:
	typedef struct tag_PBN
	{
		struct tag_PBN*	next;
		struct tag_PBN*	prev;
		uint			index;
	}PBN;
	typedef struct tag_PBA
	{
		struct tag_PBN*	head;
		struct tag_PBN*	table;
		uint			count;
		uint			level;
		uint			number;
	}PBA;

protected:
	int		AcquirePages(uint& pageidx, uint pagenum);
	int		ReleasePages(uint  pageidx, uint pagenum);
	int		AcquireE(uint& address, uint pagenum, uint level);
	int		AcquireL(uint& address, uint pagenum, uint level);
	int		AcquireH(uint& address, uint pagenum, uint level);
	bool	ExpandLCheck(uint address, uint pagenum, uint level, uint& result);
	int		ExpandL(uint address, uint pagenum, uint level, uint& result);
	bool	ExpandHCheck(uint address, uint pagenum, uint level, uint& result);
	int		ExpandH(uint address, uint pagenum, uint level, uint& result);

	int		ReleaseL(uint address, uint pagenum, uint level);
	int		ReleaseH(uint address, uint pagenum, uint level);
	int		MergeNode(uint address, uint level);

	int		RemoveNode(PBA* pba, PBN* node);
	int		InsertNode(uint pos, uint level);

protected:
	char*		m_spacename;
	uint		m_pagenum;		//	页面数
	uint		m_pageuse;		//	已经使用的总的页面数
	uint		m_pagemax;		//	最大使用的总页面数
	uint		m_pagelvl;		//	最大页面节点数
	PBA*		m_PBAs;

public:
	virtual void	Dump(CQVString* doc = NULL);
protected:
	virtual void	Dump(CQVString* doc, int level);
};

#endif//__DFSPACEPOOL_H__