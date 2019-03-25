/******************************************************************************

@File         XEProperty.h

@Version       1.0

@Created      2017, 9, 27

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/


#ifndef _XE_PROPERTY_H_
#define _XE_PROPERTY_H_

#include "XTypes.h"
#include "XMath3D.h"
#include "XString.h"
#include "XBase3DTypes.h"
#include "XArray.h"
#include "XHashTable.h"
#include "XEVariant.h"
#if X_PLATFORM_WIN_DESKTOP
#include "rapidjson/document.h"
#endif

#define P_FLOAT_MAX  9000000.0f
#define P_INT_MAX	0x7fffffff
#define P_UINT_MAX	0xffffffff

class XEProperty;
class XEPropertyTree;
typedef XArray<XEProperty*> XEPropertyList;
class XEProperty
{
	friend class XEPropertyTree;
public:
	enum EProperType	{ PNT_NODE = 0, PNT_VALUE };
	//callback function to notify the widgets.
	typedef void(*lpFuncUpdateWidget)(XEProperty* pPropertyData, void* pWidgetPtr);
	struct SUpdateWidgetData
	{
		mutable lpFuncUpdateWidget lpFunc;
		mutable void* pWidgetPtr;
	};
public:
										XEProperty();
										XEProperty(XEPropertyTree *pTree, const xchar *szName = "", xint32 nIndex = 0, const xchar* szExt = "");
	virtual								~XEProperty();

	virtual	EProperType					GetPropertyType() const { return PNT_NODE; }
	inline XEPropertyTree*				GetTree() { return m_pTree; }
	inline const XEPropertyTree*		GetTree()const { return m_pTree; }

	const XEProperty*					GetParent() const { return m_pParent; }
	const XEPropertyList&				GetChilds() const { return m_ChildProperty; }
	XEPropertyList&						GetChilds() { return m_ChildProperty; }
	const XEProperty*                   GetChildByIndex(const xint32 nIndex) const;
	SUpdateWidgetData&                  GetUpdateWidgetData(){ return m_updateWidgetData; }
	const SUpdateWidgetData&            GetUpdateWidgetData() const{ return m_updateWidgetData; }

	inline void							SetName(const xchar *szName) { m_strName = szName; }
	inline const XString&				GetName() const { return m_strName; }

	inline void							SetIndex(xint32 nIndex) { m_nIndex = nIndex; }
	inline xint32						GetIndex() const { return m_nIndex; }

	inline void                         SetUserData(const XEVariant& data){ m_UserData = data; }
	inline const XEVariant&             GetUserData() const{ return m_UserData; }

	//ZSX
	inline void							SetExt(const xchar* szExt){ m_strExt = szExt; }
	inline const XString&				GetExt()const{ return m_strExt; }
protected:

	void								AddChild(XEProperty *pChild);
	void								RemoveChild(XEProperty *pChild);

	XString								m_strName;
	xint32								m_nIndex;

	XEProperty							*m_pParent;
	XEPropertyList						m_ChildProperty;
	XEPropertyTree						*m_pTree;
	
	//callback data for updating widgets.
	SUpdateWidgetData                   m_updateWidgetData;
	//user data.
	XEVariant                           m_UserData;
	//ZSX
	XString								m_strExt;
};


#define PRO_SET_VALUE(F, V, VF, WTP)  inline void Set##F(V Value) { m_Value.Set##VF(Value); m_eWidgetType = WTP;}	
#define PRO_SET_VALUE_CONST(F, V, VF, WTP)  inline void Set##F(const V &Value) { m_Value.Set##VF(Value); m_eWidgetType = WTP;}	
#define PRO_GET_VALUE(F, V, VF)  inline V Get##F() const { return m_Value.Get##VF(); }	
#define PRO_GET_VALUE_CONST(F, V, VF)  inline const V& Get##F() const { return m_Value.Get##VF(); }	
#define PRO_SET_GET_VALUE(F, V, VF, WTP) \
	PRO_SET_VALUE(F, V, VF, WTP) \
	PRO_GET_VALUE(F, V, VF)	
#define PRO_SET_GET_VALUE_CONST(F, V, VF, WTP) \
	PRO_SET_VALUE_CONST(F, V, VF, WTP) \
	PRO_GET_VALUE_CONST(F, V, VF)

class XEValueProperty : public XEProperty
{
	friend class XEPropertyTree;
public:
	enum EWidgetType {
		XWT_NONE,
		XWT_FLOAT,
		XWT_VECTOR2,
		XWT_VECTOR3,
		XWT_VECTOR3_FULL,
		XWT_VECTOR4,
		XWT_COLORRGB,
		XWT_COLORRGBA,
		XWT_BOOL,
		XWT_INT,
		XWT_INTBUTTON_ADD_DEL,
		XWT_STRING,
		XWT_DESCVALUE,
		XWT_TEXTURE,
		XWT_PARTICLE,
		XWT_SKINMODEL,
		XWT_COMBOBOXSTR,
		XWT_COMBOBOXSTR_WITH_REMOVE,
		XWT_OPTIONALSTR,
		XWT_SINGLE_PUSH_BUTTON,
		XWT_SHORTCUT_CUSTOMIZATION,
		XWT_AUTO_SUFFIX_ASSET,//auto build asset by the suffix.
		XWT_PATH,
		XWT_CLOTH,
		XWT_LONG_TEXT,
		XWT_SLIDER,
//		XWT_PHYSICAL_ASSET
		XWT_TRANSFORM_SCALE,  //with a scale lock.
		XWT_PATH_CANDEL,
		XWT_BUTTON_WITHICON,
		XWT_DROP_POINTER,
		XWT_SOUND, 
		XWT_ACTOR_VISIBLE_EVENT_DATA, //for trigger
		XWT_9SLICE,
		XWT_PLAY_ANIMATION_EVENT_DATA, //for trigger
	};

	enum EWidgetRequestCode{
		XWRC_CURVE_SETTING,
		XWRC_BUTTON_ADD,//format: "[PT]|btn1|btn2|btn3|...", btn can be img path or button text.
		XWRC_FILE_PATH_SELECT_FBSU,//1 edit box, File path edit box, 3 buttons: browser, search, use
		//to be added.
	};

	/**
	* Potential results from accessing the values of properties
	*/
	enum EPropertyAccessType
	{
		/** Multiple values were found so the value could not be read */
		EPA_MULTIPLE_VALUES,
		/** Failed to set or get the value */
		EPA_FAIL,
		/** Successfully set the got the value */
		EPA_SUCCESS
	};
