#include "utility.h"
#include "psapi.h"
#include <QtGui>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QTreeView>
#include <QLineEdit>
#include <QDesktopWidget>
#include <QLabel>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QApplication>
#include "CodeConvert.h"
#include  <shellapi.h>
#include "password.h"
#include "trtext.h"
#include <qsharedmemory.h>
#include "QVCClient/QVCClient.h"
#include "vmsapplication.h"
#include "qvc/QVCConfiguration.h"
#include "qvc/QVCDefines.h"

VMSUtility* VMSUtility::s_instance = NULL;
bool VMSUtility::s_appInitialized = false;

VMSUtility::VMSUtility(QObject* /*parent*/) : /*QObject(qApp),*/
    deviceTreeModel(NULL)
{
    m_timeForElapsed.start();

	QString strIniFile = QString(QLatin1String(APPLICATION_INI));
	m_appsetting.setPath(QSettings::IniFormat, QSettings::UserScope, strIniFile);
	m_appsetting.setIniCodec("UTF-8");
}

VMSUtility::~VMSUtility()
{

}

QSettings& VMSUtility::GetAppSettings()
{
	return this->m_appsetting;
}

VMSUtility* VMSUtility::instance()
{
    static QMutex utilMutex;
    if (!s_instance)
    {
        QMutexLocker locker(&utilMutex);
        if (!s_instance)
            s_instance = new VMSUtility;
    }
    return s_instance;
}

void VMSUtility::uninit()
{
    if(s_instance)
    {
        delete s_instance;
        s_instance = NULL;
    }
}

bool VMSUtility::appInitialized(bool inited /*= false*/)
{
    if(inited)
        s_appInitialized = true;

    return s_appInitialized;
}

void VMSUtility::showForm(QWidget* form, QWidget* ref/* = NULL*/, EmShowFormType showType)
{
    if(NULL == form)
        return;

    QRect refGeometry;
    if(NULL == ref)
    {
        QDesktopWidget * deskTop = QApplication::desktop();
        int curMonitor = deskTop->screenNumber ( form->parentWidget() );
        refGeometry = deskTop->availableGeometry(curMonitor);
    }
    else
    {
        refGeometry = ref->geometry();
    }

    int x,y=0;
    switch (showType) {
    case emCenter:
        x = ( refGeometry.width() - form->width() )/2 + refGeometry.left();
        y = ( refGeometry.height() - form->height() )/2 + refGeometry.top();
        break;
    case emRightBottom:
        x =  refGeometry.width() - form->width() + refGeometry.left();
        y =  refGeometry.height() - form->height() + refGeometry.top();
        break;
    default:
        break;
    }

    form->move(x, y);
}

void VMSUtility::setAppStyle(const QString& styleName, const QColor& palette /*= QColor(Qt::black)*/)
{
    VMSUtility::instance()->qssName = styleName;
    QFile file(QString("res/%1/qss/%2.qss").arg(styleName).arg(styleName));
    file.open(QFile::ReadOnly);
    QString qss = QString(file.readAll());

    QFile PicFile(QString("res/%1/qss/picture.qss").arg(styleName));
    PicFile.open(QFile::ReadOnly);
    QString picQss = QString(PicFile.readAll());
    qss += picQss;
    qApp->setStyleSheet(qss);
    //qApp->setPalette(palette);
}
void VMSUtility::setAppStyle(QWidget* w)
{
	QString stylefile = w->objectName();

	if (!w) {
			return;
	}
	QString strConfigPath = QString("%1/%2").arg(MODULE_FILE_PATH).arg(QLatin1String(LOGIN_FILE));
	QSettings setting(strConfigPath, QSettings::IniFormat);
	QString strSkin = setting.value(QStringLiteral("skin/Res"), "").toString();

	QString stylename = "";
	if (strSkin.isEmpty())
		stylename = QStringLiteral("default");
	else
		stylename = strSkin;

	QFile file(QString("res/%1/qss/%2.qss").arg(stylename).arg(stylefile));
	file.open(QFile::ReadOnly);
	QString qss = QString(file.readAll());
	w->setStyleSheet(qss);
}
QString VMSUtility::GetAppStylebyQssFile(const QString& qssfilename)
{
	QString strConfigPath = QString("%1/%2").arg(MODULE_FILE_PATH).arg(QLatin1String(LOGIN_FILE));
	QSettings setting(strConfigPath, QSettings::IniFormat);
	QString strSkin = setting.value(QStringLiteral("skin/Res"), "").toString();

	QString stylename = "";
	if (strSkin.isEmpty())
		stylename = QStringLiteral("default");
	else
		stylename = strSkin;

	QFile file(QString("res/%1/qss/%2.qss").arg(stylename).arg(qssfilename));
	file.open(QFile::ReadOnly);
	QString qss = QString(file.readAll());
	return qss;
}

QString VMSUtility::GetStyleFolder()
{
	QString strConfigPath = QString("%1/%2").arg(MODULE_FILE_PATH).arg(QLatin1String(LOGIN_FILE));
	QSettings setting(strConfigPath, QSettings::IniFormat);
	QString strSkin = setting.value(QStringLiteral("skin/Res"), "").toString();

	QString stylename = "";
	if (strSkin.isEmpty())
		stylename = QStringLiteral("default");
	else
		stylename = strSkin;
	QString stylefolder = QString("res/%1/").arg(stylename);
	return stylefolder;
}

