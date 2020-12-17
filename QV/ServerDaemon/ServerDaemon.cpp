#include <QMouseEvent>
#include <QIcon>
#include <QMenu>
#include <QDir>

#include "ServerDaemon.h"
#include "ServerDaemonPages.h"
#include "MsgBox.h"
#include "trtext.h"

#define QSS "res/default/qss/ServerDaemonStyleSheet.qss"
#define ICON "res/default/image/serverdaemon/ServerIcon.png"
#define CONFIGFILE	"ServerConfig.ini"


//QTranslator  ServerDaemon::translator = NULL;

ServerDaemon::ServerDaemon(QWidget* parent)
    :QWidget(parent),
    ui(new Ui::ServerDeamonClass)
{
    ui->setupUi(this);
    this->loadStyleSheet(QSS);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Sheet);

    OnStartup();

    this->showMinimized();
    this->hide();
}

void ServerDaemon::IconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        this->showNormal();
        this->activateWindow();     //窗口置顶
        break;
    default:
        ;
    }
}

void ServerDaemon::OnBtnMinimizeClicked()
{
    this->hide();
}


void ServerDaemon::ExitApp()
{
    MsgBox* msgBox = new MsgBox(_CS("K4604_LbWarning"), _CS("K4515_LogoutInfo"));
    if (msgBox->exec() == QDialog::Accepted)
    {
        ::QVSStopServer(PgConfig::m_server);
        ::QVSReleaseServer(PgConfig::m_server);
        qApp->quit();
    }
}


ServerDaemonPages* ServerDaemon::GetCurrentPage()
{
    int index = this->GetPageIndex();
    if (m_pages.find(index) == m_pages.end())
        return nullptr;
    return m_pages[index];
}

void ServerDaemon::OnStartup()
{
    SetSystemTray();

    initCbLanguage();

    connect(ui->BtnMinimize, SIGNAL(clicked()), this, SLOT(OnBtnMinimizeClicked()));//窗口最小化；
    m_mspreesed = false;    //避免第一次页面启动点击language页面闪动
    //m_bIsFrist = true;
    ui->CbLanguage->setView(new  QListView());  //对language应用cb新样式

    //initLanguageCombobox();


    setWindowIcon(QIcon(ICON));

    ui->m_list_menu->setDragEnabled(false);											//list不可拖动复制
    m_pages = {
         { 0,new PgConfig(ServerDaemonPages::PgConfig,this) }
        ,{ 1,new PgMaintain(ServerDaemonPages::PgMaintain,this) }
        ,{ 2,new PgLog(ServerDaemonPages::PgLog,this) }
    };
    QObject::connect(ui->m_list_menu, SIGNAL(currentRowChanged(int)), this, SLOT(OnSwitchPage(int)));
    emit ui->m_list_menu->currentRowChanged(0);										//默认选中系统配置 发出信号初始化
}

void ServerDaemon::OnExit()
{
}

void ServerDaemon::SetSystemTray()
{
    QAction* restoreAction = new QAction(_CS("K4513_Set"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    QAction* quitAction = new QAction(_CS("K4514_Logout"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(ExitApp()));

    QMenu* trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addAction(quitAction);

    QIcon icon(ICON);
    m_systemTray = new QSystemTrayIcon(this);

    m_systemTray->setIcon(icon);
    m_systemTray->setToolTip(_CS("K4502_LbTitle"));
    m_systemTray->setContextMenu(trayIconMenu);
    m_systemTray->show();

    connect(m_systemTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
        this, SLOT(IconActivated(QSystemTrayIcon::ActivationReason)));
}


void ServerDaemon::OnSwitchPage(int index)
{
    if (m_pageid != index)
    {
        m_pages[m_pageid]->OnExit();	//对上个页面执行退出操作
    }

    m_pageid = index;
    ServerDaemonPages* page = GetCurrentPage();
    if (!page) return;

    page->OnStartup();
    emit ui->stackedWidget->setCurrentIndex(m_pageid);
}

//void ServerDaemon::OnCbLanguageChanged(int index)
//{
//    QTranslator  translator;
//    //QSettings* setting = new QSettings(CONFIGFILE, QSettings::IniFormat);
//    setting->setValue("skin/language", index);
//
//    if (index==0)
//    {
//        translator.load("./translations/Chinese.qm");
//
//    }
//    else if (index==1)
//    {
//        translator.load("./translations/English.qm");
//    }
//    qApp->installTranslator(&translator);
//    ui->retranslateUi(this);
//
//
//
//
//        curLang = arg1;
//
//
//    QSettings setting(CONFIGFILE, QSettings::IniFormat);
//    setting.setIniCodec("UTF8");
//    QStringList keylist = setting.allKeys();
//    QString name;
//    for (int i = 0; i < keylist.count(); i++)
//    {
//        QString key = keylist.at(i);
//        QString tempname = setting.value(key, "").toString();
//        if (tempname == arg1)
//        {
//            QStringList keysplit = key.split('/');
//            if (keysplit.count() != 2)
//                return;
//            name = keysplit.at(1);
//            break;
//        }
//    }
//    if (name.isEmpty())
//        return;
//
//    QString strIniFile = QString(QLatin1String(LOGIN_FILE));
//    QSettings settings(strIniFile, QSettings::IniFormat);
//    settings.setIniCodec("UTF-8");
//    if (VMSUtility::instance()->initLanguage(name))
//    {
//        settings.setValue(QStringLiteral("skin/Language"), name);
//    }
//    else
//    {
//        QString str = QString("English");
//        VMSUtility::instance()->initLanguage(str);
//        settings.setValue(QStringLiteral("skin/Language"), str);
//    }
//
//
//}


void ServerDaemon::loadStyleSheet(const QString& styleSheetFile)
{
    QFile file(styleSheetFile);
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());
        this->setStyleSheet(styleSheet);			
        file.close();
    }
}



//void ServerDaemon::changeEvent(QEvent* e)
//{
//    if (e->type() == QEvent::LanguageChange)
//    {
//        retranslate();
//    }
//}

//--窗体移动
static QPoint mousePosition;
void ServerDaemon::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton && m_mspreesed)
    {
        this->move(event->globalPos() - mousePosition);
    }
}

