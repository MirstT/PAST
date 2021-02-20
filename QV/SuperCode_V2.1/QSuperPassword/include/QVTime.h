#ifndef __QVTIME_H__
#define __QVTIME_H__
#include "QVString.h"
#include "QVList.h"

#if( defined(QVOS_WIN32) | defined(QVOS_WIN64) )
QVBASEAPI int QVAPI gettimeofday(struct timeval* tp, void* tzp);
#else
QVBASEAPI int QVAPI	gettimespec(struct timespec* tsp, uint ms/*ms*/);
#endif

QVBASEAPI int QVAPI QVSleepMS(uint ms);

#define	QVTM_CMP_YEAR	0
#define	QVTM_CMP_MONTH	1
#define	QVTM_CMP_DAY	2
#define	QVTM_CMP_HOUR	3
#define	QVTM_CMP_MIN	4
#define	QVTM_CMP_SEC	5
#define QVTM_CMP_MS		6

#ifndef __SMALL_FILE_TIME_DEFINED__
#define __SMALL_FILE_TIME_DEFINED__
//时间结构
#ifndef _DHTIME
#define _DHTIME
typedef struct _DHTIME
{
    uint second        :6;                    //    秒    1-60
    uint minute        :6;                    //    分    1-60
    uint hour          :5;                    //    时    1-24
    uint day           :5;                    //    日    1-31
    uint month         :4;                    //    月    1-12
    uint year          :6;                    //    年    2000-2063
}DHTIME, *PDHTIME, *pDHTIME;
#endif
#endif


class QVBASEDLL CQVTime : public CQVObject
{
public:	
	CQVTime(DHTIME* t=NULL, uint ms = 0);
	CQVTime(const CQVTime& src);
#ifdef QVPLATFORM_XVRV10
	CQVTime(SYSTEM_TIME* tmc);
#endif
	CQVTime(struct timeval* src);
	CQVTime(struct tm* src);
	CQVTime(bool empty);
	~CQVTime(void){};

    
public:
	void FillCurrentTime(bool utc = false);

	void clone(CQVTime* pQvTime);
	bool SetTime(void);
#ifdef QVPLATFORM_XVRV10
	bool SetTime(SYSTEM_TIME* tmc);
#endif
	bool SetTime(struct timeval* src);
	bool SetTime(const DHTIME* src, uint ms = 0);
	bool SetTime(struct tm* src);
	bool SetTime(time_t tmt);

	bool SetYear(uint year);
	bool SetMonth(uint month);
	bool SetDay(uint day);
	bool SetHour(uint hour);
	bool SetMinute(uint minute);
	bool SetSecond(uint second);
	bool SetMS(ushort ms);

	bool GetTime(DHTIME* dst) const;
#ifdef QVPLATFORM_XVRV10
	bool GetTime(SYSTEM_TIME* dst);
#endif
	bool GetTime(struct tm* dst) const;
	time_t GetTime(void) const;
	uint64 GetTicks() const;
	bool SetTicks(uint ticks);


	uint GetYear(void) const { return m_dht.year+2000;}
	uint GetMonth(void) const { return m_dht.month;}
	uint GetDay(void) const { return m_dht.day;}
	uint GetHour(void) const { return m_dht.hour;}
	uint GetMinute(void) const { return m_dht.minute;}
	uint GetSecond(void) const { return m_dht.second;}
	uint GetMS(void) const { return m_ms;}
	uint GetWeekDay(void) const;

	void	Add(uint ms);
	void	Sub(uint ms);

	bool	IsEmpty(void) const;
	void	Empty(void);

public:
	int		ToString(char* buffer, int size);
	int		ToString(CQVString* str, bool utc = true) const;
	int		ParseISO8601(const char* doc);
	int		BuildISO8601(CQVString* doc);

public:
	int		Compare(const CQVTime& dst, int rule = QVTM_CMP_SEC) const;
	int		Compare(const DHTIME* dst,  int rule = QVTM_CMP_SEC) const;

public:
	static	int		Compare(const DHTIME* src, const DHTIME* dst, int rule = QVTM_CMP_SEC);
	//static	int		ToString(DHTIME* dht, char* buffer, int size);
	static  bool	IsNull(DHTIME* dht);
	static	void	SetNull(DHTIME* dht);
	static	int64	GetTimeSpan(CQVTime* pTime1, CQVTime* pTime2);
	static	uint64 	GetTimeUS(void);
	static	uint64	GetTimeMS(void);
	static	uint64 	GetClockTimeUS(void);
	static	uint64	GetClockTimeMS(void);
	static	void	GetDateTime(DHTIME& tms, bool utc = true);
	static	void	GetDateTime(struct tm& tms, bool utc = true);
	static	int		GetYearDay(uint year, uint month, uint day);
	static	int		GetWeekDay(uint year, uint month, uint day);

public:
	bool operator==(const CQVTime& dst) const;
	bool operator<(const CQVTime& dst) const;
	bool operator<=(const CQVTime& dst) const;
	bool operator>(const CQVTime& dst) const;
	bool operator>=(const CQVTime& dst) const;
	bool operator==(const DHTIME&  dst) const;
	bool operator<(const DHTIME& dst) const;
	bool operator<=(const DHTIME& dst) const;
	bool operator>(const DHTIME& dst) const;
	bool operator>=(const DHTIME& dst) const;

