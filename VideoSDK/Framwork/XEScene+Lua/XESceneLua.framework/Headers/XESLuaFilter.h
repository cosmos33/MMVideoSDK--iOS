//
//  XESLuaFilter.hpp
//  FaceDecorationKit
//
//  Created by HongjieFu on 2018/8/8.
//

#ifndef XESLuaFilter_h
#define XESLuaFilter_h

#include "filter/XESSceneFilter.h"

using namespace XESCENE_NAMESPACE;

class LuaSceneConfig : public SceneConfig {

public:
    LuaSceneConfig(const XString &mScenePath, const XString &scriptFile);
    ~LuaSceneConfig();

    void LoadConfig(const XString &mJsonBuffer, const XString &mScenePath) override;

    const XString & TypeName() const override;
    static const XString  SCENE_TYPENAME;
    
private:
    
    XString scriptFile;
    XString m_strScenePath;
};

class LuaSceneFilter : public SceneFilter {
public:
    void LoadScene(SceneConfig *pSceneConfig, const XString &mSceneID) override;

public:
    void Tick(xfloat32 fTickTime) override;
    virtual ~LuaSceneFilter() override;
};


#endif /* XESLuaFilter_hpp */
