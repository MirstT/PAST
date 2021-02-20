#ifndef __QVTYPE_H__
#define __QVTYPE_H__

#include "QVBaseConf.h"

//#define	QVOS_MAC
#ifdef QVTARGET_OS_IPHONE_OPENSSL
#define    QV_USED_OPENSSL
#endif

#ifdef QVTARGET_OS_IPHONE
#define    QVOS_MAC

#define LOAD_QVSHOW

#define LOAD_QVCODEC

#define LOAD_QVAUDIO

#define LOAD_QVNETSDK

#define LOAD_QVRECORD
//
//#define LOAD_QVRECORDFS
#endif

//#ifdef WIN32
#if ( defined(WIN32) | defined(_WINDOWS) )
#define	QVOS_WIN32
#define	QVOS_BIT32
//#define	QVOS_WIN64
#elif(defined(QVOS_MAC))
#define	QVOS_LINUX
#elif(defined(__HuaweiLiteOs__))
#define QVOS_LITEOS
#elif(defined(LINUX_SDK))
#define QVOS_LINUX
#elif(!defined(QVOS_LINUX))
#define	QVOS_LINUX
#if(!defined(LINUX_X86) )
#define	QVPLATFORM_XVRV10
#endif
#endif // WIN32



#if( defined(QVOS_WIN32) | defined(QVOS_WIN64) )
	//Windows
	#define	_CRT_SECURE_NO_WARNINGS	1

	#ifndef WINVER                  // Specifies that the minimum required platform is Windows Vista.
	#define WINVER 0x0600           // Change this to the appropriate value to target other versions of Windows.
	#endif

	#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
	#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
	#endif

	#ifndef _WIN32_WINDOWS          // Specifies that the minimum required platform is Windows 98.
	#define _WIN32_WINDOWS 0x0410	// Change this to the appropriate value to target Windows Me or later.
	#endif

	#ifndef _WIN32_IE               // Specifies that the minimum required platform is Internet Explorer 7.0.
	#define _WIN32_IE 0x0700        // Change this to the appropriate value to target other versions of IE.
	#endif

	#ifndef _WINDOWS_
	#define WIN32_LEAN_AND_MEAN     // Exclude rarely-used stuff from Windows headers
	#include <windows.h>
	#include <Winsock2.h>
	#include <Ws2tcpip.h>
	#pragma comment(lib, "ws2_32.lib")
	#endif
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	#include <assert.h>
	#include <errno.h>

	#ifndef __GNUC__
	#define QVAPI	WINAPI
	#else
	#define QVAPI
	#endif

	#define	QVAPIV	WINAPIV

	#define	random()	rand()
	typedef __int64	int64;


	#define	STRPrintf		sprintf_s
	#define	strncasecmp		_strnicmp
	#define	strcasecmp		_stricmp
	#define	QVTID			DWORD
#elif( defined(QVOS_LINUX) | defined(QVOS_MAC) | defined(QVOS_LITEOS) )
	//Linux
	#ifndef _GNU_SOURCE
		#define _GNU_SOURCE
	#endif
	#ifndef _LARGEFILE64_SOURCE
		#define _LARGEFILE64_SOURCE
	#endif
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#include <signal.h>
	#include <pthread.h>
	#include <fcntl.h>
	#include <ctype.h>
#if( !defined(QVOS_MAC) & !defined(QVOS_LITEOS) )
	#include <wait.h>
#endif
	#include <time.h>
	#include <errno.h>
	#include <netdb.h>
	#include <wchar.h>
	#include <stdarg.h>
	#include <sys/ioctl.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/time.h>
	#include <arpa/inet.h>
	#include <ifaddrs.h>
	#include <net/if.h>
	#include <assert.h>
	#include <sys/syscall.h>	/* For SYS_xxx definitions */
	#define	QVAPI
	#define	QVAPIV
#ifndef BYTE
	typedef	unsigned char		BYTE;
#endif
	typedef unsigned char		UCHAR;
#ifndef WORD
	typedef unsigned short		WORD;
#endif
#ifndef USHORT
	typedef unsigned short		USHORT;
#endif
	typedef short				WCHAR;
	typedef short				SHORT;

	typedef unsigned long		ULONG;
#ifndef  LONG
	typedef long				LONG;
#endif
	typedef unsigned long long	DWORD64;
#ifndef ULONG64
	typedef unsigned long long	ULONG64;
#endif
#ifndef LONG64
	typedef long long			LONG64;
#endif
#ifndef HANDLE
	typedef void*				HANDLE;
#endif
	typedef void*				HMODULE;
#ifndef HWND
	typedef void*				HWND;
#endif
#ifndef HDC
	typedef void*				HDC;
#endif
#if(!defined(QVPLATFORM_XVRV10))
	typedef long long			int64;
#endif
#ifndef DWORD
    typedef unsigned long		DWORD;
#endif

#if( !defined(OBJC_INC))
#ifndef BOOL
	typedef unsigned int		BOOL;
#endif
#endif
	#ifndef TRUE
	#define	TRUE				1
	#endif
	#ifndef FALSE
	#define FALSE				0
	#endif

	#define	INVALID_HANDLE_VALUE	(-1)
