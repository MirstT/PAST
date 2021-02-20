#ifndef __QVJSON_H__
#define __QVJSON_H__
#include "QVObject.h"
#include "QVTime.h"
#include "QUFile.h"
#include <vector>
#include <string>

class QVBASEDLL IQVJsonNode : public CQVObject
{
public:
	IQVJsonNode(void);
	virtual ~IQVJsonNode(void);
public:
    uint GetNumber(void) const;
	/*
	@Function:
		bool	GetChild(IQVJsonNode& node, const char* key, bool created = false);
	@Description:
		获取子节点
	@Parameters:
		1. IQVJsonNode&	node:		指向IQVJsonNode的引用，成功时返回获取的子节点
		2. const char*		key:		子节点名
		3. bool				created:	如果子节点是空，是否创建一个新的子节点标志。
	@Return:
		如果获得子节点成功，返回true
	*/
	bool	GetChild(IQVJsonNode& node, const char* key, bool created = false);

     
	/*
	@Function:
		bool	GetChild(IQVJsonNode& node, int idx, bool created = false);
	@Description:
		获取子节点,当前节点必须是一个数组类型
	@Parameters:
		1. IQVJsonNode&	node:		指向IQVJsonNode的引用，成功时返回获取的子节点
		2. int				idx:		子节点序号
		3. bool				created:	如果子节点是空，是否创建一个新的子节点标志。
	@Return:
		如果获得子节点成功，返回true
	*/
	bool	GetChild(IQVJsonNode& node, int idx, bool created = false);
public:
	/*
	@Function:
		bool	Exchange(const char* key, uint64& val, bool save = false);	
	@Description:
		获取或设置节点值（类型uint64).
	@Parameters:
		1. const char*		key:	子节点名，如果为NULL,则表示当前节点。
		2. uint64&			val:	指向uint64的引用，如果save为false,成功时返回获取的值；否则是待设置的节点值。
		3. bool				save:	true: 表示设置节点值；false: 表示获取节点值
	@Return:
		true:	表示成功。
	*/
	bool	Exchange(const char* key, uint64& val, bool save = false);

	/*
	@Function:
		bool	Exchange(const char* key, int& val, bool save = false);
	@Description:
		获取或设置节点值（类型int).
	@Parameters:
		1. const char*		key:	子节点名，如果为NULL,则表示当前节点。
		2. int&				val:	指向int的引用，如果save为false,成功时返回获取的值；否则是待设置的节点值。
		3. bool				save:	true: 表示设置节点值；false: 表示获取节点值
	@Return:
		true:	表示成功。
	*/
	bool	Exchange(const char* key, int& val, bool save = false);

	/*
	@Function:
		bool	Exchange(const char* key, uint&	val, bool save = false);
	@Description:
		获取或设置节点值（类型uint).
	@Parameters:
		1. const char*		key:	子节点名，如果为NULL,则表示当前节点。
		2. uint&			val:	指向uint的引用，如果save为false,成功时返回获取的值；否则是待设置的节点值。
		3. bool				save:	true: 表示设置节点值；false: 表示获取节点值
	@Return:
		true:	表示成功。
	*/
	bool	Exchange(const char* key, uint&	val, bool save = false);

	/*
	@Function:
		bool	Exchange(const char* key, ushort& val, bool save = false);
	@Description:
		获取或设置节点值（类型ushort).
	@Parameters:
		1. const char*		key:	子节点名，如果为NULL,则表示当前节点。
		2. ushort&			val:	指向ushort的引用，如果save为false,成功时返回获取的值；否则是待设置的节点值。
		3. bool				save:	true: 表示设置节点值；false: 表示获取节点值
	@Return:
		true:	表示成功。
	*/
	bool	Exchange(const char* key, ushort& val, bool save = false);

