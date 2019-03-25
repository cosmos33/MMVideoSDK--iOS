/******************************************************************************

@File         XEAnimElementModelAnimationModelAnimation.h

@Version       1.0

@Created      2017,12, 22

@HISTORY:

******************************************************************************/
#ifndef XE_ANIM_MON_ELEMENT_MODEL_ANIMATION
#define XE_ANIM_MON_ELEMENT_MODEL_ANIMATION
#include "XEAnimMonElement.h"

class XEAnimMonElementModelAnimation
	:public XEAnimMonElement
{
	friend class XEAnimMonElementModelAnimationIns;
public:
	                                      XEAnimMonElementModelAnimation();
	virtual                              ~XEAnimMonElementModelAnimation();
public:					                 
	virtual void                          Deserialize(const XMLElement* pEleElement, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*                   Serialize(XMLElement* pEleParent)override;
public:
	XE_USER_NODE_CAST(XEAnimMonElementModelAnimation)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
	XString m_strAnimLayerPath;
};

#endif // XE_ANIM_MON_ELEMENT_MODEL_ANIMATION
