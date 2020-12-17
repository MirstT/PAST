#ifndef __CMSUTILITY_H__
#define __CMSUTILITY_H__

#include "infra/defines.h"
#include "windows.h"
#include <qcolor.h>
#include <QDateTime>
#include <QTime>
#include <QTimer>
#include <QSettings>
#include <QMap>
#include "VMSCore/VMSData/VMSDataGRP.h"
#include "qvc/QVCDefines.h"

#define _TR QObject::tr

#define UX_ATTRIBUTE_DECLARE(p,v) ;

#define pDeviceTreeModel        (VMSUtility::instance()->deviceTreeModel)
#define pDisplayMaster          (VMSUtility::instance()->m_displayManager)
#define pCmsPage(_pageId_)      (VMSUtility::instance()->pageInfo[_pageId_])
#define pMainWindow             ((PageMainWindow*)VMSUtility::instance()->m_pmainwindow)
#define URL_HOST "91.93.38.20:8098"
#define URL_BODY "GuvenliHayatService.asmx"

#define MODULE_FILE_PATH (VMSUtility::GetModuleFileInformations())
#define LOGINGIFPATH QString("res/%1/image/login.gif").arg(VMSUtility::instance()->qssName)
#define LOADGIFPATH QString("res/%1/image/loading.gif").arg(VMSUtility::instance()->qssName)
#define APPSettings() VMSUtility::instance()->GetAppSettings()

#define USERROLE Qt::UserRole

#define DISK_FREE_MIN				1024*1024*800 // 存储空间只有800M时不能再录像。
#define DISK_FREE_LOCALMIN			(1024*1024*100)//手动录像时磁盘至少预留200兆空间
#define DISK_FREE_LOCALMAX          2    //单位GB 改成2G (1024*1024*400)//手动录像启动时初始检测磁盘空间大小

enum PASSWORD_CHECK_TYPE
{
	PASSWORD_NUMBER = 0,
	PASSWORD_SMALL_LETTER,
	PASSWORD_CAPITAL,
	PASSWORD_SPECIALCHAR,

	PASSWORD_TYPE_ALL,
};

enum PASSWORD_LEVEL
{
	LEVEL_INVALID = 0,
	LEVEL_LOW,
	LEVEL_MID,
	LEVEL_HIGH,

	LEVEL_ALL,
};

enum COLOR_LEVEL
{
	COLOR_LEVEL_INVALID = qRgb(170, 170, 170),
	COLOR_LEVEL_LOW = qRgb(255, 0, 0)/*RGB(120,8,8)*/,
	COLOR_LEVEL_MID = qRgb(144, 144, 8),
	COLOR_LEVEL_HIGH = qRgb(8, 128, 8),
};

class QIcon;
class QStandardItemModel;
class QStandardItem;
class QTreeView;
class QLineEdit;

class VMSUtility
{
private:
    explicit VMSUtility(QObject* parent = 0); //No object should be created outside!
    ~VMSUtility();

private:
    static VMSUtility* s_instance;
    static bool s_appInitialized;

public:
    QString m_strUser;
    QString m_strPassword;
    QDateTime m_logTime;
    QString m_strEMapPath;
    QString curLang;
    void* m_pmainwindow;
    QString qssName;
    QString biges365UserName;
    QString biges365Password;
    QMap<QString,QMap<QString,QVariant> > biges365MapList;
    std::map<int,void*> pageInfo;

	QSettings m_appsetting;
    QTime m_timeForElapsed;
    QStandardItemModel* deviceTreeModel;

    char m_szCloudAddress[256];
    char m_szCloudAuthId[256];
    char m_szCloudPassword[256];
    int  m_nCloudPort;
    char m_szTDKCloudAddr[256];
    int  m_nTDKCloudPort;

public:
	QSettings&			GetAppSettings();
    static VMSUtility*	instance();
    static void			uninit();

	static int			initLanguage(void);
	static bool			initLanguage(const QString& lanType);

	static int			initSkin(void);
	static int			checkSingleInstance(QString& appName);
    //useful methods
    static bool     appInitialized(bool inited = false);
    static void     setAppStyle(const QString& styleName, const QColor& palette = QColor(Qt::black));
	static void		setAppStyle(QWidget* widget);
	static QString	GetAppStylebyQssFile(const QString &qss);
	static QString	GetStyleFolder();
    static void     showForm(QWidget* form, QWidget* ref = NULL, EmShowFormType showType=emCenter); //when ref is null, center to desktop
  
