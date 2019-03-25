//
//  XESCVAboutEventListener.h
//  XEScene
//
//  Created by momo783 on 06/02/2018.
//

#ifndef XESCVABOUTEVENTLISTENER_H_
#define XESCVABOUTEVENTLISTENER_H_

#include "core/events/XESEventListener.h"

XESCENE_NAMESPACE_BEGIN

class CVBody;
class CVObject;

class CVBodyEventListener : public EventListener {

XESCENE_CONSTRUCTOR_ACCESS:
    CVBodyEventListener();
    XESS_IGNORE xbool Init();
    
public:
    XESS_IGNORE static const ListenerID LISTENER_ID;
    
    static CVBodyEventListener* Create();
    
    virtual ~CVBodyEventListener() override;
    XESS_IGNORE virtual void Release() override;
    
    virtual xbool CheckAvailable() override;
    virtual CVBodyEventListener* Clone() override;
    
public:
    
    typedef std::function<void(const XArray<CVBody*>&, Event*)> CVBodysCallback;
    
    CVBodysCallback   OnBodyLostCallback;
    CVBodysCallback   OnBodyTrackingCallback;
    
private:
    
    friend class EventDispatcher;
};

class CVObjectEventListener : public EventListener {
    
protected:
    CVObjectEventListener();
    XESS_IGNORE xbool Init();
    
public:
    XESS_IGNORE static const ListenerID LISTENER_ID;
    
    static CVObjectEventListener* Create();
    
    virtual ~CVObjectEventListener() override;
    XESS_IGNORE virtual void Release() override;
    
    virtual xbool CheckAvailable() override;
    virtual CVObjectEventListener* Clone() override;
    
public:
    
    typedef std::function<void(const XArray<CVObject*>&, Event*)> CVObjectsCallback;
    
    CVObjectsCallback   OnObjectLostCallback;
    CVObjectsCallback   OnObjectTrackingCallback;
    
private:
    
    friend class EventDispatcher;
};

XESCENE_NAMESPACE_END

#endif /* XESCVABOUTEVENTLISTENER_H_ */
