#ifndef _XUINODE_H_H_
#define _XUINODE_H_H_

#include "XArray.h"
#include "XMath3D.h"
#include "XXMLExtendTool.h"
#include "XUIGeometry.h"
#include <functional>
#include "XRefCount.h"
#include "XClass.h"
class XUIEventDispatcher;
class IXWorld;
class XUIAction;
class XUIScene;

//#define XESS_CLASSNAME(__CLASS_NAME__) \
//        virtual const char* GetClassName() const override{ \
//    return #__CLASS_NAME__; \
//}

class XUINode : public XRefCount, public XMemBase, public XClass
{ 
public:
//	virtual const char* GetClassName() const
//	{
//		return "XUINode";
//	}
    X_CLASS_DEF(XUINode);
    
	static XUINode*					Create();	
	XUINode();
	virtual ~XUINode();	
	
	virtual XUINode*				GetParent() { return m_pParent; }
	virtual const XUINode*			GetParent() const { return m_pParent; }
	virtual void					RemoveFromParent(xbool bClean = xtrue);
	virtual void					RemoveAllChildren(xbool bClean = xtrue);
	virtual XUINode*				GetAllChildByNameRecrusive(const XString& strChild)const;
	virtual XUINode*				GetAllChildByGUIDRecrusive(xuint32 unGUID)const;
	
	// child
	virtual void					AddChild(XUINode* pChild);
	virtual xint32					GetChildrenNum()const{ return m_aChildren.Num(); }
	virtual XArray<XUINode*>&		GetChildren(){ return m_aChildren; }
	virtual const XArray<XUINode*>& GetChildren() const { return m_aChildren; }
	virtual XUINode*				GetChildByName(const XString& strChild)const;
	virtual XUINode*				GetChildByNameRecrusive(const XString& strChild)const;
	virtual XUINode*				GetChildByGUIDRecrusive(xuint32 unGUID)const;
	virtual void					RemoveChild(XUINode* pChild, xbool bClean = xtrue);	
	virtual void					SortChildren();
	
	// protected child
	virtual void					AddProtectedChild(XUINode* pChild);
	virtual xint32					GetProtectedChildrenNum()const{ return m_aProtectedChildren.Num(); }
	virtual XArray<XUINode*>&		GetProtectedChildren(){ return m_aProtectedChildren; }
	virtual const XArray<XUINode*>& GetProtectedChildren() const { return m_aProtectedChildren; }
	virtual XUINode*				GetProtectedChildByName(const XString& strChild)const;
	virtual XUINode*				GetProtectedChildByNameRecrusive(const XString& strChild)const;
	virtual XUINode*				GetProtectedChildByGUIDRecrusive(xuint32 unGUID)const;
	virtual void					RemoveProtectedChild(XUINode* pChild, xbool bClean = xtrue);
	virtual void					SortProtectedChildren();

	static XString					MakeProtectedName(const XString& strName);

