#include <QIntValidator>
#include <QtNetwork>
#include <QFileDialog>

#include "ServerDaemonPages.h"
#include "ServerDaemon.h"
#include "MsgBox.h"
#include "ExcelExport.h"
#include "trtext.h"

#define AUTO_RUN		"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"
#define UI()			this->m_form->GetUI()
#define DefaultPort		8088
#define NoPort			"----"
#define NoIP			"0.0.0.0"
#define SavePortState	true
#define EditPortState	false
#define	ClientColum		3
#define	ResourceColum	3
HANDLE	PgConfig::m_server = nullptr;
bool	PgConfig::m_serverstatus = false;

QString ServerDaemonPages::SelectFilePath(QString fileFilter,QString fileName)
{
	QFileDialog dlg;

	dlg.setAcceptMode(QFileDialog::AcceptSave);
	dlg.setDirectory(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
	if (!fileFilter.isEmpty())
	{
		dlg.setNameFilter(fileFilter);
	}
	fileName = fileName + QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
	dlg.selectFile(fileName);
	dlg.setAttribute(Qt::WA_QuitOnClose, false);
	if (dlg.exec() != QDialog::Accepted)
		return NULL;
	QString filePath = dlg.selectedFiles()[0];	//�õ��û�ѡ����ļ���
	return filePath;
}

ServerDaemonPages::PageID ServerDaemonPages::GetPageID()
{
	return m_pageid;
}

PgConfig::PgConfig(ServerDaemonPages::PageID page, ServerDaemon* parent)
	:ServerDaemonPages(page, parent),
	m_data(ServerDaemonData::GetServerDaemonData()->GetConfigData())
{

	m_Timer = new QTimer(this);
	m_Timer->stop();
	m_Timer->setInterval(500);//���ö�ʱ���ڣ���λ������
	connect(m_Timer, SIGNAL(timeout()), this, SLOT(OnTimerTimeout()));

	m_BtnSavePortStyle = "QPushButton{background:#1B6DC3;width:50px;}\
							QPushButton:hover{background:#298CF4;}";
	m_BtnEditPortStyle = "QPushButton{background:#484D58;}\
							QPushButton:hover{background:#6A6F7A;}";
	m_BtnStartServerStyle = "QPushButton{background:#1B6DC3;}\
							QPushButton:hover{background:#298CF4;}";
	m_BtnStopServerStyle = "QPushButton{background:#DD5044;}\
							QPushButton:hover{background:#EC6153;}";
	m_BtnStartServerDisabledStyle = "QPushButton:disabled{background:#484D58;color:#757575;}";

	UI()->EdtPort->setValidator(new QIntValidator(80, 65535, this));
	UI()->CbAutostart->setCheckState(m_data.runstartup ? Qt::Checked : Qt::Unchecked);
	UI()->BtnCanclePort->hide();
	UI()->EdtPort->setEnabled(false);
	m_EditOrSavePort = EditPortState;

	connect(UI()->BtnStopStartServer, SIGNAL(clicked()), this, SLOT(OnBtnStopStartServerClicked()));
	connect(UI()->BtnEditPort, SIGNAL(clicked()), this, SLOT(OnBtnEditPortClicked()));
	connect(UI()->BtnCanclePort, SIGNAL(clicked()), this, SLOT(OnBtnCanclePortClicked()));
	connect(UI()->CbAutostart, SIGNAL(stateChanged(int)), this, SLOT(OnCbAutostartClicked()));
	connect(UI()->BtnExportCetification, SIGNAL(clicked()), this, SLOT(OnBtnExportCetificationClicked()));
	
	//m_LastPort = m_data.port;
	//m_server = ::QVSCreateServer(m_data.port);				//�����һ����������server

	m_data.port = m_data.port ? m_data.port : DefaultPort;	//port������ʱ����Ĭ��DefaultPort
	StartServer();											//����server
}

void PgConfig::OnStartup()
{
	//��ʾ�˿ں�/�༭״̬�·����л������������ָ�
	UI()->EdtPort->setText(QString::number(m_data.port));

	if (!m_serverstatus)
	{
		ChangeToEditPort();
	}
}

void PgConfig::OnBtnStopStartServerClicked()
{
    if (!m_serverstatus)
	{
		StartServer();
    }
    else 
	{
		MsgBox* msgBox = new MsgBox(_CS("K4604_LbWarning"), _CS("K4524_LbWhetherStopServer"));
		if (msgBox->exec() == QDialog::Accepted)
		{
			StopServer();
		}
    }
}


void PgConfig::OnBtnEditPortClicked()
{
	if (m_EditOrSavePort == EditPortState)
	{
		ChangeToSavePort();
	}
	else
	{
		OnBtnSavePortClicked();
	}
}

void PgConfig::OnBtnSavePortClicked()
{
	//--�Ƿ��ַ�Ϊ0������ΪĬ�϶˿ں�
	m_data.port = UI()->EdtPort->text().toUShort() ? UI()->EdtPort->text().toUShort() : DefaultPort;
	UI()->EdtPort->setText(QString::number(m_data.port));
	ChangeToEditPort();
	//m_LastPort = m_data.port;	//��¼����ǰ�Ķ˿ں�
	m_data.Save();
}

void PgConfig::OnBtnCanclePortClicked()
{
	//�ָ�����
	UI()->EdtPort->setText(QString::number(m_data.port));
	ChangeToEditPort();
}

void PgConfig::AutoRunWithSystem(bool autosstart)
{
	QString application_name = QApplication::applicationName();	//��ȡӦ������
	QSettings* settings = new QSettings(AUTO_RUN, QSettings::NativeFormat);	//����QSetting, ��Ҫ���QSettingͷ�ļ�
	if (autosstart) {
		QString application_path = QApplication::applicationFilePath();	//�ҵ�Ӧ�õ�Ŀ¼
		settings->setValue(application_name, application_path.replace("/", "\\"));	//д��ע���
	}
	else
	{
		settings->remove(application_name);
	}
}


void PgConfig::OnCbAutostartClicked()
{
	bool runstartup = UI()->CbAutostart->isChecked();
	if (m_data.runstartup != runstartup)
	{
		m_data.runstartup = runstartup;
		m_data.Save();
	}
}

void PgConfig::OnTimerTimeout()
{
	UI()->LbUptime->setText(GetRunningTime(m_TimeCounter.elapsed()));
}

void PgConfig::OnBtnExportCetificationClicked()
{
	QString filePath = SelectFilePath("*.xml",_CS("K4525_LbCetification"));
	CQVString cetification;
	QVSExportCetification(PgConfig::m_server, cetification);
	
	//--Test DATA!!!
	cetification = "This is the test data about Cetification";

	if (!filePath.isEmpty())
	{
		QFile fp(filePath);
		fp.open(QIODevice::WriteOnly);
		fp.write(cetification.GetBuffer());
		fp.close();
	}
}

QString PgConfig::GetRunningTime(int ms)
{
	int ss = 1000;
	int mi = ss * 60;
	int hh = mi * 60;
	int dd = hh * 24;

	long day = ms / dd;
	long hour = (ms - day * dd) / hh; 
	long minute = (ms - day * dd - hour * hh) / mi;
	long second = (ms - day * dd - hour * hh - minute * mi) / ss;
	//long milliSecond = ms - day * dd - hour * hh - minute * mi - second * ss;

	QString d = QString::number(day, 10);
	QString hou = QString::number(hour, 10).sprintf("%02d", hour);
	QString min = QString::number(minute, 10).sprintf("%02d", minute);
	QString sec = QString::number(second,10).sprintf("%02d",second);

	if (day)
	{
		return day + ":" + hou + ":" + min + ":" + sec;
	}
	else
	{
		return hou + ":" + min + ":" + sec;
	}
}

void PgConfig::StartServer()
{
	////--�˿ںŸı䣬�ͷžɶ˿ڷ������������¶˿ڷ�����
	//if (m_data.port != m_LastPort)
	//{
	//	::QVSReleaseServer(m_server);
	//	m_server = ::QVSCreateServer(m_data.port);
	//}

	m_server = ::QVSCreateServer(m_data.port);
	if (::QVSStartServer(m_server) < 0) 
	{
		m_form->m_systemTray->showMessage(_CS("K4505_Fail"), _CS("K4506_VMSServerFail"));
		AfterStopServer();
	}
	else 
	{
		m_form->m_systemTray->showMessage(_CS("K4503_Success"), _CS("K4504_VMSServerSuccess"));
		AfterStartServer();
	}
}

void PgConfig::StopServer()
{
	::QVSStopServer(m_server);
	::QVSReleaseServer(m_server);
	m_form->m_systemTray->showMessage(_CS("K4507_Close"), _CS("K4508_VMSServerStop"));
	AfterStopServer();
}

void PgConfig::ChangeToEditPort()
{
	m_EditOrSavePort = EditPortState;
	UI()->BtnCanclePort->hide();
	UI()->EdtPort->setEnabled(false);
	UI()->BtnStopStartServer->setEnabled(true);
	UI()->BtnStopStartServer->setStyleSheet(m_BtnStartServerStyle);
	UI()->BtnEditPort->setText(_CS("K4528_BtnEditPort"));
	UI()->BtnEditPort->setStyleSheet(m_BtnEditPortStyle);
}

void PgConfig::ChangeToSavePort()
{
	m_EditOrSavePort = SavePortState;
	UI()->BtnCanclePort->show();
	UI()->EdtPort->setEnabled(true);
	UI()->BtnStopStartServer->setEnabled(false);
	UI()->BtnStopStartServer->setStyleSheet(m_BtnStartServerDisabledStyle);
	UI()->BtnEditPort->setText(_CS("K4529_BtnSavePort"));
	UI()->BtnEditPort->setStyleSheet(m_BtnSavePortStyle);
}

void PgConfig::AfterStartServer()
{
	m_serverstatus = true;
	UI()->BtnStopStartServer->setStyleSheet(m_BtnStopServerStyle);
	UI()->BtnStopStartServer->setText(_CS("K4522_BtnStopServer"));
	UI()->BtnEditPort->setEnabled(false);
	UI()->LbPortInfo->setText(QString::number(m_data.port));    //����������ʾ״̬���˿���IP��Ϣ
	UI()->LbIPInfo->setText(GetHostIpAddress());
	m_Timer->start();		//��ʱ����ʼ����
	m_TimeCounter.start();	//��ʱ����ʼ����
}

void PgConfig::AfterStopServer()
{
	m_serverstatus = false;
	UI()->BtnStopStartServer->setStyleSheet(m_BtnStartServerStyle);
	UI()->BtnStopStartServer->setText(_CS("K4523_BtnStartServer"));
	UI()->BtnEditPort->setEnabled(true);
	UI()->LbPortInfo->setText(NoPort);
	UI()->LbIPInfo->setText(NoIP);
	m_Timer->stop();
}

QString PgConfig::GetHostIpAddress()
{

	QString strIpAddress;
	QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
	// ��ȡ��һ����������IPv4��ַ
	int nListSize = ipAddressesList.size();
	for (int i = 0; i < nListSize; ++i)
	{
		if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
			ipAddressesList.at(i).toIPv4Address()) {
			strIpAddress = ipAddressesList.at(i).toString();
			break;
		}
	}
	// ���û���ҵ������Ա���IP��ַΪIP
	if (strIpAddress.isEmpty())
		strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
	return strIpAddress;
}

