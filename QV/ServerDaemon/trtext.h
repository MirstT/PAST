#ifndef TRTEXT_H
#define TRTEXT_H
#include <QObject>
#include <QString>
#include <QMap>

#define GETTEXT INFRA::TRTEXT::Instance()
#define _CS(id) (INFRA::TRTEXT::Instance()->GetText(id))

namespace INFRA {
	class TRTEXT : public QObject
	{
		Q_OBJECT
	public:
		TRTEXT();
	private:
		static TRTEXT* s_trText;
		QMap<QString, QString> m_str;
	public:
		static TRTEXT* Instance();
		static void UnInstance();

		void Refresh();
		QString GetText(const char* szID);
	};
}

#endif // TRTEXT_H
