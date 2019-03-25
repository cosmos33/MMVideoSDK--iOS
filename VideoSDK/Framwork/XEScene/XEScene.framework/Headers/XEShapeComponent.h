/******************************************************************************

@File         XEShapeComponent.h

@Version       1.0

@Created      2018, 12, 20 add by yanglj

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XE_SHAPE_COMPONENT_H
#define XE_SHAPE_COMPONENT_H
#include "XEActorComponent.h"

class XEShapeComponent 
	: public XEActorComponent
{
public:
	XEShapeComponent();
	virtual ~XEShapeComponent();

	//XEActorComponent Interface Begin
	virtual void						Render(XEViewport* pViewport) override;
	virtual void						Deserialize(const XMLElement* pEleComponent) override;
	virtual XMLElement*					Serialize(XMLElement* pEleParent) override;
	virtual XCusAABB					GetCusAABB(xfloat32* pfRadius = NULL) const override;
	//XEActorComponent Interface End

	X_FORCEINLINE void					SetShapeColor(const XCOLOR& color){ m_shapeColor = color; }
	X_FORCEINLINE const XCOLOR&			GetShapeColor(){ return m_shapeColor; }
	//X_FORCEINLINE void					SetShapeModify(xbool bModify){ m_bShapeModify = bModify; }
	//X_FORCEINLINE xbool					GetShapeModify(){ return m_bShapeModify; }

	void								TransformAABB(const XMATRIX4& matTrans, XCusAABB& aABB) const;
public:
	XE_COMPONENT_CAST(XEShapeComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XEShapeComponent)
	static const XString COMPONENT_TYPENAME;

protected:
	static const XCOLORBASE				SELECT_COLOR;
	XCOLOR								m_shapeColor;
	//xbool								m_bShapeModify;
	XCusAABB							m_initAABB;
};
#endif