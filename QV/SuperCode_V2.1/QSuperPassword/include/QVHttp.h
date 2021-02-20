#ifndef __QVHTTP_H__
#define __QVHTTP_H__
#include "QVSocket.h"
#include "QVSignal.h"
#include "QVTime.h"
#include "QVUrl.h"
//测试

class QVBASEDLL CHTTPParser : public CQVObject
{
public:
    CHTTPParser(void);
    virtual ~CHTTPParser(void);

public:
    virtual int Setup(const char* doc, uint len);
    virtual int Reset(bool clear);
    const char* ParseNext(void);
    const char* GetLine(void){ return m_line.GetBuffer();}

protected:
    uint            m_len;
    const char*     m_doc;
    const char*     m_ptr;
    CQVString       m_line;
};

////////////////////////////////////////////////////////////////////////
//class CQVHTTPUrl
class QVBASEDLL CQVHTTPUrl : public CQVObject
{
public:
    CQVHTTPUrl(void);
    CQVHTTPUrl(const char* url);
    virtual ~CQVHTTPUrl(void);
public:
    virtual void Dump(void);

public:
    int Reset(void);
    int Parse(const char* url);

public:
    const char* GetURL(void) { return m_url;}
    const char* GetIP(void) { return m_ip;}
    const char* GetHost(void){ return m_host;}
    const char* GetPath(void){ return m_path;}
    const char* GetProtocol(void) { return m_protocol;}
    ushort      GetPort(void) { return m_port;}

public:
    void operator=(const char* url){ Parse(url);}
	void operator=(const CQVHTTPUrl& url);
	bool operator==(const CQVHTTPUrl& url);
    bool operator==(const char* url);
    bool operator!=(const char* url);
    bool IsEmpty(void) { return m_url == NULL;}

protected:
    char*   m_url;
    char*   m_protocol;
    char*   m_host;
    char*   m_path;
    char*   m_ip;
    ushort  m_port;
};

///////////////////////////////////////////////////////////////////////////////
//class CQVHTTPAuthen
#define	HTTPAUTHEN_BASIC	0
#define	HTTPAUTHEN_DIGEST	1
class QVBASEDLL CQVHTTPAuthen : public CQVObject
{
public:
	CQVHTTPAuthen(void);
	virtual ~CQVHTTPAuthen(void);

public:
	void	Reset(void);
	int		SetUser(const char* username, const char* password);
	int		SetRealmNonce(const char* realm, const char* nonce);
	int		ParseResponse(const char* line);
	int		ParseRequest(const char* line);
	BOOL	IsBasic(void) { return m_mode == HTTPAUTHEN_BASIC; }
	const char* GetUsername(void) const { return m_username; };
	const char* GetPassword(void) const { return m_password; };
	const char*	GetAuthenRequBasic(void);
	const char*	GetAuthenRequDigest(const char* cmd, const char* url);

protected:	
	uint	m_mode;
	char*	m_username;
	char*	m_password;
	char*	m_realm;
	char*	m_nonce;
	char*	m_authen;
};

///////////////////////////////////////////////////////////////////////////////
//class CQVHTTPCommand
class QVBASEDLL CQVHTTPCommand : public CQVObject
{
public:
    CQVHTTPCommand(void);
    virtual ~CQVHTTPCommand(void);

public:
    virtual void    Dump(void);
	int		ToString(CQVString& doc);

public:
	static const char*	GetError(int& code);

public:
    virtual int BuildRequest(CQVString* cmd, CQVString* content);
    virtual int ParseRequest(const char* src, int len);
	virtual int RecvRequest(const char* src, int len, CQVString* content);

public:
	void    SetCode(int code)                   { m_code = code; };
	void    SetKeepalive(bool keep)				{ m_keepalive = keep; };
	void	SetChunked(bool chunked)			{ m_chunked = chunked; };
	void	SetCached(bool cached)				{ m_cached = cached; };
	void	SetGZip(bool enable)				{ m_gzip = enable; };
	void	SetCookie(const char* cokie);
    void    SetMethod(const char* method);
    void    SetProtocol(const char* protocol);
    void    SetURI(const char* uri);
    void    SetHost(const char* host);
    void    SetLocation(const char* location);
    void    SetContentType(const char* type);
    void    SetMIMEVerSion(const char* mimever);
    void    SetContentDesc(const char* contentdesc);
	void	SetContentLen(uint len){ m_contentlen = len;};
    void    SetAuthen(const char* authen);
    void    SetAuthenWWW(const char* authenwww);
    void    SetAuthenDigestWWW(const char* authenDwww);
	void	SetAccept(const char* accept);
	void	SetAcceptEncoding(const char* val);
	void	SetRange(const char* range);