public:		
										XEValueProperty();
	virtual								~XEValueProperty();

	virtual	EProperType					GetPropertyType() const { return PNT_VALUE; }
	inline EWidgetType					GetWidgetType() const { return m_eWidgetType; }

	inline void							SetDescInfo(const xchar *szDesc) { m_strDesc = szDesc; }
	inline const XString&				GetDescInfo() const { return m_strDesc; }
	inline void							SetEnabled(xbool bEnable) { m_bEnabled = bEnable; }
	inline xbool						IsEnabled() const { return m_bEnabled; }
	inline void                         SetEditable(xbool bEditable){ m_bEdiabled = bEditable; }
	inline xbool                        IsEditabled()const{ return m_bEdiabled; }
	inline void							SetVisible(xbool bVisible) { m_bVisible = bVisible; }
	inline xbool						GetVisible() const { return m_bVisible; }

	inline void							SetMax(xfloat32 fMax) { m_fMax = fMax; }
	inline xfloat32						GetMax() const { return m_fMax; }
	inline void							SetMin(xfloat32 fMin) { m_fMin = fMin; }
	inline xfloat32						GetMin() const { return m_fMin; }	
	inline void							SetStep(xfloat32 fStep) { m_fStep = fStep; }
	inline xfloat32						GetStep() const { return m_fStep; }

	inline XEVariant&					GetValue() { return m_Value; }
	inline const XEVariant&				GetValue() const { return m_Value; }
	inline const XArray<XEVariant>&     GetDataContainer() const { return m_vDataContainer; }
	inline const xbool                  SetDataItem(int nIndex, const XEVariant& val){ if (nIndex < m_vDataContainer.Num()) { m_vDataContainer[nIndex] = val; return xtrue; } else { return xfalse; } }
	
										PRO_SET_GET_VALUE(Float, xfloat32, Float, XWT_FLOAT);
										PRO_SET_GET_VALUE(Slider, xfloat32, Float, XWT_SLIDER);
										PRO_SET_GET_VALUE(VECTOR2, XVECTOR2, VECTOR2, XWT_VECTOR2);
										PRO_SET_GET_VALUE(VECTOR3, XVECTOR3, VECTOR3, XWT_VECTOR3);
										PRO_SET_GET_VALUE(VECTOR3Full, XVECTOR3, VECTOR3, XWT_VECTOR3_FULL);
										PRO_SET_GET_VALUE(VECTOR4, XVECTOR4, VECTOR4, XWT_VECTOR4);
										PRO_SET_GET_VALUE(COLORGBASE, XCOLORBASE, COLORGBASE, XWT_COLORRGBA);
										PRO_SET_GET_VALUE(Bool, xbool, Bool, XWT_BOOL);
										PRO_SET_GET_VALUE(Int, xint32, Int, XWT_INT);
										PRO_SET_GET_VALUE(IntButtonAddDel, xint32, Int, XWT_INTBUTTON_ADD_DEL);
										PRO_SET_GET_VALUE(SinglePushButton, xint32, Int, XWT_SINGLE_PUSH_BUTTON);//single button.
										PRO_SET_GET_VALUE_CONST(ShortcutCustomization,XString,String,XWT_SHORTCUT_CUSTOMIZATION)//customization.
										PRO_SET_GET_VALUE_CONST(String, XString, String, XWT_STRING);
										PRO_SET_GET_VALUE_CONST(DescValue, XString, String, XWT_DESCVALUE);
										PRO_SET_GET_VALUE_CONST(Texture, XString, String, XWT_TEXTURE);
										PRO_SET_GET_VALUE_CONST(Particle, XString, String, XWT_PARTICLE);
										PRO_SET_GET_VALUE_CONST(SkinModel, XString, String, XWT_SKINMODEL);
										PRO_SET_GET_VALUE_CONST(AutoSuffixAsset, XString, String, XWT_AUTO_SUFFIX_ASSET);
										PRO_SET_GET_VALUE_CONST(ClothName, XString, String, XWT_CLOTH);
