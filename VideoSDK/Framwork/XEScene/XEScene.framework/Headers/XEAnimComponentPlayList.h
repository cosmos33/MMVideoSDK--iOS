/******************************************************************************

@File         XEAnimComponentPlayList.h

@Version       1.0

@Created      2018,3, 6

@HISTORY:

******************************************************************************/
#ifndef XE_ANIM_PLAY_LIST_H
#define XE_ANIM_PLAY_LIST_H
#include "XMath3D.h"
#include "XArray.h"
#include "XMemBase.h"
#include "XEAnimController.h"
#include <functional>

class XEModelComponent;
//play list is also an anim-controller.
class XEAnimComponentPlayList 
	:public XEAnimController
{
public:
	XEAnimComponentPlayList();
	XEAnimComponentPlayList(XEModelComponent* pAnimOwnerComponent);
	virtual ~XEAnimComponentPlayList();
private:
	//inner use.
	class AnimControllerListener :public XEAnimController::Listener
	{
		friend class XEAnimComponentPlayList;
	public:
		             AnimControllerListener(XEAnimComponentPlayList* p);
		            ~AnimControllerListener();
					virtual void Ls_PlayOneTimeFinished(xbool bReversePlaying) override;
	private:
		XEAnimComponentPlayList* m_pListPlayer;
	};
public:
	//outer use.
	class Listener : public XEAnimController::Listener
	{
		friend class XEAnimComponentPlayList;
	public:
		typedef std::function<void(xint32, const XEModelComponent*, const XEAnimComponentPlayList*)> ListenerFunction;
		X_ECB_AUTO(ListenerFunction,void,xint32,const XEModelComponent*, const XEAnimComponentPlayList*)
		Listener() :_func(nullptr){}
		virtual ~Listener(){}
		X_EES_LINE virtual void Ls_PlayItemFinished(xint32 nFinishedItemIndex, const XEModelComponent* pHolderComponent,const XEAnimComponentPlayList* pPlayList){}
		void RegisterPlayItemFinishedCallback(ListenerFunction lpFunc){ _func = lpFunc; }
	protected:
		ListenerFunction _func;
	};

public:
	struct AnimWrapper
	{
	public:
		AnimWrapper() :nAddIndex(0), bSetAsScreenSaver(xfalse){}
		~AnimWrapper(){}
	public:
		xbool operator == (const AnimWrapper& aw) const;
	public:
		xint32         nAddIndex;
		xbool          bSetAsScreenSaver;
		XString        strAnimAssetPath;//using path to generate the actual animation.
	};

	typedef XArray<AnimWrapper> AnimWrapperArray;
public:
	X_FORCEINLINE const AnimWrapperArray&       GetAnimWrapperList() const{ return m_aAnimWrapper; }
	X_FORCEINLINE AnimWrapperArray&             GetAnimWrapperList(){ return m_aAnimWrapper; }
	X_FORCEINLINE xbool                         IsInTurnsPlay() const{ return m_bInTurnsPlay; }
	X_FORCEINLINE xint32                        GetCurPlayIndex() const{ return m_nCurPlayIndex; }
	X_FORCEINLINE void                          SetComponentOwner(XEModelComponent* pOwner){ m_pComponentOwner = pOwner; }
	X_FORCEINLINE XEModelComponent*             GetComponentOwner(){ return m_pComponentOwner; }
public:
	virtual void                                Tick(xfloat32 fInterval) override;
	virtual void                                SetTime(xint32 nTime) override;
	virtual xint32                              GetTimeLength() const override;
	virtual void                                Play() override;//goto 0, and play again.
	virtual void                                Stop() override;
protected:
	void                                        ChangePlaySource(xbool bReversePlaying,xbool bDelayPlay = xtrue);
	xint32                                      GetMaxAddIndex();
	void                                        BroadcastPlayItemFinished();
	void                                        PlayScreenSaver();
public:
	xbool                                       PlayItem(xint32 nArrangeIndex);
	xbool                                       SetCurrentPlayItemAt(xint32 nArrangeIndex);
	xint32                                      AddAnimWrapper(const xchar* pAssetPath, xbool bSetAsScreenSaver = xfalse);
	void                                        AddAnimPendingToPlay(const xchar* pAssetPath, xbool bSetListLoop = xfalse) const;//callbacks in listener should call this, in safely mode. 
	void                                        ApplyPendingAnimNow();//you can apply the pending animation immediately, instead of waiting for the next tick.
	xbool                                       RemoveAnimWrapper(const xchar* pAssetPath, xint32 nAddIndex = -1);//if nAddIndex set to -1, means try to remove all animwrapper in the same asset path.
	xbool                                       RemoveAnimWrapperForAddIndex(xint32 nAddIndex);
	void                                        RemoveAllAnimWrapper();
	AnimWrapper*                                GetAnimWrapperForAddIndex(xint32 nAddIndex);
	X_EES_LINE const AnimWrapper*               GetAnimWrapperForAddIndex(xint32 nAddIndex) const;
	xint32                                      GetArrangeIndexForAddIndex(xint32 nAddIndex) const;
	xint32                                      GetAddIndexForArrangeIndex(xint32 nArrangeIndex) const;
	xint32                                      GetAddIndexForOneAnim(const xchar* pAssetPath) const;
	void                                        Shuffle();//to shuffle the list, generate a shuffle indexes.
	void                                        MakeInTurns();//in turns.
	XEAnimController*                           GetCurAnimController();
	X_EES_LINE const XEAnimController*          GetCurAnimController() const;
	xbool                                       IsCurrentScreenSaver();
	
	X_CLASS_DEF(XEAnimComponentPlayList)
protected:
	AnimWrapperArray                            m_aAnimWrapper;
	XArray<xint32>                              m_aArrangeIndex;
	xint32                                      m_nCurPlayIndex;//regard it as in turns.
	XEModelComponent*                           m_pComponentOwner;
	AnimControllerListener*                     m_pAnimControllerListener;
	xbool                                       m_bInTurnsPlay;
	xbool                                       m_bPlayNext;
	xbool                                       m_bItemReverse;
	xbool                                       m_bOneItemMode;
private:
	xbool                                       m_bTicked;
	struct pendingToPlay
	{
		XArray<XString> arrAnimAssetPaths;//using path to generate the actual animation.
		xbool bListLoop;
		void Clear()
		{
			arrAnimAssetPaths.Clear();
			bListLoop = xfalse;
		}
		pendingToPlay() :bListLoop(xfalse){}
	};
	mutable pendingToPlay                      m_animPendingToPlay;//can be changed at callback const.
};

#endif // XE_ANIM_PLAY_LIST_H
