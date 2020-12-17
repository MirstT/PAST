#include "pages.h"
#include "qvc/QVCConfiguration.h"
#include "qvc/systemconfig/pageconfigure.h"
#include "Csmtp.h"
#include "infra/notifywindow.h"

#include <QListView>
#include <QDir>
#include <QFileDialog>
#include <QSound>
#include <QItemDelegate>
#include <utility\trtext.h>


#define ColumnNum			6
#define DefaultAlarmNum		8
#define EditableAlarmColum  3

#define UI() this->m_form->GetUI()

ConfigPage::PageID ConfigPage::GetPageID()
{
	return m_pageid;
}

void CommonConfig::OnStartup()
{
	QVC::CommonOption& m_comm = QVCConfiguration::GetQVCConfig()->GetCommonOption();
	loadData(m_comm);

	UI()->keeplogtime->setView(new  QListView());									//应用combo box新样式
}

void CommonConfig::OnSave()
{
	QVC::CommonOption& m_comm = QVCConfiguration::GetQVCConfig()->GetCommonOption();
	SaveData(m_comm);
}

void CommonConfig::OnRestore()
{
	QVC::CommonOption& m_comm = QVCConfiguration::GetQVCConfig()->GetDefaultCommonOption();
	loadData(m_comm);
}

void CommonConfig::OnExit()
{
	QVC::CommonOption compare;
	QVC::CommonOption m_comm = QVCConfiguration::GetQVCConfig()->GetCommonOption();

	SaveData(compare);

	bool flag;
	flag = (m_comm.keeplogtime != compare.keeplogtime ? true :
		(m_comm.restorelast != compare.restorelast ? true :
		(m_comm.runstartup != compare.runstartup ? true :
			(m_comm.openfullscreen != compare.openfullscreen ? true : false))));

	if (flag)
	{
		INFRA::NotifierManager::instance()->notify("Unsaved", "CommonConfig changes lost", INFRA::NotifyWanrning);
	}
}

void CommonConfig::loadData(QVC::CommonOption& m_comm)
{
	UI()->keeplogtime->setCurrentIndex(m_comm.keeplogtime - 1);							//起步OneDay的值为1，需要置为0；
	UI()->restorelast->setCheckState(m_comm.restorelast ? Qt::Checked : Qt::Unchecked);
	UI()->runstartup->setCheckState(m_comm.runstartup ? Qt::Checked : Qt::Unchecked);
	UI()->openfullscreen->setCheckState(m_comm.openfullscreen ? Qt::Checked : Qt::Unchecked);
}

void CommonConfig::SaveData(QVC::CommonOption& m_comm)
{
	m_comm.keeplogtime = (UI()->keeplogtime->currentIndex() == QVC::OneDay - 1 ? QVC::OneDay :
		(UI()->keeplogtime->currentIndex() == QVC::OneWeek - 1 ? QVC::OneWeek :
		(UI()->keeplogtime->currentIndex() == QVC::HalfMonth - 1 ? QVC::HalfMonth :
			(UI()->keeplogtime->currentIndex() == QVC::OneMonth - 1 ? QVC::OneMonth :
			(UI()->keeplogtime->currentIndex() == QVC::TwoMonth - 1 ? QVC::TwoMonth :
				(UI()->keeplogtime->currentIndex() == QVC::ThreeMonth - 1 ? QVC::ThreeMonth : QVC::SixMonth))))));
	m_comm.restorelast = UI()->restorelast->isChecked();
	m_comm.runstartup = UI()->runstartup->isChecked();
	m_comm.openfullscreen = UI()->openfullscreen->isChecked();
}

void FileConfig::OnStartup()
{
	QVC::FileSaveOption& m_file = QVCConfiguration::GetQVCConfig()->GetFileOption();
	loadData(m_file);

	UI()->videoreg->setView(new  QListView());													//应用combo box新样式
	UI()->packfmt->setView(new  QListView());
	UI()->imgreg->setView(new  QListView());

	connect(UI()->imgpath, SIGNAL(SignalClicked()), this, SLOT(OnImgPathPbClicked()), Qt::UniqueConnection);			//重写lineedit双击事件
	connect(UI()->videopath, SIGNAL(SignalClicked()), this, SLOT(OnVideoPathPbClicked()), Qt::UniqueConnection);
	connect(UI()->videopathPb, SIGNAL(clicked()), this, SLOT(OnVideoPathPbClicked()), Qt::UniqueConnection);
	connect(UI()->imgpathPb, SIGNAL(clicked()), this, SLOT(OnImgPathPbClicked()), Qt::UniqueConnection);
}

void FileConfig::OnSave()
{
	QVC::FileSaveOption& m_file = QVCConfiguration::GetQVCConfig()->GetFileOption();
	SaveData(m_file);
}

#define VIDEOFILE       QCoreApplication::applicationDirPath() + "/Video"
#define IMGFILE         QCoreApplication::applicationDirPath() + "/Picture"
void FileConfig::OnRestore()
{
	QVC::FileSaveOption& m_file = QVCConfiguration::GetQVCConfig()->GetDefaultFileOption();
	loadData(m_file);
}

