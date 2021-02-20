#ifndef __QVBASECONF_H__
#define __QVBASECONF_H__

#define QVSSL_ENABLED	1
#if(QVSSL_ENABLED)
#	define	QV_USED_OPENSSL	1
#	define	QV_USED_AES		1
#endif

#endif//__QVBASECONF_H__