	/*
	@Function:
		bool	Exchange(const char* key, uchar& val, bool save = false);
	@Description:
		获取或设置节点值（类型uchar).
	@Parameters:
		1. const char*		key:	子节点名，如果为NULL,则表示当前节点。
		2. uchar&			val:	指向uint64的引用，如果save为false,成功时返回获取的值；否则是待设置的节点值。
		3. bool				save:	true: 表示设置节点值；false: 表示获取节点值
	@Return:
		true:	表示成功。
	*/
	bool	Exchange(const char* key, uchar& val, bool save = false);
	/*
	@Function:
		bool	Exchange(const char* key, const char*&	val, bool save = false);
	@Description:
		获取或设置节点值（类型const char*).
	@Parameters:
		1. const char*		key:	子节点名，如果为NULL,则表示当前节点。
		2. const char*&		val:	指向const char*的引用，如果save为false,成功时返回获取的值；否则是待设置的节点值。
		3. bool				save:	true: 表示设置节点值；false: 表示获取节点值
	@Return:
		true:	表示成功。
	*/
	bool	Exchange(const char* key, const char*&	val, bool save = false);

	/*
	@Function:
		bool	Exchange(const char* key, char*& val, bool save = false);
	@Description:
		获取或设置节点值（类型char*).特别需要注意，这个函数在读取（save=false)时，val的值内部会重新分配内存，如果输入时不为NULL,必须保证
		该指针有效，同时调用者负责最后把该指针删除(free)。
	@Parameters:
		1. const char*		key:	子节点名，如果为NULL,则表示当前节点。
		2. char*&			val:	指向char*的引用，如果save为false,成功时返回获取的值；否则是待设置的节点值。
		3. bool				save:	true: 表示设置节点值；false: 表示获取节点值
	@Return:
		true:	表示成功。
	*/
	bool	Exchange(const char* key, char*& val, bool save = false);

	/*
	@Function:
		bool	Exchange(const char* key, char* tbl, uint num, bool save = false);
	@Description:
		设置或获取数组表的内容。每个数组项类型为char.
	@Parameters:
		1. const char*		key:	子节点名，如果为NULL,则表示当前节点。
		2. char*			tbl:	指向char的指针，save为true时，表示待设置数组值；save为false时，成功时返回数组内容。
		3. uint				num:	数组维数。
		4. bool				save:	true: 表示设置节点值；false: 表示获取节点值
	@Return:
		true:	表示成功。
	*/
	bool	Exchange(const char* key, char*	tbl, uint num, bool save = false);

	/*
	@Function:
		bool	Exchange(const char* key, uint* tbl, uint num, bool save = false);
	@Description:
		设置或获取数组表的内容。每个数组项类型为uint.
	@Parameters:
		1. const char*		key:	子节点名，如果为NULL,则表示当前节点。
		2. uint*			tbl:	指向uint的指针，save为true时，表示待设置数组值；save为false时，成功时返回数组内容。
		3. uint				num:	数组维数。
		4. bool				save:	true: 表示设置节点值；false: 表示获取节点值
	@Return:
		true:	表示成功。
	*/
	bool	Exchange(const char* key, uint*		tbl, uint num, bool save = false);

	/*
	@Function:
		bool	Exchange(const char* key, int* tbl, uint num, bool save = false);
	@Description:
		设置或获取数组表的内容。每个数组项类型为int.
	@Parameters:
		1. const char*	key:	子节点名，如果为NULL,则表示当前节点。
		2. int*			tbl:	指向int的指针，save为true时，表示待设置数组值；save为false时，成功时返回数组内容。
		3. uint			num:	数组维数。
		4. bool			save:	true: 表示设置节点值；false: 表示获取节点值
	@Return:
		true:	表示成功。
	*/
	bool	Exchange(const char* key, int*		tbl, uint num, bool save = false);