void FileConfig::OnExit()
{
	QVC::FileSaveOption compare;
	QVC::FileSaveOption m_file = QVCConfiguration::GetQVCConfig()->GetFileOption();

	SaveData(compare);

	bool flag;
	flag = (m_file.videopath != compare.videopath ? true :
			(m_file.imgpath != compare.imgpath ? true : 
			(m_file.videoreg != compare.videoreg ? true :
			(m_file.packfmt != compare.packfmt ? true :
			(m_file.imgreg != compare.imgreg ? true : false)))));

	if (flag)
	{
		INFRA::NotifierManager::instance()->notify("Unsaved", "FileConfig changes lost", INFRA::NotifyWanrning);
	}
}

void FileConfig::loadData(QVC::FileSaveOption& m_file)
{
	UI()->videopath->setText(m_file.videopath.c_str());
	UI()->videoreg->setCurrentText(m_file.videoreg.c_str());
	UI()->packfmt->setCurrentText(m_file.packfmt.c_str());
	UI()->imgpath->setText(m_file.imgpath.c_str());
	UI()->imgreg->setCurrentText(m_file.imgreg.c_str());
}

void FileConfig::SaveData(QVC::FileSaveOption& m_file)
{
	m_file.videopath = UI()->videopath->text().toStdString();
	m_file.videoreg = UI()->videoreg->currentText().toStdString();
	m_file.packfmt = UI()->packfmt->currentText().toStdString();
	m_file.imgpath = UI()->imgpath->text().toStdString();
	m_file.imgreg = UI()->imgreg->currentText().toStdString();
}

QString FileConfig::Browse()
{
	QString directory =
		QDir::toNativeSeparators(QFileDialog::getExistingDirectory(m_form, tr("Select File Storage Path"), QDir::currentPath()));
	return directory;
}

void FileConfig::OnVideoPathPbClicked()
{
	QString directory = Browse();
	if (!directory.isEmpty())
		UI()->videopath->setText(directory);
}

void FileConfig::OnImgPathPbClicked()
{
	QString directory = Browse();
	if (!directory.isEmpty())
		UI()->imgpath->setText(directory);
}

void PreviewConfig::OnStartup()
{
	QVC::PreviewOption& m_preview = QVCConfiguration::GetQVCConfig()->GetPreviewOption();
	loadData(m_preview);

	UI()->picfmt->setView(new  QListView());										//应用combo box新样式
	UI()->mergerate->setView(new  QListView());
	UI()->wheresearch->setView(new  QListView());
	UI()->priorplay->setView(new  QListView());
}

void PreviewConfig::OnSave()
{
	QVC::PreviewOption& m_preview = QVCConfiguration::GetQVCConfig()->GetPreviewOption();
	SaveData(m_preview);
}

void PreviewConfig::OnRestore()
{
	QVC::PreviewOption& m_preview = QVCConfiguration::GetQVCConfig()->GetDefaultPreviewOption();
	loadData(m_preview);
}

void PreviewConfig::OnExit()
{
	QVC::PreviewOption compare;
	QVC::PreviewOption m_preview = QVCConfiguration::GetQVCConfig()->GetPreviewOption();

	SaveData(compare);

	bool flag;
	flag = (m_preview.picfmt != compare.picfmt ? true :
		(m_preview.mergerate != compare.mergerate ? true :
		(m_preview.wheresearch != compare.wheresearch ? true :
			(m_preview.priorplay != compare.priorplay ? true :
			(m_preview.qvrpriority != compare.qvrpriority ? true :
				(m_preview.offpreview != compare.offpreview ? true :
				(m_preview.smartrecord != compare.smartrecord ? true : false)))))));

	if (flag)
	{
		INFRA::NotifierManager::instance()->notify("Unsaved", "PreviewConfig changes lost", INFRA::NotifyWanrning);
	}
}

void PreviewConfig::loadData(QVC::PreviewOption& m_preview)
{
	UI()->picfmt->setCurrentIndex(m_preview.picfmt);
	UI()->mergerate->setCurrentIndex(m_preview.mergerate);
	UI()->wheresearch->setCurrentIndex(m_preview.wheresearch);
	UI()->priorplay->setCurrentIndex(m_preview.priorplay == QVC::OneSecond ? 0 :	//枚举值不连续，需自己赋值index
		(m_preview.priorplay == QVC::FiveSeconds ? 1 :
		(m_preview.priorplay == QVC::TenSeconds ? 2 :
			(m_preview.priorplay == QVC::HalfMinute ? 3 :
			(m_preview.priorplay == QVC::OneMinite ? 4 :
				(m_preview.priorplay == QVC::NintySeconds ? 5 :
				(m_preview.priorplay == QVC::HalfHour ? 6 : 7)))))));
	UI()->qvrpriority->setCheckState(m_preview.qvrpriority ? Qt::Checked : Qt::Unchecked);
	UI()->offpreview->setCheckState(m_preview.offpreview ? Qt::Checked : Qt::Unchecked);
	UI()->smartrecord->setCheckState(m_preview.smartrecord ? Qt::Checked : Qt::Unchecked);
}

