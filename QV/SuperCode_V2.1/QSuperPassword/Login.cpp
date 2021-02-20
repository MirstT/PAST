#include "Login.h"
#include <QMessageBox>
#include <QVAuthen.h>

#define CONFIGFILE		"config.ini"
#define customersNum	200
#define Key				"SuperPasswordOfOemid"

QSettings* Login::m_setting = new QSettings(CONFIGFILE, QSettings::IniFormat);
QString Login::m_oemid = "";

Login::Login(QWidget* parent)
	: QDialog(parent),
	ui(new Ui::Login)
{
	ui->setupUi(this);
	this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);	//隐藏右上角问号

	connect(ui->loginbtn, SIGNAL(clicked()), this, SLOT(checkLogin()));
	connect(ui->loginbtn, SIGNAL(returnPressed()), this, SLOT(checkLogin()));
}
Login::~Login()
{
	delete ui;
}

void Login::checkLogin()
{
	if (VerifyOemid(ui->oemidinput->text()))
	{
		m_setting->setValue("key",ui->oemidinput->text());
		accept();
	}
	else
	{   
		QMessageBox::warning(this, tr("Input Error!"), tr("Wrong Oemid!\nPlease enter the correct Oemid!"),QMessageBox::Yes);
		ui->oemidinput->clear();
		ui->oemidinput->setFocus();
	}
}

bool Login::VerifyOemid(QString encrypt)
{
	//------解密oemid
	CQVString	decodeOemid;
	CQVString	decryptOemid;
	CQVString	key = Key;
	QString		encryptOemid = encrypt;
	CQVString::BASE64Decode(decodeOemid, (const char*)encryptOemid.toStdString().c_str(), encryptOemid.length());
	QVAESDecrypt(decryptOemid, (uchar*)decodeOemid.GetBuffer(), decodeOemid.Length(), (uchar*)key.GetBuffer());

	//------获取预设的用户oemid C0000-C0200
	std::vector<QString> allOemid;
	for (size_t i = 0; i <= customersNum; i++)
	{
		QString id = QString::number(i);
		QString oemid = "C" + QString("%1").arg(id.toInt(), 4, 10, QLatin1Char('0'));
		allOemid.push_back(oemid);
	}

	//------验证用户oemid(一一比对)
	if (std::count(allOemid.begin(), allOemid.end(), CQVString::Clone(decryptOemid)) != 1)
	{
		return false;
	}
	else
	{
		m_oemid = CQVString::Clone(decryptOemid);
		return true;
	}
}