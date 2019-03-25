#ifndef _UIACTIONMANAGER_H_
#define _UIACTIONMANAGER_H_

#include "XMemBase.h"
#include "XArray.h"

class XUIAction;
class XUINode;


class IXUIActionManager : public XMemBase
{
public:

	virtual ~IXUIActionManager() {}

	virtual xbool			Init() = 0;
	virtual void			Release() = 0;

	virtual void AddAction(XUIAction* pAction, XUINode* pTargetNode, const xbool& bPaused) = 0;

	virtual void RemoveAllActions() = 0;
	virtual void RemoveAllActionsFromTarget(XUINode* pTargetNode) = 0;
	virtual void RemoveAction(XUIAction* pAction) = 0;

	virtual xint32 GetNumberofRunningActionsInTarget(const XUINode* pTargetNode) = 0;
	virtual xint32 GetNumberOfRunningActions() const = 0;
	
	virtual void PauseTarget(XUINode* pTargetNode) = 0;
	virtual void ResumeTarget(XUINode* pTargetNode) = 0;

	virtual XArray<XUINode*> PauseAllRunningActions() = 0;

	virtual void ResumeTargets(const XArray<XUINode*>& vTargetsToResume) = 0;

	virtual void Tick(const xfloat32& dt) = 0;



protected:
	void ActionStartWithTarget(XUIAction* pAction, XUINode* pTarget);
	void ActionStop(XUIAction* pAction);
	void ActionStep(XUIAction* pAction, const xfloat32& dt);
	xbool ActionIsDone(XUIAction* pAction);
	void ActionUpdate(XUIAction* pAction, const xfloat32& fProgress);
	void DeleteAction(XUIAction* pAction);

};

extern IXUIActionManager* g_pIXUIActionManager;

#endif
