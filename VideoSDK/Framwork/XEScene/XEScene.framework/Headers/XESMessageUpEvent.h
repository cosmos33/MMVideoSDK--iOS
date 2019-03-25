//
//  XESMessageUpEvent.h
//  XEScene
//
//  Created by momo783 on 01/04/2018.
//

#ifndef XESMESSAGEUPEVENT_H_
#define XESMESSAGEUPEVENT_H_

#include "message/up/XESMessageUp.h"
#include "core/XESGeometry.h"

XESCENE_NAMESPACE_BEGIN

class MessageUpFace : public MessageUp {
    
public:
    
    static MessageUpFace* Create();
    
    virtual XString JSONString() override;
    
public:
    
    xbool m_bIsEnd;
    
    xint32 m_nExpFlag;
    
    Rect  m_Bounds;
    
    XVECTOR2 m_vMouse;
    XVECTOR2 m_vLeye;
    XVECTOR2 m_vReye;
    XVECTOR2 m_vNose;
    
    
protected:
    
    MessageUpFace();
    virtual ~MessageUpFace() override {};
    virtual void Release() override {};
    virtual xbool Parser(const XString& strMessage) override {return xfalse;};
};

class MessageUpTouch : public MessageUp {
    
public:
    
    static MessageUpTouch* Create();
    
    virtual XString JSONString() override;
    
public:
    
    xbool m_bIsEnd;
    
    XString m_touchName;
    XVECTOR2 m_vTouch;
    
    xfloat32 m_fScale;
    
protected:
    
    MessageUpTouch();
    virtual ~MessageUpTouch() override {};
    virtual void Release() override {};
    virtual xbool Parser(const XString& strMessage) override {return xfalse;};
};

class MessageUpSensor : public MessageUp {
    
public:
    
    static MessageUpSensor* Create();
    
    virtual XString JSONString() override;
    
public:
    
    XString m_sensorName;
    XVECTOR3 m_vSensorValue;
    
protected:
    
    MessageUpSensor();
    virtual ~MessageUpSensor() override {};
    virtual void Release() override {};
    virtual xbool Parser(const XString& strMessage) override {return xfalse;};
};

class MessageUpObject : public MessageUp {
    
public:
    
    static MessageUpObject* Create();
    
    virtual XString JSONString() override;
    
public:
    
    XString m_ObjName;
    Rect m_vObjValue;
    
protected:
    
    MessageUpObject();
    virtual ~MessageUpObject() override {};
    virtual void Release() override {};
    virtual xbool Parser(const XString& strMessage) override {return xfalse;};
};

XESCENE_NAMESPACE_END

#endif /* XESMESSAGEUPEVENT_H_ */
