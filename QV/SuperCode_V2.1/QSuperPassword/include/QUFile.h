#ifndef __QUFILE_H__
#define __QUFILE_H__
#include "QVObject.h"
#include "QVTime.h"

#define	QUFILE_TYPE_STD		0		//	标准文件打开方式
#define	QUFILE_TYPE_LOW		1		//	底层文件打开方式

/********************************************************************\
class IQUFileInfo
	文件信息类
\********************************************************************/
class QVBASEDLL IQUFileInfo : public CQVObject
{	
public:
	IQUFileInfo(void){ m_filename = NULL; m_fileattr = 0; m_filesize = 0; };
	IQUFileInfo(const IQUFileInfo& info);
	virtual ~IQUFileInfo(void){ QVFree(m_filename); };
public:
	/////////////////////////////////////////////////////////////////
	//	@GetFileName
	//		获取文件名
	//	参数:
	//		无
	//	返回:
	//		返回文件名指针
	const char*	GetFileName(void) const { return m_filename; };
	/////////////////////////////////////////////////////////////////
	//	@SetFileName
	//		设置文件名
	//	参数:
	//		1. const char* filename:	文件名指针
	//	返回:
	//		无
	void		SetFileName(const char* filename);
	/////////////////////////////////////////////////////////////////
	//	@GetFileAttr:
	//		获取文件属性
	//	返回:
	//		指向文件属性的引用
	uint&		GetFileAttr(void){ return m_fileattr; };
	/////////////////////////////////////////////////////////////////
	//	@GetFileSize
	//		获取文件长度
	//	返回:
	//		指向文件长度的引用
	uint64&		GetFileSize(void){ return m_filesize; };
	/////////////////////////////////////////////////////////////////
	//	@GetTimeCreate:
	//		获取文件创建时间
	//	返回:
	//		指向类型CQVTime的引用
	CQVTime&	GetTimeCreate(void) { return m_timecreate; };
	/////////////////////////////////////////////////////////////////
	//	@GetTimeAccess:
	//		获取文件最后一次访问时间
	//	返回:
	//		指向类型CQVTime的引用
	CQVTime&	GetTimeAccess(void) { return m_timeaccess; };
	/////////////////////////////////////////////////////////////////
	//	@GetTimeWrite:
	//		获取文件最后一次修改时间
	//	返回:
	//		指向类型CQVTime的引用
	CQVTime&	GetTimeWrite(void){ return m_timewrite; };

public:
	BOOL	IsReadOnly(void) const;
	BOOL	IsDirectory(void) const;
	BOOL	IsHidden(void) const;
	BOOL	IsNormal(void) const;
	BOOL    HasSubDir(void) const;
public:
	/////////////////////////////////////////////////////////////////
	//	@ operator=
	//		赋值操作符
	void operator=(const IQUFileInfo& info);

protected:
	char*	m_filename;
	uint	m_fileattr;		//	文件属性
	uint64	m_filesize;		//	文件长度
	CQVTime m_timecreate;	//	文件创建时间
	CQVTime	m_timeaccess;	//	最后一次访问时间
	CQVTime	m_timewrite;	//	最后一次写入时间
};

/********************************************************************\
class IQUFileFind
	文件搜索类
\********************************************************************/
class QVBASEDLL IQUFileFind : public CQVObject
{
public:
	IQUFileFind(void);
	virtual ~IQUFileFind(void);
public:
	/////////////////////////////////////////////////////////////////
	//	@Close
	//		关闭文件查找句柄
	void				Close(void);
	/////////////////////////////////////////////////////////////////
	//	@FindFile
	//		开始查找文件
	//	参数:
	//		1. const char* filename
	//	返回：
	//		QV_OK:	成功。
	int					FindFile(const char* filename);
	/////////////////////////////////////////////////////////////////
	//	@FindNext
	//		查找下一文件
	int					FindNext(void);
	/////////////////////////////////////////////////////////////////
	//	@GetFindInfo
	//		获取查找到文件信息.必须在FindFile/FindNext函数调用返回QV_OK后调用
	//		该函数，否则返回的文件信息不保证正确。
	const IQUFileInfo&	GetFileInfo(void) const { return m_fileinfo; };
protected:
#if(defined(QVOS_WIN32)|defined(QVOS_WIN64))
	intptr_t		m_hFind;
#else
	HANDLE			m_hFind;		//	文件查找句柄
#endif
	char*			m_pathname;		//	查找路径
	char*			m_filename;		//	查找文件名
	IQUFileInfo		m_fileinfo;		//	当前查找到文件信息
};


