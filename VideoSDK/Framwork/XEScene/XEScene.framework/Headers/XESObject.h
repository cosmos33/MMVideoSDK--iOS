//
//  XEObject.h
//  Pods
//
//  Created by momo783 on 02/02/2018.
//
//

#ifndef XESOBJECT_H_
#define XESOBJECT_H_

#include "core/XESDefine.h"

XESCENE_NAMESPACE_BEGIN

class Object
{
public:
    
    Object();
    virtual ~Object();
    
public:
    /**
     *  Object节点释放
     */
    XESS_IGNORE virtual void Release();
    
};

XESCENE_NAMESPACE_END

#endif /* XESOBJECT_H_ */
