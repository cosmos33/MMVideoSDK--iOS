#ifndef _XANIMPARAMETERPACK_H_
#define _XANIMPARAMETERPACK_H_

#include "XName.h"
#include "XMath3D.h"

class XFileBase;
class XXMLExtendTool;

enum class EAnimParameterType
{
    // 会存盘
    PT_BOOL,
    PT_FLOAT32,
    PT_INT32,
    PT_UINT32,
    PT_UINT64,
    PT_VECTOR2,
    PT_VECTOR3,
    NUM_PT
};

struct AnimParamVariant
{
    EAnimParameterType m_type;
    union
    {
        bool		boolVal;
        xint32      intVal;
        xuint32     uintVal;
        xuint64     uint64Val;
        xfloat32    floatVal;
        xfloat32    floatArray[3];
        xuint32     rawData[3];
    } m_data;

    template <typename T>
    T GetVal() const; // TODO: validate type

    //template <typename T>
    //void SetVal(T val) { assert(false && "Type not supported"); }

    //template<bool>
    void SetVal(bool val) { m_data.boolVal = val; m_type = EAnimParameterType::PT_BOOL; }

    //template<xint32>
    void SetVal(xint32 val) { m_data.intVal = val; m_type = EAnimParameterType::PT_INT32; }

    //template<xuint32>
    void SetVal(xuint32 val) { m_data.uintVal = val; m_type = EAnimParameterType::PT_UINT32; }

    //template<xuint64>
    void SetVal(xuint64 val) { m_data.uint64Val = val; m_type = EAnimParameterType::PT_UINT64; }

    //template<xfloat32>
    void SetVal(xfloat32 val) { m_data.floatVal = val; m_type = EAnimParameterType::PT_FLOAT32; }

    //template<const XVECTOR2&>
    void SetVal(const XVECTOR2& val) { memcpy(m_data.floatArray, val.m, sizeof(xfloat32) * 2); m_type = EAnimParameterType::PT_VECTOR2; }

    //template<const XVECTOR3&>
    void SetVal(const XVECTOR3& val) { memcpy(m_data.floatArray, val.m, sizeof(xfloat32) * 3); m_type = EAnimParameterType::PT_VECTOR3; }

    bool Save(XFileBase* pFile) const;
    bool Load(XFileBase* pFile);
    bool Serialize(XXMLExtendTool& ar);
};

template <typename T>
AnimParamVariant MakeParamVariant(const T& val)
{
    AnimParamVariant ret;
    ret.SetVal(val);
    return ret;
}

struct XAnimParam
{
private:
    typedef XHashTable<XName, AnimParamVariant>     TParamVariantTable;
    TParamVariantTable                              VariantTable;
    XHashTable<XName, XString>                      StringTable;
public:
    XAnimParam();

    xint32 GetInt32(XName name, xint32 fallBack) const;
    void SetInt32(XName name, xint32 val);

    xuint32 GetUInt32(XName name, xuint32 fallBack) const;
    void SetUInt32(XName name, xuint32 val);

    xuint64 GetUInt64(XName name, xuint64 fallBack) const;
    void SetUInt64(XName name, xuint64 val);

    xfloat32 GetFloat(XName name, xfloat32 fallbackVal) const;
    void SetFloat(XName name, xfloat32 val);

    bool GetBool(XName name, bool fallbackVal) const;
    void SetBool(XName name, bool val);

    XString GetString(XName name, XString const & fallbackVal) const;
    bool SetString(XName name, XString const & str);

    bool Save(XFileBase* pFile) const;
    bool Load(XFileBase* pFile);
    bool Serialize(XXMLExtendTool& ar);

    void Clear();
};

#endif
