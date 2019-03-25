/******************************************************************************

 @File         XSys.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  XSys.

 @HISTORY:

******************************************************************************/
#ifndef _X_SYS_H_
#define _X_SYS_H_

#include "XTypes.h"
#include "XString.h"
#include "XMemBase.h"
#include "XArray.h"

typedef void 			(*pOutputInfoFunction)(const char*);

class XSys : public XMemBase
{
public:
	X_FORCEINLINE static bool 			IsFileExist(const char* szFileName);
	X_FORCEINLINE static bool 			DeleteFile(const char* szFile);
    X_FORCEINLINE static bool 			CopyFile(const char* src,const char* des,bool bFailIfExists);
    X_FORCEINLINE static bool 			MoveFile(const char* src,const char* des);
	//删除目录及其内部的所有文件
	static bool 						DeleteDirectory(const char* szDir);
	//创建目录，不会递归创建，若该目录的上级
	X_FORCEINLINE static bool 			CreateDirectory(const char* szDir);

	//遍历目录, 输入文件夹结尾没有斜杠，返回的文件名中不包含路径
	static bool 						GetFilesInDirectory(XArray<XString>& arrFiles, const char* szDir);
	//获取工作目录的绝对路径
	static bool 						GetBaseDirectory(char* szBaseDir);
	//获取可以写入文档的目录，ios 上并不是所有目录下都能写文件的
	static bool 						GetDocumentsDirectory(char* szDocumentDir);
	//获取文件改动的时间戳
	X_FORCEINLINE static xuint32 			GetFileTimeStamp(const char* szFileName);
	X_FORCEINLINE static xuint32 			GetFileSize(const char* szFileName);
    //S_IREAD,S_IWRITE,S_IRWXU
	X_FORCEINLINE static xuint32 			ChangeFileAttributes(const char* szFileName, int mode);
    static bool    							GetVersion(XString& strVersion);
	static xfloat32 						GetUserResolutionScale();
    static void 							SetUserResolutionScale(xfloat32 scale);
	static void 							SetUIDevSize(xfloat32 fWidth, xfloat32 fHeight);
	static xuint32 							GetUIDevWidth();
	static xuint32 							GetUIDevHeight();
	static xfloat32 						GetDeviceScreenScale();
	static xfloat32 						GetWindowScale();
    static xfloat32 						GetDeviceDpiScale();
	static xuint32 							GetOriginalWindowWidth();
	static xuint32 							GetOriginalWindowHeight();
    static xbool 							IsRetinaScreen();
	static void 							SetDeviceDpiScale(xfloat32 scale);
	static void 							SetOriginalWindowWidth(xuint32 width);
	static void 							SetOriginalWindowHeight(xuint32 height);
	//	Get Milli-second
	static xuint32 							GetMilliSecond();
	//	Get micro-second
	static xuint64 							GetMicroSecond();
	//	Get seconds elapsed since midnight (00:00:00), January 1, 1970, UTC
	static xuint64 							GetTimeSince1970();
	//	Make XTIME structure from time value returned by GetTimeSince1970()
	static void 							GMTime(xuint64 _time, XTIME& atm);
	static void 							LocalTime(xuint64 _time, XTIME& atm);
	//	Make time value from XTIME structure
	//	wday in atm are not used.
	static xuint64 							TimeGM(const XTIME& atm);	//	Note: this function isn't implemented now and always return 0.
	static xuint64							TimeLocal(const XTIME& atm);
	//	Get current time
	//	piMilliSec: can be NULL, used to get millisecond. Not every system support this, and on those
	//		systems -1 will be returned.
	static void 							GetCurGMTime(XTIME& atm, xuint32* piMilliSec);
	static void 							GetCurLocalTime(XTIME& atm, xuint32* piMilliSec);

	//让当前线程睡眠
	X_FORCEINLINE static void 				Sleep(unsigned int nMilliSecond);
	//输出信息到调试窗口
	static void 							OutputDebug(const char* szDebugInfo);
	static void 							SetOutputDebugFunction(pOutputInfoFunction pFun);

