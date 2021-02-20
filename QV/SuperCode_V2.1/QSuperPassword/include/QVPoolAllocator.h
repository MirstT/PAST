

#ifndef __QVPOOLALLOCATOR_H__
#define __QVPOOLALLOCATOR_H__

#include "QVBase/QVType.h"

#if( !defined(QVOS_LITEOS))

#if 0//def QVPLATFORM_XVRV10
#include "Foundation/pool_allocator.h"
#else

#include "QVBase/QVMutex.h"

#include <stddef.h>
#include <exception>
#include <algorithm>

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// CQVPool based on Chunk
class  QVBASEDLL CQVPool : public CQVObject
{
	struct Link
	{
		Link* next;
	};
	struct Chunk
	{
		char *mem;					// allocation area first to get stringent alignment
		Chunk *next;
	};

	enum
	{
		ecount_default = 1024,		//defaut element count in a chunk
	};

	Chunk *chunks;
	const unsigned int esize;
	unsigned int ecount;
	Link* head;
	CQVMutex mutex;

	CQVPool(CQVPool&);					// copy protection
	void operator=(CQVPool&);			// copy protection
	void grow();					// make pool larger

public:
	CQVPool(unsigned int sz);			// sz is the size of elements
	~CQVPool();

	void* alloc();					// allocate one element
	void free(void *b);				// put an element back into the pool
	void setec(unsigned int n);		//set max element count in a chunk
	unsigned int getec();			//get max element count in a chunk
};

inline void *CQVPool::alloc()
{
	mutex.Enter();
	if(head == 0) grow();
	Link *p = head;					// return first element
	head = p->next;
	mutex.Leave();
	return p;
}

inline void CQVPool::free(void *b)
{
	mutex.Enter();
	Link *p = static_cast<Link*>(b);
	p->next = head;					// put b back as first element
	head = p;
	mutex.Leave();
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// CQVPoolAllocator
template <class T> class CQVPoolAllocator;

template<> class CQVPoolAllocator<void>
{
public:
	typedef void        value_type;
	typedef void*       pointer;
	typedef const void* const_pointer;
	
	template <class U> 
	struct rebind { typedef CQVPoolAllocator<U> other; };
};

	template <class T> class CQVPoolAllocator
{
private:
	static CQVPool mem;				// pool of elements of sizeof(T)

public:
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T value_type;
	
	template <class U> 
	struct rebind { typedef CQVPoolAllocator<U> other; };
	
	
	CQVPoolAllocator() {}
	template <class U> 
	CQVPoolAllocator(const CQVPoolAllocator<U>&) {}
	~CQVPoolAllocator() {}

	
	pointer address(reference x) const { return &x; }
	const_pointer address(const_reference x) const
	{ 
		return x;
	}

	static void setchunksize(unsigned int n)
	{
		mem.setec(n);
	}

	static unsigned int getchunksize()
	{
		return mem.getec();
	}

	pointer allocate(size_type n, CQVPoolAllocator<void>::const_pointer hint = 0)
	{
		assert(n == 1);
		return static_cast<T*>(mem.alloc());
	}

	void deallocate(pointer p, size_type n)
	{
		assert(n == 1);
		mem.free(p);
	}
	
	size_type max_size() const
	{ 
		return static_cast<size_type>(-1) / sizeof(T);
	}
	
	void construct(pointer p, const value_type& x)
	{ 
		new(p) value_type(x); 
	}
	void destroy(pointer p) { p->~T(); }
};

template<class T>CQVPool CQVPoolAllocator<T>::mem(sizeof(T));

template <class T>
inline bool operator==(const CQVPoolAllocator<T>&,
	const CQVPoolAllocator<T>&)
{
	return true;
}


template <class T>
inline bool operator!=(const CQVPoolAllocator<T>&,
	const CQVPoolAllocator<T>&)
{
	
return false;
}
#endif

#endif //#if( !defined(QVOS_LITEOS))

#endif // __QVPOOLALLOCATOR_H__

