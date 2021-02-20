#include "QSuperPassword.h"
#include "Login.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	QSuperPassword w;
	Login l;

	if(Login::VerifyOemid(Login::m_setting->value("key").toString()))
	{

		w.show();
		return a.exec();
		
	}
	else
	{
		if (l.exec() == QDialog::Accepted)
		{
			w.show();
			return a.exec();
		}
	}
}
