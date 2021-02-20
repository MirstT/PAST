#ifndef __QVAUTHEN_H__
#define __QVAUTHEN_H__
#include "QVString.h"

///////////////////////////////////////////////////////////////////////////////////////
//BASE64 Encode/Decode
QVBASEAPI BOOL QVAPI QVBASE64Decode(uchar** result, uint* resultsize, const char* in, int TrimTrailingZeros);
QVBASEAPI BOOL QVAPI QVBASE64Encode(char** result, uint* resultsize, const uchar* orig, uint size);
QVBASEAPI int  QVAPI QVBASE64DecodeExt(uchar* out, const char* in, int TrimTrailingZeros);
QVBASEAPI int  QVAPI QVBASE64DecodeExt2(uchar* out, uint outsize, const char* in, int TrimTrailingZeros);

///////////////////////////////////////////////////////////////////////////////////////
//MD5 Encode/Decode
QVBASEAPI char* QVAPI QVMD5Data(const uchar* data, uint len, char* buf);
QVBASEAPI BOOL	QVAPI QVMD5Encode(const uchar* data, uint len, uchar* buf /*uchar[16]*/);

///////////////////////////////////////////////////////////////////////////////////////
//HASH1/HMAC-SHA1
#define	HASH_LEN	20
#define HASH_BLK	64
QVBASEAPI BOOL QVAPI QVSHA1(uchar* text, int len, uchar* result/*HASH_LEN*/);
QVBASEAPI BOOL QVAPI QVHMAC_SHA1(uchar* text, int text_len, uchar* key, int key_len, uchar* result/*HASH_LEN*/);

///////////////////////////////////////////////////////////////////////////////////////
//Packbits/Unpackbits
QVBASEAPI uint QVAPI QVPackbits(uchar* pSrc, uchar* pDst, int nLen);
QVBASEAPI uint QVAPI QVUnpackbits(uchar* pIn, int nLenIn, uchar* pOut, int nLenOut);

///////////////////////////////////////////////////////////////////////////////////////
// AES-encrypt/decrypt

/*
@Function:
	int QVAPI QVAESEncrypt(CQVString& result, const uchar* data, uint len, const uchar* key, uint bits = 128 );
@Description:
	AES-128/AES-192/AES-256����.
@Parameters:
	1. CQVString&	result:	ָ��CQVString�����ã��ɹ�ʱ���ؼ��ܽ��
	2. const uchar*	data:	��������������
	3. uint			len:	���������ĳ��ȡ�������len�����Ǵ���0�����ⳤ�ȣ����������16�ı�����
	4. const char*	key:	AES��Կ�����ȱ���Ϊbits/8���ֽ�
	5. uint			bits:	���ܱ�������ֻ��128/192/256��Ч��
@Return:
	�ɹ�ʱ�������ĳ��ȡ�
*/
QVBASEAPI int QVAPI QVAESEncrypt(CQVString& result, const uchar* data, uint len, const uchar* key, uint bits = 128);

/*
@Function:
	int QVAPI QVAESDecrypt(CQVString& result, const uchar* data, uint len, const uchar* key, uint bits = 128 );
@Description:
	AES-128/AES-192/AES-256���ܡ�
@Parameters:
	1. CQVString&	result:	ָ��CQVString�����ã��ɹ�ʱ���ؽ��ܽ��
	2. const uchar*	data:	��������������
	3. uint			len:	���������ĳ���
	4. const char*	key:	AES��Կ�����ȱ���Ϊbits/8���ֽ�
	5. uint			bits:	���ܱ�������ֻ��128/192/256��Ч��
@Return:
	�ɹ�ʱ�������ĳ��ȡ�
*/
QVBASEAPI int QVAPI QVAESDecrypt(CQVString& result, const uchar* data, uint len, const uchar* key, uint bits = 128);

/*
@Function:
	int QVAPI QVAESEncryptMD5(CQVString& result, const uchar* data, uint len, const char* key, uint bits = 128 );
@Description:
	AES-128/AES-256����.AES��Կͨ��ʹ��MD5(key)��ȡ��
@Parameters:
	1. CQVString&	result:	ָ��CQVString�����ã��ɹ�ʱ���ؼ��ܽ��
	2. const uchar*	data:	��������������
	3. uint			len:	���������ĳ��ȡ�������len�����Ǵ���0�����ⳤ�ȣ����������16�ı�����
	4. const char*	key:	���룬�����Ǵ���0�����ⳤ�ȡ�
	5. int			keylen:	���볤�ȣ����С�ڵ���0�����ڲ�ʹ��strlen(key)���㣬��ʱkey��������'\0'�������ַ�����
	6. uint			bits:	���ܱ�������ֻ��128/192/256��Ч��
@Return:
	�ɹ�ʱ�������ĳ��ȡ�
*/
QVBASEAPI int QVAPI QVAESEncryptMD5(CQVString& result, const uchar* data, uint len, const char* key, int keylen, uint bits = 128 );

/*
@Function:
	int QVAPI QVAESDecryptMD5(CQVString& result, const uchar* data, uint len, const char* key, uint bits = 128 );
@Description:
	AES-128/AES-256���ܡ�AES��Կͨ��ʹ��MD5(key)��ȡ��
@Parameters:
	1. CQVString&	result:	ָ��CQVString�����ã��ɹ�ʱ���ؽ��ܽ��
	2. const uchar*	data:	��������������
	3. uint			len:	���������ĳ���
	4. const char*	key:	���룬�����Ǵ���0�����ⳤ�ȡ�
	5. int			keylen:	���볤�ȣ����С�ڵ���0�����ڲ�ʹ��strlen(key)���㣬��ʱkey��������'\0'�������ַ�����
	6. uint			bits:	���ܱ�������ֻ��128/192/256��Ч��
@Return:
	�ɹ�ʱ�������ĳ��ȡ�
*/
QVBASEAPI int QVAPI QVAESDecryptMD5(CQVString& result, const uchar* data, uint len, const char* key, int keylen, uint bits = 128);

#endif//__QVAUTHEN_H__