#ifndef CONFIG_PAGES_H
#define CONFIG_PAGES_H
#include <QStandardItemModel>
#include <QCompleter>
#include <QPushButton>

#include "qvc/QVCConfiguration.h"

class PageConfigure;
class ConfigPage :public QObject
{
    Q_OBJECT
public:
    enum PageID {
        PgEmail,
        PgFile,
        PgPreview,
        PgVideo,
        PgCommonm,
        PgToolbar,
        PgAlarm,
    };

public:
    ConfigPage(ConfigPage::PageID pg, PageConfigure* parent)
        :m_pageid(pg)
        , m_form(parent) {}
    ~ConfigPage() {}
public:
    virtual void OnStartup() {}
    virtual void OnSave() {};
    virtual void OnRestore() {};
    virtual void OnExit() {};
    ConfigPage::PageID GetPageID();

protected:
    ConfigPage::PageID m_pageid;
    PageConfigure* m_form;
};

class CommonConfig :public ConfigPage {
    Q_OBJECT
public:
    CommonConfig(ConfigPage::PageID page, PageConfigure* parent) :ConfigPage(page, parent) {}
    ~CommonConfig() {}

public:
    void OnStartup();
    void OnSave();
    void OnRestore();
    void OnExit();
    void loadData(QVC::CommonOption&);
    void SaveData(QVC::CommonOption&);
};

class FileConfig :public ConfigPage {
    Q_OBJECT
public:
    FileConfig(ConfigPage::PageID page, PageConfigure* parent) :ConfigPage(page, parent) {}
    ~FileConfig() {}
public:
    void OnStartup();
    void OnSave();
    void OnRestore();
    void OnExit();
    void loadData(QVC::FileSaveOption&);
    void SaveData(QVC::FileSaveOption&);

    QString Browse();
public slots:
    void OnVideoPathPbClicked();
    void OnImgPathPbClicked();
};

class PreviewConfig :public ConfigPage {
    Q_OBJECT
public:
    PreviewConfig(ConfigPage::PageID page, PageConfigure* parent) :ConfigPage(page, parent) {}
    ~PreviewConfig() {}
public:
    void OnStartup();
    void OnSave();
    void OnRestore();
    void OnExit();
    void loadData(QVC::PreviewOption&);
    void SaveData(QVC::PreviewOption&);
};

class VideoConfig :public ConfigPage {
    Q_OBJECT
public:
    VideoConfig(ConfigPage::PageID page, PageConfigure* parent) :ConfigPage(page, parent) {}
    ~VideoConfig() {}
public:
    void OnStartup();
    void OnSave();
    void OnRestore();
    void OnExit();
    void loadData(QVC::VideoOption&);
    void SaveData(QVC::VideoOption&);
};

class ToolbarConfig :public ConfigPage {
    Q_OBJECT
public:
    ToolbarConfig(ConfigPage::PageID page, PageConfigure* parent) :ConfigPage(page, parent) {}
    ~ToolbarConfig() {}
public:
    void OnStartup();
    void OnSave();
    void OnRestore();
    void OnExit();
    void loadData(QVC::ToolbarOption&);
    void SaveData(QVC::ToolbarOption&);


};

class AlarmConfig :public ConfigPage {
    Q_OBJECT
public:
    AlarmConfig(ConfigPage::PageID page, PageConfigure* parent) :ConfigPage(page, parent) {}
    ~AlarmConfig() {}
public:
    void OnStartup();
    void OnSave();
    void OnRestore();
    void OnExit();
    void loadData(QVC::AlarmOption&);
    void SaveData(QVC::AlarmOption&);

public slots:
    void ClickTvButton();                           //表格按钮点击
    void OnAddAudioClicked();

private:
    void SetFixedColWidth();                        //固定列宽
    void SetTableStyle();                           //表格样式
    void SetItemButtonStyle(int row, int col);      //设置表格内容页面部分内容的格式
    void SetModel();                                //设置数据模型
    void PlayAudio(QString audioFile);
    QString GetAudioPath();

public:
    enum tvColName { colId, colType, colAudioPath, colEditAudioPath, colSound, colDel }; //alarm表格列名
    QPushButton* tvButton;                          //表格中的控件
    QStandardItemModel* theModel;
    QStandardItem* aItem;
};

class EmailConfig :public ConfigPage {
    Q_OBJECT
public:
    EmailConfig(ConfigPage::PageID page, PageConfigure* parent) :ConfigPage(page, parent), m_email(QVCConfiguration::GetQVCConfig()->GetEmailOption()) {}
    ~EmailConfig() {}
public:
    void OnStartup();
    void OnSave();
    void OnRestore();
    void OnExit();
    void loadData(QVC::EmailOption&);
    void SaveData(QVC::EmailOption&);
public slots:
    void OnEmailChoosed(const QString& email);
    void OnEmailChanged(const QString& str);
    void SetEmailFmt();                         //设置Email页面 补全与校验
    void SwichPortNum();
    void SendTestEmail();

public:
    QStandardItemModel* emailModel; //补全模型
    QCompleter* emailCompleter;     //邮箱提示
    QVC::EmailOption& m_email;
};

#endif