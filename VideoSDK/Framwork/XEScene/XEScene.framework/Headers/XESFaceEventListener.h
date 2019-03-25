//
//  XESFaceEventListener.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESFACEEVENTLISTENER_H_
#define XESFACEEVENTLISTENER_H_

#include "core/events/XESEventListener.h"

XESCENE_NAMESPACE_BEGIN

class Face;

class FaceEventListener : public EventListener {

XESCENE_CONSTRUCTOR_ACCESS:
    FaceEventListener();
    xbool Init();
    
public:
    static const ListenerID LISTENER_ID;
    
    static FaceEventListener* Create();
    
    virtual ~FaceEventListener() override;
    virtual void Release() override;
    
    virtual xbool CheckAvailable() override;
    virtual FaceEventListener* Clone() override;
    
public:
    
    typedef std::function<void(const XArray<Face*>&, Event*)> FacesCallback;
    
    FacesCallback   OnFaceLostCallback;
    FacesCallback   OnFaceTrackingCallback;
    
private:
    
    friend class EventDispatcher;
};

XESCENE_NAMESPACE_END

#endif /* XESFACEEVENTLISTENER_H_ */
