//
// Created by momo783 on 22/07/2018.
//

#ifndef XES_XESANIMOJIFACETRACK_H
#define XES_XESANIMOJIFACETRACK_H

#include "core/XESFace.h"
#include "core/events/XESFaceEventListener.h"
#include "core/events/XESEventDispatcher.h"

class XEActor;

XESCENE_NAMESPACE_BEGIN

class AnimojiFaceTrack : public Object {

public:

    AnimojiFaceTrack(XEActor* pActor);
    AnimojiFaceTrack(XEActor* pActor, xbool bEnableTrackMode);

    virtual ~AnimojiFaceTrack() override;
    virtual void Release() override;

    void Update(Face *pFace);

    void Tick(xfloat32 fTime);

public:
    typedef std::function<void(XEActor*, const Face*, xbool)> AnimojiFaceTrackCallBack;
    AnimojiFaceTrackCallBack OnFaceTrackCallBack;

    enum FaceTrackMode {
        MODE_NONE,
        MODE_WILL_TRACK,
        MODE_TRACK,
        MODE_TRACK_LOST,
        MODE_RESET
    };

protected:
    
    void ClearFaces();
    
    void SetLastTrackFace(Face* pFace);

    void AddFaceTrackListener();

    void SetTrackMode(FaceTrackMode eTrackMode);
    
    Face* ResetFaceWithLastFace(Face* pLastFace, xfloat32 fScale);
    
    Face* WillTrackFace();

protected:

    XEActor*    m_pActor;
    FaceEventListener *m_pFaceEventListener;

    xbool m_bEnableTrackMode;
    FaceTrackMode m_TrackMode;

    xfloat32 m_fWaitResetTime;

    Face* m_LastTrackFace;
    XArray<Face* > m_WillTrackFaces;

    xint32 m_ResetTickNums;
    
    static xfloat32 gRestWaitTime;
    
    static xint32 gResetTickTimes;
    static xint32 gWillTrackTimes;

};


XESCENE_NAMESPACE_END


#endif //XES_XESANIMOJIFACETRACK_H