	ushort	GetSN(void) { return m_sn; }
	ushort	GetTimeout(void) { return m_timeout; }
	ushort	SetSN(ushort sn) { m_sn = sn; return m_sn; }
	ushort	SetTimeout(ushort val) { m_timeout = val; return m_timeout; }
	const char*	GetSessionID(void) const { return m_session; }
	void	SetSessionID(const char* sessionid);

////////////////////////////////////////////
public:
    virtual int BuildResponse(CQVString* cmd, CQVString* content);

    virtual int ParseResponse(const char* src, int len);
    virtual int ParseContent(const char* src, int len, CQVString* content);
	virtual int ParseChunked(const char* src, int len, CQVString* content);
	virtual int ParseBoundary(const char* src, int len, CQVString* content);
	virtual int RecvResponse(const char* src, int len, CQVString* content);
	
    virtual int Reset(void);

protected:
	virtual bool ParseHeadLine(const char* line);
	virtual bool ParseLineConnection(const char* line);
	virtual bool ParseLineTransferEncoding(const char* line);
	virtual bool ParseLineContentLength(const char* line);
	virtual bool ParseLineSessionID(const char* line);
	virtual bool ParseLineCSeq(const char* line);
	virtual	bool ParseSetCookie(const char* line);
	virtual	bool ParseContentEncoding(const char* line);
	virtual bool BuildHeadLine(CQVString& doc);

public:
	virtual int	 BuildChunked(CQVString& doc, const char* content, size_t len);
	virtual int	 BuildContent(CQVString& doc, const char* content, size_t len);

	//virtual int	 BuildContent(CQVString& doc, const char* src, size_t len = 0);

public:
    bool        IsCompleted(void);
    int         GetCode(void) { return m_code;}
	bool		IsChunked(void) { return m_chunked;};
    bool        IsKeepAlive(void){ return m_keepalive;};
	bool		IsCached(void) { return m_cached; };
	bool		IsGZip(void) { return m_gzip; };
	bool		IsAcceptingGZip(void);
	const char* GetProtocol(void) { return m_protocol;};
    const char* GetLocation(void) { return m_location;}
    const char* GetAuthen(void) { return m_authen;}
    const char* GetAuthenWWW(void) { return m_authenwww;}
    const char* GetAuthenDigestWWW(void) { return m_authenDwww;}
	const char* GetAuthenticateDigest(void) { return m_authenwww;}
	const char*	GetAccept(void) { return m_accept; };
	const char*	GetAcceptEncoding(void) { return m_accept_encoding; };
	const char*	GetCookie(void) { return m_cookie; };
	const char* GetHost(void) { return m_host; };
    
    const char* GetContentType(void) { return m_contenttype;}
    const char* GetMIMEVersion(void) { return m_mimevers; }
    const char* GetMethod(void) { return m_method;}
    const char* GetURI(void) { return m_uri;}
    const char* GetTransport(void) { return m_transport;}
	const char* GetRange(void) { return m_range; };
	const char* GetBoundary(void) { return m_boundary; };

    CQVString*  GetContent(void) { return &m_content;}
	const char*	GetSetCookie(const char* key);
protected:       
	virtual bool ParseOther(const char* line){ return true; };
	bool	ParseLine(char*& result, const char* line, const char* key);
	bool	ParseLine(uint&  result, const char* line, const char* key);
	bool	BuildLine(CQVString& doc, const char* key, const char * line);
	bool	BuildLine(CQVString& doc, const char* key, uint val);

protected:
    int         m_code;             //返回值
    char*       m_error;            //返回错误描述
    char*       m_method;           //方法
    char*       m_protocol;         //协议
    char*       m_uri;              //
    char*       m_host;             //Host:    
	//char*		m_connection;		//Connection:
    char*       m_location;         //Location:
  	char*		m_authen;			//Authorization:
  	char*		m_authenwww;		//WWW-Authenticate: Basic/Digest
  	char*       m_authenDwww;       //WWW-Authenticate: Basic/Digest
  	char*       m_agent;            //Agent:
	char*		m_accept;			//Accept:
	char*		m_accept_encoding;	//Accept-Encoding:
	char*		m_transport;		//Transport:
	char*		m_range;			//Range:
	bool		m_keepalive;		//Connection: close
	bool		m_chunked;			//Transfer-Encoding: chunked
	bool		m_cached;			//cachable flag
	bool		m_gzip;				//gzip flag
	char*		m_cookie;
    char*       m_mimevers;         //MIME-Version: 1.0
    char*       m_contentdesc;      //Content-Description: GetSystemBackupResponse
	ushort      m_sn;
	ushort		m_timeout;
	char*       m_session;
	CQVListP<char>*		m_listsetcookie;

/*
	//General-header
	char*		m_cache;			//Cache-Control:
	char*		m_connection;		//Connection:
	char*		m_date;			    //Date:
	char*		m_via;			    //Via:
	//Request
	char*		m_accept;			//Accept:
	char*		m_accept_enc;		//Accept-Encoding:
	char*		m_accept_lan;		//Accept-Language:
	char*		m_authen;			//Authorization:
	char*		m_from;			    //From:
	char*		m_ims;			    //If-Modified-Since:
	char*		m_range;			//Range:
	char*		m_refer;			//Referer:
	char*		m_agent;			//User-Agent:
	char*		m_transport;		//Transport:
*/
	//Content
	char*		m_boundary;		//	used for HTTP Server push
	char*		m_contenttype;
    uint        m_contentlen;
    uint        m_contentused;
	CQVString   m_content;
};