void VMSUtility::reLoadAppStyle(const QString& styleName, void *ptr)
{
    QFile file(QString("res/%1/qss/%2.qss").arg(VMSUtility::instance()->qssName).arg(styleName));
    file.open(QFile::ReadOnly);
    QString qss = QString(file.readAll());
    ((QWidget *)ptr)->setStyleSheet(qss);
    //qApp->setPalette(palette);
}

QIcon  VMSUtility::clip(int x, int y, int w, int h, const QPixmap& pix)
{
	if (pix.isNull())
	{
		return QIcon();
	}

	int iconStartPosX = x;
	int iconStartPosY = y;
	int iconSizeW = w;
	int iconSizeH = h;

	return QIcon(pix.copy(iconStartPosX, iconStartPosY, iconSizeW, iconSizeH));
}

QIcon  VMSUtility::clip(int x, int y, int w, int h, const QString& file)
{
	return VMSUtility::clip(x, y, w, h, QPixmap(file));
}

QIcon VMSUtility::getCommonIcon(QString name)
{
	QString pixPath = QString("res/%1/image/common/%2.png").arg(VMSUtility::instance()->qssName).arg(name);
	QPixmap lockPixmap(pixPath);
	int iconStartPosX = 0;
	int iconStartPosY = 0;
	int iconSizeW = 20;
	int iconSizeH = 20;

	return QIcon(lockPixmap.copy(iconStartPosX, iconStartPosY, iconSizeW, iconSizeH));
}
QIcon VMSUtility::getUserIcon()
{
	QString pixPath = QString("res/%1/image/common/user.png").arg(VMSUtility::instance()->qssName);
	QPixmap lockPixmap(pixPath);
	int iconStartPosX = 0;
	int iconStartPosY = 0;
	int iconSizeW = 20;
	int iconSizeH = 20;

	return QIcon(lockPixmap.copy(iconStartPosX, iconStartPosY, iconSizeW, iconSizeH));
}
QIcon VMSUtility::getIcon(char* dir, char* name, int w, int h)
{
	QString pixPath = QString("res/%1/image/%2/%3").arg(VMSUtility::instance()->qssName).arg(dir).arg(name);
	QPixmap lockPixmap(pixPath);
	return QIcon(lockPixmap.copy(0, 0, w?w:20, h?h:20));
}
QIcon VMSUtility::getLockIcon(EmButtonStatus status)
{
    QString pixPath=QString("res/%1/image/playback/playback-lock.png").arg(VMSUtility::instance()->qssName);
    QPixmap lockPixmap(pixPath);
    int iconStartPosX = 0;
    int iconStartPosY = 0;
    int iconSizeW = 16;
    int iconSizeH = 16;
    if(status == emTurnUp)
    {
        iconStartPosX += iconSizeW;
    }
    return QIcon(lockPixmap.copy(iconStartPosX,iconStartPosY,iconSizeW,iconSizeH));
}

QPixmap VMSUtility::getLockDialogPixmap()
{
    QString pixPath=QString("res/%1/image/cms-lock.png").arg(VMSUtility::instance()->qssName);
    QPixmap lockPixmap(pixPath);
    int iconStartPosX = 170/*180*/;
    int iconStartPosY = 20;
    int iconSizeW = /*50*/85;
    int iconSizeH =50 /*86*/;
    return (QPixmap(lockPixmap.copy(iconStartPosX,iconStartPosY,iconSizeW,iconSizeH)))
            .scaled(20,20);
}



bool VMSUtility::FindProcess(QString strExeName)
{
#ifdef Q_OS_WIN32
    strExeName.replace("/", "\\");
    DWORD dwProcesses[1024], dwNeeded, dwProcNum;

    if (!EnumProcesses(dwProcesses, sizeof(dwProcesses), &dwNeeded))
    {
        return false;
    }

    dwProcNum = dwNeeded / sizeof(DWORD);   /*计算进程数*/
    for (int i = 0; i < dwProcNum; i++)
    {
        HANDLE hProcess = OpenProcess(PROCESS_TERMINATE | PROCESS_VM_READ | PROCESS_QUERY_INFORMATION,
            FALSE, dwProcesses[i]);
        if (NULL == hProcess)
        {
            continue;
        }

        HMODULE hMods[1024];
        DWORD	dwNeeded;
        if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &dwNeeded))
        {
            char szModName[MAX_PATH];
            if (GetModuleFileNameExA(hProcess, hMods[0], szModName, sizeof(szModName)))
            {
                QString TempName = QString::fromLocal8Bit(szModName);
                strExeName = strExeName.toUpper();
                TempName = TempName.toUpper();
                if (0 == QString::compare(strExeName, TempName))
                {
                    return true;
                }
            }
        }
    }

    return false;
#endif
#ifdef Q_OS_MAC
    //......mac
#endif
}