void ServerDaemon::mousePressEvent(QMouseEvent* event)
{
    mousePosition = event->globalPos() - this->pos();
    m_mspreesed = true;
}

void ServerDaemon::mouseReleaseEvent(QMouseEvent* event)
{
    m_mspreesed = false;
}

void ServerDaemon::initCbLanguage()
{
    QString strCurPath = QDir::currentPath();
    strCurPath.append(QStringLiteral("/translations/"));

    m_strPathLanguagesIni = QString("%1languages.ini").arg(strCurPath);
    SearchQMFile(strCurPath);

    QString strPathIni = QString(QLatin1String(CONFIGFILE));
    QSettings settings(strPathIni, QSettings::IniFormat);
    settings.setIniCodec("UTF8");
    QString strLanguage = settings.value(QStringLiteral("skin/Language"),QStringLiteral("English")).toString();

    QSettings setting(m_strPathLanguagesIni, QSettings::IniFormat);
    setting.setIniCodec("UTF8");
    QString strKey = QString("Languages/%1").arg(strLanguage);
    strLanguage = setting.value(strKey, "").toString();

    int count = ui->CbLanguage->count();
    int nIndex = ui->CbLanguage->currentIndex();
    bool isFind = false;
    int nDefault = 0;
    for (int i = 0; i < count; i++)
    {
        QString strTemp = ui->CbLanguage->itemText(i);
        if (strTemp == strLanguage)
        {
            ui->CbLanguage->setCurrentIndex(i);
            if (nIndex == i)
                OnCbLanguageChanged(ui->CbLanguage->currentText());
            isFind = true;
            break;
        }
        if (strTemp == QString("English"))
            nDefault = i;
    }
    if (!isFind)
    {
        ui->CbLanguage->setCurrentIndex(nDefault);
    }

    connect(ui->CbLanguage, SIGNAL(currentTextChanged(const QString&)), this, SLOT(OnCbLanguageChanged(const QString&)));
}




void ServerDaemon::SearchQMFile(QString strPath)
{
    QDir dir(strPath);
    QSettings setting(m_strPathLanguagesIni, QSettings::IniFormat);
    setting.setIniCodec("UTF8");
    foreach(QFileInfo fileInfo, dir.entryInfoList(QDir::Dirs | QDir::Files))
    {
        QString strName = fileInfo.fileName();
        if ((strName == QString(".")) || (strName == QString("..")))
            continue;
        if (fileInfo.isDir())
        {
            SearchQMFile(fileInfo.path());
        }
        else if (fileInfo.isFile())
        {
            QString strKey = QString("Languages/%1").arg(fileInfo.baseName());
            QString strLanguages = setting.value(strKey, "").toString();
            if (!strLanguages.isEmpty())
                ui->CbLanguage->addItem(strLanguages);
        }
    }
}

void ServerDaemon::OnCbLanguageChanged(const QString& curLanguage)
{
    //curLang = arg1;

    //if (m_bIsFrist)
    //{
    //    //插入语言的时候会系统调用一次，这个时候不设置语言。
    //    m_bIsFrist = false;
    //    return;
    //}

    QSettings setting(m_strPathLanguagesIni, QSettings::IniFormat);
    setting.setIniCodec("UTF8");
    QStringList languageKeyList = setting.allKeys();
    QString curLanguageName;
    for (int i = 0; i < languageKeyList.count(); i++)
    {
        QString languageKey = languageKeyList.at(i);
        QString tempLanguage = setting.value(languageKey, "").toString();
        if (tempLanguage == curLanguage)
        {
            QStringList languageKeySplit = languageKey.split('/');
            if (languageKeySplit.count() != 2)
                return;
            curLanguageName = languageKeySplit.at(1);
            break;
        }
    }
    if (curLanguageName.isEmpty())
        return;

    QString strIniFile = QString(QLatin1String(CONFIGFILE));
    QSettings settings(strIniFile, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");
    if (initLanguage(curLanguageName))
    {
        settings.setValue(QStringLiteral("skin/Language"), curLanguageName);
    }
    else
    {
        curLanguageName = QString("English");
        initLanguage(curLanguageName);
        settings.setValue(QStringLiteral("skin/Language"), curLanguageName);
    }
}

bool ServerDaemon::initLanguage(const QString& curLanguage)
{
    QString languageFile;
    QString strCurPath = QDir::currentPath();
    languageFile = strCurPath + QString("/translations/%1.qm").arg(curLanguage);

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
    return true;//removable line
}

void ServerDaemon::changeEvent(QEvent* event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}
