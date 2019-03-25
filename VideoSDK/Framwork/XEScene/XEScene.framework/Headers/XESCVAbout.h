//
//  XESCVAbout.h
//  XEScene
//
//  Created by momo783 on 13/03/2018.
//

#ifndef XESCVABOUT_H_
#define XESCVABOUT_H_

#include "core/XESObject.h"
#include "core/XESGeometry.h"

XESCENE_NAMESPACE_BEGIN

static const xint32 JointsMaps[14] = {13,0,1,13,3,4,0,6,7,0,9,10,13,12};

class CVBody : public Object {
    
public:
    CVBody() {};
    virtual ~CVBody() override {};
    virtual void Release() override {};
    
public:
    
    struct Joint {
        XVECTOR2 m_Location;
        xfloat32 m_Score;
        XVECTOR3 m_vLocation3D;
        XVECTOR2 m_vLocation3DTo2D;
    };
    
    XArray<Joint> m_joints;
    
};

// "heart"
// "yeah"
// "one"
// "baoquan"
// "five"
// "bainian"
// "zan"

class CVObject : public Object {
    
public:
    CVObject() {};
    virtual ~CVObject() override {};
    virtual void Release() override {};
    
public:
    
    XString     m_Type;
    Rect        m_Bounds;
    xfloat32    m_Score;
};

XESCENE_NAMESPACE_END

#endif /* XESCVABOUT_H_ */
