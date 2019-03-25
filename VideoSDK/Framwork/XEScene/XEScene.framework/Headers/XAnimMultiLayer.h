#ifndef _XANIMMULTILAYER_H_
#define _XANIMMULTILAYER_H_

#include "XAnimatable.h"
#include "XArray.h"
#include "XString.h"
#include "XTimeline.h"

struct XAnimInstance;
struct UpdateParam;
class XTimeline;
class XSkelAnimController;
class XFullPose;
class XSkeleton;
class IXAnimationBase;

enum AnimControllerType
{
	BUILDINBIT = XBit(31),
	SKEL_ANIMCONTROLLER = 0 | BUILDINBIT,
	SKEL_BLENDSHAPE_ANIMCONTROLLER = 1 | BUILDINBIT,
};

/****************************************************************************/
/* 具有多个控制器(层)的动画组件,用于控制骨骼对象								*/
/* 每一层包含表示一个控制器,每个控制器包含一个动画文件,来实施具体的骨骼动画更新	*/			
/****************************************************************************/
class XAnimMultiLayer : public IXAnimatable
{
public:
									XAnimMultiLayer(XSkeleton* pSkeleton);
    virtual							~XAnimMultiLayer();

	// IXAnimatable interface
    virtual void                    Play() override;
    virtual void                    Pause() override;
    virtual void                    Resume() override;
    virtual xbool					IsPaused() const override;
    virtual xfloat32				GetStartTime() const override;
	virtual xfloat32				GetEndTime() const override;
	virtual xfloat32				GetCurrentTime() const;
	// setTime，会执行骨骼等的更新
	virtual void                    SetCurrentTime(xfloat32 fValue);
	virtual void				    SetEndTime(xfloat32 fValue);
    virtual void                    Update(xfloat32 deltaTime) override;
	virtual void                    UpdateToCurTime(const UpdateParam &ctx);

	// Layer control
	virtual bool					ActivateLayer(xint32 nIndex);
	virtual bool					DeactivateLayer(xint32 nIndex);
	virtual void				    ActivateAll();
	virtual void				    DeactivateAll();
	virtual xint32                  AddLayer(AnimControllerType eType, const xchar* szLayerName, IXAnimationBase* pAsset);
    virtual void                    RemoveLayer(xint32 nIndex);
    virtual void                    RemoveLayer(const xchar* szName);
    virtual void                    RemoveAllLayers();
	virtual xint32                  GetLayerNum() const;
	virtual XSkelAnimController*	GetLayer(xint32 nIndex);
	virtual XSkelAnimController*	GetLayer(const xchar* szName);

	
	// Wrap Mode
	virtual void					SetWrapMode(AnimationWrapMode eLoopMode);

protected:	
	virtual bool                    BindSkeleton(XSkeleton* pSkeleton);
    void                            Clear();
    void                            UpdateActiveLayers(const UpdateParam& ctx);
    void                            UpdateSkeleton();
	void							UpdatePose(const XAnimInstance& instData, XFullPose& pose);
    xint32                          GetLayerIndex(const xchar* szLayerName) const;
	
protected:
	XArray<XSkelAnimController*>	m_aControllers;
	XTimeline*                      m_pTimeline;
    xbool							m_bPaused;
	xfloat32						m_fStartTime;
	xfloat32						m_fEndTime;
    XSkeleton*                      m_pSkeleton;
    XFullPose*                      m_pPose;
    XAnimInstance*					m_pAnimInstance;
};

#endif
