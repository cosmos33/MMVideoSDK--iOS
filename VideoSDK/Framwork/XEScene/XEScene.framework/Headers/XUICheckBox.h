#ifndef _XUICHECKBOX_H_
#define _XUICHECKBOX_H_

#include "XUIAbstractCheckButton.h"




class XUIImage;
class XUICheckBox : public XUIAbstractCheckButton
{
public:
	X_CLASS_DEF(XUICheckBox)

	typedef enum
	{
		CHECKBOX_STATE_EVENT_SELECTED,
		CHECKBOX_STATE_EVENT_UNSELECTED
	} CheckBoxEventType;

	enum class EventType
	{
		SELECTED,
		UNSELECTED
	};
	typedef std::function<void(XUINode*, XUICheckBox::EventType)> XUICheckBoxCallback;

	XUICheckBox();
	virtual ~XUICheckBox();

public:
	static XUICheckBox*		Create();
	static XUICheckBox*		Create(const XString& strBackGroundNormalTexture, const XString& strBackGroundSelectedTexture, const XString& strCrossTexture,
		const XString& strBackGroundDisabledTexture, const XString& strFrontCrossDisabledTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	static XUICheckBox*		Create(const XString& strBackGroundTexture, const XString& strCrossTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);

	void					AddCheckBoxEventListener(const XUICheckBoxCallback& callback);

	virtual void			Draw(IXWorld* pWorld, xuint32 unParentFlags)override;

	virtual xbool			SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;
protected:
	virtual xbool			Init() override;
	virtual xbool			Init(const XString& strBackGroundNormalTexture, const XString& strBackGroundSelectedTexture, const XString& strCrossTexture,
		const XString& strBackGroundDisabledTexture, const XString& strFrontCrossDisabledTexture, TextureResType eTextureType =TextureResType::XUI_LOCAL);

	virtual void			OnTouchEnded(XUITouch *pTouch, XUIEvent* pUnusedEvent) override;
	virtual void			DispatchSelectChangedEvent(xbool bSelected) override;

	virtual XUINode*		CreateClonedInstance() override;
	virtual void			CopyProperties(XUINode* pNode) override;

protected:
	XUICheckBoxCallback		m_CheckBoxEventCallback;
};
#endif