void PgConfig::OnExit()
{
}


void PgMaintain::OnStartup()
{
	if (!PgConfig::m_serverstatus)
	{
		UI()->BtnExportClient->setEnabled(false);
		UI()->BtnExportResource->setEnabled(false);
		m_resourceModel->clear();
		m_clientModel->clear();
	}
	else
	{
		UI()->BtnExportClient->setEnabled(true);
		UI()->BtnExportResource->setEnabled(true);
		SetTvClient();
		SetTvResource();
	}
}

void PgMaintain::OnExit()
{
}

PgMaintain::PgMaintain(ServerDaemonPages::PageID page, ServerDaemon* parent)
	:ServerDaemonPages(page, parent)
{
	//SetTvClient();
	//SetTvResource();

	connect(UI()->BtnExportClient, SIGNAL(clicked()), this, SLOT(OnBtnExportClientClicked()));
	connect(UI()->BtnExportResource, SIGNAL(clicked()), this, SLOT(OnBtnExportResourceClicked()));
}

void PgMaintain::OnBtnExportClientClicked()
{
	QString filePath = SelectFilePath("*.xlsx", _CS("K4551_TbClient"));
	if (filePath.isEmpty())
		return;
	ExcelExport clientExcel;
	clientExcel.newExcel(filePath);
	int row, col, eRow, eCol;
	for (row = 0; row < m_clientModel->rowCount(); row++)
	{
		for (col = 0; col < m_clientModel->columnCount(); col++)
		{
			eRow = row + 1;
			eCol = col + 1;
			QStandardItem* aItem = m_clientModel->item(row, col);
			clientExcel.setCellValue(eRow, eCol, aItem->text());
		}
	}
	clientExcel.saveExcel(filePath);
}