// 										PRO_SET_GET_VALUE_CONST(PhysicalAsset, XString, String, XWT_PHYSICAL_ASSET);
										PRO_SET_GET_VALUE_CONST(AssetPath, XString, String, XWT_PATH);
										PRO_SET_GET_VALUE_CONST(CanDelAssetPath, XString, String, XWT_PATH_CANDEL);
										PRO_SET_GET_VALUE_CONST(LongText, XString, String, XWT_LONG_TEXT);
										PRO_SET_GET_VALUE_CONST(Sound, XString, String, XWT_SOUND);
										PRO_SET_GET_VALUE_CONST(PlayAnimationEventData, XString, String, XWT_PLAY_ANIMATION_EVENT_DATA);
										PRO_SET_GET_VALUE(TransformScale, XVECTOR3, VECTOR3, XWT_TRANSFORM_SCALE); 
										PRO_SET_GET_VALUE(ButtonWithIcon, xbool, Bool, XWT_BUTTON_WITHICON);
										PRO_SET_GET_VALUE(ActorVisibleEventData, xbool, Bool, XWT_ACTOR_VISIBLE_EVENT_DATA);
										PRO_SET_GET_VALUE(9Slice, XVECTOR4, VECTOR4, XWT_9SLICE);
									
	
	inline void							SetCOLORGB(xfloat32 r, xfloat32 g, xfloat32 b) { m_Value.SetColor(r, g, b); m_eWidgetType = XWT_COLORRGB; }
	inline void							GetCOLORGB(xfloat32 &r, xfloat32 &g, xfloat32 &b) const { m_Value.GetColor(r, g, b);}

	void								SetComboBoxStr(xint32 nCurSelect, const XArray<XString> &vSelectStr, bool bWithRemoveButton = false);
	void								SetComboBoxStr(xint32 nCurSelect, const XString *pSelectStr, xint32 nNum, bool bWithRemoveButton = false);
	void								SetComboBoxStrSelect(xint32 nCurSelect, bool bWithRemoveButton = false);
	xint32						        GetComboBoxStrSelect(bool bWithRemoveButton = false) const;
	XString                             GetComboBoxStr() const;

	void								Set9SliceSpritePath(const XString& strSpritePath);

	void								SetOptionalStr(xint32 nCurSelect, const XArray<XString> &vSelectStr);
	void								SetOptionalStr(xint32 nCurSelect, const XString *pSelectStr, xint32 nNum);
	void								SetOptionalStrSelect(xint32 nCurSelect);
	inline xint32						GetOptionalStrSelect() const { ASSERT(XWT_OPTIONALSTR == m_eWidgetType); return m_Value.GetInt(); }
	

	xbool								SetVariant(const XEVariant &Value, EWidgetType type);
	static xbool						ValidVariantOfType(const XEVariant &Value, EWidgetType type);

	void								SetPropertyAccessType(EPropertyAccessType eType){ m_ePropertyAccessType = eType; }
	EPropertyAccessType					GetPropertyAccessType(){ return m_ePropertyAccessType; }
	const EPropertyAccessType			GetPropertyAccessType() const { return m_ePropertyAccessType; }

	xint32                              AddRequest(xint32 nRequestCode, const XEVariant& data);//return 0 if successes.
	xint32                              SetResponse(xint32 nRequestCode, const XEVariant& data);//return 0 if successes.
	XEVariant*                          GetResponse(xint32 nRequestCode);
	const XEVariant*                    GetResponse(xint32 nRequestCode) const;
	xbool                               RemoveResponse(xint32 nRequestCode);
	XEVariant*                          GetRequestData(xint32 nRequestCode);
	const XEVariant*                    GetRequestData(xint32 nRequestCode) const;

