#pragma once
#include "ui_Login.h"
#include <QSettings>

namespace Ui {
	class Login;
}
class Login : public QDialog
{
	Q_OBJECT

public:
	Login(QWidget* parent = Q_NULLPTR);
	~Login();

	static bool VerifyOemid(QString encryptOemid);
public:
	static QSettings*	m_setting;
	static QString		m_oemid;
private slots:
	void checkLogin();
private:
	Ui::Login* ui;
};