	XUINode*						Clone();
	virtual xbool					IsProtected()const{ return m_bProtected; }
	virtual const XString&			GetTypeString()const{ return m_strType; }
	virtual XUIScene*				GetScene();
	xuint32							GetGUID()const{ return m_unGUID; }
	virtual const XString&			GetName() const{ return m_strName; }
	virtual void					SetName(const XString& strName){ m_strName = strName; }
	virtual void					SetLocalZOrder(xint32 nLocalZOrder);
	virtual xint32					GetLocalZOrder() const { return m_nLocalZOrder; }
	virtual void					SetGlobalZOrder(xfloat32 fGlobalZOrder);
	virtual xfloat32				GetGlobalZOrder() const { return m_fGlobalZOrder; }
	virtual void					SetScaleX(xfloat32 fScaleX);
	virtual xfloat32				GetScaleX() const{ return m_vScale.x; }
	virtual void					SetScaleY(xfloat32 fScaleY);
	virtual xfloat32				GetScaleY() const{ return m_vScale.y; }
	virtual void					SetScale(xfloat32 fScaleX, xfloat32 fScaleY);	
	virtual void					SetScale(const XVECTOR2& vScale);
	virtual const XVECTOR2&			GetScale()const{ return m_vScale; }
	virtual void					SetPositionX(xfloat32 x);
	virtual xfloat32				GetPositionX(void) const{ return m_vPosition.x; }
	virtual void					SetPositionY(xfloat32 y);
	virtual xfloat32				GetPositionY(void) const{ return m_vPosition.y; }
	virtual void					SetPosition(xfloat32 x, xfloat32 y);
	virtual void					SetPosition(const XVECTOR2& vPos);
	virtual const XVECTOR2&			GetPosition() const{ return m_vPosition; }
	virtual void					SetAnchorPoint(const XVECTOR2& vAnchorPoint);
	virtual const XVECTOR2&			GetAnchorPoint() const{ return m_vAnchorPoint; }
	virtual const XVECTOR2&			GetAnchorPointInPoints() const{ return m_vAnchorPointInPoints; }
	virtual void					SetContentSize(const XVECTOR2& vContentSize);
	virtual void					SetContentSize(xfloat32 fContentX, xfloat32 fContentY);
	virtual const XVECTOR2&			GetContentSize() const{ return m_vContentSize; }
	virtual void					SetContentSizeX(xfloat32 fContentX);
	virtual xfloat32				GetContentSizeX()const{ return m_vContentSize.x; }
	virtual void					SetContentSizeY(xfloat32 fContentY);
	virtual xfloat32				GetContentSizeY()const{ return m_vContentSize.y; }
	virtual void					SetRotation(xfloat32 fRotation);
	virtual xfloat32				GetRotation() const{ return m_fRotation; }
	virtual void					SetVisible(xbool bVisible);
	virtual xbool					IsVisible() const{ return m_bVisible; }

	virtual xbool					IsRunning() const{ return m_bRunning; }
	virtual void					OnEnter();
	virtual void					OnExit();	
	virtual void					Resume(void);
	virtual void					Pause(void);
	virtual void					Cleanup();
	virtual void					RunAction(XUIAction* pAction);
	virtual void					StopAllActions();
	virtual void					StopAction(XUIAction* pAction);

	virtual void					FirstTick();
	virtual void					Tick(xfloat32 fDelta);
	virtual void					Update(xfloat32 fDelta){}
	virtual void					Visit(IXWorld* pWorld, const XMATRIX4& matParentTransform, xuint32 unParentFlags);
	virtual void					Draw(IXWorld* pWorld, xuint32 unParentFlags){}
	
	virtual void					EnableMask(xbool bEnable){ m_bMask = bEnable; }
	virtual xbool					IsMask()const{ return m_bMask; }
	virtual void					SetScreenMask(const XVECTOR2& vPos, const XVECTOR2& vWAxis, const XVECTOR2& vHAxis, xfloat32 fWidth, xfloat32 fHeight);
	virtual void					GetMask(XVECTOR4& vPosAndWH, XVECTOR4& vWHAxis);

	void							SetOnEnterCallback(const std::function<void()>& callback) { m_OnEnterCallback = callback; }
	const std::function<void()>&	GetOnEnterCallback() const { return m_OnEnterCallback; }
	void							SetOnExitCallback(const std::function<void()>& callback) { m_OnExitCallback = callback; }
	const std::function<void()>&	GetOnExitCallback() const { return m_OnExitCallback; }

	// 相对父空间
	virtual XUIRect					GetBoundingBox();
	virtual xfloat32				GetLeftBoundary();
	virtual xfloat32				GetRightBoundary();
	virtual xfloat32				GetTopBoundary();
	virtual xfloat32				GetBottomBoundary();

