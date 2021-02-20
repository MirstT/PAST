#ifndef __QVSOCKET_H__
#define __QVSOCKET_H__
#include "QVString.h"
#include "QVList.h"
#include "QVSsl.h"

typedef struct sockaddr_in	QVSOCKADDR, *PQVSOCKADDR;

#if(defined(QVOS_WIN32) | defined(QVOS_WIN64) )
#define	QVSOCKGetLastError()	WSAGetLastError()
//#ifndef EWOULDBLOCK
//#define	EWOULDBLOCK		WSAEWOULDBLOCK
//#define	EAGAIN			WSAEWOULDBLOCK
//#endif
#define QVECONNECT		WSAEWOULDBLOCK
#define QVEAGAIN		WSAEWOULDBLOCK
//#define	ECONNECTPEDING	WSAEWOULDBLOCK
typedef SOCKET QVSOCK;
#else
#define QVSOCKGetLastError()	errno
#define QVECONNECT		EINPROGRESS
#define QVEAGAIN		EAGAIN
//#define	ECONNECTPEDING			EAGAIN //EINPROGRESS
//typedef int		SOCKET;
typedef int	    QVSOCK;
#ifndef closesocket
#define	closesocket			close
#endif

#ifndef INVALID_SOCKET
#define INVALID_SOCKET		-1
#endif

#ifndef SD_BOTH
#define	SD_BOTH				SHUT_RDWR
#endif
#endif

////////////////////////////////////////////////////////////////////
//class CQVSocketSET
class QVBASEDLL CQVSocketSET : public CQVObject
{
public:
	CQVSocketSET(void);
	virtual ~CQVSocketSET(void);
public:
	int		Clear(void);
	int		Select(QVSOCK fd, bool fRecv, bool fSend);
	int		Wait(uint timeout = 0);
	bool	CheckSend(QVSOCK fd);
	bool	CheckRecv(QVSOCK fd);
	bool	CheckError(QVSOCK fd);
protected:
	QVSOCK	m_fd;
	uint	m_num;
	fd_set	m_fdr;
	fd_set	m_fdw;
	fd_set	m_fde;
};

////////////////////////////////////////////////////////////////////
//class CQVSocketAddress
class QVBASEDLL CQVSocketAddress : public CQVObject
{
public:
	CQVSocketAddress(ushort af = AF_INET);
	CQVSocketAddress(const char* doc);
	CQVSocketAddress(const CQVSocketAddress& address);
	CQVSocketAddress(const struct sockaddr* address);
	virtual ~CQVSocketAddress(void);

public:
	static	int			ETHListQuery(CQVListOBJ* list, int af);
	static	int			FindEthIF(CQVSocketAddress* addressl, const CQVSocketAddress* addressp);

public:
	bool				Init(ushort af = AF_INET);
	bool				IsValid(void) const { return m_address != NULL; };
	void				Clear(void);
	ushort				GetFamily(void) const;
	ushort				GetPort(void) const;
	int					GetLength(void) const { return m_addrlen; };
	struct sockaddr*	GetAddress(void) const { return m_address; };
	int					SetAddress(struct sockaddr* address, int len);
	int					SetSocketName(QVSOCK fd);
	int					SetSocketPeer(QVSOCK fd);
	int					SetPort(ushort port);
	int                 SetPortEx(ushort port);
	int					BindEthnet(const char* name, ushort af = AF_INET, ushort type = 0);	//0: IP; 1: NetMask; 2: Broadcast

public:
	int		ToString(CQVString& doc, bool appendport=false);
	int		FromString(const char* doc);
	void	operator=(const char* doc);
	void	operator=(const CQVSocketAddress& address);
	void	operator=(const struct sockaddr* address);
	bool	operator==(const CQVSocketAddress& address);	//only check IP
	bool	operator==(const char* doc);					//only check IP
	bool	operator==(const struct sockaddr* address);		//only check IP

protected:	
	int					m_addrlen;
	struct sockaddr*	m_address;
};

////////////////////////////////////////////////////////////////////
//class CQVSocketMSG
class QVBASEDLL CQVSocketMSG : public CQVString
{
public:
    CQVSocketMSG(void);
    CQVSocketMSG(const CQVSocketMSG& msg):CQVString(){ Clone(msg);}
    virtual ~CQVSocketMSG(void);

public:
    virtual void Dump(void);

public:
    CQVSocketAddress* GetLocal(void){ return &m_local;}
    int SetLocal(CQVSocketAddress* addr);
   
    CQVSocketAddress* GetPeer(void) { return &m_remote;}
    int SetPeer(CQVSocketAddress* addr);    
    int SetPeer(const char* ip, ushort port);

public:
    int     GetFreeSize(void);
    char*   GetFreeBuffer(void);
    int     AddLength(int len);

public:
    int Clone(const CQVSocketMSG& msg);
    CQVSocketMSG*   Clone(void) const;
    void operator=(const CQVSocketMSG& msg){Clone(msg);}

protected:
	CQVSocketAddress	m_local;
	CQVSocketAddress	m_remote;
};


