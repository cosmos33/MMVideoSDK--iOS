/******************************************************************************

 @File         XString.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  String operating class.

 @HISTORY:

******************************************************************************/

#ifndef _XSTRING_H_
#define _XSTRING_H_

#include "XTypes.h"
#include "XMemBase.h"

class XString
{
public:
	// XString Utility
	static xbool	IsNumeric(const char* szStr);
	static xint32	FindChar(const xchar* szStr, xchar c);
	static xint32	Find(const char* szStr, const xchar c, xint32 nStart = 0, xint32 nEnd = -1);
	static xbool	CharIsLower(xint32 c);
	static xbool	CharIsUpper(xint32 c);
	static xchar	ToLower(xchar c);
	static xchar	ToUpper(xchar c);
	static xint32	Hash(const xchar* szStr);
	static xint32	Hash(const xchar *szStr, xint32 nLen);
	static xint32	IHash(const xchar *szStr);
	static xint32	IHash(const xchar *szStr, xint32 nLen);
	static xint32 	GetFormatLen(const char* szFormat, va_list argList);

public:
	friend XString operator + (const XString& str1, const XString& str2) { return XString(str1, str2); }
	friend XString operator + (xchar ch, const XString& str) { return XString(ch, str); }
	friend XString operator + (const XString& str, xchar ch) { return XString(str, ch); }
	friend XString operator + (const xchar* szStr, const XString& str) { return XString(szStr, str); }
	friend XString operator + (const XString& str, const xchar* szStr) { return XString(str, szStr); }
	
	const XString& operator = (xchar ch);
	const XString& operator = (const xchar* szStr);
	const XString& operator = (const XString& str);
	const XString& operator += (xchar ch);
	const XString& operator += (const xchar* szStr);
	const XString& operator += (const XString& str);

	bool operator			== (xchar ch) const { return (GetLength() == 1 && m_pStr[0] == ch); }
	bool operator			== (const xchar* szStr) const;
	bool operator			== (const XString& str) const;
	bool operator			!= (xchar ch) const { return !(GetLength() == 1 && m_pStr[0] == ch); }
	bool operator			!= (const xchar* szStr) const { return !((*this) == szStr); }
	bool operator			!= (const XString& str) const { return !((*this) == str); }
	bool operator			> (const xchar* szStr) const { return Compare(szStr) > 0; }
	bool operator			< (const xchar* szStr) const { return Compare(szStr) < 0; }
	bool operator			>= (const xchar* szStr) const { return !((*this) < szStr); }
	bool operator			<= (const xchar* szStr) const { return !((*this) > szStr); }
	xchar operator			[] (xint32 n) const { ASSERT(n >= 0 && n <= GetLength()); return m_pStr[n]; }
	xchar& operator			[] (xint32 n);
	operator const xchar* 	() const { return m_pStr; }
	const xchar* CStr() const { return m_pStr;}
	
					XString() : m_pStr(m_pEmptyStr) {}
					XString(const XString& str);
					XString(const xchar* szStr);
					XString(const xchar* szStr, xint32 iLen);
					XString(xchar ch, xint32 iRepeat);
					~XString();
	xint32			Compare(const xchar* szStr) const;
	xint32			CompareNoCase(const xchar* szStr) const;
	xint32			GetLength()	const;
	xbool 			IsEmpty() const;
	void 			Empty();	
	void 			ToUpper();
	void 			ToLower();
	XString& 		Format(const xchar* szFormat, ...);
	xchar*			GetBuffer(xint32 iMinSize);
	void 			ReleaseBuffer(xint32 iNewSize = -1);
	xchar* 			LockBuffer();
	void 			UnlockBuffer();

	void 			TrimLeft();
	void 			TrimLeft(xchar ch);
	void 			TrimLeft(const xchar* szChars);
	void 			TrimRight();
	void 			TrimRight(xchar ch);
	void 			TrimRight(const xchar* szChars);
	void 			CutLeft(xint32 n);
	void 			CutRight(xint32 n);
	XString 		Left(xint32 n) const;
	XString 		Right(xint32 n) const;
	XString 		Mid(xint32 iFrom, xint32 iNum = -1) const;

	xint32			Find(xchar ch, xint32 nStart = 0) const;
	xint32 			Find(const xchar* szSub, xint32 nStart = 0) const;
	xint32 			ReverseFind(xchar ch) const;
	xint32 			FindOneOf(const xchar* szCharSet) const;
    
	XString& 		Replace(const xchar* szFrom, const xchar* szTo);
	XString& 		Replace(const xchar cFrom, const xchar cTo);

	xint32			ToInt() const;
	xfloat32 		ToFloat() const;
	xuint64 		ToInt64() const;
	double 			ToDouble() const;

	XString&		SetFileExtension( const xchar *szExt );		
	XString&		StripFileExtension( void );
	XString&		StripFileExtension(const xchar* szExt);

public:
	struct s_STRINGDATA
	{
		xint32		iRefs;
		xint32		iDataLen;
		xint32		iMaxLen;

		xchar*	Data()	{ return (xchar*)(this + 1); }
	};

	struct s_DOUBLE
	{
		unsigned char	aDoubleBits[sizeof(double)];
	};

protected:
					XString(const XString& str1, const XString& str2);
					XString(char ch, const XString& str);
					XString(const XString& str, char ch);
					XString(const char* szStr, const XString& str);
					XString(const XString& str, const char* szStr);

	s_STRINGDATA*	GetData() const { return ((s_STRINGDATA*)m_pStr) - 1; }
	static xint32 	SafeStrLen(const xchar* szStr) { return szStr ? static_cast<xint32>(strlen(szStr)) : 0; }
	static void 	StringCopy(xchar* szDest, const xchar* szSrc, xint32 iLen);
	static xchar* 	AllocBuffer(xint32 iLen);
	static void 	FreeBuffer(s_STRINGDATA* pStrData);
	static bool 	StringEqual(const xchar* s1, const xchar* s2, xint32 iLen);
	static xchar* 	AllocThenCopy(const xchar* szSrc, xint32 iLen);
	static xchar* 	AllocThenCopy(const xchar* szSrc, xchar ch, xint32 iLen);
	static xchar* 	AllocThenCopy(xchar ch, const xchar* szSrc, xint32 iLen);
	static xchar* 	AllocThenCopy(const xchar* s1, const xchar* s2, xint32 iLen1, xint32 iLen2);

protected:
	xchar*			m_pStr;
	static xchar*	m_pEmptyStr;
};

#endif	//	_ASTRING_H_
