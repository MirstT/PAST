#include "pageconfigure.h"
#include "ui_pageconfigure.h"
#include "pagebase.h"
#include "pages.h"
#include "infra/notifywindow.h"

#define QSS "res/default/qss/pageConfigStyleSheet.qss"

PageConfigure::PageConfigure(QWidget* parent)
	:QWidget(parent),
	ui(new Ui::PageConfigure)
{
	ui->setupUi(this);
	this->loadStyleSheet(QSS);				
	OnStartup();
}
PageConfigure::~PageConfigure()
{
	delete ui;
}

void PageConfigure::OnStartup()
{
	ui->listWidget->setDragEnabled(false);											//list不可拖动复制
	m_pages = { 
		 { 0,new CommonConfig(ConfigPage::PgCommonm,this) } 
		,{ 1,new FileConfig(ConfigPage::PgFile,this) }
		,{ 2,new PreviewConfig(ConfigPage::PgPreview,this) }
		,{ 3,new VideoConfig(ConfigPage::PgVideo,this) }
		,{ 4,new AlarmConfig(ConfigPage::PgAlarm,this) }
		,{ 5,new ToolbarConfig(ConfigPage::PgToolbar,this) }
		,{ 6,new EmailConfig(ConfigPage::PgEmail,this) }
	};
	QObject::connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(OnSwitchPage(int)));	
	QObject::connect(ui->btnSaveConfig, SIGNAL(clicked()), this, SLOT(OnSave()));
	QObject::connect(ui->btnRestoreDefault, SIGNAL(clicked()), this, SLOT(OnRestore()));
	emit ui->listWidget->currentRowChanged(0);										//默认选中list基本配置 发出信号初始化
}

void PageConfigure::OnSave()
{
	ConfigPage *page = this->GetCurrentPage();
	if (!page) return;
	
	page->OnSave();

	QVCConfiguration* c = QVCConfiguration::GetQVCConfig();
	bool saveAnswer = c->Serialize();
	if (saveAnswer == VMS_OK)
	{
		INFRA::NotifierManager::instance()->notify("Success", "Save successfully", INFRA::NotifyInfo);
	}
	else
	{
		INFRA::NotifierManager::instance()->notify("Fail", "Save failed", INFRA::NotifyWanrning);
	}
}

void PageConfigure::hideEvent(QHideEvent* event)
{
	QWidget::hideEvent(event);
	this->OnExit();
}

void PageConfigure::OnRestore()
{
	ConfigPage* page = this->GetCurrentPage();
	if (!page) return;
	page->OnRestore();
}

void PageConfigure::OnExit()
{
	m_pages[m_pageid]->OnExit();		//子页面退出
	m_pages[m_pageid]->OnStartup();		//子页面重新初始化---为了重置子页面数据
}

ConfigPage* PageConfigure::GetCurrentPage()
{
	int index = this->GetPageIndex();
	if(m_pages.find(index) == m_pages.end())
		return nullptr;
	return m_pages[index];
}

void PageConfigure::OnSwitchPage(int index)
{
	if (m_pageid != index)
	{
		m_pages[m_pageid]->OnExit();	//对上个页面执行退出操作
	}

	m_pageid = index;
	ConfigPage* page = GetCurrentPage();
	if (!page) return;

	page->OnStartup();
	emit ui->pageConfigStackWidget->setCurrentIndex(m_pageid);
}

void PageConfigure::loadStyleSheet(const QString& styleSheetFile)
{
	QFile file(styleSheetFile);
	file.open(QFile::ReadOnly);
	if (file.isOpen())
	{
		QString styleSheet = this->styleSheet();
		styleSheet += QLatin1String(file.readAll());								//读取样式表文件
		this->setStyleSheet(styleSheet);											//把文件内容传参
		file.close();
	}
}
