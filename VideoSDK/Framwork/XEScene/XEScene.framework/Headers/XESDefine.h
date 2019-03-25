//
//  XEDefine.h
//  XEScene
//
//  Created by momo783 on 02/02/2018.
//

#ifndef XEDEFINE_H_
#define XEDEFINE_H_

/**  public include */

#include "xcommon/XPlatform.h"
#include "xcommon/XTypes.h"
#include "xcommon/XMath3D.h"
#include "xcommon/XMemBase.h"
#include "xcommon/XString.h"
#include "xcommon/XArray.h"
#include "xcommon/XHashTable.h"
#include "xcommon/XGlobalFuncs.h"

#include <stdio.h>
#include <string>
/**  namespace define */

#define XESCENE_VERSION "0.1.11"

#ifndef XESCENE_NAMESPACE
#define XESCENE_NAMESPACE xes
#endif
#ifndef XESCENE_NAMESPACE_BEGIN
#define XESCENE_NAMESPACE_BEGIN namespace XESCENE_NAMESPACE {
#endif
#ifndef XESCENE_NAMESPACE_END
#define XESCENE_NAMESPACE_END }
#endif

#define EVENT_COME_TO_FOREGROUND    "event_come_to_foreground"

#define EVENT_COME_TO_BACKGROUND    "event_come_to_background"

XESCENE_NAMESPACE_BEGIN



/**
 *  @def XESCENE_REQUIRES_NULL_TERMINATION
 */
#if !defined(XESCENE_REQUIRES_NULL_TERMINATION)
#if defined(__APPLE_CC__) && (__APPLE_CC__ >= 5549)
#define XESCENE_REQUIRES_NULL_TERMINATION __attribute__((sentinel(0,1)))
#elif defined(__GNUC__)
#define XESCENE_REQUIRES_NULL_TERMINATION __attribute__((sentinel))
#else
#define XESCENE_REQUIRES_NULL_TERMINATION
#endif
#endif

/**
 * @def XESCENE_ENABLE_SCRIPT_BINDING
 */

#ifndef XESCENE_ENABLE_SCRIPT_BINDING
#define XESCENE_ENABLE_SCRIPT_BINDING = 1
#endif

#ifndef XESCENE_CONSTRUCTOR_ACCESS
#ifdef XESCENE_ENABLE_SCRIPT_BINDING
#define XESCENE_CONSTRUCTOR_ACCESS public
#else
#define XESCENE_CONSTRUCTOR_ACCESS protected
#endif
#endif

/**
 *  @def Debug
 */
#define XES_DEBUG 0
#define XES_DEBUG_LOG 0
#define XES_DEBUG_LUA_LOG 1

#if XES_DEBUG
#define XESAssert(x) assert(x)
#else
#define XESAssert(x) {}
#endif

    namespace StringUtils {

        XString Format(const char *format, ...);

        void PrintLog(const char *format, ...);
    }


#if XES_DEBUG_LOG
#define XESLog(format, args...) StringUtils::PrintLog(format, ##args)
#else
#define XESLog(format, args...) {}
#endif

#if XES_DEBUG_LUA_LOG
#define XESLLog(format, args...) StringUtils::PrintLog((std::string("[LUA]") + format).c_str() , ##args)
#else
#define XESLLog(format, args...) {}
#endif

XESCENE_NAMESPACE_END

//Scripting
#define XESS_IGNORE     //忽略导出方法    不允许加在实现方法上
#define XESS_MANUAL     //手动导出方法    不允许加在实现方法上
#define XESS_HIDE_START     //大段忽略-开始   不允许嵌套
#define XESS_HIDE_END       //大段忽略-结束   不允许嵌套

#endif /* XEDEFINE_H_ */
