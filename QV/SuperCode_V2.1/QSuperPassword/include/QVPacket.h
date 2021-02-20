#ifndef __QVPACKET_H__
#define __QVPACKET_H__
#include "QVTime.h"
#include "QVMutex.h"
#include "QVList.h"

#if(defined(QVPLATFORM_XVRV10))
#include "Foundation/Packet.h"
#include "Foundation/pkg_analysis.h"
#else
enum PackSmartFlag
{
	PACK_SMART_FLAG_MD      = 0,
	PACK_SMART_FLAG_COMOBJ  = 1,
	PACK_SMART_FLAG_FACEOBJ = 2,
	PACK_SMART_FLAG_FACEPIC = 3,
	PACK_SMART_FLAG_NUM
};

enum pkg_sour_type
{
	PKG_SOUR_NONE = 0,
	PKG_SOUR_REC1 = 1,
	PKG_SOUR_REC2 = 2,
	PKG_SOUR_Backup = 3,
	PKG_SOUR_BackupRT = 4,
	PKG_SOUR_BellPlayBack = 5,
	PKG_SOUR_BellRealMedia = 6,
	PKG_SOUR_BellRtpClient = 7,
	PKG_SOUR_BellVapConfig = 8,
	PKG_SOUR_Bell_VsConfigInExport = 9,
	PKG_SOUR_ChinaMobile = 10,
	PKG_SOUR_ClientDVR = 11,
	PKG_SOUR_Cmds_DecVSPProcess = 12,
	PKG_SOUR_CRegManager = 13,
	PKG_SOUR_CRTCPPacket = 14,
	PKG_SOUR_CRTPPacket = 15,
	PKG_SOUR_CRtpStreamDec = 16,
	PKG_SOUR_CRtpStreamDecTcp = 17, //目前主要用在音视频，接收tcp协议的RTP包后去除RTP头,组成私有视频帧
	PKG_SOUR_DevAudioIn = 18,
	PKG_SOUR_DevBackup = 19,
	PKG_SOUR_DevCapBuf = 20,
	PKG_SOUR_DevCapture = 21,
	PKG_SOUR_DevExCapture = 22,
	PKG_SOUR_DevHDiskReader = 23,
	PKG_SOUR_DevPlay = 24,
	PKG_SOUR_DHFile = 25,
	PKG_SOUR_DlgSmtpCli = 26,
	PKG_SOUR_FilterHelper = 27,
	PKG_SOUR_FrameGeneral = 28,
	PKG_SOUR_FtpClient = 29,
	PKG_SOUR_FtpUpgrade = 30,
	PKG_SOUR_IVNConfig = 31,
	PKG_SOUR_IVNControl = 32,
	PKG_SOUR_IVNLogState = 33,
	PKG_SOUR_IVnPdu = 34,
	PKG_SOUR_IVNRemoteConfig = 35,
	PKG_SOUR_IVNSysConfig = 36,
	PKG_SOUR_IVNSystemUp = 37,
	PKG_SOUR_IVNUser = 38,
	PKG_SOUR_Listener = 39,
	PKG_SOUR_MegaEyes = 40,
	PKG_SOUR_MegaHead = 41,
	PKG_SOUR_MegaRealPlayV1 = 42,
	PKG_SOUR_MegaRealPlayV2 = 43,
	PKG_SOUR_MegaRecord = 44,
	PKG_SOUR_MultiMediaProc = 45,
	PKG_SOUR_NetCapture = 46,
	PKG_SOUR_NetCli28181 = 47,
	PKG_SOUR_NetCliDss = 48,
	PKG_SOUR_NetCliIts = 49,
	PKG_SOUR_NetCliSimple = 50,
	PKG_SOUR_NetCli_HuangHe = 51,
	PKG_SOUR_NetCli_ZK = 52,
	PKG_SOUR_NetIo = 53,
	PKG_SOUR_NetVSPConfig = 54,
	PKG_SOUR_PageConfigOperate = 55,
	PKG_SOUR_PicThread = 56,
	PKG_SOUR_Preview = 57,
	PKG_SOUR_PuCtrl = 58,
	PKG_SOUR_Record = 59,
	PKG_SOUR_RtcpClient = 60,
	PKG_SOUR_RtpClient = 61,
	PKG_SOUR_RtspMedia = 62, //主要用在音频，存放rtsp接收后重新组成私有协议数据帧
	PKG_SOUR_RtspServerMediaVD = 63,
	PKG_SOUR_RtspSession = 64,
	PKG_SOUR_RtspSrvTest = 65,
	PKG_SOUR_RtspSvrAszeno = 66,
	PKG_SOUR_SHReg = 67,
	PKG_SOUR_SHRegPdu = 68,
	PKG_SOUR_SipUserAgent_Task = 69,
	PKG_SOUR_Support = 70,
	PKG_SOUR_SzYyPdu = 71,
	PKG_SOUR_TestDlg = 72,
	PKG_SOUR_ThreadTest = 73,
	PKG_SOUR_Tlv = 74,
	PKG_SOUR_Upgrader = 75,
	PKG_SOUR_V8 = 76,
	PKG_SOUR_VS300 = 77,
	PKG_SOUR_YY = 78,
	PKG_SOUR_YYReg = 79,
	PKG_SOUR_ZTEAppMediaManager = 80,
	PKG_SOUR_ZTEAppPlayBack = 81,
	PKG_SOUR_ZteRecordPlay = 82,
	PKG_SOUR_ZteRTSPSession = 83,
	PKG_SOUR_ZteUpgrade = 84,
	PKG_SOUR_BellVapVideo = 85,
	PKG_SOUR_Packet = 86,
	PKG_SOUR_COU
};

