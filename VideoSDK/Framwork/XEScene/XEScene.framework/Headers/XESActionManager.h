//
//  XESActionManager.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESACTIONMANAGER_H_
#define XESACTIONMANAGER_H_

#include "core/XESObject.h"
#include "core/actions/XESAction.h"

class  XEActor;

XESCENE_NAMESPACE_BEGIN

class Action;
struct _HashElement;

class ActionManager : public Object {
    
public:
    ActionManager();
    
    virtual ~ActionManager() override;
    virtual void Release() override;
    
    static  ActionManager* GetInstance();
    
public:
    
    void    AddAction(Action* pAction, XEActor* pTarget, xbool bPaued);
    
    void    RemoveAction(Action* pAction);
    void    RemoveActionByTag(xint32 nTag, XEActor* pTarget);
    
    void    RemoveAllActions();
    void    RemoveAllActionsByTag(xint32 nTag, XEActor* pTarget);
    void    RemoveAllActionsFromTarget(XEActor* pActor);
    void    RemoveAllActionsByFlags(xuint32 uFlags, XEActor* pTarget);
    
    Action* GetActionByTag(xint32 nTag, const XEActor* pTarget) const;
    
    xint32  GetNumOfRunningActionsInTarget(const XEActor* pTarget) const;
    
    void    PauseTarget(XEActor* pTarget);
    void    ResumeTarget(XEActor* pTarget);
    
public:
    
    void    Tick(xfloat32 fDelta);
    
protected:
    
    void    DeleteHashElement(struct _HashElement *element);
    void    RemoveActionAtIndex(struct _HashElement *element, xint32 nIndex);
    
protected:
    
    struct _HashElement  *m_CurrentTarget;
    
    XHashTable<XEActor*, _HashElement*> m_Targets;
    
    xbool  m_CurrentTargetSalvged;
};

XESCENE_NAMESPACE_END

#endif /* XESACTIONMANAGER_H_ */