////////////////////////////////////////////////////////////
//class CQVSocket
//  Socket基类
class QVBASEDLL CQVSocket : public CQVObject
{
public:
    CQVSocket(void);
    virtual ~CQVSocket(void);
public:
	QVSOCK				GetSocket(void) const { return m_fd; };
	CQVSocketAddress*	GetLocal(void){ return &m_local; };
	CQVSocketAddress*	GetPeer(void){ return &m_remote; };
	int					GetLocal(CQVSocketAddress* address){ if( address == NULL ) return QVERR_PARAMETER; *address = m_local; return QV_OK;};
	int					GetPeer(CQVSocketAddress* address){ if( address == NULL ) return QVERR_PARAMETER; *address = m_remote; return QV_OK;};

public:
    virtual bool    IsValid(void) { return m_fd != INVALID_SOCKET;}
    virtual int     Open(const char* ip, ushort port){ return -1;}
    virtual int     Close(void);
	virtual int		Bind(const CQVSocketAddress& address);
    virtual int     BindEth(const char* eth, ushort af = AF_INET);
	virtual int     Bind(const char* domain);
    virtual int     Bind(ushort port);
    virtual int     EnableBlock(bool enable = false);
    virtual int     Send(const CQVString* msg){ return -1;}
	virtual int     Send(const CQVString* msg, CQVSocketAddress* to){ return -1; }

    virtual int     Send(const char* buffer, int len, uint timeout) { return -1;}   //同步发送
    virtual int     Recv(char* buffer, int size, uint timeout){ return -1;}         //同步接收

public:
    virtual int     Select(QVSOCK& fd, fd_set* fdr, fd_set* fdw, fd_set* fde, bool fSend = false);
    virtual bool    IsSending(void){ return false;};
    virtual int     OnSend(fd_set* fds){ return -1;}
	virtual int		OnRecv(fd_set* fds){ return -1;}
    virtual int     OnRecv(fd_set* fds, CQVSocketMSG* msg){ return -1;}
    virtual int     OnRecv(fd_set* fds, char* buffer, int size){ return -1;}

	virtual CQVString*		GetSendBuf(void) { return NULL; };
	virtual CQVString*		GetRecvBuf(void) { return NULL; };

public:
    static  int GetIPv4Addr(const char* ethname, uint* ip, uint* mask);
    static  int EnableBlock(QVSOCK fd, bool enable);

	static	QVSOCK	UDPOpen(CQVSocketAddress* addrl);
	static	QVSOCK	TCPOpen(CQVSocketAddress* addrl);

	static	int		MCASTGroupAdd(QVSOCK fd, CQVSocketAddress& addrl, CQVSocketAddress& addrp);
	static	int		MCASTGroupDrop(QVSOCK fd, CQVSocketAddress& addrl, CQVSocketAddress& addrp);
	static	int		MCASTEnableLoop(QVSOCK fd, bool enable);
	
protected:
    QVSOCK				m_fd;           //SOCKET句柄
    CQVSocketAddress	m_local;        //本地IP地址
    CQVSocketAddress	m_remote;       //远端IP地址
};

////////////////////////////////////////////////////////////
//class CQVSocket
//  TCP socket类
class QVBASEDLL CQVSocketTCP : public CQVSocket
{
public:
    CQVSocketTCP(void);
    virtual ~CQVSocketTCP(void);

public:
	virtual int		Accept(QVSOCK fd);
	virtual int     Open(const char* ip, ushort port);
	virtual int     OpenSock(const char* ip, ushort port, bool bNB = false);
	virtual int     OpenSockEx(const char* ip, ushort port, bool bNB = false, uint nTimeout = 1000);
    virtual int     Close(void);
    virtual int     Send(const CQVString* msg);                     //异步发送
    virtual int     Send(const char* buffer, int len, uint timeout);//同步发送
    virtual int     Recv(char* buffer, int size, uint timeout);     //同步接收
    virtual int     SetUseSsl(bool bEnable);
	virtual int		SetCertsPathName(const char *pCaPathName, const char *pCertPathName, const char *pKeyPathName);
public:
    virtual bool    IsSending(void);
    virtual int     OnSend(fd_set* fds);
	virtual int		OnRecv(fd_set* fds);
    virtual int     OnSend(fd_set* fds, char* buffer, int size);
    virtual int     OnRecv(fd_set* fds, char* buffer, int size);

	virtual CQVString*		GetSendBuf(void) { return &m_sendbuf; };
	virtual CQVString*		GetRecvBuf(void) { return &m_recvbuf; };

public:
	virtual int MoveTo(CQVSocketTCP* socket);
	
protected:
    CQVString	m_sendbuf;
	CQVString	m_recvbuf;
	CQVSsl		*m_QVSsl;
};

////////////////////////////////////////////////////////////
//class CQVSocketUDP
//  UDP socket类
class QVBASEDLL CQVSocketUDP : public CQVSocket
{
public:
    CQVSocketUDP(void);
    virtual ~CQVSocketUDP(void);

public:
    virtual int     Open(const char* ip, ushort port);
    virtual int     Close(void);
    virtual int     Send(const CQVString* msg);
    virtual int     Send(const CQVString* msg, CQVSocketAddress* to);

public:
	virtual int		OpenEx(const char* ip, ushort port);
	virtual int     Send(const char* buffer, int len, uint timeout);//同步发送
	virtual int     Recv(char* buffer, int size, uint timeout);     //同步接收

public:
    virtual bool    IsSending(void);
    virtual int     OnSend(fd_set* fds);
    virtual int     OnRecv(fd_set* fds, CQVSocketMSG* msg);

protected:
    CQVListOBJ  m_listsend;     //待发送的消息队列
};

////////////////////////////////////////////////////////////
//class CQVSocketMCAST
//  组播socket类
class QVBASEDLL CQVSocketMCAST : public CQVSocketUDP
{
public:
    CQVSocketMCAST(void);
    virtual ~CQVSocketMCAST(void);

public:
    virtual int Open(const char* ip, ushort port);
    virtual int Close(void);

};



#endif//__QVSOCKET_H__
