#ifndef __QVSTR_H__
#define __QVSTR_H__
#include "QVObject.h"
//#include "QVTime.h"

class CQVTime;
class QVBASEDLL CQVString : public CQVObject
{
public:
	CQVString(ushort maxsz=0, ushort align=5);
	CQVString(const char* text);
	CQVString(const CQVString& text);
	virtual ~CQVString(void);
public:
	virtual void Dump(void);

public:
	int		Init(uint size);
	BOOL	IsEmpty(void) const { return (m_len==0)||(m_buffer==NULL);}
	BOOL	EqualTo(const CQVString& ref) const;
	BOOL	EqualTo(const char* ref) const;
    uint	GetLength(void) const { return m_len;}
	uint	Length(void) const { return m_len;}
    uint	GetSize(void) const { return m_size;}
	uint	Size(void) const { return m_size;}
    char*   GetBuffer(void) const { return m_buffer;}
	uint	GetSpace(void) const;
    int     Flush(int len);
    int     Add(int len);

	void	Empty(bool reset = false);
	int		AllocBuffer(uint len);
    int     AppendDAT(const unsigned char* data, uint len);
    int     AppendSTR(const char* src, uint len=0);
	int		QVAPIV Append(const char* fmt, ...);
	int		Append(va_list* args, const char* fmt);

	char*	Clone(void);
	CQVString& Replace(const char* oldstr,const char* newstr);
	void	ToUpper(void);
	void	ToLower(void);
public:
	BOOL	operator==(const char* src);
	BOOL	operator!=(const char* src);
    void    operator=(const char* src);
    void    operator=(const CQVString& src);
    void    operator+=(const char* src);
    void    operator+=(const CQVString& src);
	char	operator[](int idx);

    virtual int     operator<<(const char* src);
    virtual int     operator<<(const CQVString& src);
    virtual int     operator<<(const CQVString* src);
    //virtual int     operator<<(CQVTime& tmc);

protected:
    char*   m_buffer;   //缓冲区地址
    uint	m_size;     //缓冲区长度
    uint	m_len;      //有效字符长度
	ushort	m_align;	//内存分配对齐比特数,0表示不用对齐
	ushort	m_maxsz;	//最大内存长度,单位KB，0表示不作限制
public:
	static	BOOL	IsEqual(const char* text0, const char* text1);
	static	BOOL	IsEmpty(const char* text);
	static	char*	Clone(const char* text, size_t len=0);
	static	char*	Clone(const CQVString& text);
	static	void	Clone(char** hr, const char* text, size_t len = 0);

	//maxLen为最多复制的字符个数，包含最后的'\0'，传默认值0（或者小于0）表示src有多少copy多少, 返回值表示实际copy的字符个数
	static	int		Copy(char* dest, const char* src, int maxLen = 0);
	static	const char*	Find(const char* key, const char* text, size_t len=0);
	static	const char*	ReverseFind(const char* key, const char* text, size_t len = 0);
	static	const char*	TrimL(const char* text);
	static  const char* TrimL(const char* head, const char* tail, char ch = ' ');
	static	const char* TrimL(const char* head, const char* tail, const char* key);

	///////////////////////////////////////////////////////////////////////////////////////
	//	@FindL
	//		从头开始查找关键字符串中出现的第一字符的位置
	//	Paramseters:
	//		1. const char*	head:	开始查找的字符串位置
	//		2. const char*	tail:	结束查找的字符串位置，如果为NULL, 则内部设置到head字符串的结束位置
	//								tail = head + strlen(head)
	//		3. const char*	key:	包含所有待查找字符的字符串
	//	Return:
	//		head == NULL:	return NULL
	//		key	 == NULL:	return NULL
	//		没有查找到:		return NULL
	//		查找到，返回相应的字符位置
	//	Examples:
	//		head = "abcdefg 123456", tail = NULL
	//		const char*	str1 = FindL(head, tail, "123"),	结果str1 = "123456"
	//		const char*	str2 = FindL(head, tail, "mk5a"),	结果str2 = "56"
	//		const char*	str3 = FindL(head, tail, "mnv"),	结果str3 = NULL
	static	const char*	FindL(const char* head, const char* tail, const char* key);

	static	const char* TrimR(const char* head, const char* tail, char ch = ' ');
	static	const char* TrimR(const char* head, const char* tail, const char* key);

	static	const char* Find(char key, const char* head, const char* tail);
	static  BOOL	Compare(const char* head, const char* tail, const char* key);
    static int BASE64Encode(CQVString& code, const char* orig, int size);
    static int BASE64Decode(CQVString& code, const char* orig, int size);

	static	int Multi2UTF8(CQVString& result, const char* text);

public:
	int AppendChar(char chr, uint num);
	int AppendTime(CQVTime* time, int mode = 0);
	int AppendTime(uint64 times, int mode = 0);
};


#endif//__QVSTR_H__
