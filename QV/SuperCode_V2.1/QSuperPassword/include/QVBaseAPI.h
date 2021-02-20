#ifndef __QVBASEAPI_H__
#define __QVBASEAPI_H__

#include "QVType.h"

#if( defined(QVOS_WIN32) | defined(QVOS_WIN64) )
#if( !defined(QVLIBS))
#ifdef QVBASE_EXPORTS
#define	QVBASEDLL	__declspec(dllexport)
#else
#define	QVBASEDLL	__declspec(dllimport)
#pragma comment(lib, "QVBase.lib")
#endif
#else
#define	QVBASEDLL
#endif
#define	QVBASEAPI	QVAPIC QVBASEDLL
#else
#define	QVBASEDLL
#define	QVBASEAPI	QVAPIC
#endif

#ifndef INFINITE
#define	INFINITE	(uint)(-1)
#endif

QVBASEAPI void* QVAPI TDKMalloc(size_t size);
QVBASEAPI void* QVAPI TDKCalloc(size_t count, size_t size);
QVBASEAPI void* QVAPI TDKRealloc(void* p, size_t size);
QVBASEAPI void  QVAPI TDKFree(void* p);

QVBASEAPI uint  QVAPI QVGetProcessorNum(void);
//#if( defined(QVOS_WIN32) | defined(QVOS_WIN64) )
QVBASEAPI int QVAPIV QVPrintf(const char* fmt, ...);
//QVBASEAPI int QVAPI	 QVOutput(const char* doc, size_t len = 0);
//#else
//#define	QVPrintf(fmt, args ...)	printf(fmt, ## args)
//#endif

#define	QVTrace()	QVPrintf("%s====>(Func = %s, line = %d)\n", __FILE__, __FUNCTION__, __LINE__);
#define	QV_Printf	QVPrintf
#define	QV_Trace	QVTrace

typedef struct tag_QVTIME_HMS
{
	ushort	ms;			//	0~999
	uchar	sec;		//	0~59
	uchar	min;		//	0~59
	uint	hour;		//	0~
}QVTIME_HMS, *PQVTIME_HMS;



#endif//__QVBASEAPI_H__