	/*
	@Function:
		bool	Exchange(const char* key, ushort* tbl, uint num, bool save = false);
	@Description:
		设置或获取数组表的内容。每个数组项类型为ushort.
	@Parameters:
		1. const char*		key:	子节点名，如果为NULL,则表示当前节点。
		2. char*			tbl:	指向ushort的指针，save为true时，表示待设置数组值；save为false时，成功时返回数组内容。
		3. uint				num:	数组维数。
		4. bool				save:	true: 表示设置节点值；false: 表示获取节点值
	@Return:
		true:	表示成功。
	*/
	bool	Exchange(const char* key, ushort*	tbl, uint num, bool save = false);
	/*
	@Function:
		bool	Exchange(const char* key, uchar* tbl, uint num, bool save = false);
	@Description:
		设置或获取数组表的内容。每个数组项类型为uchar.
	@Parameters:
		1. const char*		key:	子节点名，如果为NULL,则表示当前节点。
		2. uchar*			tbl:	指向uchar的指针，save为true时，表示待设置数组值；save为false时，成功时返回数组内容。
		3. uint				num:	数组维数。
		4. bool				save:	true: 表示设置节点值；false: 表示获取节点值
	@Return:
		true:	表示成功。
	*/
	bool	Exchange(const char* key, uchar* tbl, uint num, bool save = false);
	/*
	@Function:
		bool Exchange(const char* key, CQVTime& datetime, bool save = false);
	@Description:
		设置或获取时间日期值
	@Parameters:
		1. const char*		key:		子节点名，如果为NULL,则表示当前节点。
		2. CQVTime&			datetime:	指向CQVTime的引用，save为true时表示待设置时间值，save为false时，返回读取的时间值
		3. bool				save:	true: 表示设置节点值；false: 表示获取节点值
	@Return:
		true:	表示成功。
	*/
	bool	Exchange(const char* key, CQVTime& datetime, bool save = false);
	bool	Exchange(const char* key, DHTIME&  datetime, bool save = false);

	/*
	@Function:
		bool Exchange(const char* key, uint&   mask, bool save = false);
		bool Exchange(const char* key, uint64& mask, bool save = false);
	@Description:
		设置或获取掩码值
	@Parameters:
		1. const char*		key:	子节点名，如果为NULL,则表示当前节点。
		2. uint&			mask:	指向uint/uint64的引用
		3. bool				save:	true: 表示设置节点值；false: 表示获取节点值
	@Return:
		true:	表示成功。
	*/
	bool	ExchangeMask(const char* key, uint&   mask, bool save = false);
	bool	ExchangeMask(const char* key, uint64& mask, bool save = false);
	bool	Exchange(const char* key, bool& value, bool save = false);
	bool	Exchange(const char* key, double& value, bool save = false);

	bool	Exchange(const char* key, const CQVString& text, bool save = false);
	bool	Exchange(const char* key, CQVString& text, bool save = false);
    bool    Exchange(const char* key, std::string& text, bool save);
    //--
    bool	Exchange(const char* key, std::vector<std::string>& strlist, bool tojson = false);
    bool	Exchange(const char* key, std::vector<int>& intlist, bool tojson = false);
	bool	Exchange(std::vector<std::string>& strlist, bool tojson = false);
	bool	Exchange(const char *key,char ** cstrlist,int num, bool tojson = false);
	bool	Exchange(std::vector<int>& intlist, bool tojson = false);
	bool	Exchange(std::vector<uint>& intlist, bool tojson = false);

	//-- username & password
	bool	ExchangePassword(const char* key, char*& username, char*& password, bool tojson = false);
	bool	ExchangePassword(const char* key, CQVString& username, CQVString& password, bool tojson = false);
	bool	ExchangePassword(const char* key, std::string& username, std::string& password, bool tojson = false);

public:
	bool	Create(void);
	bool	Delete(void);
	void	Clear(void);
	int		Parse(const char* text, int len = -1);
	int		Build(CQVString& text);
    int		Build(std::string& text);
	int		Load(const char* filename, int type = QUFILE_TYPE_STD, const char* mode = "r");
	int		Save(const char* filename, int type = QUFILE_TYPE_STD, const char* mode = "w");
	//int		Save(const char* dbname);
	//int		Load(const char* dbname);
    bool	IsEmpty(void) const { return m_json == NULL; }
	int		Dump(void);
private:
	bool	Create(void* hJson);
	bool	GetAESCode(uchar* code /*32*/, const char* username, int len = -1);

private:
	void*	m_json;
	bool	m_owned;
protected:
    template<class T>
    bool	Exchange_ListType(const char* key, std::vector<T> data, bool save = false);
    void	operator=(const IQVJsonNode &){}
};

#endif//__QVJSON_H__
