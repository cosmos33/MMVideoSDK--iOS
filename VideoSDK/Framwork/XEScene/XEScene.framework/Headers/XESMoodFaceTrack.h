//
//  XESMoodFaceTrack.h
//  XEScene
//
//  Created by momo783 on 01/07/2018.
//

#ifndef XESMOODFACETRACK_H_
#define XESMOODFACETRACK_H_

#include "core/XESObject.h"
#include "core/XESFace.h"
#include "core/events/XESFaceEventListener.h"
#include "core/events/XESEventDispatcher.h"

class XEActor;

XESCENE_NAMESPACE_BEGIN

class MoodFaceTrack : public Object {
    
public:

    MoodFaceTrack(XEActor* pActor);
    
    virtual ~MoodFaceTrack() override;
    virtual void Release() override;

    X_INLINE XEActor* GetTarget() const { return m_pActor; }

    void Update(Face *pFace);
    
    XMATRIX4 LowPassFilter(XMATRIX4& mat, xfloat32 fRate);
    
    XMATRIX4 MeanValueFilter(XArray<Face*> faces);

public:
    typedef std::function<void(XEActor*, const Face*, xbool)> MoodFaceTrackCallBack;
    MoodFaceTrackCallBack OnFaceTrackCallBack;
    
protected:
    void ClearFaces();
    
protected:
    
    XEActor*    m_pActor;
    FaceEventListener *m_pFaceEventListener;
    
    xint32 m_nCacheNum;
    XArray<Face* > m_CacheFaces;
    XArray<Face* > m_DelayFaces;

    xint32 m_nDelayFrames;
    
    XMATRIX4 m_LastModelViewMat;

};

XESCENE_NAMESPACE_END

#endif /* XESMOODFACETRACK_H_ */