bool VMSUtility::CloseProcess(QString strExeName, bool bNotify)
{
#ifdef Q_OS_WIN32
    strExeName.replace("/", "\\");
    DWORD dwProcesses[1024], dwNeeded, dwProcNum;

    if (!EnumProcesses(dwProcesses, sizeof(dwProcesses), &dwNeeded))
    {
        return false;
    }

    dwProcNum = dwNeeded / sizeof(DWORD);   /*计算进程数*/
    for (int i = 0; i < dwProcNum; i++)
    {
        HANDLE hProcess = OpenProcess(PROCESS_TERMINATE | PROCESS_VM_READ | PROCESS_QUERY_INFORMATION,
            FALSE, dwProcesses[i]);
        if (NULL == hProcess)
        {
            continue;
        }

        HMODULE hMods[1024];
        DWORD	dwNeeded;
        if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &dwNeeded))
        {
            char szModName[MAX_PATH];
            if (GetModuleFileNameExA(hProcess, hMods[0], szModName, sizeof(szModName)))
            {
                QString TempName = QString::fromLocal8Bit(szModName);
                QString strExeNameUpper = strExeName.toUpper();
                TempName = TempName.toUpper();
                if (0 == QString::compare(strExeNameUpper, TempName, Qt::CaseInsensitive))
                {
                    if (bNotify)
                    {
                        QStringList strlist = strExeName.split("\\");
                        QString exename = strlist.at(strlist.size() - 1);
                        HWND hWnd = ::FindWindow(NULL, (LPCWSTR)exename.data());
                        if (hWnd != NULL)
                        {
                            COPYDATASTRUCT cpd;
                            memset(&cpd, 0, sizeof(cpd));
                            ::SendMessage(hWnd, WM_COPYDATA, NULL, (LPARAM)&cpd);
                        }
                        else
                        {

                        }
                    }
                    TerminateProcess(hProcess, 0);
                    return true;
                }
            }
        }
    }
    return false;
#endif
#ifdef Q_OS_MAC
    //......mac
#endif
}

void VMSUtility::MyOpenProcess(QString strExeName)
{
#ifdef Q_OS_WIN32
    bool bFlag = FindProcess(strExeName);
    if (!bFlag)
    {
        wchar_t sz[256] = { 0 };
        memcpy(sz, strExeName.unicode(), strExeName.length() * 2);
        HINSTANCE hinstance = ShellExecute(NULL, L"open", sz,
            NULL, NULL, SW_HIDE);
    }
#endif
#ifdef Q_OS_MAC
    //......mac
#endif
}

bool VMSUtility::MakeDirFromPath(QString strPath)
{
    bool bRet = false;
    QDir* dir = new QDir;

    QString temp;
    QString strDir = strPath.replace('\\', '/');

    int nIndex = strDir.lastIndexOf(".");
    if (nIndex != -1)
    {
        nIndex = strDir.lastIndexOf("/");
        if (nIndex != -1)
        {
            temp = strDir.left(nIndex);
        }
    }
    else
    {
        temp = strPath;
    }
    bRet = dir->mkpath(temp);

    delete dir;
    dir = NULL;

    return bRet;
}

void VMSUtility::SetImageInEditFront(QString strImage, QLineEdit* edit)
{
    edit->setMinimumHeight(24);
    edit->setTextMargins(34, 0, 0, 0);
    QLabel* lock = new QLabel(edit);
    lock->setMaximumSize(24, 24);
    //lock->setCursor(QCursor(Qt::ArrowCursor));
    lock->setPixmap(QPixmap(strImage));

    QSpacerItem* spaceItem = new QSpacerItem(150, 10, QSizePolicy::Expanding);
    QHBoxLayout* editLayout = new QHBoxLayout();
    editLayout->setContentsMargins(15, 0, 1, 0);
    editLayout->addWidget(lock);
    editLayout->addSpacerItem(spaceItem);
    edit->setLayout(editLayout);
}

bool VMSUtility::copyFile(QString strFromPath, QString strToPath, bool isConverIfExist)
{
    strFromPath.replace("\\", "/");
    strToPath.replace("\\", "/");
    if (strFromPath == strToPath) {
        return true;
    }
    if (!QFile::exists(strFromPath)) {
        return false;
    }
    QDir* createfile = new QDir;
    bool exist = createfile->exists(strToPath);
    if (exist) {
        if (isConverIfExist) {
            createfile->remove(strToPath);
        }
    }//end if
    delete createfile;
    createfile = NULL;

    if (!QFile::copy(strFromPath, strToPath))
    {
        return false;
    }
    return true;
}

void VMSUtility::setAppFont()
{
    QString fontName("Microsoft Yahei");

    QString qstr = QString("%1/custom.ini").arg(QDir::currentPath());
    QSettings settings(qstr, QSettings::IniFormat);
    settings.setIniCodec("UTF8");

    fontName = settings.value(QStringLiteral("Font/App"),
        QStringLiteral("Microsoft Yahei")).toString();

    QFont font;
    font.setFamily(fontName);
    qApp->setFont(font);
}

QString VMSUtility::getTextLocal8bitByLenght(QString strSource, int len)
{
    QString strTemp;
    int nLen = strSource.length();
    for (int i = 0; i < nLen; i++)
    {
        if (strTemp.toLocal8Bit().length() < len - 2)
        {
            strTemp += strSource.at(i);
        }
        else
            break;
    }
    return strTemp;
}