	virtual void					ForceUpdateTransform();
	virtual const XMATRIX4&			GetLocalToParentTransform();
	virtual XMATRIX4				GetScreenToLocalOriginTransform();
	virtual XMATRIX4				GetLocalOriginToScreenTransform();
	virtual const XMATRIX4&			GetLocalOriginToWorldTransform() const;
	virtual XMATRIX4				GetLocalToScreenTransform();
	virtual const XMATRIX4&			GetLocalToWorldTransform() const;

	virtual void					RefreshLayout();

	// 内部使用
	virtual xbool					SerilizeXML(XXMLExtendTool& outXmlArchive);
	virtual xbool					SerilizeSelfXML(XXMLExtendTool& outXmlArchive);
	virtual xbool					SerilizeChildrenXML(XXMLExtendTool& outXmlArchive);
	virtual xbool					SerilizeBinary(XFileBase* pFile, xbool bLoad);
	virtual xbool					SerilizeEnd();
protected:
	enum 
	{
		XUI_FLAGS_TRANSFORM_DIRTY = (1 << 0),
		XUI_FLAGS_CONTENT_SIZE_DIRTY = (1 << 1),
		XUI_FLAGS_DIRTY_MASK = (XUI_FLAGS_TRANSFORM_DIRTY | XUI_FLAGS_CONTENT_SIZE_DIRTY),
	};
	virtual xbool					Init();
	virtual void					ReorderChild(XUINode* pChild, xint32 nLocalZOrder);
	virtual void					ReorderProtectedChild(XUINode* pChild, xint32 nLocalZOrder);
	virtual void					SetParent(XUINode* pParent);	
	virtual XUINode*				CreateClonedInstance();
	virtual void					CopyProperties(XUINode* pNode);
	virtual void					CopyClonedChildren(XUINode* pNode);
	xuint32							ProcessParentFlags(const XMATRIX4& matParentTransform, xuint32 unParentFlags);
	void							AddChildHelper(XUINode* pChild);
	void							AddProtectedChildHelper(XUINode* pChild);
	static xint32					CompareLocalZ(XUINode* const* A, XUINode* const* B);
	void							UpdateBoundingBox();
protected:
	XString							m_strType;
	XString							m_strName;
	XUINode*						m_pParent;
	XUIScene*						m_pScene;
	xbool							m_bVisible;
	xbool							m_bProtected;
	XArray<XUINode*>				m_aChildren;
	XArray<XUINode*>				m_aProtectedChildren;
	XUIEventDispatcher*				m_pEventDispatcher;
	xbool							m_bRunning;
	xint32							m_nLocalZOrder;
	xfloat32						m_fGlobalZOrder;
	xbool							m_bReorderChildDirty;
	xbool							m_bReorderProtectedChildDirty;

	XVECTOR2						m_vScale;
	XVECTOR2						m_vPosition;
	XVECTOR2						m_vAnchorPointInPoints;
	XVECTOR2						m_vAnchorPoint;
	XVECTOR2						m_vContentSize;
	xbool							m_bContentSizeDirty;
	XMATRIX4						m_matLocalOriginToWorld;	// 左上角到世界的变换矩阵
	XMATRIX4						m_matLocalToWorld;			// 控件中心到世界的变换矩阵
	mutable XMATRIX4				m_matLocalToParent;			// 控件中心到父节点的变换矩阵
	XUIRect							m_BoundingBox;
	xfloat32						m_fRotation;
	mutable xbool					m_bTransformDirty;
	mutable xbool					m_bInverseDirty;
	xbool							m_bTransformUpdated;

	xbool							m_bMask;
	XVECTOR4						m_vPosAndHalfWH;
	XVECTOR4						m_vWHAxis;
	xuint32							m_unGUID;

	xbool							m_bFirstTick;
	xbool							m_bNeedUpdateTransform;
	std::function<void()>			m_OnEnterCallback;
	std::function<void()>			m_OnExitCallback;
	static xint32					m_nAttachedNodeCount;
	friend class					XUIManager;
};

#endif