/////////////////////////////////////////////////////
//Codec Types
#define 	CODEC_NONE 	0		
#define 	CODEC_H264 	1		//H264
#define		CODEC_H265 	2		//H265
#define		CODEC_JPEG 	3		//JPEG
#define 	CODEC_PCMA 	4		//PCMA
#define 	CODEC_PCMU 	5		//PCMU
#define 	CODEC_ADPCM	6		//ADPCM
#define		CODEC_MP3 	7		//MP3
#define		CODEC_AAC 	8		//AAC
#define		CODEC_PCM	9		//PCM
#define     CODEC_SMART 10
#define     CODEC_CURRC 11
#define		CODEC_UYVY	0x21	//YUV422:	U0Y0V0Y1U1Y2V1Y3...
#define		CODEC_YV12	0x22	//YUV420:	
#define		CODEC_RGB	0x23	//RGB:	R0,G0,B0,R1,G1,B1,...
#define		CODEC_ARGB	0X24	//ARGB:	A0,R0,G0,B0,A1,R1,G1,B1,...
#define     CODEC_H264P(_n_) (0x10 + (_n_))     //H264P(0)~H264P(15)
#define     CODEC_H265P(_n_) (0x20 + (_n_))     //H265P(0)~H265P(15)
#define     CODEC_PS     0x30


