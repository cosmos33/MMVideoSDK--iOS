/******************************************************************************

@File         XFileAnalyseTool.h

@Version       1.0

@Created      2017, 4, 14

@Description

@HISTORY:

******************************************************************************/

#ifndef _XFILE_ANALYSE_TOOL_H_
#define _XFILE_ANALYSE_TOOL_H_

#include "XFileBase.h"


class XFileAnalyse
{
public:
						XFileAnalyse();						
	virtual				~XFileAnalyse();
	virtual xbool		OpenFile(const xchar* szFilePath);
	virtual xbool		AttachBuff(xbyte* pBuffer, xuint32 nLen);

protected:
	void				ReleaseBuf();

	xbyte*				m_pBuffer;
	xuint32				m_nFileLen;
};


class XFileTokenAnalyse : public XFileAnalyse
{
public:
	enum
	{
		MAX_LINELEN = XFILE_LINEMAXLEN
	};

public:					
						XFileTokenAnalyse();
	virtual				~XFileTokenAnalyse(){}

	virtual xbool		OpenFile(const xchar* szFilePath);
	virtual xbool		AttachBuff(xbyte* pBuffer, xuint32 nLen) override;
	xbool	 			GetNextToken(xbool bCrossLine);
	xbool 				PeekNextToken(xbool bCrossLine);

	inline xbool		IsEnd() { return m_pCur >= m_pEnd; }
	inline xint32 		GetCurLine() { return m_nLine; }

	xbyte*				GetCurPtr() { return m_pCur; }
	xint32 				GetBOMSize() { return m_nBOMSize; }
	void				SetPos(xint32 nLine, xbyte* pCur){ m_nLine = nLine; m_pCur = pCur; }

	xchar				m_szToken[MAX_LINELEN];

protected:
	xbool				ResetState();

	xbyte*				m_pStart;
	xbyte*				m_pEnd;
	xbyte*				m_pCur;
	xint32				m_nLine;
	xint32				m_nBOMSize;
};




#endif
