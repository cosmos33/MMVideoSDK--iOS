/******************************************************************************

@File         XFileReadMem.h

@Version       1.0

@Created      2017, 12, 19

@Description  ÎÄ¼þ²Ù×÷

@HISTORY:

******************************************************************************/



#ifndef _X_FILEREAD_MEM_H_
#define _X_FILEREAD_MEM_H_

#include "XFileBase.h"
#if X_PLATFORM_ANDROID
#include "XAPKFile.h"
#endif

#define XF_READONLY_VALUE(N,A)	\
	virtual xbool Write##N(const A &value) override { return xfalse; }

#define XF_READONLYCO_VALUE(N,A)	\
	virtual xbool Write##N(A value) override { return xfalse; }

class XFileReadMem : public XFileBase
{
public:
					XFileReadMem();
	virtual			~XFileReadMem();

	virtual xbool		OpenFullPath(const xchar* szFullPath, xuint32 nFlags, xbool bPrintError = xtrue) override;
	virtual xbool 		Close();
	virtual xbool 		Read(void* pBuffer, xuint32 nBufLen, xuint32* pReadLen) override;
	virtual xbool 		Write(const void* pBuffer, xuint32 nBufLen, xuint32* pWriteLen) override { return xfalse; }
	virtual xbool		Seek(xint32 nOffset, XFILE_SEEK eSeektype) override;
	virtual xbool 		Flush() override { return xfalse; }

	virtual xbool 		ReadLine(xchar * szBuf, xuint32 nBufLen, xuint32 * pReadLen) override;
	virtual xbool 		WriteLine(const xchar * szBuf) override { return xfalse; }

	virtual xbool 		WriteString(const XString& str) override { return xfalse; }

	virtual xuint32	GetFileLength() const override { return m_nFileLen; }
	virtual xuint32	GetCurPos() const override { return m_nCurPos; }

	XF_READONLYCO_VALUE(Bool, bool);
	XF_READONLYCO_VALUE(Int8, xint8);
	XF_READONLYCO_VALUE(Int16, xint16);
	XF_READONLYCO_VALUE(Int32, xint32);
	XF_READONLYCO_VALUE(Int64, xint64);
	XF_READONLYCO_VALUE(UInt8, xuint8);
	XF_READONLYCO_VALUE(UInt16, xuint16);
	XF_READONLYCO_VALUE(UInt32, xuint32);
	XF_READONLYCO_VALUE(UInt64, xuint64);
	XF_READONLYCO_VALUE(Float32, xfloat32);
	XF_READONLYCO_VALUE(Float64, xfloat64);
	XF_READONLY_VALUE(Vector2, XVECTOR2);
	XF_READONLY_VALUE(Vector3, XVECTOR3);
	XF_READONLY_VALUE(Vector4, XVECTOR4);
	XF_READONLY_VALUE(Matrix3, XMATRIX3);
	XF_READONLY_VALUE(Matrix4, XMATRIX4);
	XF_READONLY_VALUE(ColorValue, XCOLORBASE);


protected:
	virtual xbool		OpenImpl(const xchar *szPathFile, const xchar *szModel);
	xbool			ReadAllData(const xchar* szFullPath, xbool bPrintError = xtrue);
	xbool			ReadAPKAllData(const xchar* szRelativePath, xbool bPrintError);
	xbool			CreateFileMemory(xint32 nBufflen/*, xbool bTempMem*/);
	void				ReleaseFileMemory();

	xbool			ReadMem(void* pBuffer, xuint32 nBufLen, xuint32* pReadLen);
	xbool			ReadLineMem(xchar * szBuf, xuint32 nBufLen, xuint32 * pReadLen);
	xbool			SeekMem(xint32 nOffset, XFILE_SEEK eSeektype);

	xuint32			m_nFileLen;
	unsigned char*		m_pFileData;	//	Memory pointer of the file image in memory;
	xuint32			m_nCurPos;

#if X_PLATFORM_ANDROID
	XAPKFile*			m_pAPKFile;
#endif
};



#endif