void PreviewConfig::SaveData(QVC::PreviewOption& m_preview)
{
	m_preview.picfmt = (UI()->picfmt->currentIndex() == QVC::JPEG ? QVC::JPEG :
		(UI()->picfmt->currentIndex() == QVC::PNG ? QVC::PNG : QVC::BMP));
	m_preview.mergerate = (UI()->mergerate->currentIndex() == QVC::MergeNIL ? QVC::MergeNIL :
		(UI()->mergerate->currentIndex() == QVC::MergeFirst ? QVC::MergeFirst : QVC::MergeLast));
	m_preview.wheresearch = (UI()->wheresearch->currentIndex() == QVC::VCLOUD ? QVC::VCLOUD : QVC::VQVR);
	m_preview.priorplay = (UI()->priorplay->currentIndex() == 0 ? QVC::OneSecond :
		(UI()->priorplay->currentIndex() == 1 ? QVC::FiveSeconds :
		(UI()->priorplay->currentIndex() == 2 ? QVC::TenSeconds :
			(UI()->priorplay->currentIndex() == 3 ? QVC::HalfMinute :
			(UI()->priorplay->currentIndex() == 4 ? QVC::OneMinite :
				(UI()->priorplay->currentIndex() == 5 ? QVC::NintySeconds :
				(UI()->priorplay->currentIndex() == 6 ? QVC::HalfHour : QVC::OneHour)))))));
	m_preview.qvrpriority = UI()->qvrpriority->isChecked();
	m_preview.offpreview = UI()->offpreview->isChecked();
	m_preview.smartrecord = UI()->smartrecord->isChecked();
}


#define DefaultFramerate    30
#define MinFramerate        1
#define MaxFramerate        144
void VideoConfig::OnStartup()
{
	QVC::VideoOption& m_video = QVCConfiguration::GetQVCConfig()->GetVideoOption();
	loadData(m_video);

	UI()->framerate->setRange(MinFramerate, MaxFramerate);
	UI()->videoratio->setView(new  QListView());										//应用combo box新样式
	UI()->quality->setView(new  QListView());
}

void VideoConfig::OnSave()
{
	QVC::VideoOption& m_video = QVCConfiguration::GetQVCConfig()->GetVideoOption();
	SaveData(m_video);
}

void VideoConfig::OnRestore()
{
	QVC::VideoOption& m_video = QVCConfiguration::GetQVCConfig()->GetDefaultVideoOption();
	loadData(m_video);
}

void VideoConfig::OnExit()
{
	QVC::VideoOption compare;
	QVC::VideoOption m_video = QVCConfiguration::GetQVCConfig()->GetVideoOption();

	SaveData(compare);

	bool flag;
	flag = (m_video.videoratio != compare.videoratio ? true :
		(m_video.quality != compare.quality ? true :
		(m_video.framerate != compare.framerate ? true :
			(m_video.autostream != compare.autostream ? true :
			(m_video.harddecoder != compare.harddecoder ? true :
				(m_video.smartreg != compare.smartreg ? true :false))))));

	if (flag)
	{
		INFRA::NotifierManager::instance()->notify("Unsaved", "VideoConfig changes lost", INFRA::NotifyWanrning);
	}
}

void VideoConfig::loadData(QVC::VideoOption& m_video)
{
	UI()->videoratio->setCurrentIndex(m_video.videoratio);
	UI()->quality->setCurrentIndex(m_video.quality);
	UI()->framerate->setValue(m_video.framerate);
	UI()->autostream->setCheckState(m_video.autostream ? Qt::Checked : Qt::Unchecked);
	UI()->harddecoder->setCheckState(m_video.harddecoder ? Qt::Checked : Qt::Unchecked);
	UI()->smartreg->setCheckState(m_video.smartreg ? Qt::Checked : Qt::Unchecked);
}

void VideoConfig::SaveData(QVC::VideoOption& m_video)
{
	m_video.videoratio = (UI()->videoratio->currentIndex() == QVC::VR16_9 ? QVC::VR16_9 :
		(UI()->videoratio->currentIndex() == QVC::VR4_3 ? QVC::VR4_3 : QVC::VR1_1));
	m_video.quality = (UI()->quality->currentIndex() == QVC::VSmooth ? QVC::VSmooth :
		(UI()->quality->currentIndex() == QVC::VClear ? QVC::VClear : QVC::VHD));
	m_video.framerate = UI()->framerate->text().toInt();
	m_video.autostream = UI()->autostream->isChecked();
	m_video.harddecoder = UI()->harddecoder->isChecked();
	m_video.smartreg = UI()->smartreg->isChecked();
}

void ToolbarConfig::OnStartup()
{
	QVC::ToolbarOption& m_toolbar = QVCConfiguration::GetQVCConfig()->GetToolBarOption();
	loadData(m_toolbar);

	//暂时隐藏功能label
	UI()->infoPreviewToobar->setVisible(false);
	UI()->infoPlaybackToobar->setVisible(false);

}

void ToolbarConfig::OnSave()
{
	QVC::ToolbarOption& m_toolbar = QVCConfiguration::GetQVCConfig()->GetToolBarOption();
	SaveData(m_toolbar);
}

void ToolbarConfig::OnRestore()
{
	QVC::ToolbarOption& m_toolbar = QVCConfiguration::GetQVCConfig()->GetDefaultToolBarOption();
	loadData(m_toolbar);
}

void ToolbarConfig::OnExit()
{
	QVC::ToolbarOption compare;
	QVC::ToolbarOption m_toolbar = QVCConfiguration::GetQVCConfig()->GetToolBarOption();

	SaveData(compare);

	bool flag;
	flag = (m_toolbar.previewtb != compare.previewtb ? true :
		(m_toolbar.playbacktb != compare.playbacktb ? true :false));

	if (flag)
	{
		INFRA::NotifierManager::instance()->notify("Unsaved", "ToolbarOption changes lost", INFRA::NotifyWanrning);
	}
}