/********************************************************************\
class IQUFile
	定义基础文件/目录操作接口
\********************************************************************/
class QVBASEDLL IQUFile : public CQVObject
{
public:
	enum AccessMode
	{
		ACCESS_EXIST	=0,
		ACCESS_RD		=2,
		ACCESS_WR		=4,
		ACCESS_RW		=6
	};
	enum FileAttr
	{
		FILE_ATTR_NORMAL= 0,
		FILE_ATTR_RDO	= 0x01,
		FILE_ATTR_HID	= 0x02,
		FILE_ATTR_SYS	= 0x04,
		FILE_ATTR_VOL	= 0x08,
		FILE_ATTR_DIR	= 0x10,
		FILE_ATTR_ARCH	= 0x20
	};

public:
	/////////////////////////////////////////////////////////////////
	//	@IsValid
	//		检查文件是否打开
	//	参数:
	//		无
	//	返回:
	//		true:	文件已经打开
	//		false:	文件未打开
	virtual bool	IsValid(void) const = 0;
	/////////////////////////////////////////////////////////////////
	//	@Open
	//		打开/创建一个文件
	//	参数:
	//		1. const char* filename:	文件名
	//		2. const char* mode:		文件打开方式，参照标准文件打开模式
	//									"a":	O_WRONLY | O_CREAT | O_APPEND
	//									"a+":	O_RDWR | O_APPEND | O_CREAT
	//									"r":	O_RDONLY
	//									"r+":	O_RDWR
	//									"w":	O_WRONLY | O_CREAT | O_TRUNC
	//									"w+":	O_RDWR | O_CREAT | O_TRUNC
	//	返回:
	//		QV_OK:	文件打开成功。
	virtual int		Open(const char* filename, const char* mode) = 0;

	/////////////////////////////////////////////////////////////////
	//	@Close
	//		关闭文件
	//	参数:	
	//		无
	//	返回:
	//		QV_OK:	文件关闭成功
	virtual int		Close(void) = 0;

	/////////////////////////////////////////////////////////////////
	//	@Write
	//		从当前文件位置写入数据
	//	参数:
	//		1. const char*	buffer:	待写入数据缓冲区指针。
	//		2. int			len:	待写入数据长度。如果<=0, 则内部会调用
	//								len = strlen(buffer)确定长度,此时
	//								必须保证buffer中包含的是以'\0'结束的
	//								字符串。
	//	返回:
	//		<0:		表示写入出错。
	//		>=0:	表示写入文件的字节数
	virtual int		Write(const char* buffer, int len) = 0;

	/////////////////////////////////////////////////////////////////
	//	@Read
	//		从当前文件位置读取数据
	//	参数:
	//		1. char* buffer:		待读取数据缓冲区
	//		2. int	 len:			待读取数据长度
	//	返回:
	//		<0:		表示读取失败。
	//		>=0:	表示实际读取数据长度。
	virtual int		Read(char* buffer, int len) = 0;

	/////////////////////////////////////////////////////////////////
	//	@Flush
	//		清空文件读写缓冲区.
	//	参数:
	//		无
	//	返回:
	//		QV_OK:	成功
	virtual int		Flush(void) = 0;

	/////////////////////////////////////////////////////////////////
	//	@GetPosition
	//		获取当前文件指针位置（相对于文件头的偏移值)
	//	参数:
	//		无
	//	返回:
	//		<0:		读取失败
	//		>=0:	返回当前文件指针位置
	virtual int64	GetPosition(void) = 0;

	/////////////////////////////////////////////////////////////////
	//	@Seek
	//		移动文件指针到指定的位置
	//	参数:
	//		1. int64 offset:	偏移位置
	//		2. int	 whence:	基准位置。SEEK_SET:	文件头位置
	//									SEEK_CUR:	当前文件位置
	//									SEEK_END:	文件结束位置
	//	返回：
	//		<0:		移动文件指针失败
	//		>=0:	文件移动以后的位置
	virtual int64	Seek(int64 offset, int whence) = 0;


public:
	/////////////////////////////////////////////////////////////////
	//	@GetFileName:
	//		获取当前文件名
	//	参数:
	//		无
	//	返回:
	//		返回文件名字符串指针
	const char* GetFileName(void) const { return m_filename; };

	/////////////////////////////////////////////////////////////////
	//	@GetLength
	//		获取文件长度
	//	参数:
	//		无
	//	返回:
	//		< 0:	获取文件长度失败
	//		>=0:	获取到的文件长度
	int64	GetLength(void);

