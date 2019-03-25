//
//  XESMessageActor.h
//  XEScene
//
//  Created by momo783 on 01/04/2018.
//

#ifndef XESMESSAGEACTOR_H_
#define XESMESSAGEACTOR_H_

#include "message/down/XESMessageDown.h"

XESCENE_NAMESPACE_BEGIN

class MessageDownActor : public MessageDown {
    
public:
    virtual xbool Parser(const XString& strMessage) override;
    
public:
    
    xbool m_bHide;
    XVECTOR3 m_Location;
    XVECTOR3 m_Scale;
    XVECTOR3 m_Rotate;
    XVECTOR3 m_Dir;
    XVECTOR3 m_Up;
    XMATRIX4 m_Mat;
    
protected:
    
    MessageDownActor();
    virtual ~MessageDownActor() override {};
    virtual void Release() override {};
    
    friend class Message;
};

class MessageDownActorModel : public MessageDown {
    
public:
    virtual xbool Parser(const XString& strMessage) override;
    
public:
    
    // 动画控制
    XString m_strAction;
    xint32  m_aniIndex;
    
    // 物理控制
    XVECTOR3 m_phyLinearVelocity;
    XVECTOR3 m_phyAngularVelocity;
    xbool    m_phyEnable;
    
protected:
    
    MessageDownActorModel();
    virtual ~MessageDownActorModel() override {};
    virtual void Release() override {};
    
    friend class Message;
};

class MessageDownActorParticle : public MessageDown {
    
public:
    virtual xbool Parser(const XString& strMessage) override;
    
public:
    // 粒子动画播放
    XString m_strAction;
    
protected:
    
    MessageDownActorParticle();
    virtual ~MessageDownActorParticle() override {};
    virtual void Release() override {};
    
    friend class Message;
};

class MessageDownActorLight : public MessageDown {
    
public:
    virtual xbool Parser(const XString& strMessage) override;
    
public:
    
    xfloat32    m_fIntensity;
    XCOLORBASE  m_LightColor;
    XVECTOR3    m_LightDir;
    
protected:
    
    MessageDownActorLight();
    virtual ~MessageDownActorLight() override {};
    virtual void Release() override {};
    
    friend class Message;
};

class MessageDownActorControl : public MessageDown {
    
public:
    virtual xbool Parser(const XString& strMessage) override;
    
public:
    
    XString m_CloneActorName;
    
protected:
    
    MessageDownActorControl();
    virtual ~MessageDownActorControl() override {};
    virtual void Release() override {};
    
    friend class Message;
};

XESCENE_NAMESPACE_END

#endif /* XESMESSAGEACTOR_H_ */