void PgMaintain::OnBtnExportResourceClicked()
{
	QString filePath = SelectFilePath("*.xlsx", _CS("K4560_TbResource"));
	if (filePath.isEmpty())
		return;
	ExcelExport clientExcel;
	clientExcel.newExcel(filePath);
	int row, col, eRow, eCol;
	for (row = 0; row < m_resourceModel->rowCount(); row++)
	{
		for (col = 0; col < m_resourceModel->columnCount(); col++)
		{
			eRow = row + 1;
			eCol = col + 1;
			QStandardItem* aItem = m_resourceModel->item(row, col);
			clientExcel.setCellValue(eRow, eCol, aItem->text());
		}
	}
	clientExcel.saveExcel(filePath);
}

void PgMaintain::SetTvClient()
{
	//--��ʼ��ģ��
	m_clientModel = new QStandardItemModel(0, ClientColum, this);
	UI()->TbvClient->setModel(m_clientModel);
	UI()->TbvClient->setEditTriggers(QAbstractItemView::NoEditTriggers);

	//--���ñ�ͷ
	QStringList clientHeader;
	clientHeader << _CS("K4552_HvIP") << _CS("K4553_HvAccount") << _CS("K4554_HvLogTime");
	m_clientModel->setHorizontalHeaderLabels(clientHeader);

	//QVSOnlineClients(PgConfig::m_server,m_client);
	LoadFakeClient();

	int clientRowCnt = m_client.size();
	m_clientModel->setRowCount(clientRowCnt);

	//--��ʾ����
	std::list<QVSDTOClient>::iterator cit;
	QVSDTOClient	client;
	QStandardItem* clinetItem;
	int				clientRow = 0;
	for (cit = this->m_client.begin(); cit != this->m_client.end(); cit++, clientRow++)
	{
		client = *cit;
		clinetItem = new QStandardItem(client.ipaddress.c_str());
		m_clientModel->setItem(clientRow, colIP, clinetItem);

		clinetItem = new QStandardItem(client.account.c_str());
		m_clientModel->setItem(clientRow, colAccount, clinetItem);

		clinetItem = new QStandardItem(client.lastlogin.c_str());
		m_clientModel->setItem(clientRow, colLastlogin, clinetItem);
	}

	//--������ʽ
	UI()->TbvClient->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	UI()->TbvClient->setSelectionMode(QAbstractItemView::NoSelection);
	UI()->TbvClient->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	UI()->TbvClient->setFocusPolicy(Qt::NoFocus);
	UI()->TbvClient->setAlternatingRowColors(true);

	UI()->TbvClient->setColumnWidth(0, 130);
	UI()->TbvClient->setColumnWidth(1, 170);
	UI()->TbvClient->horizontalHeader()->setStretchLastSection(true);
}

