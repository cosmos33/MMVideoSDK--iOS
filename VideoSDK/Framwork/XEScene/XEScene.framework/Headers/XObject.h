/******************************************************************************

 @File         XObject.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  The interface of XObject.

 @HISTORY:

******************************************************************************/
#ifndef _X_OBJECT_H_
#define _X_OBJECT_H_

#include "XMemBase.h"

class IXPrimitiveBase;
class IXWorld;

class IXObject : public XMemBase
{
public:
	virtual						~IXObject() {}
	virtual void				RegisterToScene(IXWorld* pScene) = 0;
	virtual IXPrimitiveBase*	GetPrimitive() = 0;
};
#endif //_X_OBJECT_H_