    static QStandardItemModel* CreateTreeOrgnization(long lOrgID, QStandardItem* item = NULL, bool bIsMain = false);
    static QIcon    clip(int x,int y,int w,int h,const QPixmap &pix);
	static QIcon    clip(int x, int y, int w, int h, const QString &file);
    static QIcon    getLockIcon(EmButtonStatus status = emNormalStatus);
    static QPixmap  getLockDialogPixmap();//软件锁定之后的对话框里文字前面的图标

    static bool     FindProcess(QString strExeName);
    static bool     CloseProcess(QString strExeName, bool bNotify=false);
    static void     MyOpenProcess(QString strExeName);
    static bool     MakeDirFromPath(QString strPath);
    static void     SetImageInEditFront(QString strImage, QLineEdit *edit);
    
    
    ///
    /// \brief 拷贝文件
    /// \param strFromPath 源文件地址
    /// \param strToPath 目的文件地址
    /// \param isConverIfExist 如果目的地址存在文件是否覆盖
    /// \return
    ///
    static bool     copyFile(QString strFromPath, QString strToPath, bool isConverIfExist=false);
    static void     setAppFont();
    ///
    /// \brief getTextLocal8bitByLenght 从strSource获取len字节长度的字符串
    /// \param strSource 源字符串
    /// \param len       需要获取的字节数
    /// \return          获取到的字符串
    ///
    static QString  getTextLocal8bitByLenght(QString strSource, int len);
    static QString  EncryptStringEx(QString strSource);
    static bool     DecryptStringEx(QString strSource, QString &strTarget);
    static void		tabTextWrap(QString &text);
    ///
    /// \brief 删除某个目录下的所有文件,不删除其中文件夹和文件夹中的文件
    /// \param strPath目录
    /// \return
    ///
    static bool     DeleteAllFileInPath(QString strPath);
    ///
    /// \brief 改变文件编码格式
    /// \param 文件路径
    /// \param 编码格式 "UTF-8"等
    /// \return
    ///
    static bool     ChangeFileToAnotherCode(QString strFile, const char *codename);
    static void     reLoadAppStyle(const QString& styleName,void* ptr);
    static void     readTitle(QString& title);//主界面上标题栏中显示的名称
    static void     readDesktopName(QString& name);//桌面上程序图标显示的名称
    static void     readDefaultMediaPort(QString &port);
    static void     readDefaultPassword(QString &password);
    
    static void     readCustomer(QString& strCustomer);
    static bool     isValidIP(QString strIP);
    static QString  GetRightName(QString strDir, int nIndex);
    static BOOL     CheckSuffix(char* szFileName,const char* szSuffixName, int nLen);
    static QString  GetResolutionRatio(int nSize);
    static QString  GetResolutionRatio(int nWidth, int nHeight,int special_parameter = 0);
    static const QString& GetModuleFileInformations();

#if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
    ///
    /// \brief RegDllControl 注册ocx控件
    /// \param strDll        ocx完整路径名
    /// \return              true成功 false失败
    ///
    //static bool RegDllControl(QString strDll);
#endif
    static ULONGLONG				getGBtoByte(int nGb);
    static bool						charCopy(const char* szSource, char* szDes, int nMaxDes);
    static bool						QStringCopy2UTF8(char* dst, QString src, int maxdst);
    static int						getLocalChar(QString strSrc, char *szDest, int nDestLen);
    static QString					getPathSuffixName(QString strPath);
    static int						MakePassword(QString &strPassword, bool bRestore = false);

	static __int64					CompareFileTime(FILETIME time1, FILETIME time2);
	static PASSWORD_LEVEL			checkPasswordFormat(QString pwd);

	static QIcon					getUserIcon();
	static QIcon					getCommonIcon(QString name);
	static QIcon					getIcon(char* dir, char* name, int w=0, int h=0);

	static BOOL						CheckDiskFreeSpace(QString& disk, ULONGLONG nFreespaceMinSize);
    static QString                  getSaveFileName(IVMSDataGRPVideoItem* item, CQVTime* time, bool record, bool ext=true);
    static QString                  getSaveFileName(uint devId, uint chnIndex, streamType stream, CQVTime* time, bool record, bool ext=true, QVC::RecordFormat format=QVC::REC_FORMAT_UK);
    static QString                  getSaveUrl(bool recordFile, QVC::RecordFormat fmt=QVC::REC_FORMAT_DAV);
};

#endif // __CMSUTILITY_H__