	//	Output message to a popup message box
	//	pTextKey: utf-8 encoding string
	//	pOptionKey: utf-8 encoding string
	static xuint32 							MessageBox(const char* pTextKey, const char* pOptionKey, xuint32 uType, xuint32 timeout = 10000);
	//	Output message to a popup message box
	//	pTextKey: C-text encoding string
	//	pOptionKey: C-text encoding string
	static xuint32 							MessageBox_CText(const char* pTextKey, const char* pOptionKey, xuint32 uType, xuint32 timeout = 10000);
    
    static xbool 							CopyDataToPasteboard(const char* pData);
    static xbool 							GetPastebordData(XString& data);

	// 字符编码转换函数。
	// 字符编码转换函数 Part I: 单个字符UTF32 <-> UTF8，自己实现的。
	struct UTF8_EncodedChar
	{
		UTF8_EncodedChar()
		{
			memset(bytes, 0, 8);
		}
		int GetByteCount()
		{
			return len > 6 ? 6 : len;
		}
		union
		{
			xchar bytes[8];
			struct
			{
				xchar byte0;
				xchar byte1;
				xchar byte2;
				xchar byte3;
				xchar byte4;
				xchar byte5;
				xchar byte6; // always null
				xuint8 len;
			};
		};
	};

	static xbool						IsUnicodeSpace(xuint32 ch);
	static xbool						IsCJKUnicode(xuint32 ch);
	static xbool						IsUnicodeNonBreaking(xuint32 ch);


	static xint32 						ParseUnicodeFromUTF8Str(const xchar* szUTF8, xint32* pnAdvancedInUtf8Str = 0, xuint32 nUtf8StrMaxLen = X_MAX_UINT32);
	static UTF8_EncodedChar 			EncodeUTF8(xint32 ch);
	static xint32 						ParseUnicodeFromUTF8StrEx(const xchar* szUTF8, xint32 iParsePos = 0, xint32* piParsedHeadPos = 0, xint32* pnUtf8ByteCounts = 0, xuint32 nUtf8StrMaxLen = X_MAX_UINT32);
	// 字符编码转换函数 Part II: UTF16LE <-> UTF8，自己实现的。
	static xint32 						UTF16Len(const xuint16* sz16); // returns the xuint16-char count NOT including \0.
	static xint32 						UTF8ToUTF16LE(xuint16* sz16, const xchar* sz8); // returns the xuint16-char count including \0 of the converted string.
	static xint32 						UTF16LEToUTF8(xchar* sz8, const xuint16* sz16); // returns the byte count including \0 of the converted string.
	// 字符编码转换函数 Part III: 平台相关。下面的函数在不同系统上采用了不同的实现。
	// iSrcLen: if < 0, whole szSrc including ending character ('\0') will be converted.
	static xint32 						CPPTextToGB2312(xchar* szDest, const char* szSrc, int iSrcLen, int nDestBufferMaxSize); // returns the byte count including \0 of the converted string.
	static xint32 						GB2312ToCPPText(xchar* szDest, const char* szSrc, int iSrcLen, int nDestBufferMaxSize); // returns the byte count including \0 of the converted string.
	// 字符编码转换函数 Part IV: 引擎常用编码转换。
	// iSrcLen: if < 0, whole szSrc including ending character ('\0') will be converted.
	static xint32 						GB2312ToUTF8(xchar* szDest, const char* szSrc, int iSrcLen, int nDestBufferMaxSize); // returns the byte count including \0 of the converted string.
	static xint32 						UTF8ToGB2312(xchar* szDest, const char* szSrc, int iSrcLen, int nDestBufferMaxSize); // returns the byte count including \0 of the converted string.
	// From GB2132 to system's file name encoding format
	static xint32 						GB2132ToFileNameEncoding(xchar* szDest, const xchar* szSrc, xint32 nDestBufferMaxSize);
	// From UTF8 to UTF32 format
	static xuint32						UTF8TOUTF32(xuint32* szDest, const xchar *szSrc, xuint32 iSrcLen, xuint32 nDestBufferMaxSize);