void ToolbarConfig::loadData(QVC::ToolbarOption& m_toolbar)
{
	UI()->showonstartup->setCheckState(m_toolbar.showonstartup ? Qt::Checked : Qt::Unchecked);
	UI()->PPause->setCheckState(std::find(m_toolbar.previewtb.begin(), m_toolbar.previewtb.end(), QVC::TBPause) == m_toolbar.previewtb.end() ? Qt::Unchecked : Qt::Checked);
	UI()->PLocate->setCheckState(std::find(m_toolbar.previewtb.begin(), m_toolbar.previewtb.end(), QVC::TBLocate) == m_toolbar.previewtb.end() ? Qt::Unchecked : Qt::Checked);
	UI()->PSnapshot->setCheckState(std::find(m_toolbar.previewtb.begin(), m_toolbar.previewtb.end(), QVC::TBSnapshot) == m_toolbar.previewtb.end() ? Qt::Unchecked : Qt::Checked);
	UI()->PVideo->setCheckState(std::find(m_toolbar.previewtb.begin(), m_toolbar.previewtb.end(), QVC::TBVideo) == m_toolbar.previewtb.end() ? Qt::Unchecked : Qt::Checked);
	UI()->PTalk->setCheckState(std::find(m_toolbar.previewtb.begin(), m_toolbar.previewtb.end(), QVC::TBTalk) == m_toolbar.previewtb.end() ? Qt::Unchecked : Qt::Checked);
	UI()->PMagnify->setCheckState(std::find(m_toolbar.previewtb.begin(), m_toolbar.previewtb.end(), QVC::TBMagnify) == m_toolbar.previewtb.end() ? Qt::Unchecked : Qt::Checked);
	UI()->PLoop->setCheckState(std::find(m_toolbar.previewtb.begin(), m_toolbar.previewtb.end(), QVC::TBLoop) == m_toolbar.previewtb.end() ? Qt::Unchecked : Qt::Checked);
	UI()->PSettings->setCheckState(std::find(m_toolbar.previewtb.begin(), m_toolbar.previewtb.end(), QVC::TBSettings) == m_toolbar.previewtb.end() ? Qt::Unchecked : Qt::Checked);
	UI()->PRecord->setCheckState(std::find(m_toolbar.previewtb.begin(), m_toolbar.previewtb.end(), QVC::TBRecord) == m_toolbar.previewtb.end() ? Qt::Unchecked : Qt::Checked);
	UI()->TSnapshot->setCheckState(std::find(m_toolbar.playbacktb.begin(), m_toolbar.playbacktb.end(), QVC::TBSnapshot) == m_toolbar.playbacktb.end() ? Qt::Unchecked : Qt::Checked);
	UI()->TVideo->setCheckState(std::find(m_toolbar.playbacktb.begin(), m_toolbar.playbacktb.end(), QVC::TBVideo) == m_toolbar.playbacktb.end() ? Qt::Unchecked : Qt::Checked);
	UI()->TMagnify->setCheckState(std::find(m_toolbar.playbacktb.begin(), m_toolbar.playbacktb.end(), QVC::TBMagnify) == m_toolbar.playbacktb.end() ? Qt::Unchecked : Qt::Checked);
	UI()->TPlayback->setCheckState(std::find(m_toolbar.playbacktb.begin(), m_toolbar.playbacktb.end(), QVC::TBPlayback) == m_toolbar.playbacktb.end() ? Qt::Unchecked : Qt::Checked);
	UI()->TDownload->setCheckState(std::find(m_toolbar.playbacktb.begin(), m_toolbar.playbacktb.end(), QVC::TBDownload) == m_toolbar.playbacktb.end() ? Qt::Unchecked : Qt::Checked);
	UI()->TTag->setCheckState(std::find(m_toolbar.playbacktb.begin(), m_toolbar.playbacktb.end(), QVC::TBTag) == m_toolbar.playbacktb.end() ? Qt::Unchecked : Qt::Checked);
	UI()->TRecord->setCheckState(std::find(m_toolbar.playbacktb.begin(), m_toolbar.playbacktb.end(), QVC::TBRecord) == m_toolbar.playbacktb.end() ? Qt::Unchecked : Qt::Checked);
	m_toolbar.previewtb.clear();
	m_toolbar.playbacktb.clear();
}