	/////////////////////////////////////////////////////////////////
	//	@Append:
	//		格式化写入文件
	//	参数:
	//		1. const char* fmt:	格式字符串
	//		2. ... :			不定长参数
	//	返回:
	//		<0:		表示写入错误
	//		>=0:	表示写入文件字节数
	int QVAPIV	Append(const char* fmt, ...);


public:
	/////////////////////////////////////////////////////////////////
	//	@FileCreate
	//		创建一个IQUFile实例
	//	参数:
	//		1. IQUFile*& pf:	指向IQUFile*的引用，成功时返回创建的IQUFile实例指针。
	//		2. int		 type:	待创建的IQUFile实例的类型。
	//							QUFILE_TYPE_STD:	标准文件打开方式
	//							QUFILE_TYPE_LOW:	底层文件打开方式
	//	返回:
	//		QV_OK:	成功
	static	int FileCreate(IQUFile*& pf, int type);

	/////////////////////////////////////////////////////////////////
	//	@FileDelete
	//		删除一个IQUFile实例
	//	参数:
	//		1. IQUFile*& pf:	指向IQUFile*的引用，如果pf!=NULL,则删除pf实例，
	//							然后设置pf=NULL.
	//	返回:
	//		QV_OK:	成功
	static	int FileDelete(IQUFile*& pf);

public:
	///////////////////////////////////////////////////////////////////
	//	@Rename
	//		重新命名一个文件
	//	参数:
	//		1. const char* filenamesrc:	原始文件名
	//		2. const char* filenamedst:	目的文件名
	//	返回:
	//		QV_OK:	成功
	static	int Rename(const char* filenamesrc, const char* filenamedst);

	///////////////////////////////////////////////////////////////////
	//	@Remove
	//		删除一个文件
	//	参数:
	//		1. const char* filename:	待删除文件名
	//	返回:
	//		QV_OK:	成功
	static	int Remove(const char* filename);

	///////////////////////////////////////////////////////////////////
	//	@Copy
	//		复制一个文件
	//	参数:
	//		1. const char* filenamesrc:	待复制文件名
	//		2. const char* filenamedst:	新文件名
	//	返回:
	//		QV_OK:	成功
	static	int Copy(const char* filenamesrc, const char* filenamedst);

	///////////////////////////////////////////////////////////////////
	//	@MakeDir
	//		创建一个目录
	//	参数:
	//		1. const char* dirname:	待创建目录名
	//	返回:
	//		QV_OK:	成功
	static	int	MakeDir(const char* dirname);

	///////////////////////////////////////////////////////////////////
	//	@RemoveDir
	//		删除一个目录
	//	参数:
	//		1. const char* dirname:	待删除目录名
	//	返回:
	//		QV_OK:	成功
	static	int RemoveDir(const char* dirname);

	///////////////////////////////////////////////////////////////////
	//	@GetSpaceInfo
	//		获取磁盘空间信息
	//	参数:
	//		1. const char*	path:		磁盘路径名（或目录名)
	//		2. uint64&		spaceavail:	指向uint64的引用，返回用户可以使用的字节数
	//		3. uint64&		spacetotal:	指向uint64的引用，返回磁盘总的容量
	//		4. uint64&		spacefreed:	指向uint64的引用，返回磁盘空余容量
	//	返回:
	//		QV_OK:	成功
	static	int GetSpaceInfo(const char* path, uint64& spaceavail, uint64& spacetotal, uint64& spacefreed);

	///////////////////////////////////////////////////////////////////
	//	@Access
	//		检查文件访问权限
	//	参数:
	//		1. const char*	path:	待检查的文件名
	//		2. int			mode:	待检查的权限，
	//								ACCESS_EXIST：	检查文件是否存在
	//								ACCESS_RD:		检查是否有读的权限
	//								ACCESS_WR:		检查是否有写的权限
	//								ACCESS_RW:		检查是否有读写的权限
	//	返回：
	//		QV_OK:	有相应的权限
	static	int Access(const char* filename, int mode);

	///////////////////////////////////////////////////////////////////
	//	@GetFileInfo
	//		获取文件信息
	//	参数:
	//		1. const char*	filename:	文件名
	//		2. IQUFileInfo& info:		指向IQUFileInfo的引用，返回文件信息
	//	返回:
	//		QV_OK:	成功
	static	int GetFileInfo(const char* filename, IQUFileInfo& info);

	static  BOOL    CheckDirhasFile(const char* dir, const char* suffix);
	static  int     CreateFilePath(const char* pathname, bool parent = true);
	static  int     DeleteFilePath(const char* pathname, bool childs = true);
protected:
	IQUFile(void);
	virtual ~IQUFile(void);
protected:
	char*	m_filename;	
};

#endif//__QUFILE_H__