QString VMSUtility::EncryptStringEx(QString strSource)
{
    QString strEncode;
    QString strS = strSource;
    strS.insert(0, QStringLiteral("TDK"));
    QString strTemp;
    int i = 0;
    while (!strS.isEmpty())
    {
        strTemp += strS.at(0);
        if (strTemp.toLocal8Bit().length() == 16)
        {
            char szBuff[17] = { 0 };
            char szTarget[33] = { 0 };
            memcpy(szBuff, strTemp.toStdString().c_str(), 16);
            EncryptString(szBuff, szTarget);
            strEncode += QString(szTarget);

            strTemp.clear();
        }
        strS.remove(0, 1);
    }
    if (!strTemp.isNull() && strTemp.length() > 0)
    {
        char szBuff[17] = { 0 };
        char szTarget[33] = { 0 };
        int nCount = strTemp.toStdString().length();
        memcpy(szBuff, strTemp.toStdString().c_str(), nCount >= 16 ? 16 : nCount);
        EncryptString(szBuff, szTarget);
        strEncode += QString(szTarget);
    }

    return strEncode;
}

bool VMSUtility::DecryptStringEx(QString strSource, QString& strTarget)
{
    int nCount = strSource.length();
    if (nCount % 32 != 0)
        return false;

    QString strTemp;
    int round = nCount / 32;
    for (int i = 0; i < round; i++)
    {
        char szBuff[33] = { 0 };
        char szTarget[17] = { 0 };
        memcpy(szBuff, strSource.mid(i * 32, 32).toStdString().c_str(), 32);
        DecryptString(szBuff, szTarget);

        strTemp += QString(szTarget);
    }

    if (strTemp.isEmpty() || strTemp.isNull())
        return false;

    if (strTemp[0] != 'T' || strTemp[1] != 'D' || strTemp[2] != 'K')
        return false;

    strTarget = strTemp.remove(0, 3);

    return true;
}

void VMSUtility::tabTextWrap(QString& text)
{

    if (text.size() < 16)
        return;
    int x1, x2;
    x1 = text.indexOf(" ");
    x2 = text.indexOf(" ", x1 + 1);
    if (x2 < 16 && x2 >= 0)
        text.insert(x2, "\n");
    else if (x1 < 16 && x1 >= 0)
        text.insert(x1, "\n");
    return;
}

bool VMSUtility::DeleteAllFileInPath(QString strPath)
{
    QDir dir(strPath);
    foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Dirs | QDir::Files))
    {
        QString strName = fileInfo.fileName();
        if ((strName == QString(".")) || (strName == QString("..")))
            continue;
        if (fileInfo.isDir())
            continue;
        else if (fileInfo.isFile())
        {
            QFile file(fileInfo.absoluteFilePath());
            if (file.exists())
            {
                file.remove();
            }
        }
    }

    return true;
}


bool VMSUtility::ChangeFileToAnotherCode(QString strFile, const char* codename)
{
    QFileInfo fileinfo(strFile);
    QDir filedir = fileinfo.absoluteDir();
    QString tempfilepath = QString("%1/temp.temp").arg(filedir.path());

    QFile file(strFile);
    if (!file.open(QFile::ReadWrite))
        return false;

    QFile fileTemp(tempfilepath);
    if (!fileTemp.open(QFile::ReadWrite))
    {
        file.close();
        return false;
    }

    QTextStream in(&file);
    QTextStream out(&fileTemp);

    QString AllText;

    out.setCodec("UTF-8");
    out.setGenerateByteOrderMark(true);

    AllText = in.readAll();
    AllText = AllText.replace(QRegExp("\\\\"), "/");
    out << AllText;

    file.close();
    file.remove();

    fileTemp.close();

    if (!QFile::copy(tempfilepath, strFile))
        return false;

    fileTemp.remove();

    return true;
}
int VMSUtility::checkSingleInstance(QString& appName)
{
	QSharedMemory shm(appName);
	if (shm.create(200) == false)
		return -1;
	return 0;
}
int VMSUtility::initLanguage(void)
{
	//启动就加载语言以便提示
	QString strConfigPath = QString("%1/%2").arg(MODULE_FILE_PATH).arg(QLatin1String(LOGIN_FILE));
	QSettings setting(strConfigPath, QSettings::IniFormat);
	QString strLanguage = setting.value(QStringLiteral("skin/Language")).toString();
	if (!strLanguage.isEmpty())
	{
		bool isInit = initLanguage(strLanguage);
		if (!isInit)
			initLanguage(QString("English"));
	}
	else
	{
		initLanguage(QString("English"));
	}
	return 0;
}

bool VMSUtility::initLanguage(const QString& lanType)
{
    QString languageFile;

    languageFile = MODULE_FILE_PATH + QString("/Languages/%1.qm").arg(lanType);

    if (languageFile.isEmpty())
        return false;

    if (QFile(languageFile).exists())
    {
        QTranslator* pTran = new QTranslator(qApp);
        bool bIs = pTran->load(languageFile);
        bIs = qApp->installTranslator(pTran);
        if (bIs)
        {
            GETTEXT->Refresh();
        }
        return bIs;
    }
    else
    {
        qDebug() << "Sorry, language file does not exists ...";
        return false;
    }

    return true;//removable line
}