///////////////////////////////////////////////////////////////////////////////
//class CQVHTTPSocket
class QVBASEDLL CQVHTTPSocket : public CQVSocketTCP
{
public:
    CQVHTTPSocket(void);
    virtual ~CQVHTTPSocket(void);

public:
    CQVHTTPCommand* GetRequest(void) { return &m_requ;}
    CQVHTTPCommand* GetResponse(void){ return &m_resp;}

public:
    int Commit(const char* method, const char* url, CQVString* content,  uint timeout);

protected:
    int SendRequ(CQVHTTPCommand* requ, CQVString* content, uint timeout);
    int RecvResp(CQVHTTPCommand* resp, CQVString* content, uint timeout);

protected:	
    CQVHTTPUrl          m_url;
    CQVHTTPCommand      m_requ;
    CQVHTTPCommand      m_resp;
};


///////////////////////////////////////////////////////////////////////////////
//class CQVHTTPSession
//	HTTP会话
#define	HTTP_STATE_IDLE		0
#define	HTTP_STATE_OPEN		1
#define	HTTP_STATE_RECV		2
#define	HTTP_STATE_SEND		3
#define	HTTP_STATE_CLOSE	4
#define	HTTP_STATE_START	5
#define	HTTP_STATE_STOP		6
class QVBASEDLL CQVHTTPSession : public CQVSocketTCP
{
	friend class CQVListP<CQVHTTPSession>;
protected:
	CQVHTTPSession(void);
	virtual ~CQVHTTPSession(void);

public:
	static	CQVHTTPSession*	Acquire(void) { return new CQVHTTPSession;};
	
public:
	virtual int		Accept(QVSOCK fd);
	virtual int		AddRef(void);
	virtual int		Release(void);

public:
	int		Commit(const char* method, const char* url, const char* content = NULL, size_t contentlen = 0, const char* contenttype = NULL, uint timeout = 5000);
protected:
	int		OnCommit(const char* content, size_t contentlen);

public:
	int		Polling(uint timeout = 0);
	int		RecvRequ(CQVHTTPCommand* requ);
	int		RecvRequContent(CQVHTTPCommand* requ, CQVString& content);
	int		RecvResp(CQVHTTPCommand* resp);
	int		RecvRespContent(CQVHTTPCommand* resp, CQVString& content);

	int		SendRequ(CQVHTTPCommand* requ);
	int		SendRequContent(CQVHTTPCommand* requ, const char* content, size_t len = 0);
	int		SendResp(CQVHTTPCommand* resp);
	int		SendRespContent(CQVHTTPCommand* resp, const char* content, size_t len = 0);
	
public:
	bool			IsServer(void) const { return m_server;};
	CQVHTTPCommand* GetRequest(void) { return &m_requ; };
	CQVHTTPCommand* GetResponse(void){ return &m_resp; };
	void			Lock(void) { m_mutexwork.Enter();};
	void			Unlock(void) { m_mutexwork.Leave();};

	uint			GetState(void) { CQVGuard guard(m_mutexref); return m_workstate; };
	uint			SetState(uint state){ CQVGuard guard(m_mutexref); m_workstate = state; return m_workstate; };

	void			TimeoutSet(uint timeout) { m_timeout.Setup(timeout);};
	void			TimeoutUpdate(void) { m_timeout.Update();};
	bool			TimeoutCheck(void) { return m_timeout.Check();};

protected:
	bool				m_server;		//是否是会话服务端标志
	CQVMutex			m_mutexwork;	//同步锁
	CQVHTTPCommand		m_requ;
	CQVHTTPCommand		m_resp;
	CQVMutex			m_mutexref;
	int					m_ref;
	uint				m_workstate;
	CQVTimeout			m_timeout;
	CQVUrl				m_url;

	//////////////////////////////////////////////////////////////////////////////
	// 调用以下方法必须注意要先设置m_requ的相关信息
public:
	int		HTTPOpen(const CQVUrl& url);
	int		HTTPCommit(CQVString* requ, CQVString* resp, uint timeout = 5000);
protected:
	int		OnHTTPCommit(CQVString *requ, CQVString* resp);
};


#endif//__QVHTTP_H__