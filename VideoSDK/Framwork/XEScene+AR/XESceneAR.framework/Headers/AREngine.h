#ifndef _H_AR_H_
#define _H_AR_H_

#include "xcommon/XViewport.h"
#include "platform/armodule/XESARModule.h"
#include "platform/armodule/XEARAnchor.h"

class IXTexture2D;
namespace AR
{
#if X_PLATFORM_ANDROID
    class ARCoreHitTestListener
    {
    public:
        virtual void        HitTest(const XVECTOR2& vScreenPosition,XArray<HitTestResult>& aResults){}
    };
#endif
    
    class AREngine : public ARModule {
        
        AREngine();
        ~AREngine();
        
    public:
        
        static AREngine* GetInstance();

		xbool			Init(XViewport &vViewport,AR::EARStartMode eMode = ESM_Internal);
		xbool			Release();
		void			Tick();


		AR::EARStartMode    GetStartMode();
		/**
		 * 获取相机view矩阵
		 *
		 * @param viewMatrix        相机view矩阵
		 * @return     xbool            是否获取成功
		 */
		xbool			GetCameraViewMatrix(XMATRIX4& viewMatrix);

		/**
		 * 获取特征点
		 *
		 * @param aPoints       ARKit/Tango检测到的特征点列表
		 */
		void			GetFeaturePoints(XArray<XVECTOR3>& aPoints);

		/**
		 * 获取平面信息
		 *
         * @param aAllPlaneAnchors    检测到的平面信息(平面世界变换矩阵)
		 */
		void     		GetAllPlaneAnchors(XArray<AR::XEARPlaneAnchor*>& aAllPlaneAnchors);

		/**
		 * 点击事件
		 *
		 * @param vScreenPosition        屏幕坐标
		 * @param aResults                点击结果列表
		 */
		void            HitTest(const XVECTOR2& vScreenPosition, XArray<HitTestResult>& aResults);

		/**
		 * 获取FOV
		 *
		 * @return xfloat32                视口返回值(弧度)
		 */
		xfloat32 		GetCameraFOV();

		/**
		 * 设置视口参数
		 *
		 * @param vViewport                视口
		 */
		//void			SetViewport(XViewport &vViewport);

		/**
		 * 停止追踪
		 */
		void            StopTrackingSession();

		/**
		 * 重置追踪
		 */
		xbool            ResetTrackingSession(void *env = NULL, void *context = NULL, void *activity = NULL);

		/**
		 * 设置屏幕旋转朝向
		 *
		 * @param nOri                当前屏幕朝向
		 */
		void            SetScreenOrientation(xint32 nOri,XViewport* pViewPort = NULL);

		/**
		 * 获取屏幕旋转的矩阵
		 *
		 * @param nMode                当前屏幕朝向
		 * @param vAixs                绕指定轴旋转的轴
		 * @return                    屏幕旋转矩阵
		 */
		XMATRIX4        GetTransformFromDeviceOrientation(const xint32& nMode, const XVECTOR3 &vAixs);
        
        void            SetARSessionStatusListener(ARSessionStatusListener* pSessionListener);
        void             RemoveARSessionStatusListener();


	#if ARKIT_SUPPORT
		/**
		 * 获取ARKit返回的Y纹理
		 *
		 * @return IXTexture2D*                指向2D纹理指针
		 */
		IXTexture2D*	GetCameraYTexture();

		/**
		 * 获取ARKit返回的CbCr纹理
		 *
		 * @return IXTexture2D*                指向2D纹理指针
		 */
		IXTexture2D*	GetCameraCbcrTexture();

		void*           GetDelegate();
	#endif

	#if X_PLATFORM_ANDROID
		/**
		 * 获取Tango返回的纹理（使用OES扩展纹理，For Tango and ARCore）
		 *
		 * @return IXTexture2D*                指向2D纹理指针
		 */
		IXTexture2D*    GetCameraTexture();
        
		//外部启动ARCore  start-----
		XMATRIX4        ConvertModelMatrixForLeftHandSpace(const XMATRIX4& matModelRightHand);
		XMATRIX4        ConvertCameraViewForLeftHandSpace(const XMATRIX4& matViewRightHand);
		xfloat32        CalculateCameraFOVForLeftSpace(const XMATRIX4& matProjectRightHand);
		//HitTest监听
		void            SetHitTestListener(ARCoreHitTestListener *pListener);
		void			SaveLeftSpaveProjectMatrix(const XMATRIX4& matProjectInRightSpace);
		void			SaveLeftSpaveCameraViewMatrix(const XMATRIX4& matCameraViewInRightSpace);
        
        void            UpdateAnchorStatus(XArray<AR::XEARAnchor *> aOriginAnchors,xbool bConvertInner = xfalse) ;
		//外部启动ARCore  end--------
	#endif
        
    };
};


#endif
