#ifndef __QVZIP_H__
#define __QVZIP_H__
#include "QVString.h"
#ifndef QVZIP_ENABLED
#	define QVZIP_ENABLED	1
#endif //QVZIP_ENABLED

#if( QVZIP_ENABLED )

QVBASEAPI int		QVAPI QVZIPDataCompress(CQVString& buffer, const char* data, int len = -1);
QVBASEAPI int		QVAPI QVZIPDataUncompress(CQVString& buffer, const uchar* data, uint len);
QVBASEAPI HANDLE	QVAPI QVZIPFileOpen(const char* filename, const char* mode);
QVBASEAPI int		QVAPI QVZIPFileClose(HANDLE hFile);
QVBASEAPI int		QVAPI QVZIPFileWrite(HANDLE hFile, const char* data, size_t len);
QVBASEAPI int		QVAPI QVZIPFileRead(HANDLE hFile, char* data, size_t len);
QVBASEAPI int		QVAPI QVZIPFileCompress(const char* filesrc, const char* filedst);
QVBASEAPI int		QVAPI QVZIPFileUncompress(const char* filesrc, const char* filedst);

#endif //#if( QVZIP_ENABLED )

#endif//__QVZIP_H__