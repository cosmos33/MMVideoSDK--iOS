//
//  XESFaceEvent.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESFACEEVENT_H_
#define XESFACEEVENT_H_

#include "core/events/XESEvent.h"
#include "core/XESFace.h"

XESCENE_NAMESPACE_BEGIN

class FaceEvent : public Event {
    
public:
    
    enum EventCode {
        NONEFACE,
        TRACKINGFACE
    };
    
    FaceEvent(EventCode nEventCode);
    
    virtual ~FaceEvent() override;
    virtual void Release() override;
    
    X_INLINE EventCode GetEventCode() const { return m_nEventCode; }
    X_INLINE XArray<Face*> GetFaces() const { return m_aFaces; }
    
    void  SetFaces(XArray<Face*> aFaces) { m_aFaces = aFaces; };
    
    
protected:
    
    EventCode m_nEventCode;

    XArray<Face*> m_aFaces;
};

XESCENE_NAMESPACE_END

#endif /* XESFACEEVENT_H_ */
