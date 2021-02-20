#ifndef __QVMSGOBJECT_H__
#define __QVMSGOBJECT_H__


///////////////////////////////////////////////////////////////////
//class CQVMsg
//回调消息类
class QVBASEDLL CQVMsg : public IQVState
{
public:
	CQVMsg(void){ m_param0 = NULL; m_param1 = NULL; };
	//CQVMsg(int error){ SetError(error); };
	virtual ~CQVMsg(void){};

public:
	void SetUrl(const char* url){ m_url = url; };
	void SetUrl(const CQVUrl& url){ m_url = url; };
	void GetUrl(CQVUrl& url)const{ url = m_url; };

	void SetParam0(void* param){ m_param0 = param; };
	const void* GetParam0(void) const { return m_param0; };
	void SetParam1(void* param){ m_param1 = param; };
	const void* GetParam1(void) const { return m_param1; };
protected:
	CQVUrl m_url;
	void* m_param0;
	void* m_param1;
};



#endif//__QVMSGOBJECT_H__