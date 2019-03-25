/******************************************************************************

@File         XECanvas2DRectangleComponent.h

@Version       1.0

@Created      2017, 9, 30

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/
#ifndef XECANVAS2DRECTANGLECOMPONENT_H
#define XECANVAS2DRECTANGLECOMPONENT_H
#include "XEActorComponent.h"

class XECanvas2DRectangleComponent:public XEActorComponent
{
public:
	XECanvas2DRectangleComponent();
	~XECanvas2DRectangleComponent(){};
public:
	virtual void                 Release() override;
	virtual void                 Render(XEViewport* pViewport) override;
	virtual void                 Deserialize(const XMLElement* pEleComponent) override;
	virtual XMLElement*          Serialize(XMLElement* pEleParent) override;
	xfloat32                     GetXRelative() const;
	xfloat32                     GetYRelative() const;
	xfloat32                     GetWRelative() const;
	xfloat32                     GetHRelative() const;
public:
	XE_COMPONENT_CAST(XECanvas2DRectangleComponent)
	XE_COMPONENT_TYPE_DEF(COMPONENT_TYPENAME)
	X_CLASS_DEF(XECanvas2DRectangleComponent)
	static const XString COMPONENT_TYPENAME;
public:
	xint32                       m_nX;
	xint32                       m_nY;
	xint32                       m_nWidth;
	xint32                       m_nHeight;
	XCOLORBASE                   m_clr;
	xbool                        m_bSolid;
	//relative width and height
	xint32                       m_nRelativeWidth;
	xint32                       m_nRelativeHeight;
};

#endif // XECANVAS2DRECTANGLECOMPONENT_H
