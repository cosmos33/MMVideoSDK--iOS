/******************************************************************************

 @File         XWinSys.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  XWinSys.

 @HISTORY:

******************************************************************************/

#ifndef _X_WIN_SYS_H_
#define _X_WIN_SYS_H_

#define a_snprintf _snprintf
#define a_isnan _isnan

X_FORCEINLINE xuint32 XSys::GetFileTimeStamp(const char* szFileName)
{
	//NEED FIX!! 传入的是UTF8，应该转换为wchar_t
	struct stat fileStat;
	stat(szFileName, &fileStat);
	return (xuint32)(fileStat.st_mtime);
}

X_FORCEINLINE xuint32 XSys::GetFileSize(const char* szFileName)
{
	struct stat fileStat;
	stat(szFileName, &fileStat);
	return (xuint32)(fileStat.st_size);
}

X_FORCEINLINE  xuint32 XSys::ChangeFileAttributes(const char* szFileName, int mode)
{
	return chmod( szFileName,mode);
}

X_FORCEINLINE bool XSys::IsFileExist(const char* szFileName)
{
	//NEED FIX!! 传入的是UTF8，应该转换为wchar_t
	if( INVALID_FILE_ATTRIBUTES != GetFileAttributesA(szFileName))
		return true;
	return false;
}

X_FORCEINLINE bool XSys::DeleteFile(const char* szFile)
{
	//NEED FIX!! 传入的是UTF8，应该转换为wchar_t
	return ::DeleteFileA(szFile) != 0;
}

X_FORCEINLINE bool XSys::CopyFile(const char* src,const char* des,bool bFailIfExists)
{
    return ::CopyFileA(src,des,bFailIfExists) != 0;
}

X_FORCEINLINE bool XSys::MoveFile(const char* src,const char* des)
{
    return ::MoveFileA(src,des) != 0;
}

X_FORCEINLINE bool XSys::CreateDirectory(const char* szDir)
{
	//NEED FIX!! 传入的是UTF8，应该转换为wchar_t
	return ::CreateDirectoryA(szDir, NULL) == TRUE;
}



X_FORCEINLINE void XSys::Sleep(unsigned int nMilliSecond)
{
	::Sleep(nMilliSecond);
}

X_FORCEINLINE xuptrint XSys::GetCurrentThreadID()
{
	return GetCurrentThreadId();
}

#define XSys_GetCurrentFrame(frame_cur) __asm\
{\
	mov frame_cur, ebp\
}

//这里不能用函数， 必须用宏
// X_FORCEINLINE xuint32 XSys::GetCurrentFrame()
// {
// 	xuint32 frame_cur = 0;
// 
// 	__asm
// 	{
// 		mov frame_cur, ebp
// 	}
// 	return frame_cur;
// }

//X_FORCEINLINE int XSys::GetSizeCharFromWChar(const wchar_t* szString)
//{
//	return WideCharToMultiByte( CP_ACP, 0, szString, -1, NULL, 0, NULL, NULL );
//}

#define X_CPPTEXT_TO_GB2312(x) (x)
#define X_GB2312_TO_CPPTEXT(x) (x)
#define X_CPPTEXT_TO_UTF8(x) X_GB2312_TO_UTF8(x)
#define X_UTF8_TO_CPPTEXT(x) X_UTF8_TO_GB2312(x)

#define XSTR_CPPTEXT_TO_GB2312(x) (x)
#define XSTR_GB2312_TO_CPPTEXT(x) (x)
#define XSTR_CPPTEXT_TO_UTF8(x) XSTR_GB2312_TO_UTF8(x)
#define XSTR_UTF8_TO_CPPTEXT(x) XSTR_UTF8_TO_GB2312(x)

#define XThreadLocal(of_type) __declspec(thread) of_type

#endif //_X_WIN_SYS_H_
