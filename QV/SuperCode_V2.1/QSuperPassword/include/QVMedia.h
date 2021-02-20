#ifndef __QVMEDIA_H__
#define __QVMEDIA_H__
#include "QVString.h"
#include "QVPacket.h"

#define		QVMEDIA_MODE_NONE		0
#define		QVMEDIA_MODE_LIVE		1
#define		QVMEDIA_MODE_FILE		2

#define		QVMEDIA_TYPE_NONE		0
#define		QVMEDIA_TYPE_VIDEO		1
#define		QVMEDIA_TYPE_AUDIO		2
#define		QVMEDIA_TYPE_SMART		3

QVBASEAPI int QVAPI QVZoomCalcuZoom(RECT& rectzoom, const RECT& rect, const POINT& pt0, const POINT& pt1);
QVBASEAPI int QVAPI QVZoomCalcuRect(RECT& dst, const RECT& rect, const RECT& rectzoom);

QVBASEAPI int QVAPI H264DecodeSPS(const uchar* sps, uint size, uint* width, uint* height, uint* profileid);
QVBASEAPI int QVAPI H265DecodeSPS(const uchar* sps, uint size, uint* width, uint* height, uint* profileid);
QVBASEAPI int QVAPI H26XFindNextNal(const uchar* nal, int size);

QVBASEAPI int QVAPI DecodeAudioPCMU(BYTE* data, int len, short* audio);
QVBASEAPI int QVAPI DecodeAudioPCMA(BYTE* data, int len, short* audio);
QVBASEAPI int QVAPI EncodeAudioPCMU(short* audio, int samples, BYTE* data);
QVBASEAPI int QVAPI EncodeAudioPCMA(short* audio, int samples, BYTE* data);
QVBASEAPI int QVAPI ConvertPCMA2PCMU(BYTE* alaw,int samples, BYTE* ulaw);
QVBASEAPI int QVAPI ConvertPCMU2PCMA(BYTE* ulaw, int samples, BYTE* alaw);

class CQVVideoHead;
class CQVAudioHead;
/////////////////////////////////////////////////////////////////////////////////////////
//class CQVMediaDesc
//	媒体描述类
class QVBASEDLL CQVMediaDesc : public CQVObject
{
protected:
	CQVMediaDesc(uint mode = QVMEDIA_MODE_NONE);
	virtual ~CQVMediaDesc(void);

public:
	static	CQVMediaDesc*	Create(uint mode = QVMEDIA_MODE_NONE);
public:
	CQVMediaDesc*	Clone(void);
	void			Release(void);
	void			Reset(void);
	int				SetMode(uint mode);
	int				SetVideoHead(CQVVideoHead* head);
	int				SetAudioHead(CQVAudioHead* head);
	int				SetTimeS(CQVTime* tms);
	int				SetTimeE(CQVTime* tme);
	void			SetTimeRange(uint64 range){ m_range = range;};
	uint			GetMode(void) const { return m_mediamode; };
	CQVTime*		GetTimeS(void){ return &m_tms; };
	uint64			GetTimeRange(void) const { return m_range; };
	uint			GetSeconds(void) const;
	CQVVideoHead*	GetVideoHead(void) { return m_videohead; };
	CQVAudioHead*	GetAudioHead(void) { return m_audiohead; };
	int				Setup(CPacket* packet);
	int				SetupAudio(ushort codec, ushort channum, uint freq);

public:
	void			operator=(const CQVMediaDesc& desc);
protected:
	uint			m_mediamode;	//媒体模式, QVMEDIA_MODE_LIVE/QVMEDIA_MODE_FILE
	CQVVideoHead*	m_videohead;	//视频描述
	CQVAudioHead*	m_audiohead;	//音频描述
	CQVTime			m_tms;			//起始时间
	uint64			m_range;		//时间长度，单位毫秒
};


/////////////////////////////////////////////////////////////////////////////////////////
class QVBASEDLL CQVMediaHead : public CQVObject
{
public:
	CQVMediaHead(void){ m_codec = CODEC_NONE; };
protected:
	virtual ~CQVMediaHead(void){};
public:
	virtual int Release(void) { delete this; return 0; };
public:
	ushort	GetCodec(void) const{ return m_codec; }
	bool	SetCodec(ushort codec){ m_codec = codec; return true; };