void ToolbarConfig::SaveData(QVC::ToolbarOption& m_toolbar)
{
	m_toolbar.showonstartup = UI()->showonstartup->isChecked();
	if (UI()->PPause->isChecked())
	{
		m_toolbar.previewtb.push_back(QVC::TBPause);
	}
	if (UI()->PLocate->isChecked())
	{
		m_toolbar.previewtb.push_back(QVC::TBLocate);
	}
	if (UI()->PSnapshot->isChecked())
	{
		m_toolbar.previewtb.push_back(QVC::TBSnapshot);
	}
	if (UI()->PVideo->isChecked())
	{
		m_toolbar.previewtb.push_back(QVC::TBVideo);
	}
	if (UI()->PTalk->isChecked())
	{
		m_toolbar.previewtb.push_back(QVC::TBTalk);
	}
	if (UI()->PMagnify->isChecked())
	{
		m_toolbar.previewtb.push_back(QVC::TBMagnify);
	}
	if (UI()->PLoop->isChecked())
	{
		m_toolbar.previewtb.push_back(QVC::TBLoop);
	}
	if (UI()->PSettings->isChecked())
	{
		m_toolbar.previewtb.push_back(QVC::TBSettings);
	}
	if (UI()->PRecord->isChecked())
	{
		m_toolbar.previewtb.push_back(QVC::TBRecord);
	}
	if (UI()->TSnapshot->isChecked())
	{
		m_toolbar.playbacktb.push_back(QVC::TBSnapshot);
	}
	if (UI()->TVideo->isChecked())
	{
		m_toolbar.playbacktb.push_back(QVC::TBVideo);
	}
	if (UI()->TMagnify->isChecked())
	{
		m_toolbar.playbacktb.push_back(QVC::TBMagnify);
	}
	if (UI()->TPlayback->isChecked())
	{
		m_toolbar.playbacktb.push_back(QVC::TBPlayback);
	}
	if (UI()->TDownload->isChecked())
	{
		m_toolbar.playbacktb.push_back(QVC::TBDownload);
	}
	if (UI()->TTag->isChecked())
	{
		m_toolbar.playbacktb.push_back(QVC::TBTag);
	}
	if (UI()->TRecord->isChecked())
	{
		m_toolbar.playbacktb.push_back(QVC::TBRecord);
	}
}


void AlarmConfig::OnStartup()
{

	QVC::AlarmOption& m_alarm = QVCConfiguration::GetQVCConfig()->GetAlarmOption();
	SetModel();				//设置模型
	loadData(m_alarm);		//加载数据

	//样式设计------
	SetTableStyle();
	SetFixedColWidth();

	connect(UI()->addAudio, SIGNAL(clicked()), this, SLOT(OnAddAudioClicked()), Qt::UniqueConnection);
}

void AlarmConfig::OnSave()
{
	QVC::AlarmOption& m_alarm = QVCConfiguration::GetQVCConfig()->GetAlarmOption();
	m_alarm.alarmfile.clear();														//清空alarmfile准备重写
	int row, col;
	QString str;
	for (row = 0; row < theModel->rowCount(); row++)
	{
		str = "";
		for (col = 0; col < EditableAlarmColum; col++)
		{
			aItem = theModel->item(row, col);
			str += aItem->text() + QString::asprintf("\t\t");
		}
		m_alarm.alarmfile.push_back(str.toStdString());
	}
}

void AlarmConfig::OnRestore()
{
	QVC::AlarmOption& m_alarm = QVCConfiguration::GetQVCConfig()->GetDefaultAlarmOption();
	loadData(m_alarm);

	SetFixedColWidth();	//初始化列宽，重置default后，列宽会改变
}

void AlarmConfig::OnExit()
{

	QVC::AlarmOption m_alarm = QVCConfiguration::GetQVCConfig()->GetAlarmOption();
	bool flag = false;

	int rowcnt = m_alarm.alarmfile.size();
	if (rowcnt != theModel->rowCount())
	{
		//行数不等数据一定发生了改变
		flag = true;
	}
	else
	{	//逐个比较原始记录项和表格现有项是否发生变化
		for (int row = 0; row < rowcnt && flag != true; row++)
		{
			QString aLineText = m_alarm.alarmfile[row].c_str();								//获取数据区的一行
			QStringList tmpList = aLineText.split(QRegExp("\\s+"), QString::SkipEmptyParts);//一个或多个空格、TAB等分隔符隔开的字符串， 分解为一个StringList
			for (int col = 0; col < EditableAlarmColum && flag != true; col++)	//TvAlarmInfo 3
			{
				QString item = tmpList.at(col);
				QString rowItem = theModel->item(row, col)->text();
				if (item != rowItem)			
				{
					flag = true;
				}
			}
		}
	}

	if (flag)
	{
		INFRA::NotifierManager::instance()->notify("Unsaved", "AlarmConfig changes lost", INFRA::NotifyWanrning);
	}
}

void AlarmConfig::loadData(QVC::AlarmOption& m_alarm)
{
	//设置模型行数------
	int rowcnt = m_alarm.alarmfile.size();
	theModel->setRowCount(rowcnt);									

	//设置表格内容区数据------
	for (int row = 0; row < rowcnt; row++)
	{
		QString aLineText = m_alarm.alarmfile[row].c_str();								//获取数据区的一行
		QStringList tmpList = aLineText.split(QRegExp("\\s+"), QString::SkipEmptyParts);//一个或多个空格、TAB等分隔符隔开的字符串， 分解为一个StringList
		for (int col = 0; col < EditableAlarmColum; col++)	//TvAlarmInfo 3
		{
			aItem = new QStandardItem(tmpList.at(col));
			SetItemButtonStyle(row, col);
			theModel->setItem(row, col, aItem);
		}

		//设置表格控件区------
		for (int col = EditableAlarmColum; col < ColumnNum; col++)
		{
			tvButton = new QPushButton();
			connect(tvButton, SIGNAL(clicked()), this, SLOT(ClickTvButton()));			//触发按钮的槽函数
			tvButton->setProperty("row", row);											//设置属性
			tvButton->setProperty("col", col);
			SetItemButtonStyle(row, col);
			UI()->tvAlarmOption->setIndexWidget(theModel->index(row, col), tvButton);
		}
	}
}

