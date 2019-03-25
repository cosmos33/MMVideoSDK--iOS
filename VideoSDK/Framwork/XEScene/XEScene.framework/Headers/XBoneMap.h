#ifndef _XBONEMAP_H_
#define _XBONEMAP_H_

#include "XArray.h"

class XSkeletonMask;

/*
BoneMap is a mapping from storage index to bone index.
Storage index means the index of an array if some types store something as an array that are part of Bones in Skeleton.
e.g. Pose stores part of the Skeleton's Bone transforms.
To make GetStorageIndex work, the bone index need to be in ascending order.
*/
class XBoneMap
{
public:
    static bool					IsSame(const XBoneMap& left, const XBoneMap& right);
public:

    XBoneMap() = default;
    XBoneMap(xint32 nMapElementCount) { SetCount(nMapElementCount); }

    void							SetCount(xint32 nMapElementCount) { m_aStorageIndexToBoneIndex.SetNum(nMapElementCount); }

    xint32							GetCount() const { return m_aStorageIndexToBoneIndex.Num(); }

    void							Clear() { m_aStorageIndexToBoneIndex.Clear(); }

    bool							Exist(xint32 iBoneIndex) const;

    // return -1 if not exist.
    // time complexity: O(log n)
    xint32							GetStorageIndex(xint32 iBoneIndex) const;
    // time complexity: O(1)
    xint32							GetBoneIndex(xint32 iStorageIndex) const { return m_aStorageIndexToBoneIndex[iStorageIndex]; }

    // make sure bone index is in ascending order.
    void							SetBoneIndex(xint32 iStorageIndex, xint32 iBoneIndex) { m_aStorageIndexToBoneIndex[iStorageIndex] = iBoneIndex; }

	xint32							AddNewBoneIndex(xint32 iBoneIndex);
    void							RemoveBoneByStorageIndex(xint32 iStorageIndex) { m_aStorageIndexToBoneIndex.RemoveAt(iStorageIndex); }

	const XArray<xint32>&			GetMapData() const { return m_aStorageIndexToBoneIndex; }

	XArray<xint32>&					GetMapData() { return m_aStorageIndexToBoneIndex; }

    XSkeletonMask                   GenerateAffectedBones() const;
private:
    XArray<xint32>					m_aStorageIndexToBoneIndex;
};

#endif // _ABONEMAP_H_