	virtual bool	IsVideo(void) const { return false; }
	virtual bool	IsAudio(void) const { return false; }
	virtual bool	IsH264(void) const { return false; };
	virtual bool	IsH265(void) const { return false; };
	virtual bool	Check(CQVMediaHead* head) const { return false; }
	virtual bool	Check(CPacket* packet) const{ return false; }
	virtual CQVMediaHead*	Clone(void) = 0;	
protected:
	ushort	m_codec;

};

class QVBASEDLL CQVAudioHead : public CQVMediaHead
{
public:
	CQVAudioHead(ushort codec = CODEC_PCMA){ m_codec = codec; m_channum = 1; m_freq = 8000; }
protected:
	virtual ~CQVAudioHead(void){};

public:
	virtual bool			IsAudio(void) const { return true; }
	virtual CQVMediaHead*	Clone(void);
	virtual int				Setup(CPacket* packet);
	virtual bool			Check(CQVMediaHead* head) const;
	virtual bool			Check(CPacket* packet) const;		
public:
	ushort	GetChannum(void) const { return m_channum; }
	uint	GetFreq(void) const { return m_freq; }
	void	SetChannum(ushort num) { m_channum = num; }
	void	SetFreq(uint freq) { m_freq = freq; }

public:
	
	bool	Clone(CQVAudioHead* head) { if (head == NULL) return false; m_codec = head->m_codec; m_channum = head->m_channum; m_freq = head->m_freq; return true; }	

protected:
	ushort	m_channum;
	uint	m_freq;
public:
	static	CQVAudioHead* 	CreateHead(CPacket* packet);
	static	CQVAudioHead*	CreateHead(ushort codec, ushort channum, uint freq);
};

class QVBASEDLL CQVVideoHead : public CQVMediaHead
{
public:
	CQVVideoHead(void);
protected:
	virtual ~CQVVideoHead(void);
public:
	virtual bool	IsVideo(void) const { return true; }
public:
	virtual int		Setup(CPacket* packet) = 0;

	virtual int		SetNAL(uint nalt, const uchar* nal, uint len)=0;
	virtual int		GetData(uchar* buffer, uint flag) = 0;
	virtual uint	GetLength(uint flag)=0;
	virtual bool	IsValid(void) = 0;
	//virtual bool	Clone(CQVVideoHead* head) = 0;
	virtual CQVMediaHead*	Clone(void) = 0;
public:
	ushort		GetWidth(void) const { return m_width; }
	ushort		GetHeight(void) const { return m_height; }
	uint		GetProfileID(void) const { return m_profile; }	
protected:
	ushort		m_width;	//视频宽度
	ushort		m_height;	//视频高度
	uint		m_profile;	//视频编码ProfileID	
public:
	static	CQVVideoHead* 	CreateHead(CPacket* packet);
};

//////////////////////////////////////////////////////////////////////////////////////
//H264
#define NAL_ERR			0
#define	NAL_NOIDR		1
#define	NAL_DPA			2
#define	NAL_DPB			3
#define	NAL_DPC			4
#define	NAL_IDR			5
#define	NAL_SEI			6
#define NAL_SPS			7
#define NAL_PPS			8
#define	NAL_PDR			9

#define	NAL_STAP_A		24
#define	NAL_STAP_B		25
#define	NAL_MTAP16		26
#define	NAL_MTAP24		27
#define	NAL_FU_A		28
#define	NAL_FU_B		29


#define RTP_H264_FUS        0x0001
#define RTP_H264_FUE        0x0002
#define RTP_H264_SPS        0x0100
#define RTP_H264_PPS        0x0200
class QVBASEDLL CQVH264Head : public CQVVideoHead
{
public:
	CQVH264Head(void);
protected:
	virtual ~CQVH264Head(void);

public:
	static int FindNextNal(const uchar* nal, int size);

public:
	virtual bool	IsH264(void) const { return true; };
	virtual bool			Check(CPacket* packet) const;
	virtual bool			Check(CQVMediaHead* head) const;
	virtual CQVMediaHead*	Clone(void);
	virtual ushort	GetCodec(void) const { return CODEC_H264; }
	virtual int		Setup(CPacket* packet);
	virtual int		SetNAL(uint nalt, const uchar* nal, uint len);
	virtual int		GetData(uchar* buffer, uint flag);
	virtual uint	GetLength(uint flag);
	virtual uint	GetCodec(void) { return CODEC_H264; }
	virtual bool	IsValid(void);
	//virtual bool	Clone(CQVVideoHead* head);
public:
	void		GetSPS(CQVString& sps){ sps.Empty(TRUE); sps = m_sps; };
	void		GetPPS(CQVString& pps){	pps.Empty(TRUE); pps = m_pps; };
	CQVString&	GetSPS(void){return m_sps;};
	CQVString&	GetPPS(void){return m_pps;};

protected:
	int	SetSPS(uint nalt, const uchar* nal, uint len);
	int SetPPS(uint nalt, const uchar* nal, uint len);
protected:
	CQVString	m_sps;
	CQVString	m_pps;
};