protected:
										XEValueProperty(XEPropertyTree *pTree, const xchar *szName = "", xint32 nIndex = 0,
											const xchar *szDesc = "", xbool bEnable = xtrue, xbool bEditable = xtrue, xbool bVisible = xtrue,
											xfloat32 fMax = P_FLOAT_MAX, xfloat32 fMin = -P_FLOAT_MAX, xfloat32 fStep = 0.1f);
	
	XString								m_strDesc;
	xbool								m_bEnabled;
	xbool                               m_bEdiabled;
	xbool								m_bVisible;
	EWidgetType							m_eWidgetType;
	EPropertyAccessType					m_ePropertyAccessType;


	xfloat32							m_fMax;
	xfloat32							m_fMin;
	xfloat32							m_fStep;

	XEVariant							m_Value;
	XArray<XEVariant>				    m_vDataContainer;

	XHashTable<xint32, XEVariant>       m_mRequestData;//for request-responding. higher 32bits for request, lower for response.
	XHashTable<xint32, XEVariant>       m_mRespondsData;//match to the request code.
};

class XEPropertyTree
{
public:
	enum { ROOT_INDEX = 0, USER_PROPRETY_INDEX };

public:
										XEPropertyTree();	
	virtual								~XEPropertyTree();

	XEValueProperty*					ModifyRoot(const xchar *szName, xint32 nIndex,
		const xchar *szDesc = "", xbool bEnable = xtrue, xbool bEditable = xfalse, xbool bVisible = xtrue,
		xfloat32 fMax = P_FLOAT_MAX, xfloat32 fMin = -P_FLOAT_MAX, xfloat32 fStep = 0.1f);

	XEProperty*							CreateNodeProperty(XEProperty *pParent, const xchar *szName, xint32 nIndex);

	XEValueProperty*					CreateValueProperty(XEProperty *pParent, const xchar *szName, xint32 nIndex, 
											const xchar *szDesc = "", xbool bEnable = xtrue, xbool bEditable = xfalse, xbool bVisible = xtrue,
											xfloat32 fMax = P_FLOAT_MAX, xfloat32 fMin = -P_FLOAT_MAX, xfloat32 fStep = 0.1f);

	XEValueProperty*					CreateValueProperty(XEProperty *pParent, const xchar *szName, xint32 nIndex, const XEVariant &Value, XEValueProperty::EWidgetType type,
											const xchar *szDesc = "", xbool bEnable = xtrue, xbool bEditable = xfalse, xbool bVisible = xtrue,
											xfloat32 fMax = P_FLOAT_MAX, xfloat32 fMin = -P_FLOAT_MAX, xfloat32 fStep = 0.1f);

	XEValueProperty*					CreateValueProperty(XEProperty *pParent, const xchar *szName, xint32 nIndex,
		xint32 nPropertyAccessType, const xchar *szDesc = "",
		xbool bEnable = xtrue, xbool bEditable = xfalse, xbool bVisible = xtrue,
		xfloat32 fMax = P_FLOAT_MAX, xfloat32 fMin = -P_FLOAT_MAX, xfloat32 fStep = 0.1f);