int VMSUtility::initSkin(void)
{
	QString strConfigPath = QString("%1/%2").arg(MODULE_FILE_PATH).arg(QLatin1String(LOGIN_FILE));
	QSettings setting(strConfigPath, QSettings::IniFormat);
	QString strSkin = setting.value(QStringLiteral("skin/Res"), "").toString();
	if (strSkin.isEmpty())
		setAppStyle(QStringLiteral("default"), Qt::lightGray);
	else
		setAppStyle(strSkin, Qt::lightGray);
	setAppFont();
	return 0;
}

void VMSUtility::readTitle(QString& title)
{
    static QString s_title("");
    if (s_title.isEmpty())
    {
        QString qstr = QString("%1/custom.ini").arg(QDir::currentPath());
        QSettings settings(qstr, QSettings::IniFormat);
        settings.setIniCodec("UTF8");

        s_title = settings.value(QStringLiteral("Name/Title"),
            QStringLiteral("CMS")).toString();

        int showver = settings.value(QStringLiteral("Name/ShowVer"), 1).toInt();
        if (showver)
        {
            qstr = QString("%1/CMSVerInfo.ini").arg(QDir::currentPath());
            QSettings settings(qstr, QSettings::IniFormat);
            settings.setIniCodec("UTF8");
            qstr = settings.value(QStringLiteral("Version_Info/Version"),
                QStringLiteral(" ")).toString();
            s_title = QString("%1 V%2").arg(s_title).arg(qstr);
        }
    }
    title = s_title;
}

void VMSUtility::readDesktopName(QString& name)
{
    static QString s_name("");
    if (s_name.isEmpty())
    {
        QString qstr = QString("%1/custom.ini").arg(QDir::currentPath());
        QSettings settings(qstr, QSettings::IniFormat);
        settings.setIniCodec("UTF8");

        s_name = settings.value(QStringLiteral("Name/App"),
            QStringLiteral("CMS")).toString();
    }
    name = s_name;
}
void VMSUtility::readDefaultMediaPort(QString& port)
{
    static QString s_mediaport("");
    if (s_mediaport.isEmpty())
    {
        QString qstr = QString("%1/custom.ini").arg(QDir::currentPath());
        QSettings settings(qstr, QSettings::IniFormat);
        settings.setIniCodec("UTF8");
        s_mediaport = settings.value(QStringLiteral("Device/MediaPort"), QStringLiteral("0")).toString();
    }

    port = s_mediaport;
}

void VMSUtility::readDefaultPassword(QString& password)
{
    static QString s_devicepassword("");
    if (s_devicepassword.isEmpty())
    {
        QString qstr = QString("%1/custom.ini").arg(QDir::currentPath());
        QSettings settings(qstr, QSettings::IniFormat);
        settings.setIniCodec("UTF8");

        s_devicepassword = settings.value(QStringLiteral("Device/Password"),
            QStringLiteral("")).toString();
    }
    password = s_devicepassword;
}


void VMSUtility::readCustomer(QString& strCustomer)
{
    static QString s_Customer("");
    if (s_Customer.isEmpty())
    {
        QString strTemp;
        QString qstr = QString("%1/custom.ini").arg(QDir::currentPath());
        QSettings settings(qstr, QSettings::IniFormat);
        settings.setIniCodec("UTF8");

        strTemp = settings.value(QStringLiteral("Customer/Id"),
            QStringLiteral("")).toString();

        int nCount = strTemp.length();
        if (nCount % 32 != 0)
            return;

        int round = nCount / 32;
        for (int i = 0; i < round; i++)
        {
            char szBuff[33] = { 0 };
            char szTarget[17] = { 0 };
            memcpy(szBuff, strTemp.mid(i * 32, 32).toStdString().c_str(), 32);
            DecryptString(szBuff, szTarget);

            s_Customer += QString(szTarget);
        }
    }
    strCustomer = s_Customer;
}

bool VMSUtility::isValidIP(QString strIP)
{
    if (strIP.isEmpty())
        return false;

    QStringList strNumList = strIP.split('.');
    if (strNumList.count() != 4)
        return false;

    for (int i = 0; i < strNumList.count(); i++)
    {
        QString strNum = strNumList.at(i);

        bool bIsInt = false;
        int nNum = strNum.toInt(&bIsInt);
        if (!bIsInt)
            return false;

        if (nNum < 0 || nNum > 255)
            return false;
    }

    return true;
}

QString VMSUtility::GetRightName(QString strDir, int nIndex)
{
    QString strTemp;
    QString strReturn;
    strTemp = QString("RightInfo/rn_%1").arg(nIndex);
    QSettings settings(strDir, QSettings::IniFormat);
    settings.setIniCodec("UTF8");
    strReturn = settings.value(strTemp).toString();

	char szTemp[256] = { 0 };
	strcpy(szTemp, strReturn.toStdString().c_str());
	strReturn = szTemp;

    return strReturn;
}

