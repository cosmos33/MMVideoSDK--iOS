#ifndef _XUIEDITBOX_H_
#define _XUIEDITBOX_H_

#include "XUIWidget.h"
#include "XUIImeDelegate.h"
#include "XUILabel.h"

class XUIEditBox;
class XUIEditBoxImpl;
class XUIEditBoxDelegate;
class XUIImage;

class XUIEditBox : public XUIWidget, public XUIImeDelegate
{
public:
	X_CLASS_DEF(XUIEditBox)

	enum class KeyboardReturnType
	{
		XUI_DEFAULT,
		XUI_DONE,
		XUI_SEND,
		XUI_SEARCH,
		XUI_GO,
		XUI_NEXT
	};
	enum class InputMode
	{
		XUI_ANY,
		XUI_EMAIL_ADDRESS,
		XUI_NUMERIC,
		XUI_PHONE_NUMBER,
		XUI_URL,
		XUI_DECIMAL,
		XUI_SINGLE_LINE,
	};
	enum class InputFlag
	{
		XUI_PASSWORD,
		XUI_SENSITIVE,
		XUI_INITIAL_CAPS_WORD,
		XUI_INITIAL_CAPS_SENTENCE,
		XUI_INITIAL_CAPS_ALL_CHARACTERS,
		XUI_LOWERCASE_ALL_CHARACTERS
	};

	enum class TextHAlignment
	{
		LEFT,
		CENTER,
		RIGHT
	};

	static XUIEditBox*		Create();
	static XUIEditBox*		Create(const XString& strNormalTexture, TextureResType eTextureType = XUIWidget::TextureResType::XUI_LOCAL);
	XUIEditBox();
	virtual ~XUIEditBox();
	virtual void			Draw(IXWorld* pWorld, xuint32 unParentFlags) override;
	XUIImage*				GetImage();
	virtual void			LoadTexture(const XString& strTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	virtual XString			GetTexture();
	virtual void			SetPosition(const XVECTOR2& vPos) override;
	virtual void			SetVisible(xbool bVisible) override;
	virtual void			SetContentSize(const XVECTOR2& vSize) override;
	virtual void			SetAnchorPoint(const XVECTOR2& vAnchorPoint) override;
	virtual void			OnEnter() override;
	virtual void			OnExit() override;
    virtual void            Update(xfloat32 fDelta) override;
	void					SetDelegate(XUIEditBoxDelegate* pDelegate);
	XUIEditBoxDelegate*		GetDelegate(){ return m_pDelegate; }
	void					SetText(const XString& strText);
	XString					GetText()const;
	void					SetFont(const XString& strFont, xint32 nFontSize);
	void					SetFontName(const XString& strFont);
	const XString&			GetFontName() const;
	void					SetFontSize(xint32 nFontSize);
	xint32					GetFontSize() const;
	void					SetFontColor(const XCOLORBASE& color);
	const XCOLORBASE&		GetFontColor() const;

	void					SetPlaceholderText(const XString& strText);
	const XString&			GetPlaceholderText()const;
	void					SetPlaceholderFont(const XString& strFont, xint32 nFontSize);
	void					SetPlaceholderFontName(const XString& strFont);
	const XString&			GetPlaceholderFontName() const;
	void					SetPlaceholderFontSize(xint32 nFontSize);
	xint32					GetPlaceholderFontSize() const;
	void					SetPlaceholderFontColor(const XCOLORBASE& color);
	const XCOLORBASE&		GetPlaceholderFontColor() const;
	void					SetInputMode(InputMode eInputMode);
	InputMode				GetInputMode() const;
	void					SetMaxLength(xint32 nMaxLength);
	xint32					GetMaxLength();
	void					SetInputFlag(InputFlag eInputFlag);
	InputFlag				GetInputFlag() const;
	void					SetReturnType(KeyboardReturnType eReturnType);
	KeyboardReturnType		GetReturnType() const;
	void					SetTextHorizontalAlignment(XUITextHAlignment eAlignment);
	XUITextHAlignment		GetTextHorizontalAlignment() const;
	virtual void			KeyboardWillShow(IMEKeyboardNotificationInfo& info) override;
	virtual void			KeyboardDidShow(IMEKeyboardNotificationInfo& info) override;
	virtual void			KeyboardWillHide(IMEKeyboardNotificationInfo& info) override;
	virtual void			KeyboardDidHide(IMEKeyboardNotificationInfo& info) override;
	void					TouchDownAction(XUINode* pNode, TouchEventType controlEvent);
	virtual void			OnFocusLost();
	virtual xbool			SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;
    
    //IOS only
    void                    SetFollowKeyBoardMoved(const xbool& bFollow);
    xbool                   IsFollowKeyBoardMoved() const;

	void					SetFollowKeyBoardMovedNode(XUINode* pNode);
    
    const xfloat32                GetPositionYBeforeKeyBoardShow(){return m_fPositionYBeforeKeyBoardShow; };
    const xfloat32                GetPositionYAfterKeyBoardShow(){return m_fPositionYAfterKeyBoardShow; };
    
	//						
	void					EndEditingWhenLostFocus(xbool bSet);
	void					ForceEndEditing();

    void                    OnKeyBoardShow(xfloat32 fKeyBoardHeight, xfloat32 fDelta);
    void                    OnKeyBoardHide();
    
protected:
	xbool					Init();
	xbool					Init(const XString& strTexture, TextureResType eTextureType = XUIWidget::TextureResType::XUI_LOCAL);
	virtual XUINode*		CreateClonedInstance() override;
	virtual void			CopyProperties(XUINode* pNode)override;
protected:
	XUIEditBoxImpl*			m_pEditBoxImpl;
	XUIEditBoxDelegate*		m_pDelegate;
    xbool                   m_bFollowKeyBoardMoved;
    xbool                   m_bOnKeyBoardShow;
    xfloat32                m_fPositionYBeforeKeyBoardShow;
    xfloat32                m_fPositionYAfterKeyBoardShow;
    xfloat32                m_fMovedDelta;
    xfloat32                m_fCurrentMoveTime;
	XUINode*				m_pFollowKeyBoardMovedNode;
};

class XUIEditBoxDelegate : public XMemBase
{
public:
    enum class EditBoxEndAction
    {
        XUI_UNKNOWN,
        XUI_TAB_TO_NEXT,
        XUI_TAB_TO_PREVIOUS,
        XUI_RETURN,
        XUI_LOST_FOCUS
    };
    