#define		PACK_TYPE_FRAME_BASE 	0xE0
#define		PACK_TYPE_FRAME_P		0
#define		PACK_TYPE_FRAME_I		1
#define		PACK_TYPE_FRAME_B		2
#define		PACK_TYPE_FRAME_AUDIO	3
#define		PACK_TYPE_FRAME_JPEG	4
#define		PACK_TYPE_FRAME_MOTION	5
#define		PACK_TYPE_FRAME_REC		6
#define		PACK_TYPE_FRAME_SMART	7
#define		PACK_TYPE_FRAME_SMARTEX	8
#define		PACK_TYPE_FRAME_VI		9
#define		PACK_TYPE_FRAME_PB		10
#define		PACK_TYPE_FRAME_NUM		11
#define		PACK_TYPE_FRAME_NULL	0xff
#ifndef tag_FRMHDR
#define tag_FRMHDR
typedef struct tag_FRMHDR
{
	uchar 	prefix[4];		//prefix[0] = 0, prefix[1] = 0, prefix[2] = 1, prefix[3] = 0xe0 + PACK_TYPE_FRAME_XXX
	uint	length;			//帧长度
	DHTIME 	tms;			//到秒的绝对时间
	ushort 	ms;				//毫秒,0~999
	uchar 	codec;			//编解码类型，CODEC_XXX
	union
	{
		uchar   flag;  		//智能帧object类型有无标记 enum PackSmartFlag,最高为用来标记是否有附加数据
		uchar	num;		//智能帧时表示智能对象个数
		uchar 	fps;		//视频帧率,6.2格式
		uchar 	channum;	//音频通道数 
	};
	union
	{
		ushort 	width;		//视频宽度
		ushort 	freq;		//音频采样率
	};
	ushort	height;			//视频高度
}FRAMEHEAD, *PFRAMEHEAD;
#endif
///////////////////////////////////////////////////////////////////
//class CPacket
class CPacketPool;
class QVBASEDLL CPacket : public CQVObject
{	
	friend class CPacketPool;
	friend class CQVListP < CPacket > ;

public:
	uint	AddRef(void);
	uint	Release(void);
	uint	GetSize(void) const { return m_size; }
    uint    GetLength(void) const { return m_len;}
    void    SetLength(uint length) { m_len = length;}
public:
	FRAMEHEAD*	FrameGetHead(void);
	uchar*		FrameGetBuffer(void);
	uint 		FrameGetSize(void);
	uchar*		FrameGetData(void);
	uint 		FrameGetLength(void);
	bool 		FrameIsKey(void);
	bool 		FrameIsVideo(void);
    bool        FrameIsVI(void) const;
    bool        FrameHasVI(void) const;
    uchar       FrameGetPBNum(void) const;
	bool		FrameIsAudio(void);
	bool		FrameIsPicture(void);
	bool		FrameIsSmart(void);
	bool		FrameIsCurrC(void);
	bool		FrameIsH264(void);
	bool		FrameIsH265(void);
	uchar 		FrameGetType(void);
	void 		FrameGetTime(DHTIME* tms, ushort* ms);
	uint64 		FrameGetTimeStamp(void);
	DHTIME*		FrameGetTime(void);
	void		FrameGetTime(CQVTime* tmc);
	ushort 		FrameGetMS(void);
	uchar 		FrameGetCodec(void);
	uchar 		FrameGetObjType(void);
	float 		FrameGetFPS(void);
	ushort		FrameGetWidth(void);
	ushort		FrameGetHeight(void);
	ushort		FrameGetFreq(void);
	uchar		FrameGetChnNum(void);

	void		FrameInit(void);
	void		FrameSetLength(uint len);
	void 		FrameSetType(uchar type);
	void 		FrameSetTime(struct timeval* val);
	void		FrameSetCodec(uchar codec);
	void		FrameSetFPS(float fps);
	void		FrameSetWidth(ushort width);
	void		FrameSetHeight(ushort height);
	void 		FrameSetObjType(uchar type);
	void		FrameSetFreq(ushort freq);
	void		FrameSetTime(DHTIME* tmc, ushort ms);
	void		FrameSetTime(CQVTime& tmc);
	void		FrameSetChannum(uchar num);

	//////////////////////////////////////////////////////////////////////////
	uchar 		FrameGetRecType(void){ uchar* data = (uchar*)&m_data; return data[0];};
	void		FrameSetRecType(uchar type){ uchar* data = (uchar*)&m_data; data[0]=type;};
	uchar 		FrameGetEvent(void) { uchar* data = (uchar*)&m_data; return data[1];};
	void		FrameSetEvent(uchar evt) { uchar* data = (uchar*)&m_data; data[1]=evt;};
	uchar 		FrameGetEventSource(uint id) { uchar* data = (uchar*)&m_data; if( id > 1) id = 1; return data[id+2];}
	void		FrameSetEventSource(uint id, uchar src){ uchar* data = (uchar*)&m_data; if( id > 1) id = 1; data[id+2] = src;};
	//////////////////////////////////////////////////////////////////////////
public:
	uint	SetUserData(uint data){ m_data[0] = data; return m_data[0];}
	void	SetUserData(uint id, uint val) { if( id>=sizeof(m_data)/sizeof(m_data[0])) return; m_data[id] = val;}
    uint    GetUserData(uint id) { if( id >= sizeof(m_data)/sizeof(m_data[0])) return 0;return m_data[id];}
	uint	GetUserData(void){ return m_data[0];}
 	void	SetMagic(size_t magic){ m_magic = magic; };
	size_t	GetMagic(void)const { return m_magic; }

public:
	virtual void Dump(void);

private:
	//CQVMutex	m_mutex;
	uint		m_ref;
	uchar*		m_buffer;
	uint		m_size;
	uint		m_len;
	uint		m_data[4];		//user data
	size_t		m_magic;
	uint		m_type;
	uint64		m_memid;
private:
	CPacket(void);
	virtual ~CPacket(void);

public:
	
