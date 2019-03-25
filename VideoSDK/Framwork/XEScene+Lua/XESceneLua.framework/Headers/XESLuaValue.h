//
// Created by momo783 on 13/05/2018.
//

#ifndef XES_XESLUAVALUE_H
#define XES_XESLUAVALUE_H

#include "core/XESObject.h"

#include <map>
#include <list>

XESCENE_NAMESPACE_BEGIN

typedef xint32 LUA_FUNCTION;
typedef xint32 LUA_TABLE;
typedef xint32 LUA_STRING;

class LuaValue;

typedef std::map<std::string, LuaValue>   LuaValueDict;
typedef LuaValueDict::const_iterator      LuaValueDictIterator;
typedef std::list<LuaValue>               LuaValueArray;
typedef LuaValueArray::const_iterator     LuaValueArrayIterator;

typedef enum {
    LuaValueTypeInt,
    LuaValueTypeFloat,
    LuaValueTypeBoolean,
    LuaValueTypeString,
    LuaValueTypeDict,
    LuaValueTypeArray,
    LuaValueTypeObject
} LuaValueType;

typedef union {
    xint32              intValue;
    xfloat32            floatValue;
    xbool               booleanValue;
    XString*            stringValue;
    LuaValueDict*       dictValue;
    LuaValueArray*      arrayValue;
    XMemBase*           xobjectValue;
} LuaValueField;

class LuaValue : public Object {

public:

    static const LuaValue IntValue(const xint32 intValue);

    static const LuaValue FloatValue(const xfloat32 floatValue);

    static const LuaValue BooleanValue(const xbool booleanValue);

    static const LuaValue StringValue(XString* stringValue);

    static const LuaValue StringValue(const XString& stringValue);

    static const LuaValue DictValue(const LuaValueDict& dictValue);

    static const LuaValue ArrayValue(const LuaValueArray& arrayValue);

    static const LuaValue XobjectValue(XMemBase* xobjectValue, XString* objectTypename);

    static const LuaValue XobjectValue(XMemBase* xobjectValue, const XString& objectTypename);

public:
    LuaValue()
    : m_type(LuaValueTypeInt)
    , m_strObjectType(nullptr) {
        memset(&m_filed, 0, sizeof(m_filed));
    }

    LuaValue(const LuaValue& mValue);

    LuaValue& operator = (const LuaValue& mValue);

    ~LuaValue() override;

    void Release() override;

    X_INLINE LuaValueType GetType() const { return m_type; }

    const  XString& GetObjectTypeName() const  { return *m_strObjectType; }


    xint32      IntValue(void)      const { return m_filed.intValue; }
 
    xfloat32    FloatValue(void)    const { return m_filed.floatValue; }

    xbool       BooleanValue(void)  const { return m_filed.booleanValue; }


    const XString& StringValue(void)        const { return *m_filed.stringValue; }

    const LuaValueDict& DictValue(void)     const { return *m_filed.dictValue; }

    const LuaValueArray& ArrayValue(void)   const { return *m_filed.arrayValue; }

    XMemBase* XObjectValue(void) const { return m_filed.xobjectValue; }

private:

    LuaValueType  m_type;
    LuaValueField m_filed;
    XString* m_strObjectType;

    void Clone(const LuaValue& mValue);

};

XESCENE_NAMESPACE_END


#endif //XES_XESLUAVALUE_H