	//	Windows system only
#if defined(X_PLATFORM_WIN_DESKTOP)
	X_FORCEINLINE static xint32 		WCharLen(const wchar_t* szWStr) { return (xint32)wcslen(szWStr); }
	static xint32 						WCharToChar(char* szDest, const wchar_t* szSrc, int nDestBufferMaxSize); // returns the byte count including \0 of the converted string.
	static xint32 						CharToWChar(wchar_t* szDest, const char* szSrc, int nDestBufferMaxSize); // returns the wchar_t count including \0 of the converted string.
	static xint32 						WCharToUTF8(char* szDest, const wchar_t* szSrc, int nDestBufferMaxSize); // returns the byte count including \0 of the converted string.
	static xint32 						UTF8ToWChar(wchar_t* szDest, const char* szSrc, int nDestBufferMaxSize); // returns the wchar_t count including \0 of the converted string.
#endif	//	X_PLATFORM_WIN_DESKTOP
	// 字符编码转换函数。

	static int 							AccessFile(const char* path, int mode);
	static int 							SetFileSize(int fd, xint32 size );
	static xint64 						XtoInt64(const char* szString);
	static int 							StrCmpNoCase(const char* sz1, const char* sz2);
	static char* 						Strlwr( char* str );
	static char* 						Strupr(char* str);
	static int  						Fileno( FILE * _File);
	static bool 						IsNan(float f);

	//NEED FIX!! 内存调试函数。这个几个函数与AMemory类耦合太紧密，需要重构
	//输出函数的调用堆栈到DebugOutput
	static void 						ExportSymbolInfo(void* ptr);
	//读入Address的符号文件
	static void 						LoadAddressSymbol(void* pAddress);
	//输出所有已经记录的函数调用栈
	static void 						DumpAllAddressSymbol(FILE* pAddiInfoFile);
	//For thread
	static xuptrint 					GetCurrentThreadID();
	//结束当前进程
	static void 						Exit();
};

#if X_PLATFORM_WIN_DESKTOP
#include "XWinSys.h"
#elif X_PLATFORM_ANDROID
#include "XAndroidSys.h"
#elif X_PLATFORM_LINUX
//
#elif X_PLATFORM_XOS
#include "XXOSSys.h"
#endif

// macros below is defined in the "XWinSys.h"or ...
// #define a_snprintf _snprintf
// #define a_isnan _isnan

// the Thread Local Storage macro is defined in the "XWinSys.h" or ...
// on Windows, it is like this:
// #define XThreadLocal(of_type) __declspec(thread) of_type

// ## Classes for string convert macros.
class BaseStackStringConverter
{
protected:
	
	BaseStackStringConverter(void* pAllocaBuffer)
	{
		nBufferLen = nBufferLenTemp;
		szBuffer = pAllocaBuffer;
	}

public:
	operator xchar*() const { return (xchar*)szBuffer; }
	operator xuchar*() const { return (xuchar*)szBuffer; }
	operator wchar_t*() const { return (wchar_t*)szBuffer; }
	operator void*() const { return szBuffer; }

	static XThreadLocal(size_t) nBufferLenTemp;
	static XThreadLocal(const void*) szConvertSrcTemp;
	static XThreadLocal(size_t) nSrcLenTemp;

	static size_t Prepare(const XString& rStr)
	{
		szConvertSrcTemp = (const char*)rStr;
		nSrcLenTemp = rStr.GetLength();
		return nSrcLenTemp;
	}

	static size_t Prepare(const BaseStackStringConverter& rStr)
	{
		szConvertSrcTemp = (const char*)rStr;
		nSrcLenTemp = rStr.GetLength();
		return nSrcLenTemp;
	}

	static size_t Prepare(const char* rStr)
	{
		szConvertSrcTemp = rStr;
		nSrcLenTemp = strlen(rStr);
		return nSrcLenTemp;
	}
	
