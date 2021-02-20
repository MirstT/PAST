#pragma once
#include "ui_QSuperPassword.h"

namespace Ui {
	class QSuperPassword;
}
class QSuperPassword : public QDialog
{
	Q_OBJECT

public:
	QSuperPassword(QWidget* parent = Q_NULLPTR);
	~QSuperPassword();

	QDate getTimeOnEquipment(QDate);
	bool GetSuperPwd(QDate);
	//void GenerateEncryptOemid();
private	slots:
	void OnBtnGetSuperPwdClicked();
	void OnBtnCancleClicked();

private:
	Ui::QSuperPasswordClass*	ui;
	QString						m_PwdByDate;
};
