#ifndef _XFACERIG_ANIM_H_
#define _XFACERIG_ANIM_H_

#include "XHashTable.h"
#include "XXMLExtendTool.h"
#include "XBlendShapeAnim.h"
#include "XBoneController.h"
#include "XBlendShapeAnim.h"

struct xFaceRigBoneControl
{
	XString strBoneName;
	xfloat32 fWeight;
};


class XFaceRigSetting
{
public:
	XFaceRigSetting(){}
	~XFaceRigSetting(){}

	xbool Load(const XString &strFilePath);

	// 识别状态与channel的对应, channel = skinname-morphtargetname-meshtargetname-channelname
	XHashTable<XString, XString> m_mStateToChannel;

	// 帧动画文件
	//XArray<XString> m_vSeq;

	// 要求各骨骼为父子关系， 数组中顺序为： 根 / 次根 / 次次根	
	XArray<xFaceRigBoneControl> m_vControlBone;

protected:

	void Clear();
	xbool LoadVersion0(tinyxml2_XEngine::XMLElement* pRootNode);
};

struct FaceRigParam
{
	XHashTable<XString, xfloat32>  mStateWeight;
	XVECTOR3					   vEuler;
};

struct xFaceRigControllerInfo
{
	xFaceRigControllerInfo() : strBoneName(""), fWeight(0.0f), pController(NULL)  {}
	XString					  strBoneName;
	xfloat32				  fWeight;
	XBoneWorldRotController	  *pController;	
};

class XFaceRigAnim : public XBlendShapeAnim
{
public:
									XFaceRigAnim(IXModelInstance *pIns);
	virtual							~XFaceRigAnim();

	void							LoadSettingFile(const XString &strFileName);
	void							TickFaceRigParam(const FaceRigParam &param, xbool bClearAllBeforeApply = xtrue);

	/* 重新生成morph weight 和由配置信息生成channel对应关系
	   当前模型skin有增删除时，weight、channel等记录需要重新生成；
	*/
	void							ReGenerateFaceRigInfo(xbool bGenerateWeight = xtrue, xbool bGenerateChannelIndexBySetting = xtrue);

	inline void						SetFaceRigBlendWeight(xfloat32 fBlendWeight) { m_fFaceRigBlendWeight = fBlendWeight; }
	inline xfloat32					GetFaceRigBlendWeight() { return m_fFaceRigBlendWeight; }

	/*以覆盖的方式，将当前anim动画的，骨头控制，绑定到骨架上。
	*/
	xbool						    ReBindBoneControllerToSkinmodelInsSkeleton();
	/*重置FaceRigParam参数
	*/
	void							ReSetFaceRigParam();

	/* 去解绑骨头控制器，与skinmodel脱离关联
	*/
	void						    UnbingBoneController();

	/* 当没有配置骨头时，左右摆动，是否直接摆动模型
	*/
	X_FORCEINLINE void				SetRotateModelOfNoBoneControl(xbool bEnable) { m_bRotateModelOfNoBoneControl = bEnable; }
	X_FORCEINLINE xbool				GetRotateModelOfNoBoneControl() const { return m_bRotateModelOfNoBoneControl; }

protected:
	virtual	void					MergeUserMorphAndBone() override;
	void							GenerateChannelIndexBySetting();
	void							MergeFaceRigSke();
	void							MergeFaceRigMorphWeight();
	void							ReleaseController(xbool bUnbindOfBone = xfalse);

	XSkinModelBlendShapeWeight		m_CurrentFaceRigMorphWeights;
	XVECTOR3					    m_vFaceRigEuler;
	xfloat32						m_fFaceRigBlendWeight;
	/* 当没有配置骨头用于左右摆动时，是否直接摆动模型
	*/
	xbool							m_bRotateModelOfNoBoneControl;

	// 权重中索引
	struct ChannelKey
	{
		xint32 nSkiIndex;
		xint32 nSkinMorphTargetIndex;
		xint32 nMeshMorphTargetIndex;
		xint32 nChannelIndex;
	};
	XHashTable<XString, ChannelKey>	 m_mStateToChannelIndex;
	XArray<xFaceRigControllerInfo>	 m_vControlBoneController;

	XString							m_strSettingFile;
	XFaceRigSetting					m_Setting;
};

#endif


