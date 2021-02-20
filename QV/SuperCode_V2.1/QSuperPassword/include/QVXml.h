#ifndef __QVXML_H__
#define __QVXML_H__

#include "QVList.h"
#include "QVString.h"

#define XML_HEAD	"<?xml version=\"1.0\"?>"

typedef struct tag_XMLTXT
{
	const char*	head;
	const char* tail;
}XMLTXT, *PXMLTXT;

class QVBASEDLL CQVXmlAttr : public CQVObject
{
public:
	CQVXmlAttr(void);
	CQVXmlAttr(const char* key, const char* val);
	virtual ~CQVXmlAttr(void);

public:
	int Parse(const char* head, const char* tail);
	int ToString(CQVString& doc);

public:
	const char* GetKey(void) const { return m_key; }
	const char* GetValue(void) const { return m_value; }
	void SetKey(const char* key) { QVFree(m_key); m_key = CQVString::Clone(key); }
	void SetValue(const char* val){ QVFree(m_value); m_value = CQVString::Clone(val); }
	bool operator==(const char* key) const;
protected:
	char*	m_key;
	char*	m_value;
};

class QVBASEDLL CQVXmlNode : public CQVObject
{
public:
	CQVXmlNode(CQVXmlNode* parent = NULL);
	virtual ~CQVXmlNode(void);

public:
	///////////////////////////////////////////////////////////////////
	//@ParseXml
	//	从文本解析XML节点
	//@parameters:
	//	1. const char*	head:	文本起始位置
	//	2. size_t		len:	文本长度，如果为0，head必须以'\0'为结束符的标
	//							准字符串，实际以head字符字符串长度计算。
	//@return:
	//	成功时返回根节点指针，否则返回NULL。
	static	CQVXmlNode*	ParseXml(const char* head, size_t len);
public:
	void	Clear(void);
	int Load(const char* filename);
	int	Load(FILE* pf);
	int Store(const char* filename);
	int Store(FILE* pf);
public:
	///////////////////////////////////////////////////////////////////
	//@GetKey
	//	获取当前节点的关键词
	//@parameters:
	//	none
	//@return:
	//	返回当前节点的关键词，有效节点该值不为空。
	const char* GetKey(void) const { return m_key; }

	///////////////////////////////////////////////////////////////////
	//@GetNames
	//	获取当前节点关键词的命名空间
	//@parameters:
	//	none
	//@return:
	//	返回当前节点关键词的命名空间，可以为NULL.
	const char* GetNames(void) const { return m_names; }

	///////////////////////////////////////////////////////////////////
	//@GetValue
	//	获取当前节点的字符串内容。
	//@parameters:
	//	none
	//@return:
	//	返回当前节点的字符串内容。
	const char* GetValue(void) const { return m_value; }

	///////////////////////////////////////////////////////////////////
	//@GetParent:
	//	获取父节点指针，根节点没有父节点。
	//@parameters:
	//	none
	//@return:
	//	返回父节点指针。
	CQVXmlNode*	GetParent(void) { return m_parent; }

	///////////////////////////////////////////////////////////////////
	//@GetFirstChild:
	//	获取第一个子节点指针
	//@parameters:
	//	1. QVLISTPOS& pos:	输入时可以是任意值，成功时返回第一个子节点的位置。
	//@return:
	//	成功时返回第一个子节点指针，否则返回NULL。
	CQVXmlNode*	GetFirstChild(QVLISTPOS& pos);

	///////////////////////////////////////////////////////////////////
	//@GetNextChild:
	//	获取指定位置的下一个子节点指针
	//@parameters:
	//	1. QVLISTPOS& pos:	输入当前子节点位置，成功时返回下一个子节点位置值。
	//@return:
	//	成功时返回指定节点位置下一个子节点指针，否则返回NULL。
	CQVXmlNode* GetNextChild(QVLISTPOS& pos);

	///////////////////////////////////////////////////////////////////
	//@GetChild
	//	从指定位置开始查找指定关键字段的子节点
	//@parameters:
	//	1. QVLISTPOS& pos:	输入时设置开始查找的位置，如果为NULL，则从头开始查找.
	//						如果找到节点，则返回该节点的位置
	//	2. const char* key:	关键字段
	//@return:
	//	成功时返回子节点指针。否则返回NULL。
	CQVXmlNode*	GetChild(QVLISTPOS& pos, const char* key);

	///////////////////////////////////////////////////////////////////
	//@GetFirstNode
	//	查找符合关键字段的第一个节点指针，该函数会遍历所有节点，返回符合条件的第一个节点指针。
	//@parameters:
	//	1. const char* key:	关键字段
	//@return:
	//	成功时返回找到的节点指针。否则返回NULL。
	CQVXmlNode* GetFirstNode(const char* key);

	///////////////////////////////////////////////////////////////////
	//@FindNode
	//	查找指定路径的节点指针
	//@parameters:
	//	1. const char* path: 节点路径，以"."分割,如"a.b.c"
	//@return:
	//	成功时返回找到的节点指针；否则返回NULL
	CQVXmlNode*	FindNode(const char* path);

	///////////////////////////////////////////////////////////////////
	//@GetFirstAttr:
	//	获取第一个属性指针
	//@parameters:
	//	1. QVLISTPOS& pos:	输入时可以是任意值，成功时返回第一个属性节点的位置。
	//@return:
	//	成功时返回第一个属性节点指针，否则返回NULL。
	CQVXmlAttr*	GetFirstAttr(QVLISTPOS& pos);

	///////////////////////////////////////////////////////////////////
	//@GetNextAttr:
	//	获取指定位置的下一个属性指针
	//@parameters:
	//	1. QVLISTPOS& pos:	输入当前属性节点位置，成功时返回下一个属性节点位置值。
	//@return:
	//	成功时返回指定属性节点下一个属性指针，否则返回NULL。
	CQVXmlAttr*	GetNextAttr(QVLISTPOS& pos);
	CQVXmlAttr*	FindAttr(const char* key);

	int AddAttr(const char* key, const char* val, bool tail = true);

public:
	///////////////////////////////////////////////////////////////////
	//@ToString
	//	实例内容转换成字符串。
	//@parameters:
	//	1. CQVString& doc:	类CQVString的引用，返回字符串内容。
	//@return:
	//	成功时返回0。
	int ToString(CQVString& doc);

	///////////////////////////////////////////////////////////////////
	//@Dump
	//	类内容的控制台输出
	virtual void Dump(void);

protected:
	static int			FindXmlItem(PXMLTXT doc, PXMLTXT item);
	static bool			IsXmlHead(PXMLTXT item);
	static bool			IsXmlTail(PXMLTXT item);

protected:
	int Parse(PXMLTXT doc, PXMLTXT item);
	int	ParseHead(const char* head, const char* tail);
	int ParseValue(const char* head, const char* tail);
	int ParseAttr(const char* head, const char* tail);

protected:
	char*		m_key;
	char*		m_names;
	char*		m_value;
	CQVXmlNode*	m_parent;
	CQVListOBJ	m_child;		//CQVXmlNode
	CQVListOBJ	m_attr;			//CQVXmlAttr	
};

#endif//__QVXML_H__