BOOL VMSUtility::CheckSuffix(char* szFileName, const char* szSuffixName, int nLen)
{
    int nFileNameLen = (int)strlen(szFileName);
    if (strcmp(szFileName + nFileNameLen - nLen, szSuffixName) == 0)
    {
        return TRUE;
    }
    return FALSE;
}

QString VMSUtility::GetResolutionRatio(int nSize)
{
    QString str("");
    switch (nSize)
    {
    case 0:
        str = "D1";
        break;
    case 1:
        str = "HD1";
        break;
    case 2:
        str = "BCIF";
        break;
    case 3:
        str = "CIF";
        break;
    case 4:
        str = "QCIF";
        break;
    case 5:
        str = "VGA";
        break;
    case 6:
        str = "QVGA";
        break;
    case 7:
        str = "SVCD";
        break;
    case 8:
        str = "4MP LiteS";
        break;
    case 9:
        str = "720P";
        break;
    case 10:
        str = "1080P";
        break;
    case 11:
        str = "5MP LiteS";
        break;
    case 12:
        str = "XVGA";
        break;
    case 13:
        str = "WXGA";
        break;
    case 14:
        str = "SXGA";
        break;
    case 15:
        str = "WSXGA";
        break;
    case 16:
        str = "USXGA";
        break;
    case 17:
        str = "WUSXGA";
        break;
    case 18:
        str = "960P";
        break;
    case 19:
        str = "960H";
        break;
    case 20:
        str = "1080N";
        break;
    case 21:
        str = "3M";
        break;
    case 22:
        str = "4M";
        break;
    case 23:
        str = "5M";
        break;
    case 24:
        str = "4X3_4M";
        break;
    case 25:
        str = "4X3_5M";
        break;
    case 26:
        str = "8M";
        break;
    case 27:
        str = "4M(2592x1520)";
        break;
    case 28:
        str = "D1_PAL";
        break;
    case 29:
        str = "4K";
        break;
    case 30:
        str = "3M";
        break;
    case 31:
        str = "720P";
        break;
    case 34:
        str = "12M";
        break;
    default:
        break;
    }
    return  str;
}

QString VMSUtility::GetResolutionRatio(int nWidth, int nHeight, int special_parameter)
{
    if ((nWidth == 1920) && (nHeight == 1080))
        return QString("1080P");//10

    if ((nWidth == 960) && (nHeight == 1080))
    {
        QString qstr = QString("%1/custom.ini").arg(QDir::currentPath());
        QSettings settings(qstr, QSettings::IniFormat);
        settings.setIniCodec("UTF8");
        QString strResolution = settings.value(QStringLiteral("Resolution/1080PLite"),
            QStringLiteral("1080P Lite")).toString();
        return strResolution;//20
        //return QString("1080P Lite");//20
    }

    if ((nWidth == 1280) && (nHeight == 720))
        return QString("720P");//9

    if (((nWidth == 960) && (nHeight == 480))
        || ((nWidth == 960) && (nHeight == 576))
        || ((nWidth == 928) && (nHeight == 480))
        || ((nWidth == 928) && (nHeight == 576)))
        return QString("960H");//19

    if (((nWidth == 704) && (nHeight == 576))
        || ((nWidth == 704) && (nHeight == 480))
        || ((nWidth == 720) && (nHeight == 576))
        || ((nWidth == 720) && (nHeight == 480)))
        return QString("D1");//0

    if (((nWidth == 352) && (nHeight == 576))
        || ((nWidth == 352) && (nHeight == 480)))
        return QString("HD1");//1

    if (((nWidth == 704) && (nHeight == 288))
        || ((nWidth == 704) && (nHeight == 240))
        || ((nWidth == 720) && (nHeight == 288))
        || ((nWidth == 720) && (nHeight == 240)))
        return QString("BCIF");//2

    if (((nWidth == 352) && (nHeight == 288))
        || ((nWidth == 352) && (nHeight == 240)))
        return QString("CIF");//3

    if (((nWidth == 176) && (nHeight == 144))
        || ((nWidth == 176) && (nHeight == 120)))
        return QString("QCIF"); //4

    if ((nWidth == 640) && (nHeight == 480))
        return QString("VGA"); //5

    if ((nWidth == 320) && (nHeight == 240))
        return QString("QVGA"); //6

    if ((nWidth == 480) && (nHeight == 480))
        return QString("SVCD"); //7

    if ((nWidth == 160) && (nHeight == 128))
        return QString("QQVGA"); //8

    if ((nWidth == 800) && (nHeight == 592))
        return QString("SVGA"); //11

    if ((nWidth == 1024) && (nHeight == 768))
        return QString("XVGA"); //12

    if ((nWidth == 1280) && (nHeight == 800))
        return QString("WXGA");//13

    if ((nWidth == 1280) && (nHeight == 1024))
        return QString("SXGA");//14

    if ((nWidth == 1600) && (nHeight == 1024))
        return QString("WSXGA");//15

    if ((nWidth == 1600) && (nHeight == 1200))
        return QString("UXGA");//16

    if ((nWidth == 1920) && (nHeight == 1200))
        return QString("WUXGA");//17

    if ((nWidth == 1280) && (nHeight == 960))
        return QString("960P");//18

    if ((nWidth == 2048) && (nHeight == 1536))
        return QString("3M");//21

    if (((nWidth == 2304) && (nHeight == 1728))
        || ((nWidth == 2592) && (nHeight == 1520)))
        return QString("4M(4:3)");//27

    if ((nWidth == 2560) && (nHeight == 1440) && special_parameter == 0)
        return QString("4M(16:9)");//22
    if ((nWidth == 2560) && (nHeight == 1440) && special_parameter == 1)
        return QString("4M(NRT)");//30
    if ((nWidth == 2560) && (nHeight == 1440) && special_parameter == 2)
        return QString("4M(RT)");//31

    if (((nWidth == 2592) && (nHeight == 2048))
        || ((nWidth == 2592) && (nHeight == 1944)))
        return QString("5M(4:3)");//23

    if ((nWidth == 3072) && (nHeight == 1728))
        return QString("5M");

    if ((nWidth == 3840) && (nHeight == 2160))
        return QString("8M");

    if ((nWidth == 4096) && (nHeight == 2160))
        return QString("4K");

    if ((nWidth == 4000) && (nHeight == 3000))
        return QString("12M");
    if ((nWidth == 1280) && (nHeight) == 1440)
        return QString("4M Lite");

    if ((nWidth == 1920) && (nHeight) == 2160)
        return QString("8M Lite");

    if ((nWidth == 1280) && (nHeight) == 1944)
        return QString("5M Lite");

    if ((nWidth == 640 && nHeight == 1440))
        return QString("4MP LiteS");

    if ((nWidth == 640 && nHeight == 1944))
        return QString("5MP LiteS");

    return QString("%1x%2").arg(nWidth).arg(nHeight);
}

