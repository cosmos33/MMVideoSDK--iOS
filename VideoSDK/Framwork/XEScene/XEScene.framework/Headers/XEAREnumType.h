//
//  XEARType.h
//  Pods
//
//  Created by MOMO_ZSX on 2018/10/16.
//

#ifndef XEARType_h
#define XEARType_h

namespace AR {
    //android: ARCore使用，包含三种状态
    //iOS:ARKit框架中目前仅有一个bool变量表示是否可追踪
    enum EArTrackingState {
        /// The object is currently tracked and its pose is current.
                EATS_AR_TRACKING_STATE_TRACKING,

        /// ARCore has paused tracking this object, but may resume tracking it in
        /// the future. This can happen if device tracking is lost, if the user
        /// enters a new space, or if the Session is currently paused. When in this
        /// state, the positional properties of the object may be wildly inaccurate
        /// and should not be used.
                EATS_AR_TRACKING_STATE_PAUSED,

        /// ARCore has stopped tracking this Trackable and will never resume
        /// tracking it.
                EATS_AR_TRACKING_STATE_STOPPED
    };


    //android:ARCore 有三种状态HORIZONTAL_UPWARD_FACING、HORIZONTAL_DOWNWARD_FACING和VERTICAL三种状态
    //iOS:ARKit仅有Horizontal和Vertical两种状态，对应ARKit的ARPlaneAnchorAlignment类型
    enum EArPlaneType {
        /// A horizontal plane facing upward (for example a floor or tabletop).
                EPT_AR_PLANE_HORIZONTAL_UPWARD_FACING = 0,
        /// A horizontal plane facing downward (for example a ceiling).
                EPT_AR_PLANE_HORIZONTAL_DOWNWARD_FACING = 1,
        /// A vertical plane (for example a wall).
                EPT_AR_PLANE_VERTICAL = 2
    };

    enum EARHitTestResultType {
#if X_PLATFORM_ANDROID
        /// A horizontal plane facing upward (for example a floor or tabletop).
        EHRT_AR_PLANE_HORIZONTAL_UPWARD_FACING = 0,
        /// A horizontal plane facing downward (for example a ceiling).
        EHRT_AR_PLANE_HORIZONTAL_DOWNWARD_FACING = 1,
        /// A vertical plane (for example a wall).
        EHRT_AR_PLANE_VERTICAL = 2,
        EHRT_ARHitTestResultTypePoint = 3
#endif

#if ARKIT_SUPPORT
        /** Result type from intersecting the nearest feature point. */
                EHRT_ARHitTestResultTypeFeaturePoint = (1 << 0),

        /** Result type from intersecting a horizontal plane estimate, determined for the current frame. */
                EHRT_ARHitTestResultTypeEstimatedHorizontalPlane = (1 << 1),

        /** Result type from intersecting a vertical plane estimate, determined for the current frame. */
        //ios(11.3)
                EHRT_ARHitTestResultTypeEstimatedVerticalPlane = (1 << 2),

        /** Result type from intersecting with an existing plane anchor. */
                EHRT_ARHitTestResultTypeExistingPlane = (1 << 3),

        /** Result type from intersecting with an existing plane anchor, taking into account the plane’s extent. */
                EHRT_ARHitTestResultTypeExistingPlaneUsingExtent = (1 << 4),

        /** Result type from intersecting with an existing plane anchor, taking into account the plane’s geometry. */
        //ios(11.3)
                EHRT_ARHitTestResultTypeExistingPlaneUsingGeometry = (1 << 5),

#endif
    };


    //AR启动模式
    enum EARStartMode {
        ESM_Internal,//引擎内部启动
        ESM_External//外部启动
    };

}

#endif /* XEARType_h */
