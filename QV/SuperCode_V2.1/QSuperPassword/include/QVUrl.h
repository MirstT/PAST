#ifndef __QVURL_H__
#define __QVURL_H__

#include "QVString.h"
/////////////////////////////////////////////////////////////////////////////////////////////
//class CQVUrl:
//	通用URL格式为: 
//		protocol://[username:password@]ip[:port][path]
//		http://admin:123456@192.168.9.100:80/path
//		rtsp://admin:123456@192.168.9.100:80/path
//		rtmp://admin:123456@192.168.9.100:80/path
//		quii://admin:123456@192.168.9.100:80/path
//		protocol:	http/rtsp/rtmp/quii
//		username:	admin
//		password:	123456
//		ip:			192.168.9.100
//		port:		80
//		path:		/path
class QVBASEDLL CQVUrl : public CQVObject
{
public:
	CQVUrl(void);
	CQVUrl(const char* url);
	CQVUrl(const CQVUrl& url);
	virtual ~CQVUrl(void);

public:
	static bool IsAbsolute(const char* uri);
	static bool BuildURL(CQVString& url, const char* src, const char* username, const char* password);

protected:
	void	Init(void);

public:
	int		Reset(void);
	int		Setup(const char* uri);
	int		SetUser(const char* username, const char* password);
	int		SetHost(const char* ip, ushort port);
	
public:
	void	operator=(const char* uri){ Setup(uri); }
	void	operator=(const CQVUrl& url);
	BOOL	operator==(const char* uri) const;
	BOOL	operator==(const CQVUrl& url) const;
	BOOL	IsEmpty(void) { return m_url == NULL; }
	BOOL	CheckUser(const char* username, const char* password);

public:
	const char* GetURLFull(void) const { return m_urlfull;};
	const char*	GetURL(void) const { return m_url;};
	const char* GetProtocol(void) const { return m_protocol; }
	const char* GetHost(void) const { return m_host; }
	const char* GetIP(void) const { return m_ip; }
	const char* GetPath(void) const { return m_path; }
	const char* GetUsername(void) const { return m_username; }
	const char* GetPassword(void) const { return m_password; }
	const char* GetPassword1(void) const { return m_password1; }
	ushort		GetPort(void) const { return m_port; }

	int			UpdateURLFull(void);
	int			UpdateURL(void);

protected:
	char*	m_urlfull;
	char*	m_url;
	char*	m_protocol;
	char*	m_host;	
	char*	m_ip;
	char*	m_path;
	char*	m_username;
	char*	m_password1;//转义@符号的密码
	char*	m_password;//取消转义@符号的密码
	ushort	m_port;
};
#endif//__QVURL_H__