#ifndef SERVERDAEMON_H
#define SERVERDAEMON_H

#include "ui_ServerDaemon.h"
#include <QSystemTrayIcon>
#include <QTranslator>

class ServerDaemonPages;

class ServerDaemon : public QWidget
{
    Q_OBJECT
        public:
    ServerDaemon(QWidget* parent = Q_NULLPTR);
    ~ServerDaemon() {}

public:
    ServerDaemonPages*     GetCurrentPage();
    Ui::ServerDeamonClass* GetUI() { return ui; }
    int                    GetPageIndex()     { return m_pageid; }
    void                   loadStyleSheet(const QString& styleSheetFile);
    void                   SetSystemTray();
    virtual void           OnStartup();
    virtual void           OnExit();

public slots:
    void ExitApp();
    void IconActivated(QSystemTrayIcon::ActivationReason reason);
    void OnBtnMinimizeClicked();
    void OnSwitchPage(int index);

protected:

    //void changeEvent(QEvent* e);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private:
    void initCbLanguage();
    void SearchQMFile(QString strPath);
    bool initLanguage(const QString& curLanguage);
    void changeEvent(QEvent* event);

private slots:
    void OnCbLanguageChanged(const QString& curLanguage);


public:
    Ui::ServerDeamonClass*  ui;
    std::map<int, ServerDaemonPages*>   m_pages;
    QSystemTrayIcon*    m_systemTray;
    int m_pageid = 0;

    QString m_strPathLanguagesIni;
    //QString curLang;
    //bool    m_bIsFrist;


private:
    bool    m_mspreesed;

};

#endif