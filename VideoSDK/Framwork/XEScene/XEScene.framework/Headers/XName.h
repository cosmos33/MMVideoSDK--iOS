/******************************************************************************

@File         XName.h

@Version      1.0

@Created      2017, 4, 14

@Description

@HISTORY:

******************************************************************************/

#ifndef _XNAME_H_
#define _XNAME_H_

#include "XTypes.h"
#include "XHashTable.h"

#define XNAME_MAX_STRING_LENGTH 2048

typedef xint32 NAME_INDEX;
static const NAME_INDEX NULL_NAME = -1;

struct XName 
{
    NAME_INDEX Index; 
public:
    XName ();
    XName (const xchar* str);
    XName (const XString& str);

    bool operator== (const XName & other) const { return Index == other.Index; }
    bool operator< (const XName & other) { return Index < other.Index; }

    const xchar*        CStr() const;
    bool               IsNull() const;
};

template<typename T>
struct XHashNode<XName , T>
{
    XName  key;
    T value;
    static bool KeyEqual(const XName & key0, const XName & key1){ return key0 == key1; }
    static xint32 GetHash(const XName & key, xint32 nTableMask)
    {
        return key.Index & (nTableMask - 1);
    }
};

#endif
