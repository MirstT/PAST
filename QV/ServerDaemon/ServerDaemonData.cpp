#include "ServerDaemonData.h"
#include <mutex>

QSettings* ServerData::m_setting = new QSettings(CONFIGFILE, QSettings::IniFormat);

ServerDaemonData* ServerDaemonData::__instance = nullptr;
static std::mutex __mutex;
ServerDaemonData* ServerDaemonData::GetServerDaemonData()
{
	if (!ServerDaemonData::__instance) {
		std::unique_lock<std::mutex> locker(__mutex);

		if (!ServerDaemonData::__instance) {
			ServerDaemonData::__instance = new ServerDaemonData();
			ServerDaemonData::__instance->Syncronize();
		}
	}
	return ServerDaemonData::__instance;
}

ServerDaemonData::ServerDaemonData(void)
{
}

ServerDaemonData::~ServerDaemonData(void)
{
}

void ServerDaemonData::Teardown(void)
{
	delete ServerDaemonData::__instance;
}

PgConfigData& ServerDaemonData::GetConfigData()
{
	return m_config;
}

void ServerDaemonData::SetConfigData(const PgConfigData& c)
{
	m_config = c;
}

PgMaintainData& ServerDaemonData::GetMaintainData()
{
	return m_maintain;
}

void ServerDaemonData::SetMaintainData(const PgMaintainData& c)
{
	m_maintain = c;
}

PgLogData& ServerDaemonData::GetLogData()
{
	return m_log;
}

void ServerDaemonData::SetLogData(const PgLogData& c)
{
	m_log = c;
}


bool ServerDaemonData::Syncronize()
{
	m_config.Load();
	m_maintain.Load();
	m_log.Load();
	return true;
}

bool ServerDaemonData::Serialize()
{
	m_config.Save();
	m_maintain.Save();
	m_log.Save();
	return true;
}

bool PgConfigData::Save()
{
	m_setting->beginGroup("PgConfigData");
	m_setting->setValue("port", this->port);
	m_setting->setValue("runstartup", this->runstartup);
	m_setting->endGroup();
	return true;
}

#define DefaultPort 8088

bool PgConfigData::Load(bool loaddefault)
{
	QString begGroup = "PgConfigData";
	if (loaddefault)
	{
		begGroup = "DefaultPgConfigData";
	}
	m_setting->beginGroup(begGroup);
	this->port = m_setting->value("port", DefaultPort).toUInt();
	this->runstartup = m_setting->value("runstartup", false).toBool();
	m_setting->endGroup();
	return true;
}

bool PgMaintainData::Save()
{
	return true;
}

bool PgMaintainData::Load(bool loaddefault)
{
	return true;
}

bool PgLogData::Save()
{
	return true;
}

bool PgLogData::Load(bool loaddefault)
{
	return true;
}