void AlarmConfig::SaveData(QVC::AlarmOption& m_alarm)
{
}

void AlarmConfig::OnAddAudioClicked()
{
	QString audioPath = GetAudioPath();
	if (!audioPath.isEmpty())
	{
		QList<QStandardItem*>   rowList; //容器类
		QString sId;
		aItem = new QStandardItem(sId.setNum(theModel->rowCount() + 1));//colId
		SetItemButtonStyle(DefaultAlarmNum, colId);			//8行以上 coId列
		rowList << aItem;
		aItem = new QStandardItem(QString::fromLocal8Bit("自定义类型"));//colType
		rowList << aItem;
		aItem = new QStandardItem(audioPath);	//colAudioPath
		SetItemButtonStyle(DefaultAlarmNum, colAudioPath);	//8行以上 colAudioPath列
		rowList << aItem;

		theModel->insertRow(theModel->rowCount(), rowList);	//插入一行，需要每个Cell的Item

		for (int col = EditableAlarmColum; col < ColumnNum; col++)
		{
			tvButton = new QPushButton();
			int row = theModel->rowCount() - 1;
			connect(tvButton, SIGNAL(clicked()), this, SLOT(ClickTvButton()));		//触发按钮的槽函数
			tvButton->setProperty("row", row);										//设置属性
			tvButton->setProperty("col", col);
			SetItemButtonStyle(row, col);
			UI()->tvAlarmOption->setIndexWidget(theModel->index(row, col), tvButton);	//插入控件
		}
	}
}

void AlarmConfig::ClickTvButton()	//表格按钮点击
{
	QPushButton* btn = (QPushButton*)sender();  //产生事件的对象
	int row = btn->property("row").toInt();		//取得按钮的行号属性
	int col = btn->property("col").toInt();		//取得按钮的列号属性
	if (col == colEditAudioPath)	//----修改路径 colEditAudioPath 3 ----------
	{
		QString audioPath = GetAudioPath();
		if (!audioPath.isEmpty())
		{
			QStandardItem* audio = new QStandardItem(audioPath);
			theModel->setItem(row, colAudioPath, audio);
		}
	}
	else if (col == colSound)		//----播放音频 colSound 4 ----------
	{
		PlayAudio(theModel->item(row, colAudioPath)->text());    //传入音频文件播放 colAudioPath 2
	}
	else
	{								//----删除一行 colDel 5 ----------
		theModel->removeRow(row);

		for (int resetRow = DefaultAlarmNum; resetRow < theModel->rowCount(); resetRow++)//对前八行以外的行的行号和按钮属性重排
		{
			QString sId;
			sId.setNum(resetRow + 1);				//序号
			aItem = new QStandardItem(sId);
			aItem->setTextAlignment(Qt::AlignCenter);
			SetItemButtonStyle(resetRow, col);
			theModel->setItem(resetRow, 0, aItem); //重设序号
			for (int col = colSound; col <= colDel; col++)    //对colSound列与colDel列的按钮属性重设
			{
				tvButton = new QPushButton();
				connect(tvButton, SIGNAL(clicked()), this, SLOT(ClickTvButton()));	//触发按钮的槽函数
				tvButton->setProperty("row", resetRow);								//设置重排后的行号
				tvButton->setProperty("col", col);									//设置重排后的列号
				SetItemButtonStyle(resetRow, col);
				UI()->tvAlarmOption->setIndexWidget(theModel->index(resetRow, col), tvButton);
			}
		}
	}
}

void AlarmConfig::PlayAudio(QString audioFile)
{
	//播放音频文件
	QSound::play(audioFile);
}

QString AlarmConfig::GetAudioPath()
{
	QString audioPath =
		QDir::toNativeSeparators(QFileDialog::getOpenFileName(m_form, tr("Select Audio File"), QDir::currentPath(), tr("Audio (*.mp3 *.wma *.rm *.wav *.midi)")));
	return audioPath;
}

void AlarmConfig::SetFixedColWidth()
{
	UI()->tvAlarmOption->setColumnWidth(colId, 75);
	UI()->tvAlarmOption->setColumnWidth(colType, 160);
	UI()->tvAlarmOption->setColumnWidth(colAudioPath, 350);
	UI()->tvAlarmOption->setColumnWidth(colEditAudioPath, 40);
	UI()->tvAlarmOption->setColumnWidth(colSound, 40);
	UI()->tvAlarmOption->horizontalHeader()->setStretchLastSection(true);			//设置最后一列colDel刚好填充完毕
}

void AlarmConfig::SetTableStyle()
{
	UI()->tvAlarmOption->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);			//关闭水平滚动条
	UI()->tvAlarmOption->setSelectionMode(QAbstractItemView::NoSelection);				//不可进行列选中
	UI()->tvAlarmOption->verticalHeader()->setHidden(true);								//隐藏列头
	UI()->tvAlarmOption->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);	//设置列宽不可改变；
	UI()->tvAlarmOption->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);		//左对齐
	UI()->tvAlarmOption->verticalHeader()->setDefaultSectionSize(35);					//设置默认行高
	UI()->tvAlarmOption->setFocusPolicy(Qt::NoFocus);									//去除选中虚线框
	UI()->tvAlarmOption->setShowGrid(false);											//隐藏表格线
	UI()->tvAlarmOption->setAlternatingRowColors(true);									//激活奇偶颜色分区
}