	static size_t PrepareUTF16_UTF8(const xuint16* rStr)
	{
		szConvertSrcTemp = (const char*)rStr;
		nSrcLenTemp = XSys::UTF16Len(rStr);
		return nSrcLenTemp * 4 + 1;
	}
	
	static size_t PrepareUTF8_UTF16(const char* rStr)
	{
		szConvertSrcTemp = rStr;
		nSrcLenTemp = strlen(rStr);
		return nSrcLenTemp * 2 + 2;
	}

	size_t GetLength() const { return nBufferLen; }

protected:

	size_t nBufferLen;
	void* szBuffer;
};

class UTF8ToGBConverter : public BaseStackStringConverter
{
public:
	UTF8ToGBConverter(void* pAllocaBuffer) : BaseStackStringConverter(pAllocaBuffer) { Convert(szConvertSrcTemp); }
protected:
	void Convert(const void* szSrc) { nBufferLen = XSys::UTF8ToGB2312((char*)szBuffer, (const char*)szSrc, (int)nSrcLenTemp+1, (int)nBufferLen); }
};

class GBToUTF8Converter : public BaseStackStringConverter
{
public:
	GBToUTF8Converter(void* pAllocaBuffer) : BaseStackStringConverter(pAllocaBuffer) { Convert(szConvertSrcTemp); }
protected:
	void Convert(const void* szSrc) { nBufferLen = XSys::GB2312ToUTF8((char*)szBuffer, (const char*)szSrc, (int)nSrcLenTemp+1, (int)nBufferLen); }
};

class CTextToGBConverter : public BaseStackStringConverter
{
public:
	CTextToGBConverter(void* pAllocaBuffer) : BaseStackStringConverter(pAllocaBuffer) { Convert(szConvertSrcTemp); }
protected:
	void Convert(const void* szSrc) { nBufferLen = XSys::CPPTextToGB2312((char*)szBuffer, (const char*)szSrc, (int)nSrcLenTemp+1, (int)nBufferLen); }
};

class GBToCTextConverter : public BaseStackStringConverter
{
public:
	GBToCTextConverter(void* pAllocaBuffer) : BaseStackStringConverter(pAllocaBuffer) { Convert(szConvertSrcTemp); }
protected:
	void Convert(const void* szSrc) { nBufferLen = XSys::GB2312ToCPPText((char*)szBuffer, (const char*)szSrc, (int)nSrcLenTemp+1, (int)nBufferLen); }
};

class UTF16ToUTF8Converter : public BaseStackStringConverter
{
public:
	UTF16ToUTF8Converter(void* pAllocaBuffer) : BaseStackStringConverter(pAllocaBuffer) { Convert(szConvertSrcTemp); }
protected:
	void Convert(const void* szSrc) { nBufferLen = XSys::UTF16LEToUTF8((char*)szBuffer, (const xuint16*)szSrc); }
};

class UTF8ToUTF16Converter : public BaseStackStringConverter
{
public:
	UTF8ToUTF16Converter(void* pAllocaBuffer) : BaseStackStringConverter(pAllocaBuffer) { Convert(szConvertSrcTemp); }
protected:
	void Convert(const void* szSrc) { nBufferLen = XSys::UTF8ToUTF16LE((xuint16*)szBuffer, (const xchar*)szSrc); }
};
// =# Classes for string convert macros. ^above^

// ## Helper Macro To Convert String To Different Encodings.
// The return values of these macros should NOT be released.

// Convert from UTF-8 to GB2312/GBK. Returned pointer should NOT be released.
#define X_UTF8_TO_GB2312(x) (xchar*)UTF8ToGBConverter(XAlloca16(BaseStackStringConverter::nBufferLenTemp = BaseStackStringConverter::Prepare(x) * 2 + 1))
// Convert to UTF-8 from GB2312/GBK. Returned pointer should NOT be released.
#define X_GB2312_TO_UTF8(x) (xchar*)GBToUTF8Converter(XAlloca16(BaseStackStringConverter::nBufferLenTemp = BaseStackStringConverter::Prepare(x) * 2 + 1))