const QString& VMSUtility::GetModuleFileInformations()
{
    static QString __module_file_path__;
    static bool s_bLoad = false;

    if (!s_bLoad)
    {
        __module_file_path__ = QCoreApplication::applicationDirPath();
        s_bLoad = true;
    }

    return __module_file_path__;
}
#if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
//bool VMSUtility::RegDllControl(QString strDll)
//{
//    if(strDll.isEmpty())
//        return false;

//    HINSTANCE hDll = LoadLibraryA(strDll.toStdString().c_str());
//    if(!hDll)
//        return false;

//    typedef int (far __stdcall *registerDll)();
//    registerDll fun = NULL;
//    fun = GetProcAddress(hDll, "DllRegisterServer");
//    if(!fun)
//    {
//        FreeLibrary(hDll);
//        return false;
//    }

//    if(fun() != 0)
//    {
//        FreeLibrary(hDll);
//        return false;
//    }

//    FreeLibrary(hDll);
//    return true;
//}
#endif
ULONGLONG VMSUtility::getGBtoByte(int nGb)
{
    ULONGLONG mb = 1024 * 1024;
    ULONGLONG gb = mb * 1024;
    ULONGLONG numByte = gb * nGb;
    return numByte;
}

bool VMSUtility::charCopy(const char* szSource, char* szDes, int nMaxDes)
{
    if (!szSource || !szDes || 0 >= nMaxDes)
        return false;
    int nLen = strlen(szSource);
    if (nLen > (nMaxDes - 1))
        nLen = nMaxDes - 1;
    memcpy(szDes, szSource, nLen);
    szDes[nLen] = '\0';
    return true;
}

bool VMSUtility::QStringCopy2UTF8(char* dst, QString src, int maxdst)
{
    return charCopy(src.toStdString().c_str(), dst, maxdst);
}

int VMSUtility::getLocalChar(QString strSrc, char* szDest, int nDestLen)
{
    if (!szDest)
        return -1;
    QTextCodec* locale = QTextCodec::codecForLocale();
    if (!locale)
        return -1;
    QByteArray qba = locale->fromUnicode(strSrc);
    int nLen = qba.length();
    nLen = nLen >= nDestLen ? nDestLen : nLen;
    memcpy(szDest, qba.data(), nLen);
    szDest[nLen] = '\0';
    return 0;
}

QString VMSUtility::getPathSuffixName(QString strPath)
{
    QString strType;
    int pos = strPath.lastIndexOf('.');
    if (pos > 0)
    {
        strType = strPath.right(strPath.length() - pos - 1);
    }

    return strType;
}

int VMSUtility::MakePassword(QString& strPassword, bool bRestore)
{
    if (strPassword.isEmpty())
        return -1;
    if (!bRestore)
        strPassword = strPassword.replace("@", "@@");
    else
        strPassword = strPassword.replace("@@", "@");
    return 0;
}

__int64 VMSUtility::CompareFileTime(FILETIME time1, FILETIME time2)

