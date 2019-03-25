//
//  XESMessageOld.h
//  XEScene
//
//  Created by momo783 on 01/04/2018.
//

#ifndef XESMESSAGEOLD_H_
#define XESMESSAGEOLD_H_

#include "message/down/XESMessageDown.h"

XESCENE_NAMESPACE_BEGIN

class MessageHide : public MessageDown {
    
public:
    
    virtual xbool Parser(const XString& strMessage) override;
    
public:
    
    xbool m_bHide;
    
protected:
    
    MessageHide();
    virtual ~MessageHide() override {};
    virtual void Release() override {};
    
    
    friend class Message;
    
};

class MessagePlace : public MessageDown {
    
public:
    
    virtual xbool Parser(const XString& strMessage) override;
    
public:
    
    XVECTOR3 m_vPosition;
    
protected:
    
    MessagePlace();
    virtual ~MessagePlace() override {};
    virtual void Release() override {};
    
    friend class Message;
};

class MessageRemove : public MessageDown {
    
public:
    
    virtual xbool Parser(const XString& strMessage) override;
    
public:
    
    XVECTOR3 vPosition;
    
protected:
    
    MessageRemove();
    virtual ~MessageRemove() override {};
    virtual void Release() override {};
    
    friend class Message;
};

class MessageScale : public MessageDown {
    
public:
    
    virtual xbool Parser(const XString& strMessage) override;
    
public:
    
    xfloat32 m_fScale;
    xfloat32 m_fDuration;
    
protected:
    
    MessageScale();
    virtual ~MessageScale() override {};
    virtual void Release() override {};
    
    friend class Message;
};

class MessageMove : public MessageDown {
    
public:
    
    virtual xbool Parser(const XString& strMessage) override;
    
public:
    
    Points *m_Points;
    xbool  m_bRepeat;
    xfloat32 m_fDuration;
    
    xbool m_bSpeedControl;
    
protected:
    
    MessageMove();
    virtual ~MessageMove() override {};
    virtual void Release() override {};
    
    friend class Message;
};

class MessageActionSpeed : public MessageDown {
    
public:
    
    virtual xbool Parser(const XString& strMessage) override;
    
public:
    
    xint32 m_nForTag;
    xfloat32 m_fSpeed;
    
protected:
    
    MessageActionSpeed();
    virtual ~MessageActionSpeed() override {};
    virtual void Release() override {};
    
    friend class Message;
};

class MessageActionClear : public MessageDown {
    
public:
    
    virtual xbool Parser(const XString& strMessage) override;
    
public:
    
    xint32 m_nForTag;
    
protected:
    
    MessageActionClear();
    virtual ~MessageActionClear() override {};
    virtual void Release() override {};
    
    friend class Message;
};

XESCENE_NAMESPACE_END

#endif /* XESMESSAGEOLD_H_ */
