#ifndef _XSKELETONMASK_H_
#define _XSKELETONMASK_H_

#include "XMemBase.h"
#include "XString.h"
#include "XName.h"

class XSkeleton;
class XXMLExtendTool;
class XFileBase;

class XSkeletonMask : public XMemBase
{
public:
    explicit XSkeletonMask(XSkeleton const* pSkeleton);
    XSkeletonMask(XArray<xint32> const& bones, XSkeleton const* pSkeleton = nullptr);
    XSkeletonMask(XSkeletonMask const& other) = default;
    XSkeletonMask& operator= (XSkeletonMask const& other) = default;

	bool						Init(const XArray<xint32>& bones);
	void						Clear();
	void						Add(xint32 iBone);
	void						AddBoneTreeToMask(XSkeleton const* pSkeleton, xint32 iRoot);
	void						Remove(xint32 iBone);
	bool						IsFullMask() const { return m_bIsFullMask; }

	const XArray<xint32>&		GetUnorderedArray() const { return m_aBones; }
    bool						Find(xint32 iBone) const;
    XSkeletonMask				Intersect(XSkeletonMask const& mask) const;
    bool						HaveIntersection(XSkeletonMask const& mask) const;
    bool						Contains(XSkeletonMask const& mask) const;
    bool						Serialize(XXMLExtendTool& ar);
    bool						Save(XFileBase* pFile) const;
    bool						Load(XFileBase* pFile);
    void						BindSkeleton(XSkeleton const* pSkeleton);

    static const XSkeletonMask  FullMask;
protected:
	XArray<xint32>				m_aBones;
	XArray<bool>				m_aMask;
	bool						m_bIsFullMask;

	void						BuildMaskFromArray();

private:
    bool						Valid() const;
    void						RecordBoneNames(XSkeleton const* pSkeleton);

private:
	XArray<XName>				m_aBoneNames;
};

#endif
