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
	AES-128/AES-192/AES-256加密.
@Parameters:
	1. CQVString&	result:	指向CQVString的引用，成功时返回加密结果
	2. const uchar*	data:	待加密明文数据
	3. uint			len:	待加密明文长度。理论上len可以是大于0的任意长度，建议最好是16的倍数。
	4. const char*	key:	AES秘钥，长度必须为bits/8个字节
	5. uint			bits:	加密比特数，只有128/192/256有效。
@Return:
	成功时返回密文长度。
*/
QVBASEAPI int QVAPI QVAESEncrypt(CQVString& result, const uchar* data, uint len, const uchar* key, uint bits = 128);

/*
@Function:
	int QVAPI QVAESDecrypt(CQVString& result, const uchar* data, uint len, const uchar* key, uint bits = 128 );
@Description:
	AES-128/AES-192/AES-256解密。
@Parameters:
	1. CQVString&	result:	指向CQVString的引用，成功时返回解密结果
	2. const uchar*	data:	待解密密文数据
	3. uint			len:	待解密密文长度
	4. const char*	key:	AES秘钥，长度必须为bits/8个字节
	5. uint			bits:	加密比特数，只有128/192/256有效。
@Return:
	成功时返回明文长度。
*/
QVBASEAPI int QVAPI QVAESDecrypt(CQVString& result, const uchar* data, uint len, const uchar* key, uint bits = 128);

/*
@Function:
	int QVAPI QVAESEncryptMD5(CQVString& result, const uchar* data, uint len, const char* key, uint bits = 128 );
@Description:
	AES-128/AES-256加密.AES秘钥通道使用MD5(key)获取。
@Parameters:
	1. CQVString&	result:	指向CQVString的引用，成功时返回加密结果
	2. const uchar*	data:	待加密明文数据
	3. uint			len:	待加密明文长度。理论上len可以是大于0的任意长度，建议最好是16的倍数。
	4. const char*	key:	密码，可以是大于0的任意长度。
	5. int			keylen:	密码长度，如果小于等于0，则内部使用strlen(key)计算，这时key必须是以'\0'结束的字符串。
	6. uint			bits:	加密比特数，只有128/192/256有效。
@Return:
	成功时返回密文长度。
*/
QVBASEAPI int QVAPI QVAESEncryptMD5(CQVString& result, const uchar* data, uint len, const char* key, int keylen, uint bits = 128 );

/*
@Function:
	int QVAPI QVAESDecryptMD5(CQVString& result, const uchar* data, uint len, const char* key, uint bits = 128 );
@Description:
	AES-128/AES-256解密。AES秘钥通道使用MD5(key)获取。
@Parameters:
	1. CQVString&	result:	指向CQVString的引用，成功时返回解密结果
	2. const uchar*	data:	待解密密文数据
	3. uint			len:	待解密密文长度
	4. const char*	key:	密码，可以是大于0的任意长度。
	5. int			keylen:	密码长度，如果小于等于0，则内部使用strlen(key)计算，这时key必须是以'\0'结束的字符串。
	6. uint			bits:	加密比特数，只有128/192/256有效。
@Return:
	成功时返回明文长度。
*/
QVBASEAPI int QVAPI QVAESDecryptMD5(CQVString& result, const uchar* data, uint len, const char* key, int keylen, uint bits = 128);

#endif//__QVAUTHEN_H__