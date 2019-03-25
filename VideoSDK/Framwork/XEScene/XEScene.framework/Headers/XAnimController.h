#ifndef _XANIMCONTROLLER_H_
#define _XANIMCONTROLLER_H_

#include "XMemBase.h"
#include "XString.h"
#include "XAnimMultiLayer.h"
#include "XClass.h"

struct UpdateParam
{
	UpdateParam() : fPrevTime(0.0f), fTime(0.0f){}
    xfloat32        fPrevTime;
    xfloat32        fTime;
};

struct XAnimInstance;
class XXMLExtendTool;

// fix flk public XClass for lua;
class XAnimController : public XMemBase, public XClass
{
public:
	XAnimController(const xchar* szName) : strName(szName), bActive(xtrue){}
    virtual                         ~XAnimController() {}	

									X_CLASS_DEF(XAnimController);   // fix flk for lua
    virtual xuint32                 Type() const = 0;
    virtual void                    Update(const UpdateParam& context, XAnimInstance& InstData) = 0;
    virtual bool                    Serialize(XXMLExtendTool& ar) = 0;
	virtual xfloat32				GetStartTime() const = 0;
	virtual xfloat32				GetEndTime() const = 0;
	const xchar*					GetName() const { return strName.CStr(); };
	xbool							IsActive() const { return bActive; }
	void							SetActive(xbool bSet){ bActive = bSet; }
protected:
	XString							strName;
	xbool							bActive;
};

#endif