	XEProperty*                         GetNode(xint32 nIndex);
	const XEProperty*					GetRoot() const { return m_pRoot; }
	void								SetRootName(const xchar* szName);
	inline void							SetTreeName(const xchar* szName){ m_Name = szName; };
	inline XString						GetTreeName()const{ return m_Name; }
	void								Clear();
	void								GetAllProperty(XArray<XEProperty*>& aPropertys);
#if X_PLATFORM_WIN_DESKTOP
	void                                GetTreeNodeJsonDesc(rapidjson::Document& doc, XEProperty* pNode = NULL);
#endif

protected:

	typedef XHashTable<xint32, XEProperty*> PropertyHashMap;
	PropertyHashMap						m_mProperties;
	XEProperty*							m_pRoot;
	XString								m_Name;

};


class XEPropertyObject
{
public:
	enum PropertyShowType{ PST_NORMAl};
	struct CacheRefreshData
	{
		enum CacheType{ CRD_REFRESH_VALUE, CRD_REFRESH_TREE, CRD_REFRESH_ALL };
		XEPropertyObject *pObject;
		int nIndex;
		int nFilters;
		bool bWaiting;//if waiting is true, means waiting to be refreshed.
		CacheType eType;
		CacheRefreshData() :pObject(NULL), nIndex(0), nFilters(-1), bWaiting(false), eType(CRD_REFRESH_VALUE){}
	};

	class Listener
	{
	public:
		virtual			~Listener() {}
		virtual	void	                Ls_PropertyRefrshValue(XEPropertyObject *pObject, int nIndex, int nFilters){}
		virtual XEPropertyTree*	        Ls_PropertyTreeRefresh(XEPropertyObject *pObject, int nFilters){ return NULL; }
		virtual void	                Ls_PropertyRefreshAll(){}
		virtual void	                Ls_PropertyTreeClear(int nFilters){}
		virtual void                    Ls_PropertyRefreshCache(const CacheRefreshData& crd, int nCacheTime = 500){}
		virtual void                    Ls_PropertyChangeBeing(XEPropertyObject *pObject, const XEProperty &Node, int nFilters){}
		virtual void                    Ls_PropertyChangeEnd(XEPropertyObject *pObject, const XEProperty &Node, int nFilters){}
	};
	void								AddListener(Listener *pListener);
	void								RemoveListener(Listener *pListener);
	void								PropertyRefrshValue(int nIndex, int nFilters = 0xFFFFFFFF);
	void								PropertyRefreshAll();
	XEPropertyTree*						PropertyTreeRefresh(int nFilters = 0xFFFFFFFF);
	void								PropertyTreeClear(int nFilters = 0xFFFFFFFF);
	void                                PropertyRefreshCache(const CacheRefreshData& crd, int nCacheTime = 500);
	XArray<Listener*>			     	m_vListener;
public:

										XEPropertyObject();
	virtual								~XEPropertyObject();

	virtual xbool						GetPropertyTree(xint32 nFilter, XEPropertyTree &PropTree) { return xtrue; }
	virtual	xbool						SetPropertyValue(const XEProperty &Node,xbool bNotifyPropertyChanged = xtrue) { return xtrue; }
	virtual	xbool						GetPropertyValue(XEProperty&Node) { return xtrue; }
	virtual xbool						IsEqualPropertyValue(void* pSourceHandleObject, void* pDestHandleObject, XEProperty& Node){ return xfalse; }
	inline void							SetFilter(xint32 nFilter) { m_nFilter = nFilter; }
	inline xint32						GetFilter() const { return m_nFilter; }
	inline void                         SetTypeName(const XString& name){ m_strTypeName = name; }
	inline XString                      GetTypeName()const { return m_strTypeName; }

	xbool                               IsAttrExpand(int nNodeIndex);
	void                                SetAttrExpand(int nNodeIndex, xbool bExpand);


protected:
	void                                OnPropertyChangeBegin(const XEProperty &Node, int nFilters = 0xFFFFFFFF);
	void                                OnPropertyChangeEnd(const XEProperty &Node, int nFilters = 0xFFFFFFFF);
protected:
	xint32								m_nFilter;
	XString                             m_strTypeName;
	XHashTable<xint32,xbool>            m_mapAttrExpand;//expand-node-status
	
};


struct XEPropertyObjectSet
{
										XEPropertyObjectSet(){}
	virtual								~XEPropertyObjectSet(){}
	XArray<XEPropertyObject*>		    m_vObject;
};

#if X_PLATFORM_WIN_DESKTOP
extern const XString c_szPropertyCollcetPath;
#endif

#endif


