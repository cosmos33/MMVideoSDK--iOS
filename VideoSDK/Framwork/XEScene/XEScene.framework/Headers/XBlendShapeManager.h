/******************************************************************************

@File         XBlendShapeManager.h

@Version       1.0

@Created      2017, 4, 16

@Description

@HISTORY:

******************************************************************************/

#ifndef _X_BLEDNSHAPE_MANAGER_H_
#define _X_BLEDNSHAPE_MANAGER_H_

#include "XMemBase.h"
#include "XString.h"
#include "XRefCount.h"

class XFileBase;
class XSkinBlendShapeTarget;

struct IBlendShapeAsset : public XMemBase, public XRefCount
{
     friend struct BlendShapeManagerImpl;
public:
     virtual                   ~IBlendShapeAsset() = 0;
     virtual void              Release() = 0;     
     const XString&            GetFilePath() const { return m_strFilePath; }
     xbool                     Save() const;
     xbool                     SaveTo(const XString& strNewPath);
     xbool                     Reload();

protected:
                               IBlendShapeAsset() = default;
     virtual void              OnReload() = 0;

private:
     void                      SetFilePath(const XString& strPath) { m_strFilePath = strPath; }
     virtual xbool             DoSave(XFileBase* pFile) const = 0;
     virtual xbool             DoLoad(XFileBase* pFile) = 0;

     XString                   m_strFilePath;
};

class XBlendShapeManager
{
public:
     static XBlendShapeManager&			Instance();

public:
     virtual                            ~XBlendShapeManager(){}
     
     virtual void                       Init() = 0;
     virtual void                       Release() = 0;

     virtual xbool                      ReloadAsset(const XString& strFilePath) = 0;
     virtual XSkinBlendShapeTarget*     GetAssetWithoutLoad(const XString& strFilePath) = 0;
     virtual XSkinBlendShapeTarget*     LoadAsset(const XString& strFilePath) = 0;
     virtual XSkinBlendShapeTarget*     LoadAsset(const XString& strBasePath, const XString& strFilePath) = 0;
     
     virtual XSkinBlendShapeTarget*     CreateAsset(const XString& strFilePath) = 0;	
     virtual XSkinBlendShapeTarget*     CreateAsset(const XString& strBasePath, const XString& strFilePath) = 0;
     virtual xbool                      ReleaseAsset(XSkinBlendShapeTarget *pAsset) = 0;
};

extern XBlendShapeManager* g_pBlendShapeManager;

#endif
