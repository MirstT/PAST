#ifndef __QVMASK_H__
#define __QVMASK_H__
#include "QVObject.h"

/*********************************************************************\
						QVMASK
\*********************************************************************/
typedef struct tag_QVMASK
{
	uint	masknum;
	uint*	mask;
}QVMASK, *PQVMASK;
QVBASEAPI bool QVAPI QVMASK_Alloc(PQVMASK* cfg, uint num);
QVBASEAPI bool QVAPI QVMASK_Free(PQVMASK* cfg);
QVBASEAPI bool QVAPI QVMASK_Init(PQVMASK cfg, uint num);
QVBASEAPI bool QVAPI QVMASK_Clear(PQVMASK cfg);
QVBASEAPI bool QVAPI QVMASK_Copy(QVMASK* dst, const QVMASK* src);
QVBASEAPI bool QVAPI QVMASK_Equals(const QVMASK* cfg0, const QVMASK* cfg1);
QVBASEAPI bool QVAPI QVMASK_Check(PQVMASK cfg, uint idx);
QVBASEAPI bool QVAPI QVMASK_Set(PQVMASK cfg, int idx, int enable);
QVBASEAPI bool QVAPI QVMASK_IsEmpty(PQVMASK cfg);
QVBASEAPI bool QVAPI QVMASK_AND(PQVMASK dst, PQVMASK src);
QVBASEAPI bool QVAPI QVMASK_OR(PQVMASK dst, PQVMASK src);
QVBASEAPI bool QVAPI QVMASK_XOR(PQVMASK dst, PQVMASK src);
QVBASEAPI bool QVAPI QVMASK_NOT(PQVMASK cfg);
QVBASEAPI bool QVAPI QVMASK_ANDNOT(PQVMASK dst, PQVMASK src);
QVBASEAPI uint QVAPI QVMASK_GetChecked(PQVMASK cfg);

class QVBASEDLL IQVMask : public CQVObject
{
public:
	IQVMask(uint num = 0);
	IQVMask(const IQVMask& mask);
	IQVMask(const IQVMask* mask);
	IQVMask(const QVMASK& mask);
	IQVMask(const QVMASK* mask);
	virtual ~IQVMask(void);
public:
	bool Init(uint num);
	bool Check(uint idx);
	bool Set(int idx, int enable = 1);
public:
	const QVMASK* GetMask(void) const { return &m_mask; };
public:
	bool operator=(const IQVMask& mask);
	bool operator=(const QVMASK& mask);
	bool operator=(const QVMASK* mask);
	bool operator==(const IQVMask& mask) const;
	bool operator==(const QVMASK& mask) const;
	bool operator==(const QVMASK* mask) const;
protected:
	QVMASK	m_mask;
};

/*********************************************************************\
					QVARRAY_UINT
\*********************************************************************/
typedef struct tag_QVARRAY_UINT
{
	uint	num;
	uint*	val;
}QVARRAY_UINT, *PQVARRAY_UINT;
QVBASEAPI bool QVAPI QVARRAY_UINT_Alloc(PQVARRAY_UINT* cfg, uint num);
QVBASEAPI bool QVAPI QVARRAY_UINT_Free(PQVARRAY_UINT* cfg);
QVBASEAPI bool QVAPI QVARRAY_UINT_Init(PQVARRAY_UINT cfg, uint num);
QVBASEAPI bool QVAPI QVARRAY_UINT_Clear(PQVARRAY_UINT cfg);
QVBASEAPI bool QVAPI QVARRAY_UINT_Copy(QVARRAY_UINT* dst, const QVARRAY_UINT* src);
QVBASEAPI bool QVAPI QVARRAY_UINT_Equals(const QVARRAY_UINT* cfg0, const QVARRAY_UINT* cfg1);


#endif//__QVMASK_H__