void AlarmConfig::SetItemButtonStyle(int row, int col)
{
	if (col == colId || col == colAudioPath || (col == colType && row < DefaultAlarmNum))
	{
		aItem->setFlags(aItem->flags() & (~Qt::ItemIsEditable));	//设置不可编辑的表格部件
	}
	if (col == colId)
	{
		aItem->setTextAlignment(Qt::AlignCenter);
	}
	else if (col == colDel)
	{
		tvButton->setFixedSize(29, 32);								//设置最后一列的可触控范围大小
		if (row < DefaultAlarmNum)
		{
			tvButton->setDisabled(true);
		}

	}
}

void AlarmConfig::SetModel()
{	
	//数据导入----
	theModel = new QStandardItemModel(2, ColumnNum, this);			//数据模型
	UI()->tvAlarmOption->setModel(theModel);						//设置数据模型

	//设置表格表头区数据------
	QStringList headerList;
	headerList << _CS("K2010_HvNo") << _CS("K2211_HvType") << _CS("K2212_HvAudioFile") << QString::fromLocal8Bit("") << _CS("K2213_HvOperattion") << QString::fromLocal8Bit("");
	theModel->setHorizontalHeaderLabels(headerList);
}

void EmailConfig::OnStartup()
{
	loadData(m_email);
	SetEmailFmt();
}

void EmailConfig::OnSave()
{
	SaveData(m_email);
}

void EmailConfig::OnRestore()
{
	m_email = QVCConfiguration::GetQVCConfig()->GetDefaultEmailOption();
	loadData(m_email);
}

void EmailConfig::OnExit()
{
	QVC::EmailOption compare;

	SaveData(compare);

	bool flag;
	flag = (m_email.smtpaddr != compare.smtpaddr ? true :
		(m_email.encrypt != compare.encrypt ? true :
		(m_email.port[m_email.encrypt] != compare.port[compare.encrypt] ? true :
			(m_email.sender != compare.sender ? true :
			(m_email.user != compare.user ? true :
				(m_email.password != compare.password ? true :
				(m_email.subject != compare.subject ? true : 
					(m_email.receiver[0] != compare.receiver[0] ? true :
					(m_email.receiver[1] != compare.receiver[1] ? true :
						(m_email.receiver[2] != compare.receiver[2] ? true : false))))))))));

	if (flag)
	{
		INFRA::NotifierManager::instance()->notify("Unsaved", "EmailConfig changes lost", INFRA::NotifyWanrning);
	}
}

void EmailConfig::loadData(QVC::EmailOption& m_email)
{
	UI()->smtpAddr->setText(m_email.smtpaddr.c_str());
	if (m_email.encrypt == QVC::SSL)
		UI()->ssl->setChecked(true);
	else if (m_email.encrypt == QVC::STARTTLS)
		UI()->smartTLS->setChecked(true);
	else
		UI()->noEncrypt->setChecked(true);
	UI()->port->setValue(m_email.port[m_email.encrypt]);
	UI()->sender->setText(m_email.sender.c_str());
	UI()->user->setText(m_email.user.c_str());
	UI()->password->setText(m_email.password.c_str());
	UI()->subject->setText(m_email.subject.c_str());
	UI()->receiver1->setText(m_email.receiver[0].c_str());
	UI()->receiver2->setText(m_email.receiver[1].c_str());
	UI()->receiver3->setText(m_email.receiver[2].c_str());
}

void EmailConfig::SaveData(QVC::EmailOption& m_email)
{
	m_email.smtpaddr = UI()->smtpAddr->text().toStdString();
	m_email.encrypt = UI()->noEncrypt->isChecked() ? QVC::NoEncryption :
		(UI()->ssl->isChecked() ? QVC::SSL : QVC::STARTTLS);
	m_email.port[m_email.encrypt] = UI()->port->text().toUShort();
	m_email.sender = UI()->sender->text().toStdString();
	m_email.user = UI()->user->text().toStdString();
	m_email.password = UI()->password->text().toStdString();
	m_email.subject = UI()->subject->text().toStdString();
	m_email.receiver[0] = UI()->receiver1->text().toStdString();
	m_email.receiver[1] = UI()->receiver2->text().toStdString();
	m_email.receiver[2] = UI()->receiver3->text().toStdString();
}

void EmailConfig::OnEmailChoosed(const QString& email)
{
	UI()->sender->clear();													// 清除已存在的文本更新内容
	UI()->sender->setText(email);
}

void EmailConfig::OnEmailChanged(const QString& str)
{
	if (str.contains("@"))													// 如果已经输入了@符号，停止补全。因为到了这一步，再补全意义也不大
	{
		return;
	}
	QStringList strlist;
	strlist << "@163.com" << "@qq.com" << "@gmail.com" << "@hotmail.com" << "@126.com" << "foxmail.com";

	emailModel->removeRows(0, emailModel->rowCount());						// 先清楚已经存在的数据，不然的话每次文本变更都会插入数据，最后出现重复数据
	for (int i = 0; i < strlist.size(); ++i)
	{
		emailModel->insertRow(0);
		emailModel->setData(emailModel->index(0, 0), str + strlist.at(i));
	}
}