//////////////////////////////////////////////////////////////////////////////////////
//H265
#define NAL_H265_SLICE_TRAIL_N			0
#define NAL_H265_SLICE_TRAIL_R		1
#define NAL_H265_SLICE_TSA_N			2
#define NAL_H265_SLICE_TSA_R			3
#define	NAL_H265_SLICE_STSA_N			4
#define	NAL_H265_SLICE_STSA_R			5
#define	NAL_H265_SLICE_RADL_N			6
#define	NAL_H265_SLICE_RADL_R			7
#define	NAL_H265_SLICE_RASL_N			8
#define	NAL_H265_SLICE_RASL_R			9
#define	NAL_H265_SLICE_BLA_W_LP			16
#define	NAL_H265_SLICE_BLA_W_RADL			17
#define	NAL_H265_SLICE_BLA_N_LP			18
#define	NAL_H265_SLICE_IDR_W_RADL			19
#define	NAL_H265_SLICE_IDR_N_LP			20
#define	NAL_H265_SLICE_CRA_NUT			21
#define	NAL_H265_UNIT_VPS		32
#define	NAL_H265_UNIT_SPS			33
#define	NAL_H265_UNIT_PPS			34
#define	NAL_H265_UNIT_AUD			35
#define	NAL_H265_UNIT_EOS		36
#define	NAL_H265_UNIT_EOB		37
#define	NAL_H265_UNIT_FD		38
#define	NAL_H265_UNIT_SEI_PREFIX		39
#define	NAL_H265_UNIT_SEI_SUFFIX		40

#define RTP_H265_FUS        0x0001
#define RTP_H265_FUE        0x0002
#define RTP_H265_SPS        0x0100
#define RTP_H265_PPS        0x0200
#define RTP_H265_VPS        0x0400
#define RTP_H265_SEI        0x0800
class QVBASEDLL CQVH265Head : public CQVVideoHead
{
public:
	CQVH265Head(void);
	virtual ~CQVH265Head(void);

public:
	static int FindNextNal(const uchar* nal, int size);

public:
	virtual bool	IsH265(void) const { return true; };
	virtual bool			Check(CPacket* packet) const;
	virtual bool			Check(CQVMediaHead* head) const;
	virtual CQVMediaHead*	Clone(void);
	virtual ushort	GetCodec(void) const { return CODEC_H265; }
	virtual int		Setup(CPacket* packet);
	virtual int		SetNAL(uint nalt, const uchar* nal, uint len);
	virtual int		GetData(uchar* buffer, uint flag);
	virtual uint	GetLength(uint flag);
	virtual bool	IsValid(void);
	//virtual bool	Clone(CQVVideoHead* head);
public:
	void		GetVPS(CQVString& vps){ vps.Empty(TRUE); vps = m_vps; };
	void		GetSPS(CQVString& sps){ sps.Empty(TRUE); sps = m_sps; };
	void		GetPPS(CQVString& pps){ pps.Empty(TRUE); pps = m_pps; };
	CQVString&	GetSPS(void){ return m_sps; };
	CQVString&	GetPPS(void){ return m_pps; };
	CQVString&	GetVPS(void){ return m_vps; };
protected:
	int	SetSPS(ushort head, const uchar* nal, uint len);
	int	SetPPS(ushort head, const uchar* nal, uint len);
	int	SetVPS(ushort head, const uchar* nal, uint len);
protected:
	CQVString	m_sps;
	CQVString	m_pps;
	CQVString	m_vps;
};

#endif//__QVMEDIA_H__