    virtual ~XUIEditBoxDelegate() {}
    virtual void EditBoxEditingDidBegin(XUIEditBox* pEditBox) {}
    virtual void EditBoxTextChanged(XUIEditBox* editBox, const XString& strText) {}
    virtual void EditBoxEditingDidEndWithAction(XUIEditBox* pEditBox, EditBoxEndAction eAction) {}
    virtual void EditBoxReturnKeyPressed(XUIEditBox* pEditBox, const XString& strText, XUIEditBox::KeyboardReturnType eType){}
    
    // @depracted, use EditBoxReturnKeyPressed instead
    virtual void EditBoxReturn(XUIEditBox* pEditBox){}
    virtual void EditBoxEditingDidSend(XUIEditBox* pEditBox, const XString& strText) {}
};


class XUIEditBoxDelegateLambda : public XUIEditBoxDelegate
{
public:
    
    typedef std::function<void(XUIEditBox* pEditBox)> EditBoxEditingDidBeginCallBack;
    typedef std::function<void(XUIEditBox* pEditBox, const XString& strText)> EditBoxTextChangedCallBack;
    typedef std::function<void(XUIEditBox* pEditBox)> EditBoxReturnCallBack;
    typedef std::function<void(XUIEditBox* pEditBox, EditBoxEndAction eAction)> EditBoxEditingDidEndWithActionCallBack;
    typedef std::function<void(XUIEditBox* pEditBox, const XString& strText)> EditBoxEditingDidSendCallBack;
    typedef std::function<void(XUIEditBox* pEditBox, const XString& strText, XUIEditBox::KeyboardReturnType eType)> EditBoxReturnKeyPressedCallBack;
    
    XUIEditBoxDelegateLambda();
    virtual ~XUIEditBoxDelegateLambda() {};
    virtual void EditBoxEditingDidBegin(XUIEditBox* pEditBox) override;
    virtual void EditBoxTextChanged(XUIEditBox* editBox, const XString& strText) override;
    virtual void EditBoxReturn(XUIEditBox* pEditBox) override;
    virtual void EditBoxEditingDidEndWithAction(XUIEditBox* pEditBox, EditBoxEndAction eAction) override;
    virtual void EditBoxEditingDidSend(XUIEditBox* pEditBox, const XString& strText) override;
    virtual void EditBoxReturnKeyPressed(XUIEditBox* pEditBox, const XString& strText, XUIEditBox::KeyboardReturnType eType) override;
    
    void SetEditBoxEditingDidBeginCallBack(EditBoxEditingDidBeginCallBack callback);
    void SetEditBoxTextChangedCallBack(EditBoxTextChangedCallBack callback);
    void SetEditBoxReturnCallBack(EditBoxReturnCallBack callback);
    void SetEditBoxEditingDidEndWithActionCallBack(EditBoxEditingDidEndWithActionCallBack callback);
    void SetEditBoxEditingDidSendCallBack(EditBoxEditingDidSendCallBack callback);
    void SetEditBoxReturnKeyPressed(EditBoxReturnKeyPressedCallBack callback);
private:
    EditBoxEditingDidBeginCallBack m_EditBoxEditingDidBegin;
    EditBoxTextChangedCallBack m_EditBoxTextChanged;
    EditBoxReturnCallBack m_EditBoxReturn;
    EditBoxEditingDidEndWithActionCallBack m_EditBoxEditingDidEndWithAction;
    EditBoxEditingDidSendCallBack m_EditBoxEditingDidSend;
    EditBoxReturnKeyPressedCallBack m_EditBoxReturnKeyPressed;
};

#endif