void PgMaintain::SetTvResource()
{
	m_resourceModel = new QStandardItemModel(0, ResourceColum, this);
	UI()->TbvResource->setModel(m_resourceModel);
	UI()->TbvResource->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QStringList headerList;
	headerList << _CS("K4561_HvResource") << _CS("K4562_HvUsed") << _CS("K4563_HvTotalResource");
	m_resourceModel->setHorizontalHeaderLabels(headerList);

	//QVSCheckResources(PgConfig::m_server,m_resource);
	LoadFakeResource();

	int resourceRowCnt = m_resource.size();
	m_resourceModel->setRowCount(resourceRowCnt);

	std::list<QVSDTOResource>::iterator rit;
	QVSDTOResource	resource;
	QStandardItem*	resourceItem;
	int				resourceRow = 0;
	for (rit = this->m_resource.begin(); rit != this->m_resource.end(); rit++, resourceRow++)
	{
		resource = *rit;
		resourceItem = new QStandardItem(resource.name.c_str());
		m_resourceModel->setItem(resourceRow, 0, resourceItem);

		resourceItem = new QStandardItem(std::to_string(resource.used).c_str());
		m_resourceModel->setItem(resourceRow, 1, resourceItem);

		resourceItem = new QStandardItem(std::to_string(resource.available).c_str());
		m_resourceModel->setItem(resourceRow, 2, resourceItem);
	}

	UI()->TbvResource->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	UI()->TbvResource->setSelectionMode(QAbstractItemView::NoSelection);
	UI()->TbvResource->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	UI()->TbvResource->setFocusPolicy(Qt::NoFocus);
	UI()->TbvResource->setAlternatingRowColors(true);

	UI()->TbvResource->setColumnWidth(0, 260);
	UI()->TbvResource->setColumnWidth(1, 100);
	UI()->TbvResource->horizontalHeader()->setStretchLastSection(true);
}

void PgMaintain::LoadFakeClient()
{
	QVSDTOClient fakeClientData;
	m_client.clear();
	for (size_t i = 10; i <= 59; i++)
	{
		fakeClientData.ipaddress = "192.168.1." + std::to_string(i);
		fakeClientData.account = "Test Account 100" + std::to_string(i);
		fakeClientData.lastlogin = "2020/2/24 18:00:" + std::to_string(i);
		m_client.push_back(fakeClientData);
	}
}

void PgMaintain::LoadFakeResource()
{
	QVSDTOResource	fakeRespurceData;
	m_resource.clear();
	for (size_t i = 10; i <= 59; i++)
	{
		fakeRespurceData.name = "Equipment Resource NO.0000" + std::to_string(i);
		fakeRespurceData.used = i;
		fakeRespurceData.available = i + 200;
		m_resource.push_back(fakeRespurceData);
	}
}

void PgLog::OnStartup()
{
	if (!PgConfig::m_serverstatus)
	{
		UI()->BtnRefreshLog->setEnabled(false);
		UI()->BtnExportLog->setEnabled(false);
	}
	else
	{
		UI()->BtnRefreshLog->setEnabled(true);
		UI()->BtnExportLog->setEnabled(true);
	}
}

void PgLog::OnExit()
{
}
