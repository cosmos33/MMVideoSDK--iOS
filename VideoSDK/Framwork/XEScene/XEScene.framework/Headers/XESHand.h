//
// Created by momo783 on 20/08/2018.
//

#ifndef PODS_XESHAND_H
#define PODS_XESHAND_H

#include "core/XESObject.h"
#include "core/XESGeometry.h"

XESCENE_NAMESPACE_BEGIN

class Hand : public Object {

public:

    struct Gesture {
        XString     m_strType;
        Rect        m_rBounds;
        xfloat32    m_fScore;
    };

    struct Joint {
        xfloat32 m_fScore;
        XVECTOR2 m_vLocation;
        XVECTOR3 m_vLocation3D;
        XVECTOR2 m_vLocation3DTo2D;
    };

    XArray<Gesture> m_arrGestures;

    // Landmarks
    XArray<Joint> m_arrLandmarks;
    // 3D手势自由度
    XArray<xfloat32> m_arrParams;

public:
    Hand();
    virtual ~Hand() override;
    virtual void Release() override;

};

XESCENE_NAMESPACE_END

#endif //PODS_XESHAND_H
