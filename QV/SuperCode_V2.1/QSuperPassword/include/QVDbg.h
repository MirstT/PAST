#ifndef __QVDBG_H__
#define __QVDBG_H__
#include "QVSignal.h"

QVBASEAPI int QVAPI	 QVDBGInitialize(void);
QVBASEAPI int QVAPI	 QVDBGInvalidate(void);
QVBASEAPI int QVAPI	 QVDBGAttachFile(const char* filename);
QVBASEAPI int QVAPI	 QVDBGDetachFile(const char* filename);
QVBASEAPI int QVAPI	 QVDBGAttachStream(CQVObject* obj, QVSIGAPI api);
QVBASEAPI int QVAPI	 QVDBGDetachStream(CQVObject* obj, QVSIGAPI api);
QVBASEAPI int QVAPI	 QVDBGOutput(const char* doc, size_t len = 0, bool timeinfo = true);
QVBASEAPI int QVAPIV QVDBGPrintf(const char* fmt, ...);
QVBASEAPI int QVAPI  QVDBGEnablePrintf(uint typemask);


#define	QVDBG_PRINT_TIMEINFO	BIT(0)
#define	QVDBG_PRINT_CONSOLE		BIT(1)
#define	QVDBG_PRINT_NETWORK		BIT(2)
QVBASEAPI uint QVAPI  QVDBG_EnablePrint(uint val, uint mask);
QVBASEAPI uint QVAPI  QVDBG_SetLevelMask(uint levelmask, uint mask);
QVBASEAPI int  QVAPI  QVDBG_Output(int level, const char* doc, size_t len);
QVBASEAPI int  QVAPIV QVDBG_Printf(int level, const char* fmt, ...);

#define	QVDBG_Trace(level)	QVDBG_Printf(level, "%s====>(Func = %s, line = %d)\n", __FILE__, __FUNCTION__, __LINE__)

#define	QVDBG_LOGOUT	1000
//p0:	const char* doc
//p1:	size_t*		len

#endif//__QVDBG_H__