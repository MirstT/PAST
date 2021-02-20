#include "QSuperPassword.h"
#include "qcustomcalendarwidget.h"
//#include <Qdebug>
#include <QVAuthen.h>
#include <Qmessagebox>
#include "Login.h"

#define Begin			QDate::fromString("2000/01/01","yyyy/MM/dd")
#define End				QDate::fromString("2037/12/31", "yyyy/MM/dd")
#define AESKey			"SuperPasswordOfOemid"
#define PwdLen			10

QSuperPassword::QSuperPassword(QWidget* parent)
	: QDialog(parent),
	ui(new Ui::QSuperPasswordClass)
{
	ui->setupUi(this);
	this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);	//隐藏右上角问号
	//GenerateEncryptOemid();											

	QDateTimeEdit* Clender = ui->leClender;
	QCustomCalendarWidget* calendarWidget = new QCustomCalendarWidget(this);//设置新的自定义日历
	ui->leClender->setDate(QDate::currentDate());
	ui->leClender->setCalendarPopup(true);									// 日历弹出
	ui->leClender->setCalendarWidget(calendarWidget);
	ui->leClender->setMinimumDate(Begin);
	ui->leClender->setMaximumDate(End);
	ui->leClender->setContextMenuPolicy(Qt::NoContextMenu);
	ui->leSuperPwd->setFocusPolicy(Qt::NoFocus);

	calendarWidget->disconnect(SIGNAL(selectionChanged()));
	calendarWidget->disconnect(SIGNAL(clicked(QDate)));
	calendarWidget->setLocale(QLocale::English);

	connect(calendarWidget, &QCustomCalendarWidget::signalSetCalendarTime, [Clender](const QDate& data) {Clender->setDate(data);});
	connect(ui->btnGetSuperPwd, SIGNAL(clicked()), this, SLOT(OnBtnGetSuperPwdClicked()));
	connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(OnBtnCancleClicked()));
}

QSuperPassword::~QSuperPassword(void)
{
	delete ui;
}


//获取设备侧时间
QDate QSuperPassword::getTimeOnEquipment(QDate equTime)
{
	return equTime;
}

bool QSuperPassword::GetSuperPwd(QDate time)
{
	char date[32] = { 0 };
	snprintf(date, sizeof(date), "%04d-%02d-%02d", time.year(), time.month(), time.day());
	uchar hash[HASH_LEN] = { 0 };
	CQVString resultPwd;
	QVHMAC_SHA1((uchar*)Login::m_oemid.toStdString().c_str(), Login::m_oemid.length(), (uchar*)date, strlen(date), hash);
	CQVString::BASE64Encode(resultPwd, (const char*)hash, sizeof(hash));
	for (size_t i = 0; i < PwdLen; i++)
	{
		m_PwdByDate[i] = *(resultPwd.GetBuffer() + i);
	}
	return true;
}

//void QSuperPassword::GenerateEncryptOemid()
//{
//	QString arg(qulonglong a, int fieldWidth = 0, int base = 10, QChar fillChar = QLatin1Char(' '));
//	for (size_t i = 0; i <= customersNum; i++)
//	{
//		QString id = QString::number(i);
//		QString oemid ="C" + QString("%1").arg(id.toInt(), 4, 10, QLatin1Char('0'));
//		CQVString aesEn;
//		CQVString aesBase64En;
//		CQVString aesKey = AESKey;
//		QVAESEncrypt(aesEn, (uchar*)oemid.toStdString().c_str(), oemid.length(), (uchar*)aesKey.GetBuffer());
//		CQVString::BASE64Encode(aesBase64En, (const char*)aesEn.GetBuffer(), aesEn.Length());
//		QString key = CQVString::Clone(aesBase64En);
//		QString fullkey ="key="+key;
//		qDebug() <<fullkey;
//	}
//}

void QSuperPassword::OnBtnGetSuperPwdClicked()
{
	//------获取当前输入时间并验证
	QDate time = ui->leClender->date();
	QDate timeBegin = Begin;
	QDate timeEnd = End;
	int spanB = time.toJulianDay() - timeBegin.toJulianDay();
	int spanE = time.toJulianDay() - timeEnd.toJulianDay();
	if (spanB < 0 || spanE > 0)
	{
		QMessageBox::information(this, tr("Date Error!"), tr("Date Error!\nPlease enter the date on Equipment Side: 2000/01/01 - 2037/12/31"));
		return;
	}

	//------获取超级密码并显示
	if (!GetSuperPwd(time))
	{
		m_PwdByDate = "";
		QMessageBox::warning(NULL, tr("Superpassword error!"), tr("Get superpassword error!\n Please check the input is right!"));
		return;
	}
	ui->leSuperPwd->setText(m_PwdByDate);
}

void QSuperPassword::OnBtnCancleClicked()
{
	ui->leClender->setDateTime(QDateTime::currentDateTime());
	ui->leSuperPwd->clear();
}
