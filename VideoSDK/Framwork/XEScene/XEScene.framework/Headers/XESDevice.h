//
//  XESDevice.h
//  XEngine
//
//  Created by momo783 on 02/02/2018.
//

#ifndef XESDevice_h
#define XESDevice_h

#include "core/XESDefine.h"
#include <stdio.h>

XESCENE_NAMESPACE_BEGIN

class Device : public XMemBase {
    
private:
    Device();
    ~Device();
    
public:
    
#if X_PLATFORM_XOS
    static void SetStaticCallBackQueue(void * queue);
    
#endif
    /**
     * To enable or disable attitude motion.
     */
    static void SetAttitudeEnabled(xbool isEnabled);
    
    /**
     *  Sets the interval of attitude motion.
     */
    static void SetAttitudeInterval(xfloat32 interval);
    
    
    /**
     * To enable or disable acceleration motion.
     */
    static void SetAccelerationEnabled(xbool isEnabled);
    
    /**
     *  Sets the interval of acceleration motion.
     */
    static void SetAccelerationInterval(xfloat32 interval);
    
};

XESCENE_NAMESPACE_END

#endif /* XESDevice_h */
