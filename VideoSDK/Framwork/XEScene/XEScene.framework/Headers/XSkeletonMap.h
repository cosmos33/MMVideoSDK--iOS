#ifndef _XSKELETONMAP_H_
#define _XSKELETONMAP_H_

#include "XTypes.h"
#include "XArray.h"

struct XSkeletonMap
{
    struct TrackBonePair
    {
        xint32 nTrackIndex;
        xint32 nBoneIndex;
    };

    XArray<xint32>          TrackToBone;
    XArray<xint32>          BoneToTrack;
    XArray<TrackBonePair>   SortedItem;

    void                    Set(xint32 nBoneIndex, xint32 nTrackIndex);
    void                    Clear();
    void                    SortItem();
	bool					IsValidBoneIndex(xint32 BoneId) const;
};
#endif
