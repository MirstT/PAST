#include "MsgBox.h"

#define QSS "res/default/qss/MsgBoxStyleSheet.qss"

MsgBox::MsgBox(QString title,QString text)
    :ui(new Ui::MsgBox)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    this->setAttribute(Qt::WA_QuitOnClose, false);  //退出后不会导致全部窗口退出
    this->loadStyleSheet(QSS);
    CenteredDisplay();                              //在父窗口中间位置显示

    if (!title.isEmpty())
    {
        ui->LbTitle->setText(title);
    }
    if (!text.isEmpty())
    {
        ui->LbText->setText(text);
    }

    connect(ui->BtnOk, SIGNAL(clicked()), this, SLOT(OnBtnOkClicked()));
    connect(ui->BtnCancle, SIGNAL(clicked()), this, SLOT(OnBtnCancleClicked()));
    connect(ui->BtnClose, SIGNAL(clicked()), this, SLOT(OnBtnCloseClicked()));
}

MsgBox::~MsgBox(void)
{
}

void MsgBox::loadStyleSheet(const QString& styleSheetFile)
{
    QFile file(styleSheetFile);
    file.open(QFile::ReadOnly);
    if (file.isOpen())
    {
        QString styleSheet = this->styleSheet();
        styleSheet += QLatin1String(file.readAll());//读取样式表文件
        this->setStyleSheet(styleSheet);			//把文件内容传参
        file.close();
    }
}

void MsgBox::CenteredDisplay()
{
    QWidget* widget = nullptr;
    //获取程序所有的widget
    QWidgetList widgetList = QApplication::allWidgets();
    //获取父窗口指针 此处获取objectName
    for (int i = 0; i < widgetList.length(); i++) {
        if (widgetList.at(i)->objectName() == "ServerDeamonClass") {
            widget = widgetList.at(i);
        }
    }
    if (widget) {
        //获取父窗口geometry
        QRect rect = widget->geometry();
        //计算显示原点
        int x = rect.x() + rect.width() / 2 - this->width() / 2;
        int y = rect.y() + rect.height() / 2 - this->height();
        this->move(x, y);
    }
}

void MsgBox::OnBtnOkClicked()
{
    this->accept();
}

void MsgBox::OnBtnCancleClicked()
{
    this->reject();
}


void MsgBox::OnBtnCloseClicked()
{
    this->close();
}


//--窗体移动
static QPoint mousePosition;

void MsgBox::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        mousePosition = event->globalPos() - this->pos();
    }
}

void MsgBox::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        this->move(event->globalPos() - mousePosition);
    }
}
