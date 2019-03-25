/******************************************************************************

@File         XFileBase.h

@Version       1.0

@Created      2017, 12, 19

@Description  文件操作

@HISTORY:

******************************************************************************/

#ifndef _X_FILEBASE_H_
#define _X_FILEBASE_H_

#include "XSys.h"
#include "XString.h"

class XVECTOR2;
class XVECTOR3;
class XVECTOR4;
class XMATRIX3;
class XMATRIX4;
class XCOLORBASE;
class XCusOBB;

#define XFILE_TEXT_FLAG		0x54584f4d
#define XFILE_BINARY_FLAG	0x42584f4d

// file seek way
enum XFILE_SEEK { XFILE_SEEK_SET = SEEK_SET, XFILE_SEEK_CUR = SEEK_CUR, XFILE_SEEK_END = SEEK_END };

// file operate flag
enum XFILE_OPE_FLAG
{
	XFILE_OPENEXIST = 1 << 0,			// 表示进行读操作
	XFILE_CREATENEW = 1 << 1,			// 表示进行写操作
	XFILE_OPENAPPEND = 1 << 2,
	XFILE_TEXT = 1 << 3,
	XFILE_BINARY = 1 << 4,
	XFILE_NOHEAD = 1 << 5,
	XFILE_TEMPMEMORY = 1 << 6,
	XFILE_NOTEMPMEMORY = 1 << 7,
	XFILE_LINEMAXLEN = 2048
};


#define XF_READWRITE_VALUE(N,A)	\
	virtual xbool Read##N(A &value); \
	virtual xbool Write##N(const A &value); 

#define XF_READWRITECO_VALUE(N,A)	\
	virtual xbool Read##N(A &value); \
	virtual xbool Write##N(A value); 

// 
class XFileBase
{
public:
								XFileBase();
	virtual 					~XFileBase();
	
	virtual xbool 				Open(const xchar* szFolder, const xchar* szFileName, xuint32 nFlags);
	virtual xbool				OpenFullPath(const xchar* szFullPath, xuint32 nFlags, xbool bPrintError = xtrue);
	virtual xbool				OpenAbsolutePath(const xchar* szAbsPath, xuint32 nFlags);
	virtual xbool 				Close();
	virtual xbool 				Read(void* pBuffer, xuint32 nBufLen, xuint32* pReadLen);
	virtual xbool 				Write(const void* pBuffer, xuint32 nBufLen, xuint32* pWriteLen);
	virtual xbool				Seek(xint32 nOffset, XFILE_SEEK eSeektype);
	virtual xbool 				Flush();

	virtual xuint32 			GetFileLength() const;
	virtual xuint32				GetCurPos() const;

	virtual xbool 				ReadLine(xchar * szBuf, xuint32 nBufLen, xuint32 * pReadLen);
	virtual xbool 				WriteLine(const xchar * szBuf);
	
	virtual xuint32 			GetFlags() const { return m_nFlags; }
	virtual const xchar*		GetFilePath() const { return m_strFilePath.CStr(); }
	virtual const xchar* 		GetRelativeName() const { return m_strFileRelativePath.CStr(); }


	virtual xbool 				ReadString(xchar * szBuf, xuint32 nBufLen, xuint32 * pReadLen);
	virtual xbool				ReadString(XString& str);	
	virtual xbool 				WriteString(const XString& str);	

	XF_READWRITECO_VALUE(Bool, bool);
	XF_READWRITECO_VALUE(Int8, xint8);
	XF_READWRITECO_VALUE(Int16, xint16);
	XF_READWRITECO_VALUE(Int32, xint32);
	XF_READWRITECO_VALUE(Int64, xint64);
	XF_READWRITECO_VALUE(UInt8, xuint8);
	XF_READWRITECO_VALUE(UInt16, xuint16);
	XF_READWRITECO_VALUE(UInt32, xuint32);
	XF_READWRITECO_VALUE(UInt64, xuint64);
	XF_READWRITECO_VALUE(Float32, xfloat32);
	XF_READWRITECO_VALUE(Float64, xfloat64);
	XF_READWRITE_VALUE(Vector2, XVECTOR2);
	XF_READWRITE_VALUE(Vector3, XVECTOR3);
	XF_READWRITE_VALUE(Vector4, XVECTOR4);
	XF_READWRITE_VALUE(Matrix3, XMATRIX3);
	XF_READWRITE_VALUE(Matrix4, XMATRIX4);
	XF_READWRITE_VALUE(ColorValue, XCOLORBASE);
	XF_READWRITE_VALUE(OBB, XCusOBB);

protected:	
	virtual xbool				OpenImpl(const xchar *szPathFile, const xchar *szModel);
	void						ConvertFlag(xuint32 nFlags, XString &strMode);
	void						ReadOrWriteBinaryOrTexFlag(xuint32 nFlags, xuint32 &outFlags);	


	xuint32						m_nFlags;
	xbool						m_bOpened;
	XString						m_strFilePath;
	XString						m_strFileRelativePath;

	FILE *						m_pFile;
};

class XFileScoped
{
public:
								XFileScoped(XFileBase* pFile);
								XFileScoped(const xchar* szFileName, xuint32 nFlag);
	virtual						~XFileScoped();

	XFileBase*					GetFile(){ return m_pFile; }
	XFileBase*					DeTachFile() { XFileBase *pFile = m_pFile; m_pFile = NULL; return pFile; }
	XFileBase*					operator->() const { return m_pFile; }

protected:
	XFileBase*					m_pFile;
};

class XFileGenarate
{
public:
								XFileGenarate(){}
								~XFileGenarate(){}
	/*
	* 根据 flag获取较优的文件工具
	*
	* @ 只读操作， 生成XFileReadMem，一次将文件读入内存
	*   有写操作， 生成XFileBase， 支持读写
	*
	* @returns
	*/
	static XFileBase*			X_GenerateOpenedFileByFlag(const xchar* szFileName, xuint32 nFlag);
};




#endif