#ifndef _GUID
#define _GUID
	typedef struct _GUID {
	    unsigned int   Data1;
		unsigned short Data2;
		unsigned short Data3;
		unsigned char  Data4[ 8 ];
	}GUID, *PGUID, *LPGUID;
#endif
#ifndef sRECT
#define sRECT
	typedef struct tag_RECT
	{
		int    left;
		int    top;
		int    right;
		int    bottom;
	}RECT, *PRECT, *LPRECT;
#endif
	typedef struct tag_SIZE
	{
		int    cx;
	    int    cy;
	}SIZE, *PSIZE, *LPSIZE;
#ifndef sPOINT
#define sPOINT
	typedef struct tag_POINT
	{
		int  x;
	    int  y;
	} POINT, *PPOINT,*LPPOINT;
#endif

	#define	HIWORD(_x_)					(WORD)(((_x_)>>16)&0x0ffff)
	#define	LOWORD(_x_)					(WORD)((_x_)&0x0ffff)
	#define	MAKEDWORD(_low_, _high_)	(DWORD)((((_high_)&0x0ffff)<<16)|((_low_)&0x0ffff))

	#define Sleep(x)	usleep(x * 1000)
	#define	QVTID	pthread_t
	#define COLORREF DWORD
	#define RGB(r,g,b)          ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#else
	#error Unknown OS
#endif

#if(defined(QVPLATFORM_XVRV10))
	#include "APIs/Types.h"
	#include "System/Support.h"
#else
    typedef unsigned char	uchar;
    typedef unsigned short	ushort;
    typedef unsigned int    uint;
	typedef unsigned long    ulong;
    typedef DWORD64			uint64;	
#endif
	typedef uchar	uint8;
	typedef ushort	uint16;
	typedef uint	uint32;

	typedef int (QVAPI *QVCALLBACK)(void* context, uint cmd, void* param0, void* param1, void* param2);

#ifdef __cplusplus
#define	QVAPIC	extern "C"
#else
#define	QVAPIC
#endif

#ifndef QVMAX
#define QVMAX(a,b)            (((a) > (b)) ? (a) : (b))
#endif
#ifndef QVMIN
#define QVMIN(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#ifndef QVABS
#define QVABS(x) ((x)>=0?(x):-(x))
#endif

#ifndef BIT
#define	BIT(x)				(DWORD)(1<<(x))
#endif

#define	BIT64(x)			(((DWORD64)1)<<(x))

#define BIT_SET(v, b)	(v) = (v) | BIT(b)
#define BIT_SET64(v, b)	(v) = (v) | BIT64(b)

#define	BIT_CLR(v, b)	(v) = (v) & (~BIT(b) )
#define	BIT_CLR64(v, b)	(v) = (v) & (~BIT64(b) )

#define	BIT_ISSET(v, b)	((v)&BIT(b))
#define BIT_ISSET64(v, b) ((v)&BIT64(b))

#define	BIT_ISCLR(v, b) (!BIT_ISSET(v, b))
#define	BIT_ISCLR64(v, b) (!BIT_ISSET64(v, b))

#if(1)
	#define	QVMalloc	malloc
	#define	QVCalloc	calloc
	#define	QVRealloc	realloc	
	#define	QVFree0		free
#else
	#define	QVMalloc	TDKMalloc
	#define	QVCalloc	TDKCalloc
	#define	QVRealloc	TDKRealloc	
	#define	QVFree0		TDKFree
#endif


//#define	QVFree0(_p_)			free(_p_)
//#define	QVMalloc(_size_)		malloc(_size_)
//#define	QVCalloc(_num_, _size_)	calloc(_num_, _size_)
//#define	QVRealloc(_p_, _size_)	realloc(_p_, _size_)

	//QVBASEAPI void* 
#define	QVMalloc0(_size_)	QVCalloc(1, _size_)
#define	QVFree(_p_)	do{ if(_p_){ QVFree0(_p_); (_p_)=NULL;}}while(0)
#define	QVMallocT(_T_)	(_T_*)QVMalloc(sizeof(_T_))
#define	QVMallocT0(_T_)	(_T_*)QVMalloc0(sizeof(_T_))
#define	QVCallocT(_T_, _num_)	(_T_*)QVCalloc( _num_, sizeof(_T_))
#define	QVDel(_obj_) do{ if(_obj_) { delete (_obj_); (_obj_) = NULL;} } while(0)
#define QVRelease(_obj_) do { if(_obj_) { (_obj_)->Release(); (_obj_)=NULL; }} while(0)

#define	QVASSERT(_val_)	do{ if(!(_val_)){ QVTrace(); assert(0);} } while(0)

#define	QVMEMFree	QVFree

#define	QVSTR_SET( _t_, _f_, _v_) do {\
	QVFree((_t_)->(_f_)); \
	if (_v_){\
		size_t _len_ = strlen(_v_); \
		(_t_)->(_f_) = (char*)QVMalloc(_len_ + 1); \
		memcpy((_t_)->(_f_), _v_, _len_); \
		(_t_)->(_f_)[_len_] = '\0';	\
	}\
	}while (0)

#include "QVError.h"

#endif//__QVTYPE_H__
