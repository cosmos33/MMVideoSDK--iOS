#ifndef _XUICHATVIEW_H_
#define _XUICHATVIEW_H_

#include "XUIListView.h"


class XUIRichText;
class XUIImage;
class XUIChatView : public XUIListView
{
public:
	X_CLASS_DEF(XUIChatView)

	class XUIChatViewItem : public XUIWidget
	{
	public:
		friend class XUIChatView;

		XUIChatViewItem();
		virtual ~XUIChatViewItem();

		static XUIChatViewItem*								Create();
		static XUIChatViewItem*								Create(const XString& strBackgroundTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);


		void												SetRichText(const XString& strString);
		XString												GetRichText() const;

		void												LoadBackgroundTexture(const XString& strBackgroundTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);

		virtual void										SetContentSize(const XVECTOR2& vContentSize);

	protected:
		virtual xbool										Init() override;
		virtual xbool										Init(const XString& strBackgroundTexture, TextureResType eTextureType = TextureResType::XUI_LOCAL);

		void												InitProtectedChild();

	protected:
		XUIRichText*										m_pRichText;
		XUIImage*											m_pBackgroundImage;

		XString												m_strRichText;

		XVECTOR2											m_vBorder;

	};



public:

	XUIChatView();
	static XUIChatView*							Create();


	void										InsertMessage(const XString& strMseeage);

	void										SetItemBackgroundTexture(const XString& strItemBgTexture);

	void										SetScrollTime(const xfloat32& fScrollTime);
	xfloat32									GetScrollTime() const {	return m_fScrollTime; }

	void										SetMaxMessageNum(const xint32& nMaxMessageNum);
	xint32										GetMaxMessageNum() const { return m_nMaxMessageNum; }

protected:
	xbool										Init() override;




private:
	xfloat32									m_nItemHeight;
	XString										m_strItemBackground;

	XArray<XUIChatViewItem*>					m_vItems;
	xfloat32									m_fScrollTime;

	xint32										m_nMaxMessageNum;
};



#endif
