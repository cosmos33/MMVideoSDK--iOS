//
//  XEObjectSet.h
//  Pods
//
//  Created by momo783 on 02/02/2018.
//
//

#ifndef XEOBJECTMANAGER_H_
#define XEOBJECTMANAGER_H_

#include "core/XESDefine.h"
#include "core/XESObject.h"

#include <set>

XESCENE_NAMESPACE_BEGIN

class ObjectManager : public XMemBase
{
private:
    
    ObjectManager();
    ~ObjectManager();
    
public:
    
    /**
     *  节点集合单例
     */
    static ObjectManager* GetInstance();
    
public:
    
    /**
     *  添加Object
     */
    void AddObject(const Object* aObject);
    
    /**
     *  移除Object
     */
    void RemoveObject(const Object* aObject);
    
    /**
     *  节点数获取
     */
    xint32 ObjectNums();
    
    /**
     *  移除所有Object
     */
    void RemoveAllObject();
    
private:
    
    std::set<const Object*> m_vObjectSet;
};

XESCENE_NAMESPACE_END

#endif /* XEOBJECTMANAGER_H_ */
