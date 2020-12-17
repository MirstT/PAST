#ifndef PAGECONFIGURE_H
#define PAGECONFIGURE_H

#include "qvc/QVCConfiguration.h"
#include "ui_pageconfigure.h"
#include "infra/pagebase.h"

namespace Ui {
    class PageConfigure;
}

class ConfigPage;

class PageConfigure:public QWidget
{
    Q_OBJECT
public:
    PageConfigure(QWidget* parent = nullptr);
    ~PageConfigure();
    void loadStyleSheet(const QString& styleSheetFile);                 //加载样式表

public:
    int GetPageIndex() { return m_pageid; }
    ConfigPage* GetCurrentPage();
    virtual void OnStartup();
    virtual void OnExit();
    Ui::PageConfigure* GetUI() { return ui; }

protected:
    virtual void hideEvent(QHideEvent* event);

public slots:
    virtual void OnSave();
    virtual void OnRestore();
    void OnSwitchPage(int index);

public:
    Ui::PageConfigure* ui;
    std::map<int, ConfigPage*> m_pages;
    int m_pageid = 0;
};



#endif // PAGECONFIGURE_H