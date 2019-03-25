//
//  XESInstantAction.h
//  XEScene
//
//  Created by momo783 on 09/02/2018.
//

#ifndef XESINSTANTACTION_H_
#define XESINSTANTACTION_H_

#include "core/actions/XESAction.h"

XESCENE_NAMESPACE_BEGIN

class InstantAction : public FiniteTimeAction {
    
public:
    
    virtual InstantAction* Clone() const override {
        XESAssert(0);return nullptr;
    }
    
    virtual InstantAction* Reverse() const override {
        XESAssert(0);return nullptr;
    }
    
    virtual xbool IsDone() override;
    
    virtual void  Tick(xfloat32 fDelta) override;
    
    virtual void  Update(xfloat32 fP) override;
    
};

// Show
class Show : public InstantAction {
    
public:
    static  Show* Create();
    
    virtual Show* Clone() const override;
    
    virtual InstantAction* Reverse() const override;
    
    virtual void Update(xfloat32 fP) override;
    
protected:
    Show() {};
    virtual ~Show() override {};
    virtual void Release() override {};
};

// Hide
class Hide : public InstantAction {
    
public:
    static  Hide* Create();
    
    virtual Hide* Clone() const override;
    
    virtual InstantAction* Reverse() const override;
    
    virtual void Update(xfloat32 fP) override;
    
protected:
    Hide() {};
    virtual ~Hide() override {};
    virtual void Release() override {};
};

// Remove Self
class RemoveSelf : public InstantAction {
    
public:
    static  RemoveSelf* Create();
    
    virtual RemoveSelf* Clone() const override;
    
    virtual RemoveSelf* Reverse() const override;
    
    virtual void Update(xfloat32 fP) override;
    
protected:
    RemoveSelf() {};
    virtual ~RemoveSelf() override {};
    virtual void Release() override {};
};

// Place Actor
class Place : public InstantAction {
    
public:
    static  Place* Create(const XVECTOR3& vPos);
    
    virtual Place* Clone() const override;
    
    virtual Place* Reverse() const override;
    
    virtual void Update(xfloat32 fP) override;
    
protected:
    Place() {};
    virtual ~Place() override {};
    virtual void Release() override {};
    
protected:
    XVECTOR3    m_vPos;
};


XESCENE_NAMESPACE_END

#endif /* XESINSTANTACTION_H_ */