	static	void	 DumpPackets(CQVString* doc);

	static	int			CreatePool(uint pagenum, uint pagebit, uint type);
	static	int			DeletePool(void);
	static	CPacket*	Acquire(uint len, uint type = 0);
private:
	static	void		Release(CPacket* packet);
private:
	static	CQVMutex		s_refmutex;
	static	CQVMutex		s_poolmutex;
	static	CPacketPool*	s_pool;
};



#endif

/////////////////////////////////////////////////////////////////////////////
//class CQVPacketList
class QVBASEDLL CQVPacketList : public CQVListT<CPacket*>
{
public:
	CQVPacketList(uint maxnum = 32, uint maxsize = (2 << 20)); 
	virtual ~CQVPacketList(void);

public:
	/////////////////////////////////////////////////////////////////////////////
	//@SetMaxVideoFrameNum:
	//	设置最大视频帧个数,如果为0，则不作视频帧数检查
	void	SetMaxVideoFrameNum(uint maxnum){ m_maxnum = maxnum; }

	/////////////////////////////////////////////////////////////////////////////
	//@SetMaxDataSize:
	//	设置最大数据长度,如果设置为0，则不作数据长度检查
	void	SetMaxDataSize(uint maxsize){ m_maxsize = maxsize; }

public:
	/////////////////////////////////////////////////////////////////////////////
	//@PutPacket:
	//	添加一个数据帧到队列。该函数实际是不做队列是否满
	//	的检查。
	virtual int	PutPacket(CPacket* packet, BOOL tail = TRUE);
	/////////////////////////////////////////////////////////////////////////////
	//@GetPacket:
	//	从队列头取个数据帧
	virtual CPacket* GetPacket(BOOL tail = FALSE);
	/////////////////////////////////////////////////////////////////////////////
	//@IsFull:
	//	检查队列是否满。判断条件是: 如果视频帧数超过规定的
	//	帧数，则返回true；如果总数据长度超过设定的长度，则
	//	返回true.
	BOOL IsFull(void);
	/////////////////////////////////////////////////////////////////////////////
	//@GetSize:
	//	获取队列中总的数据长度
	uint GetSize(void){ return m_size; }
	/////////////////////////////////////////////////////////////////////////////
	//@Clear:
	//	清空队列
	void Clear(void);
	/////////////////////////////////////////////////////////////////////////////
	//@GetVideoFrameNum:
	//	获取视频帧数
	uint GetVideoFrameNum(void) { return m_videonum; }

	int MoveTo(CQVPacketList* dst);

protected:
	virtual void OnDataFree(CPacket*& packet);

protected:
	uint	m_size;		//总数据长度
	uint 	m_videonum;	//视频帧个数
	uint	m_maxnum;
	uint	m_maxsize;
};
/////////////////////////////////////////////////////////////////////////////
//class CQVPacketListEx
class QVBASEDLL CQVPacketListEx : public CQVPacketList
{
public:
	CQVPacketListEx(uint maxnum = 32, uint maxsize = (2 << 20));
	virtual ~CQVPacketListEx(void);

public:
	/////////////////////////////////////////////////////////////////////////////
	//@PutPacket:
	//	添加一个数据帧到队列。该函数实际是不做队列是否满
	//	的检查。
	virtual int	PutPacket(CPacket* packet, BOOL tail = TRUE);
	/////////////////////////////////////////////////////////////////////////////
	//@GetPacket:
	//	从队列头取个数据帧
	virtual CPacket* GetPacket(BOOL tail = FALSE);
protected:
	virtual void OnDataFree(CPacket*& packet);
};

/////////////////////////////////////////////////////////////////////////////
#define	PIC_TYPE_NONE	0
#define	PIC_TYPE_RGB16	1
#define	PIC_TYPE_RGB24	2
#define	PIC_TYPE_RGB32	3
#define	PIC_TYPE_UYVY	4
#define	PIC_TYPE_YV12	5
#define	PIC_TYPE_NUM	6
typedef struct tag_QVFRAME
{
	int				format;
	const uint8*	data[3];
	int				linesize[3];
	int				width;
	int				height;
}QVFRAME, *PQVFRAME;


#endif//__QVPACKET_H__
