//
//  XESModuleTriggerFace.h
//  XEScene
//
//  Created by momo783 on 07/03/2018.
//

#ifndef XESMODULETRIGGERFACE_H_
#define XESMODULETRIGGERFACE_H_

#include "filter/modules/XESModuleTrigger.h"

class XEActor;

XESCENE_NAMESPACE_BEGIN

class Face;
class World;
class FaceEventListener;

class ModuleTriggerFace : public ModuleTrigger {
    
public:
    enum FaceType {
        MOUSE,
        EYE,
        ATTITUDE,
        ALL
    };
    
    enum TriggerState {
        NONE,
        READY,
        GO
    };
    
    TriggerState m_CurState;
    
    static  const XString   MODULE_TYPENAME;
    virtual const XString&  GetTypeName() const override { return MODULE_TYPENAME; }
    
public:
    ModuleTriggerFace(XEActor* pActor, FaceType eType);
    virtual ~ModuleTriggerFace() override;
    
    X_INLINE FaceType GetFaceType() const { return m_eFaceType; }
    
    virtual void Update(const Face* mFace) {};
    
    typedef std::function<void(XEActor*, const XArray<Face*>&, xbool)> FaceTriggerCallBack;
    typedef std::function<void(XEActor*, const Face*, TriggerState)> TriggerCallBack;
    
    FaceTriggerCallBack OnFaceCallBack;
    TriggerCallBack     OnTriggerCallback;
    
    void SetCallBackSkipTime(xint32 nSkipTimes);
    
protected:
    
    FaceType m_eFaceType;
    FaceEventListener *m_pFaceEventListener;
    
    xint32   m_nSkipTimes;
    xint32   m_nCallTimes;
    
};

/**
 *  张嘴闭嘴触发模块 
 */
class ModuleTriggerFaceMouse : public ModuleTriggerFace {
    
public:
    ModuleTriggerFaceMouse(XEActor* pActor);
    
    static  const XString   MODULE_TYPENAME;
    virtual const XString&  GetTypeName() const override { return MODULE_TYPENAME; }
    
public:
    
    XString m_TriggerTime; // close || open || close_ray
    
    virtual void Update(const Face* mFace) override;
    
    xbool m_bPause;
    
};

/*
 * 眨眼触发模块 （ray触发）
 */
class ModuleTriggerFaceEye : public ModuleTriggerFace {
    
public:
    ModuleTriggerFaceEye(XEActor* pActor);
    
    static  const XString   MODULE_TYPENAME;
    virtual const XString&  GetTypeName() const override { return MODULE_TYPENAME; }
    
public:
    
    XString m_TriggerTime;
    
    virtual void Update(const Face* mFace) override;
    
};

/**
 * 姿态触发模块（摇头，点头）
 */
class ModuleTriggerFaceAttitude : public ModuleTriggerFace {
    
public:
    
    ModuleTriggerFaceAttitude(XEActor* pActor);
    
    static  const XString   MODULE_TYPENAME;
    virtual const XString&  GetTypeName() const override { return MODULE_TYPENAME; }
    
public:
    
    virtual void Update(const Face* mFace) override;
    
    void SetTriggerTime(const XString& strTriggerTime);
    
protected:
    
    XString m_TriggerTime;
    
    XArray<xfloat32> attitudeValues;
    
    enum ValueType {
        NONE,
        UP,
        DOWN
    };
    
    ValueType m_valueType;
    xfloat32  m_startAttitudeValue;
    
    xfloat32  m_limitAttitudeValue;
    
};


XESCENE_NAMESPACE_END

#endif /* XESMODULETRIGGERFACE_H_ */
