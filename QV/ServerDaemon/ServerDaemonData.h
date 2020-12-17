#ifndef SERVERDAEMONDATA_H
#define SERVERDAEMONDATA_H

#include <QSettings>

#define CONFIGFILE	"ServerConfig.ini"
#define DEFAULT		true
class ServerData
{
public:
	ServerData() {};
	~ServerData() {};

	static QSettings* m_setting;
	virtual bool Save() { return true; };
	virtual bool Load() { return true; };
};

struct PgConfigData :public ServerData
{
	virtual bool Save();
	virtual bool Load(bool loaddefault = false);

	ushort	port;				//- �˿ں�
	bool	runstartup;			//- ��������
};

struct PgMaintainData :public ServerData
{
	virtual bool Save();
	virtual bool Load(bool loaddefault = false);
};

struct PgLogData :public ServerData
{
	virtual bool Save();
	virtual bool Load(bool loaddefault = false);
};


class ServerDaemonData
{
public:
	static ServerDaemonData* GetServerDaemonData();
	static void Teardown();
public:
	//QSettings&		GetServerSettings();//- ��ȡ������������ò���

	PgConfigData&	GetConfigData();
	void			SetConfigData(const PgConfigData& c);
	PgMaintainData& GetMaintainData();
	void			SetMaintainData(const PgMaintainData& c);
	PgLogData&		GetLogData();
	void			SetLogData(const PgLogData& c);

public:
	bool Syncronize();					//- �ӷ��������ߴ����ϼ�������
	bool Serialize();					//- �����ݴ洢�����������ߴ���

private:
	PgConfigData	m_config;
	PgMaintainData	m_maintain;
	PgLogData		m_log;

private:
	static ServerDaemonData* __instance;
protected:
	ServerDaemonData();
	~ServerDaemonData();
};

#endif