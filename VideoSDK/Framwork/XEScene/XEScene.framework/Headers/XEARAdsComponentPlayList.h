/******************************************************************************

@File         XEARAdsComponentPlayList.h

@Version       1.0

@Created      2018/5/30

@HISTORY:

******************************************************************************/
#ifndef XE_ARADS_PLAY_LIST_H
#define XE_ARADS_PLAY_LIST_H
#include "XMath3D.h"
#include "XArray.h"
#include "XMemBase.h"
#include "XEAnimController.h"

class XEModelComponent;

class XEARAdsComponentPlayList 
	:public XEAnimController
{
public:
	XEARAdsComponentPlayList(XEModelComponent* pAnimOwnerComponent);
	virtual ~XEARAdsComponentPlayList();
private:
	//inner use.
	class ARAdsControllerListener :public XEAnimController::Listener
	{
		friend class XEARAdsComponentPlayList;
	public:
		ARAdsControllerListener(XEARAdsComponentPlayList* p);
		~ARAdsControllerListener();
					virtual void Ls_PlayOneTimeFinished(xbool bReversePlaying) override;
	private:
		XEARAdsComponentPlayList* m_pListPlayer;
	};
public:
	//outer use.
	class Listener : public XEAnimController::Listener
	{
	public:
        virtual ~Listener(){}
		virtual void Ls_PlayItemFinished(xint32 nFinishedItemIndex, const XEModelComponent* pHolderComponent, const XEARAdsComponentPlayList* pPlayList){}
	};

public:
	class ARAdsWrapper
	{
	public:
		ARAdsWrapper() :nAddIndex(0), bSetAsScreenSaver(xfalse){}
		virtual ~ARAdsWrapper(){}
	public:
		xbool operator == (const ARAdsWrapper& aw) const;
	public:
		xint32         nAddIndex;
		xbool          bSetAsScreenSaver;
		XString        strAnimAssetPath;//using path to generate the actual animation.
	};

	typedef XArray<ARAdsWrapper> ARAdsWrapperArray;
public:
	X_FORCEINLINE const ARAdsWrapperArray&      GetAnimWrapperList() const{ return m_aAnimWrapper; }
	X_FORCEINLINE ARAdsWrapperArray&            GetAnimWrapperList(){ return m_aAnimWrapper; }
	X_FORCEINLINE xbool                         IsInTurnsPlay() const{ return m_bInTurnsPlay; }
	X_FORCEINLINE xint32                        GetCurPlayIndex() const{ return m_nCurPlayIndex; }
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
	xbool                                       RemoveAnimWrapper(const xchar* pAssetPath, xint32 nAddIndex = -1);//if nAddIndex set to -1, means try to remove all animwrapper in the same asset path.
	xbool                                       RemoveAnimWrapperForAddIndex(xint32 nAddIndex);
	void                                        RemoveAllAnimWrapper();
	ARAdsWrapper*                               GetAnimWrapperForAddIndex(xint32 nAddIndex);
	X_EES_LINE const ARAdsWrapper*              GetAnimWrapperForAddIndex(xint32 nAddIndex) const;
	xint32                                      GetArrangeIndexForAddIndex(xint32 nAddIndex) const;
	xint32                                      GetAddIndexForArrangeIndex(xint32 nArrangeIndex) const;
	xint32                                      GetAddIndexForOneAnim(const xchar* pAssetPath) const;
	void                                        Shuffle();//to shuffle the list, generate a shuffle indexes.
	void                                        MakeInTurns();//in turns.
	XEAnimController*                           GetCurAnimController();
	X_EES_LINE const XEAnimController*          GetCurAnimController() const;
	xbool                                       IsCurrentScreenSaver();
protected:
	ARAdsWrapperArray                           m_aAnimWrapper;
	XArray<xint32>                              m_aArrangeIndex;
	xint32                                      m_nCurPlayIndex;//regard it as in turns.
	XEModelComponent*                           m_pComponentOwner;
	ARAdsControllerListener*                    m_pAnimControllerListener;
	xbool                                       m_bInTurnsPlay;
	xbool                                       m_bPlayNext;
	xbool                                       m_bItemReverse;
	xbool                                       m_bOneItemMode;
};

#endif // XE_ANIM_PLAY_LIST_H
