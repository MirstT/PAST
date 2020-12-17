#ifndef SERVERDAEMONPAGES_H
#define SERVERDAEMONPAGES_H

#include <QAxObject>
#include <QTime>
#include <QStandardItemModel>
#include <QWidget>

#include "ServerDaemonData.h"
#include "QVSServer/QVSServer.h"

class ServerDaemon;
class ServerDaemonPages :public QWidget
{
	Q_OBJECT
public:
	enum PageID {
		PgConfig,
		PgMaintain,
		PgLog,
	};

public:
	ServerDaemonPages(ServerDaemonPages::PageID pg, ServerDaemon* parent)
		:m_pageid(pg)
		, m_form(parent) {}
	~ServerDaemonPages() {}
public:
	virtual void    OnStartup() {}
	virtual void    OnExit() {}
	QString			SelectFilePath(QString fileFilter=NULL, QString fileName =NULL);
	ServerDaemonPages::PageID	GetPageID();

protected:
	ServerDaemon*	m_form;
	ServerDaemonPages::PageID	m_pageid;
};


class PgConfig :public ServerDaemonPages {
	Q_OBJECT
public:
	PgConfig(ServerDaemonPages::PageID page, ServerDaemon* parent);
	~PgConfig() {}

public:
	void OnStartup();
	void OnExit();

public slots:
	void    OnBtnStopStartServerClicked();
	void    OnBtnEditPortClicked();
	void    OnBtnCanclePortClicked();
	void    OnBtnSavePortClicked();
	void    OnCbAutostartClicked();
	void    OnBtnExportCetificationClicked();
	void    OnTimerTimeout();

private:
	void    StartServer();
	void    StopServer();
	void    ChangeToEditPort();
	void    ChangeToSavePort();
	void    AfterStartServer();
	void    AfterStopServer();
	QString GetHostIpAddress();
	QString GetRunningTime(int ms);
	void	AutoRunWithSystem(bool autosstart);

public:
	static HANDLE   m_server;
	static bool		m_serverstatus;


private:
	PgConfigData	m_data;
	QString		m_BtnSavePortStyle;
	QString		m_BtnEditPortStyle;
	QString		m_BtnStartServerStyle;
	QString		m_BtnStopServerStyle;
	QString		m_BtnStartServerDisabledStyle;
	//ushort	m_LastPort;

	bool		m_EditOrSavePort;

	QTimer*		m_Timer;        //定时器
	QTime		m_TimeCounter;  //计时器
};

 
class PgMaintain :public ServerDaemonPages {
	Q_OBJECT
public:
	PgMaintain(ServerDaemonPages::PageID page, ServerDaemon* parent);
	~PgMaintain() {}

public:
	void    OnStartup();
	void    OnExit();

private slots:
	void    OnBtnExportClientClicked();
	void    OnBtnExportResourceClicked();

private:
	void	SetTvClient();
	void	SetTvResource();
	void	LoadFakeClient();
	void	LoadFakeResource();

private:
	enum m_clientCol	{colIP, colAccount, colLastlogin};
	enum m_resourceCol	{colName, colUsed, colAvailable};
	std::list<QVSDTOClient>		m_client;
	std::list<QVSDTOResource>	m_resource;
	QStandardItemModel*	m_clientModel;
	QStandardItemModel*	m_resourceModel;
};


class PgLog :public ServerDaemonPages {
	Q_OBJECT
public:
	PgLog(ServerDaemonPages::PageID page, ServerDaemon* parent) :ServerDaemonPages(page, parent) {}
	~PgLog() {}

public:
	void OnStartup();
	void OnExit();
};

#endif // SERVERDAEMONPAGES_H