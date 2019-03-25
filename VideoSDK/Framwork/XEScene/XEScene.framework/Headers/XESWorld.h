//
//  XESWorld.h
//  XEScene
//
//  Created by momo783 on 05/02/2018.
//

#ifndef XESWORLD_H_
#define XESWORLD_H_

#include "core/XESDefine.h"
#include "XECore/XEWorld.h"

XESCENE_NAMESPACE_BEGIN

class World : public XEWorld {
public:
    class WorldListener {
    public:
        WorldListener() {};

        virtual ~WorldListener() {};
    public:
        virtual void OnWorldAddActor(XEActor *aActor) {};

        virtual void OnWorldWillRemoveActor(XEActor *aActor) {};

        virtual void OnWorldUpdateActor(XEActor *aActor, XString strNewActorName) {};

        virtual void OnWorldTick(xfloat32 fDel) {};
    };

public:

    virtual ~World();

    virtual void Init() override;

    void Release();

    virtual void Tick(xfloat32 fDel) override;

    virtual void Render(XEViewport *pViewport) override;

    virtual void Deserialize(XFileBase *pFile) override;

    virtual void Serialize(XFileBase *pFile) override;


    virtual xbool LoadScene(const xchar *pRelativePath,
                            xbool bUseRelPathAsHome = xtrue) override;
    
    virtual xbool SaveScene(const xchar *pPathToSave) override;//save all in the world.

    virtual xbool ExportScene(const xchar *pPathToSave) override;//save all as default.

    inline xbool IsHaveTick() { return m_bTickable; }

    inline void ClearTickState() { m_bTickable = xfalse; }

    inline void SetWorldMode(EWorldMode mode) { m_eWorldMode = mode; }

    inline EWorldMode GetWorldMode() { return m_eWorldMode; }

    inline const XString &GetWorldName() const { return m_strName; }

    virtual XEActor *CreateActor(const XString &strActorType) override;//With the type of Actor.

    virtual XEActor *CreateActor(const XString &strActorType, const XString &strActorName) override;

    virtual void DeleteActor(XEActor *pActor);

    XEActor *FindActor(const XString &strActorName);

    const XEActor *FindActor(const XString &strActorName) const;

    XEActor *UpdateNameOfActor(const XString &strActorOldName, const XString &strActorNewName);

    xint32 GetActorCount(const XString &strActorType = "");

    void GetActorsOfType(const XString &strActorType, XArray<XEActor *> &actorList);

    XString GetActorValidName(const XString &strActorType);

    xint32 GetActorValidOrder();

    XEActorList &GetAllActors() { return m_aActor; }

    const XEActorList &GetAllActors() const { return m_aActor; }

public:

    void AddWorldListener(WorldListener *mWorldListener);

    void RemoveWorldListener(WorldListener *mWorldListener);

    XEActor *CloneActor(XEActor *pActor);

    XEActor *CloneActor(XEActor *pActor, XString strCloneActorName);

protected:

    WorldListener *m_lWorldListener;
};

XESCENE_NAMESPACE_END

#endif /* XESWORLD_H_ */
