#ifndef __QVUSER_H__
#define __QVUSER_H__

#include "QVString.h"
class QVBASEDLL CQVUser : public CQVObject
{
public:
	CQVUser(const char* username = NULL, const char* password = NULL);
	CQVUser(const CQVUser& user);
	virtual ~CQVUser(void);
public:
	const char* GetUsername(void) const { return m_username; };
	const char* GetPassword(void) const { return m_password; };
	void	SetUsername(const char* username) { QVFree(m_username); m_username = CQVString::Clone(username); };
	void	SetPassword(const char* password) { QVFree(m_password); m_password = CQVString::Clone(password); };
	bool	operator==(const char* username);
	void	operator=(const CQVUser& user);
	void	Clear(void);
protected:
	char*	m_username;
	char*	m_password;
};

#endif//__QVUSER_H__