class ComboBoxDelegate : public QItemDelegate
{
public:
	explicit ComboBoxDelegate(QObject* parent = nullptr) : QItemDelegate(parent) {}
	~ComboBoxDelegate() = default;

	QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const override
	{
		QSize size = QItemDelegate::sizeHint(option, index);
		size.setHeight(qMax(30, size.height()));

		return size;
	}
};

void EmailConfig::SetEmailFmt()
{
	UI()->port->setRange(1, 65535);

	QRegExp emailRx("^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\\.[a-zA-Z0-9_-]+)+$");	//邮箱匹配
	QRegExp smtpRx("^[a-zA-Z0-9]+(\\.[a-zA-Z0-9]+)+$");						//smtp匹配
	QRegExp userRx("^[0-9A-Za-z!@#$%&=+?*_-]{16}$");						//用户名与密码匹配
	QRegExpValidator* emailVal = new QRegExpValidator(emailRx, this);
	QRegExpValidator* smtpVal = new QRegExpValidator(smtpRx, this);
	QRegExpValidator* userVal = new QRegExpValidator(userRx, this);
	UI()->sender->setValidator(emailVal);									//启用校验
	UI()->receiver1->setValidator(emailVal);
	UI()->receiver2->setValidator(emailVal);
	UI()->receiver3->setValidator(emailVal);
	UI()->smtpAddr->setValidator(smtpVal);
	UI()->user->setValidator(userVal);
	UI()->password->setValidator(userVal);

	emailModel = new QStandardItemModel(0, 1, this);						//设置邮箱自动补全
	emailCompleter = new QCompleter(emailModel, this);

	emailCompleter->popup()->setStyleSheet("background-color: #232323;\
                                        color: #ffffff;\
                                        border: 1px solid #434343;\
										selection-background-color:#434343");
	QAbstractItemView* view = emailCompleter->popup();						//设置自动补全的Item行高
	view->setItemDelegate(new ComboBoxDelegate());

	UI()->sender->setCompleter(emailCompleter);
	UI()->receiver1->setCompleter(emailCompleter);
	UI()->receiver2->setCompleter(emailCompleter);
	UI()->receiver3->setCompleter(emailCompleter);
	UI()->password->setEchoMode(QLineEdit::PasswordEchoOnEdit);				//密码隐藏

	connect(emailModel, SIGNAL(activated(const QString&)), this, SLOT(OnEmailChoosed(const QString&)));
	connect(UI()->sender, SIGNAL(textChanged(const QString&)), this, SLOT(OnEmailChanged(const QString&)));
	connect(UI()->receiver1, SIGNAL(textChanged(const QString&)), this, SLOT(OnEmailChanged(const QString&)));
	connect(UI()->receiver2, SIGNAL(textChanged(const QString&)), this, SLOT(OnEmailChanged(const QString&)));
	connect(UI()->receiver3, SIGNAL(textChanged(const QString&)), this, SLOT(nEmailChanged(const QString&)));

	connect(UI()->noEncrypt, SIGNAL(toggled(bool)), this, SLOT(SwichPortNum()));
	connect(UI()->ssl, SIGNAL(toggled(bool)), this, SLOT(SwichPortNum()));
	connect(UI()->smartTLS, SIGNAL(toggled(bool)), this, SLOT(SwichPortNum()));

	connect(UI()->btnSendTestEmail, SIGNAL(clicked()), this, SLOT(SendTestEmail()), Qt::UniqueConnection);
}

void EmailConfig::SwichPortNum()
{
	QVC::EmailOption temp_email;
	temp_email.encrypt = UI()->noEncrypt->isChecked() ? QVC::NoEncryption :
		(UI()->ssl->isChecked() ? QVC::SSL : QVC::STARTTLS);
	UI()->port->setValue(m_email.port[temp_email.encrypt]);
}

void EmailConfig::SendTestEmail()
{
	CSmtp* testEmail = new CSmtp();
	testEmail->SetSrvDomain(UI()->smtpAddr->text().toStdString());
	testEmail->SetPortt(25);
	testEmail->SetUserName(UI()->sender->text().toStdString());
	testEmail->SetPass(UI()->password->text().toStdString());
	testEmail->SetTargetEmail(UI()->receiver1->text().toStdString());
	testEmail->SetEmailTitle(UI()->subject->text().toStdString());
	std::string str = "this is a test email! ";
	testEmail->SetContent(str);

	int emailErr = testEmail->SendEmail_Ex();
	if (emailErr == -1)
	{
		INFRA::NotifierManager::instance()->notify("Fail", "Recipient does not exist", INFRA::NotifyWanrning);
	}
	else if (emailErr == 1)
	{
		INFRA::NotifierManager::instance()->notify("Fail", "Network error, sending failed", INFRA::NotifyWanrning);

	}
	else if (emailErr == 2)
	{
		INFRA::NotifierManager::instance()->notify("Fail", "Sender error", INFRA::NotifyWanrning);

	}
	else if (emailErr == 3)
	{
		INFRA::NotifierManager::instance()->notify("Fail", "Password error", INFRA::NotifyWanrning);

	}
	else
	{
		INFRA::NotifierManager::instance()->notify("Success", "Email sent successfully", INFRA::NotifyInfo);

	}
}