	void operator+=(int sec);
	void operator+=(uint sec);
	void operator-=(int sec);
	void operator-=(uint sec);
	int64	 operator-(CQVTime& dst);
	void operator=(const CQVTime& src){ memcpy(&m_dht, &src.m_dht, sizeof(DHTIME)); m_ms = src.m_ms;}

public:
	virtual void Dump(void);

protected:
	DHTIME	m_dht;
	uint	m_ms;		//毫秒，0~999
#if( defined(QVOS_WIN32) | defined(QVOS_WIN64) )
private:
	static uint64	s_freq;
#endif
};


class QVBASEDLL CQVTimeout : public CQVObject
{
public:
	CQVTimeout(uint timeout = 0/*ms*/);
	virtual ~CQVTimeout(void);

public:
	void Setup(uint timeout/*ms*/);
	void Clear(void){ m_timeout = 0; }
	void Update(uint64 ticks = 0 /*ms*/);
	bool Check(uint64 ticks=0, bool update=false);
	uint GetTimeout(void) const { return m_timeout; };

protected:
	uint64	m_refer;
	uint	m_timeout;
};


///////////////////////////////////////////////////////////////////////////////
//class CQVTimeMaskBIT
//	封装指定时间长度内每秒钟的标志
class QVBASEDLL CQVTimeMaskBIT : public CQVObject
{
public:
	CQVTimeMaskBIT(CQVTime* tms = NULL, uint seconds = 0);
	virtual ~CQVTimeMaskBIT(void);

public:
	int	 Init(CQVTime* tms = NULL, uint seconds = 0);
	int  Clear(void);
	int  Enable(CQVTime& tms, bool enable = TRUE, uint secs = 1);
	int  Enable(uint offset,  bool enable = TRUE, uint secs = 1);
	int  Check(CQVTime& tms,  bool& enable, uint secs = 1);
	int	 Check(uint offset,   bool& enable, uint secs = 1);

	int  GetTimeS(CQVTime& tms) const ;
	int  GetTimeE(CQVTime& tme) const;
	uint GetSeconds(void) const { return m_secs; }
    uint* GetMask(void) const { return m_mask; }

protected:
	CQVTime		m_time;
	uint		m_secs;
	uint*		m_mask;
};

///////////////////////////////////////////////////////////////////////////////
//class CQVTimeMaskValue
class QVBASEDLL CQVTimeMaskValue : public CQVObject
{
public:
	CQVTimeMaskValue(CQVTime* tms = NULL, uint secs = 0);
	virtual ~CQVTimeMaskValue(void);
public:
	int  Init(CQVTime* tms = NULL, uint secs = 0);
	int  Clear(void);

	int  SetValue(uint offset, uint  value);
	int  GetValue(uint offset, uint& value);
	int	 Check(uint offset, BOOL& enable, uint secs = 1);

	int  SetValue(CQVTime& tms, uint  value);
	int  GetValue(CQVTime& tms, uint& value);
	int	 Check(CQVTime& tms, BOOL& enable, uint secs = 1);

	int  GetTimeS(CQVTime& tms) const;
	int  GetTimeE(CQVTime& tme) const;
	int  GetTime(CQVTime& tms, uint offset);
	uint GetSeconds(void) const { return m_secs; };

	int	 GetFirstValue(QVLISTPOS& pos, uint& offset, uint& value);
	int	 GetNextValue( QVLISTPOS& pos, uint& offset, uint& value);

protected:
	typedef struct tag_TMVAL_PAIR
	{
		uint	offset;
		uint	value;
	}TMVAL_PAIR, *PTMVAL_PAIR;
protected:
	CQVTime		m_time;
	uint		m_secs;
	CQVList		m_list;
};

#endif//__QVTIME_H__
