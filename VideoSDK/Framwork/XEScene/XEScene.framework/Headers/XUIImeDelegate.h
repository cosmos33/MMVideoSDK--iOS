#ifndef _UIIMEDELEGATE_H_
#define _UIIMEDELEGATE_H_

#include "XMemBase.h"
#include "XString.h"
#include "XUIGeometry.h"
#include "XUIAssist.h"

typedef struct
{
	XUIRect			begin;              // the soft keyboard rectangle when animation begins
	XUIRect			end;                // the soft keyboard rectangle when animation ends
	xfloat32		duration;           // the soft keyboard animation duration
} IMEKeyboardNotificationInfo;

class XUIImeDelegate : public XMemBase
{
public:
	virtual ~XUIImeDelegate();
	virtual xbool				Attach();
	virtual xbool				Detach();

protected:
	friend class XUIImeDispatcher;
	virtual xbool				CanAttach(){ return xfalse; }
	virtual void				DidAttach(){}
	virtual xbool				CanDetach(){ return xfalse; }
	virtual void				DidDetach(){}
	virtual void				InsertText(const XString& strText){}
	virtual void				DeleteBackward() {}
	virtual void				ControlKey(/*EventKeyboard::KeyCode keyCode*/) {}
	virtual const XString&		GetContentText() { return EMPTY_STRING; }
	virtual void				KeyboardWillShow(IMEKeyboardNotificationInfo& /*info*/)   {}
	virtual void				KeyboardDidShow(IMEKeyboardNotificationInfo& /*info*/)    {}
	virtual void				KeyboardWillHide(IMEKeyboardNotificationInfo& /*info*/)   {}
	virtual void				KeyboardDidHide(IMEKeyboardNotificationInfo& /*info*/)    {}
protected:
	XUIImeDelegate();
};

#endif
