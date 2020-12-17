#include "trtext.h"

namespace INFRA{
	TRTEXT * TRTEXT::s_trText = nullptr;

	TRTEXT::TRTEXT()
	{
		Refresh();
	}

	TRTEXT *TRTEXT::Instance()
	{
		if(s_trText == nullptr)
			s_trText = new TRTEXT;

		return s_trText;
	}

	void TRTEXT::UnInstance()
	{
		if(s_trText)
		{
			delete s_trText;
			s_trText = nullptr;
		}

	}

	QString TRTEXT::GetText(const char * szID)
	{
		QString strString = m_str[QString(szID)];
		if(strString.isEmpty())
		{
			strString = QString(szID);
		}
		return strString;
	}
}