// Convert from UTF-16 to UTF-8. Returned pointer should NOT be released.
#define X_UTF16_TO_UTF8(x) (xchar*)UTF16ToUTF8Converter(XAlloca16(BaseStackStringConverter::nBufferLenTemp = BaseStackStringConverter::PrepareUTF16_UTF8((const xuint16*)(x))))
// Convert from UTF-8 to UTF-16. Returned pointer should NOT be released.
#define X_UTF8_TO_UTF16(x) (xuint16*)(void*)UTF8ToUTF16Converter(XAlloca16(BaseStackStringConverter::nBufferLenTemp = BaseStackStringConverter::PrepareUTF8_UTF16(x)))

// ## Helper Macro To Convert String To Different Encodings. - Using XString as macro param.
// The return values of these macros should NOT be released.
// Convert from UTF-8 to GB2312/GBK. Returned pointer should NOT be released.
#define XSTR_UTF8_TO_GB2312(x) UTF8ToGBConverter(XAlloca16(BaseStackStringConverter::nBufferLenTemp = BaseStackStringConverter::Prepare(x) * 2 + 1))
// Convert to UTF-8 from GB2312/GBK. Returned pointer should NOT be released.
#define XSTR_GB2312_TO_UTF8(x) GBToUTF8Converter(XAlloca16(BaseStackStringConverter::nBufferLenTemp = BaseStackStringConverter::Prepare(x) * 2 + 1))

// Convert from UTF-16 to UTF-8. Returned pointer should NOT be released.
#define XSTR_UTF16_TO_UTF8(x) UTF16ToUTF8Converter(XAlloca16(BaseStackStringConverter::nBufferLenTemp = XSys::UTF16LEToUTF8(0, (const xuint16*)(const void*)(BaseStackStringConverter::szConvertSrcTemp = (x)))))
// Convert from UTF-8 to UTF-16. Returned pointer should NOT be released.
#define XSTR_UTF8_TO_UTF16(x) (xuint16*)(void*)UTF8ToUTF16Converter(XAlloca16(BaseStackStringConverter::nBufferLenTemp = BaseStackStringConverter::Prepare(x) * 2 + 2))
// =# Helper Macro To Convert String To Different Encodings. ^above^

////////////////////////////////////////////////////////////////////////////////////////////
//	wchar_t operations, only for windows system
////////////////////////////////////////////////////////////////////////////////////////////

#ifdef X_PLATFORM_WIN_DESKTOP

class WCharToUTF8Converter : public BaseStackStringConverter
{
public:
	WCharToUTF8Converter(void* pAllocaBuffer) : BaseStackStringConverter(pAllocaBuffer) { Convert(szConvertSrcTemp); }
protected:
	void Convert(const void* szSrc) { nBufferLen = XSys::WCharToUTF8((char*)szBuffer, (const wchar_t*)szSrc, (int)nBufferLen); }
};

class UTF8ToWCharConverter : public BaseStackStringConverter
{
public:
	UTF8ToWCharConverter(void* pAllocaBuffer) : BaseStackStringConverter(pAllocaBuffer) { Convert(szConvertSrcTemp); }
protected:
	void Convert(const void* szSrc) { nBufferLen = XSys::UTF8ToWChar((wchar_t*)szBuffer, (const char*)szSrc, (int)nBufferLen); }
};

class WCharToCharConverter : public BaseStackStringConverter
{
public:
	WCharToCharConverter(void* pAllocaBuffer) : BaseStackStringConverter(pAllocaBuffer) { Convert(szConvertSrcTemp); }
protected:
	void Convert(const void* szSrc) { nBufferLen = XSys::WCharToChar((char*)szBuffer, (const wchar_t*)szSrc, (int)nBufferLen); }
};

