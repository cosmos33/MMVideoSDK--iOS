/******************************************************************************

@File         XEMessageLog.h

@Version       1.0

@Created      2018, 5, 25

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef _XEMESSAGELOG_XECORE_H
#define _XEMESSAGELOG_XECORE_H

#include "XString.h"
enum XEMessageLogType
{
	XMLT_NONE,
	XMLT_LOAD_ERROR,//load error
	XMLT_OTHER,		//other
	XMLT_NUM
};

class XEMessageDataBase
{
public:
	XEMessageDataBase();
	XEMessageDataBase(const XEMessageDataBase& rhl);
// 	XEMessageDataBase& operator=(const XEMessageDataBase& rhl);
	virtual				       ~XEMessageDataBase(){}   
	void				       SetMessageLog(const xchar* szLostData){ m_strMessageLog = szLostData; }
	XString&			       GetMessageLog(){ return m_strMessageLog; }
	void				       SetMessageLogType(XEMessageLogType eType){ m_eMessageLogType = eType; }
	XEMessageLogType	       GetMessageLogType(){ return m_eMessageLogType; }


protected:				       
	XString				       m_strMessageLog;
	XEMessageLogType	       m_eMessageLogType;
};

class XEMessageActorData : public XEMessageDataBase
{
public:
	XEMessageActorData();
	XEMessageActorData(const XEMessageActorData& rhl);
// 	XEMessageActorData& operator=(const XEMessageActorData& rhl);
	virtual				       ~XEMessageActorData(){}
	void				       SetActorNameWithLostAsset(const xchar* szName){ m_strActorName = szName; }
	XString&			       GetActorNameWithLostAsset(){ return m_strActorName; }
protected:				       
	XString				       m_strActorName;
};


class MessageLogListener
{
public:
	MessageLogListener(){}
	virtual					   ~MessageLogListener(){}
public:
	virtual void			   Ls_AddMessageLog(XEMessageDataBase* pMessageLogData) = 0;
};

#endif // !_XEMESSAGELOG_XECORE_H




