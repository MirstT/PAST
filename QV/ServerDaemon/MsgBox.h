#ifndef MSGBOX_H
#define MSGBOX_H

#include <QMouseEvent>
#include <QDialog>
#include "ui_MsgBox.h"

class MsgBox :public QDialog
{
	Q_OBJECT
public:
	MsgBox(QString title,QString text);
	~MsgBox(void);
public:
	void	loadStyleSheet(const QString& styleSheetFile);
	void	CenteredDisplay();

protected:
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);

public slots:
	void OnBtnOkClicked();
	void OnBtnCancleClicked();
	void OnBtnCloseClicked();

private:
	Ui::MsgBox* ui;
};

#endif
