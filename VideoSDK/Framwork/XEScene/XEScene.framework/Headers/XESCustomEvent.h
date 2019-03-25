//
//  XESCustomEvent.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESCUSTOMEVENT_H_
#define XESCUSTOMEVENT_H_

#include "core/events/XESEvent.h"

XESCENE_NAMESPACE_BEGIN

class CustomEvent : public Event {
    
public:
    CustomEvent(const XString& mEventName);
    
    virtual ~CustomEvent() override;
    virtual void Release() override;
    
    X_INLINE  void SetUserData(void *pData) { m_pUserData = pData; }
    X_INLINE  void* GetUserData() const { return m_pUserData; }
    
    X_INLINE  const XString& GetEventName() const { return m_EventName; }
    
protected:
    
    void* m_pUserData;
    
    XString m_EventName;
};

XESCENE_NAMESPACE_END

#endif /* XESCUSTOMEVENT_H_ */
