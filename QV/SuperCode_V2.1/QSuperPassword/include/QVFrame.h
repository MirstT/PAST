#ifndef __QVFRAME_H__
#define __QVFRAME_H__
#include "QVPacket.h"


////////////////////////////////////////////////////////////////////
//class CQVPacketPIC
//	描述图片帧的类
class QVBASEDLL CQVPacketPIC : public CQVObject
{
protected:
	CQVPacketPIC(ushort align = 0);
	virtual ~CQVPacketPIC(void);
public:
	static CQVPacketPIC*	Acquire(ushort align = 0);		
	static CQVPacketPIC*	Acquire(uint width, uint height, ushort fmt, ushort align = 0);

public:
	int		AddRef(void);
	int		Release(void);
	int		Init(uint width, uint height, ushort fmt, ushort align = 0);
	ushort	GetFormat(void) const { return m_format; };
	uint	GetWidth(void)  const{ return m_width; };
	uint	GetHeight(void) const{ return m_height;};
	uint	GetLinesnum(uint idx) const { if (idx >= 3) return 0; return m_linesnum[idx]; };
	uint	GetLinesize(uint idx) const { if (idx >= 3) return 0; return m_linesize[idx]; };
	int		GetPitch(uint idx)  const{ if (idx >= 3) return 0; return m_pitch[idx]; };
	uint8*	GetLine(uint idx, uint line) const;
	int		SetLine(uint idx, uint line, uint8* src, int pitch, uint linenum = 1);
	int		GetLine(uint idx, uint line, uint8* dst, int pitch, uint linenum = 1);
	void	operator=(const CQVPacketPIC& packet);

protected:
	void	Reset(void);
	int		InitYV12(uint width, uint height);
	int		InitRGB32(uint width, uint height);
	int		InitRGB24(uint width, uint height);
	int		InitUYVY(int width, uint height);

private:
	CQVMutex	m_mutex;
	int			m_ref;
	ushort		m_align;
	ushort		m_format;		//图片格式
	uint		m_width;		//图片宽度
	uint		m_height;		//图片高度
	uint		m_linesnum[3];	//行数
	uint		m_linesize[3];	//每行有效数据字节数
	int			m_pitch[3];		//两行之间的字节数
	uint8*		m_data[3];		//数据缓冲区地址
	CPacket*	m_packet;
};

///////////////////////////////////////////////////////////////////
//class CQVFrame
class QVBASEDLL CQVFrame : public CQVObject
{
public:
	CQVFrame(void);
	CQVFrame(const CQVFrame& frame);
	virtual ~CQVFrame(void);

public:
	void			Clear(void);
	int				SetVideo(CPacket* packet);
	CPacket*		GetVideo(void) const { return m_packetvideo; };
	int				SetSmart(CPacket* packet);
	CPacket*		GetSmart(void) const { return m_packetsmart; };
	int				SetPicture(CQVPacketPIC* packet);
	CQVPacketPIC*	GetPicture(void) const { return m_packetpic; };

	int				SetPicture(PQVFRAME frame);
	int				GetPicture(PQVFRAME frame);

public:
	void			operator=(const CQVFrame& src);
protected:
	CPacket*		m_packetvideo;		//关联视频帧
	CPacket*		m_packetsmart;		//关联智能帧
	CQVPacketPIC*	m_packetpic;
};

#endif//__QVFRAME_H__