class CharToWCharConverter : public BaseStackStringConverter
{
public:
	CharToWCharConverter(void* pAllocaBuffer) : BaseStackStringConverter(pAllocaBuffer) { Convert(szConvertSrcTemp); }
protected:
	void Convert(const void* szSrc) { nBufferLen = XSys::CharToWChar((wchar_t*)szBuffer, (const char*)szSrc, (int)nBufferLen); }
};

// Convert a wide string to UTF-8. Returned pointer should NOT be released.
#define X_WCHAR_TO_UTF8(x) (xchar*)WCharToUTF8Converter(XAlloca16(BaseStackStringConverter::nBufferLenTemp = XSys::WCharToUTF8(0, (const wchar_t*)(const void*)(BaseStackStringConverter::szConvertSrcTemp = (x)), 0)))
// Convert from UTF-8 back to wide string. Returned pointer should NOT be released.
#define X_UTF8_TO_WCHAR(x) (wchar_t*)UTF8ToWCharConverter(XAlloca16(BaseStackStringConverter::nBufferLenTemp = XSys::UTF8ToWChar(0, (const char*)(const void*)(BaseStackStringConverter::szConvertSrcTemp = (x)), 0) * sizeof(wchar_t)))
// Convert a wide string to current code-page. Returned pointer should NOT be released.
#define X_WCHAR_TO_CHAR(x) (xchar*)WCharToCharConverter(XAlloca16(BaseStackStringConverter::nBufferLenTemp = XSys::WCharToChar(0, (const wchar_t*)(const void*)(BaseStackStringConverter::szConvertSrcTemp = (x)), 0)))
// Convert from current code-page back to wide string. Returned pointer should NOT be released.
#define X_CHAR_TO_WCHAR(x) (wchar_t*)CharToWCharConverter(XAlloca16(BaseStackStringConverter::nBufferLenTemp = XSys::CharToWChar(0, (const char*)(const void*)(BaseStackStringConverter::szConvertSrcTemp = (x)), 0) * sizeof(wchar_t)))
// Convert a wide string to UTF-8. Returned pointer should NOT be released.
#define XSTR_WCHAR_TO_UTF8(x) WCharToUTF8Converter(XAlloca16(BaseStackStringConverter::nBufferLenTemp = XSys::WCharToUTF8(0, (const wchar_t*)(const void*)(BaseStackStringConverter::szConvertSrcTemp = (x)), 0)))
// Convert from UTF-8 back to wide string. Returned pointer should NOT be released.
#define XSTR_UTF8_TO_WCHAR(x) UTF8ToWCharConverter(XAlloca16(BaseStackStringConverter::nBufferLenTemp = BaseStackStringConverter::Prepare(x) * sizeof(wchar_t) + sizeof(wchar_t)))
// Convert a wide string to current code-page. Returned pointer should NOT be released.
#define XSTR_WCHAR_TO_CHAR(x) WCharToCharConverter(XAlloca16(BaseStackStringConverter::nBufferLenTemp = XSys::WCharToChar(0, (const wchar_t*)(const void*)(BaseStackStringConverter::szConvertSrcTemp = (x)), 0)))
// Convert from current code-page back to wide string. Returned pointer should NOT be released.
#define XSTR_CHAR_TO_WCHAR(x) CharToWCharConverter(XAlloca16(BaseStackStringConverter::nBufferLenTemp = BaseStackStringConverter::Prepare(x) * sizeof(wchar_t) + sizeof(wchar_t)))


#endif	//	X_PLATFORM_WIN_DESKTOP


//	little/big endian
xint16		XLittleInt16(xint16 l);
xint32		XLittleInt32(xint32 l);
xint64		XLittleInt64(xint64 l);
xfloat32	XLittleFloat32(xfloat32 f);
xfloat64	XLittleFloat64(xfloat64 f);
void		XLittleBytes(void* pInOutBytes, xint64 nElementSize, xint64 nElementNum);
void		XByteOrderInit();
bool		XIsLittleEndian();



#endif //_X_SYS_H_

