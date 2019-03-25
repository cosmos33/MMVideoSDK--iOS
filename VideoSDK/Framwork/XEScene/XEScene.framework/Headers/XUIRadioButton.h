#ifndef _XUIRADIOBUTTON_H_
#define _XUIRADIOBUTTON_H_

#include "XUIAbstractCheckButton.h"

class XUIImage;
class XUIRadioButtonGroup;
class XUIRadioButton : public XUIAbstractCheckButton
{
public:
	X_CLASS_DEF(XUIRadioButton)
	friend class XUIRadioButtonGroup;

	enum class EventType
	{
		SELECTED,
		UNSELECTED
	};
	typedef std::function<void(XUINode*, XUIRadioButton::EventType)> XUIRadioButtonCallback;

	XUIRadioButton();
	virtual ~XUIRadioButton();

public:
	static XUIRadioButton*				Create();
	static XUIRadioButton*				Create(const XString& strBackGroundNormalTexture, const XString& strBackGroundSelectedTexture, const XString& strCrossTexture,
		const XString& strBackGroundDisabledTexture, const XString& strFrontCrossDisabledTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);
	static XUIRadioButton*				Create(const XString& strBackGroundTexture, const XString& strCrossTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);

	void								AddRadioButtonEventListener(const XUIRadioButtonCallback& callback);

	virtual void						Draw(IXWorld* pWorld, xuint32 unParentFlags)override;

	virtual xbool						SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;
	virtual xbool						SerilizeEnd() override;
	virtual void						Cleanup() override;
protected:
	virtual void						ReleaseUpEvent() override;


	virtual xbool						Init() override;
	virtual xbool						Init(const XString& strBackGroundNormalTexture, const XString& strBackGroundSelectedTexture, const XString& strCrossTexture,
		const XString& strBackGroundDisabledTexture, const XString& strFrontCrossDisabledTexture, TextureResType eTextureType =TextureResType::XUI_LOCAL);

	virtual void						DispatchSelectChangedEvent(xbool bSelected) override;

	virtual XUINode*					CreateClonedInstance() override;
	virtual void						CopyProperties(XUINode* pNode) override;

protected:
	XUIRadioButtonCallback				m_RadioButtonEventCallback;
	XUIRadioButtonGroup*				m_pGroup;
	xuint32								m_unGroupGUID;
	xbool								m_bMemberOfGroup;
};


class XUIRadioButtonGroup : public XUIWidget
{
	friend class XUIRadioButton;

public:

	X_CLASS_DEF(XUIRadioButtonGroup)

	enum class EventType
	{
		SELECT_CHANGED,
	};


	typedef std::function<void(XUIRadioButton* pRadioButton, xint32 index, XUIRadioButtonGroup::EventType)> XUIRadioButtonGroupCallback;

	XUIRadioButtonGroup();
	virtual ~XUIRadioButtonGroup();

	static XUIRadioButtonGroup*			  Create();

	void								  AddEventListener(const XUIRadioButtonGroupCallback& callback);

	virtual xint32						  GetSelectedButtonIndex() const;
	virtual void						  SetSelectedButton(const int& nIndex);
	virtual void						  SetSelectedButton(XUIRadioButton* pRadioButton);
	virtual void						  SetSelectedButtonWithoutEvent(const xint32& nIndex);
	virtual void						  SetSelectedButtonWithoutEvent(XUIRadioButton* pRadioButton);

	virtual void						  AddRadioButton(XUIRadioButton* pRadioButton);
	virtual void						  RemoveRadioButton(XUIRadioButton* pRadioButton);
	virtual void						  RemoveAllRadioButtons();

	xint32								  GetNumberOfRadioButtons() const;
	XUIRadioButton*						  GetRadioButtonByIndex(const int& nIndex) const;

	void								  SetAllowedNoSelection(const xbool& bAllowedNoSelection);
	xbool								  IsAllowedNoSelection() const;

	virtual xbool						  SerilizeSelfXML(XXMLExtendTool& outXmlArchive) override;

protected:
	void								  OnChangedRadioButtonSelect(XUIRadioButton* pRadioButton);
	void								  Deselect();

	XArray<XUIRadioButton*>				  m_vRadioButtons;
	XUIRadioButtonGroupCallback			  m_RadioButtonGroupEventCallBack;

	XUIRadioButton*						  m_pSelectedRadioButton;
	xbool								  m_bAllowedNoSelection;
};


#endif