{

	__int64 a = (DWORD64)time1.dwHighDateTime << 32 | time1.dwLowDateTime;

	__int64 b = (DWORD64)time2.dwHighDateTime << 32 | time2.dwLowDateTime;

	return (b - a);

}
PASSWORD_LEVEL	VMSUtility::checkPasswordFormat(QString pwd)
{
	if (pwd.isEmpty())
		return LEVEL_INVALID;

	int iLength = pwd.length();
	if (iLength < MIN_PSW_LENGTH)
		return LEVEL_INVALID;

	BOOL bHaveType[PASSWORD_TYPE_ALL] = { 0 };
	for (int i = 0; i < iLength; i++)
	{
		QChar ch = pwd.at(i);
		if ((ch >= '0') && (ch <= '9'))
		{
			bHaveType[PASSWORD_NUMBER] = TRUE;
		}
		else if ((ch >= 'a') && (ch <= 'z'))
		{
			bHaveType[PASSWORD_SMALL_LETTER] = TRUE;
		}
		else if ((ch >= 'A') && (ch <= 'Z'))
		{
			bHaveType[PASSWORD_CAPITAL] = TRUE;
		}
		else
		{
			bHaveType[PASSWORD_SPECIALCHAR] = TRUE;
		}
	}

	int iCount = 0;
	for (int j = 0; j < PASSWORD_TYPE_ALL; j++)
	{
		iCount += bHaveType[j];
	}
	return PASSWORD_LEVEL(iCount-1);
}


BOOL VMSUtility::CheckDiskFreeSpace(QString &disk, ULONGLONG nFreespaceMinSize)
{
	ULARGE_INTEGER  lpuse;					//用于容纳调用者可用的字节数量 
	ULARGE_INTEGER  lptotal;				//用于容纳磁盘上的总字节数  
	ULARGE_INTEGER  lpfree;					//用于容纳磁盘上可用的字节数 
	ULONGLONG lFreeSpaceStandard = nFreespaceMinSize; //(1024*1024*900)  
	QString strCurdir;

	QString root = disk.left(3);
	::GetDiskFreeSpaceExW((LPCWSTR)root.unicode(), &lpuse, &lptotal, &lpfree);//
	if (lpfree.QuadPart > lFreeSpaceStandard)
	{
		return TRUE;//表示还有空闲
	}
	return FALSE;//表示当前文件夹已满

}
QString VMSUtility::getSaveFileName(IVMSDataGRPVideoItem* item, CQVTime* time, bool record, bool ext)
{
    return getSaveFileName(item->GetDevId(),item->GetChnIndex(),item->GetStreamType(),time,record,ext);
}
QString VMSUtility::getSaveFileName(uint devId, uint chnIndex, streamType stream, CQVTime* time, bool record, bool ext, QVC::RecordFormat format)
{
    IVMSDataDEVPtr dev = (IVMSDataDEVPtr)QVCGetVMSObject(APPServer(), VMS_DEVM_OBJECT_ID_DEV, devId);
    if (!dev)
        return "";
    QString name = QString("%1-%2-%3-%4%5%6-%7%8%9")
        .arg(dev->GetGUID()).arg(chnIndex, 2, 10, QChar('0')).arg(stream, 2, 10, QChar('0'))
        .arg(time->GetYear(), 4, 10, QChar('0')).arg(time->GetMonth(), 2, 10, QChar('0')).arg(time->GetDay(), 2, 10, QChar('0'))
        .arg(time->GetHour(), 2, 10, QChar('0')).arg(time->GetMinute(), 2, 10, QChar('0')).arg(time->GetSecond(), 2, 10, QChar('0'));
    if (!ext)
        return name;
    if (record)
    {
        QVC::RecordFormat fmt = format;
        if(fmt == QVC::REC_FORMAT_UK)
           fmt = QVCConfiguration::GetQVCConfig()->GetPreviewOption().recfmt;
        if (fmt == QVC::REC_FORMAT_MP4)
            name += ".mp4";
        if (fmt == QVC::REC_FORMAT_DAV)
            name += ".dav";
        if (fmt == QVC::REC_FORMAT_AVI)
            name += ".avi";
    }
    else
        name += ".jpg";
    return name;
}
QString VMSUtility::getSaveUrl(bool recordFile, QVC::RecordFormat fmt)
{
    QString url, path;
    url += "filew://local";
    if (recordFile)
    {
        //QVC::RecordFormat fmt = QVCConfiguration::GetQVCConfig()->GetPreviewOption().recfmt;
        if (fmt == QVC::REC_FORMAT_MP4)
            url += "/type=rec&format=mp4";
        if (fmt == QVC::REC_FORMAT_DAV)
            url += "/type=rec&format=dav";
        if (fmt == QVC::REC_FORMAT_AVI)
            url += "/type=rec&format=avi";
        url += "&size=500";
        path = QString::fromUtf8(QVCConfiguration::GetQVCConfig()->GetFileOption().videopath.c_str());
    }
    else
    {
        QVC::PictureFmt fmt = QVCConfiguration::GetQVCConfig()->GetPreviewOption().picfmt;
        if(fmt == QVC::JPEG)
            url += "/type=pic&format=jpg";
        if (fmt == QVC::PNG)
            url += "/type=pic&format=png";
        if (fmt == QVC::BMP)
            url += "/type=pic&format=bmp";
        path = QString::fromUtf8(QVCConfiguration::GetQVCConfig()->GetFileOption().imgpath.c_str());
    }   
    url += "&pathname=";
#ifdef Q_OS_WIN
    path.replace('/', '\\');
    //#elif  Q_MV_OSX
#endif
    url += path;
    return url;
}