/******************************************************************************

@File         XESeqBindingCameraCuts.h

@Version       1.0

@Created      2018,2, 27

@HISTORY:

******************************************************************************/
#ifndef XE_SEQ_BINDING_CAMERA_CUTS_H
#define XE_SEQ_BINDING_CAMERA_CUTS_H
#include "XESeqBinding.h"

class XEActor;
class XESeqAnimController;

class XESeqBindingCameraCuts 
	:public XESeqBinding
{
	friend class XESeqBindingCameraCutsInstance;
public:
	XESeqBindingCameraCuts();
	virtual ~XESeqBindingCameraCuts();
public:
	//these metadatas specific the discrete-camera-segments with different/same origin-camera actors binded to the track.
	struct MetaData
	{
		MetaData() : nStartTime(0), nEndTime(0), bActive(xtrue){}
		xint32         nStartTime;//as a whole.
		xint32         nEndTime;//as a whole.
		xbool          bActive;//whether active or not.
		XString        strActorName;//the unique name of the actor(usually is a camera actor.)
		const xbool operator == (const MetaData& md)const
		{
			return 0 == strActorName.CompareNoCase(md.strActorName);
		}
	};
	typedef XArray<MetaData> MetaSegmentList;
public:
	virtual void                         Deserialize(const XMLElement* pEleParent, XETreeNode::Manager* pNodeMgr = NULL)override;
	virtual XMLElement*                  Serialize(XMLElement* pEleParent)override;
	virtual void                         Release() override;
	xbool                                AddCamera(XEActor* pCameraActor, XESeqAnimController* pSeqAnimController);
	xbool                                BindCamera(xint32 nMetaIndex, XEActor* pCameraActor);//bind to a new camera.
	xbool                                UnBindCamera(xint32 nMetaIndex);//unbind camera.
	xbool                                RemoveSegment(xint32 nMetaIndex);
	xbool                                ExpandSegmentEndTime(xint32 nMetaIndex, xint32 nDeltaTime);//keep continually.
	xbool                                ClipSegmentStartTime(xint32 nMetaIndex, xint32 nDeltaTime);//keep continually.
	xbool                                SetSegmentStartTime(xint32 nMetaIndex, xint32 nStartTime);
	xbool                                SetSegmentEndTime(xint32 nMetaIndex, xint32 nEndTime);
	xbool                                SetSegmentActive(xint32 nMetaIndex, xbool bActive);
	xbool                                SplitToSegments(xint32 nMetaIndex, xint32 nSplitTimePos);//keep continually.
	xint32                               GetUpperboundMetaDataIndex(xint32 nTime);
	void                                 MoveAsWhole(xint32 nDeltaTime);//move as whole
	xbool                                MoveSegments(XArray<xint32>& aMetaIndexes, xint32 nDeltaTime);//must be continually and head or tail must include.
	X_FORCEINLINE const MetaSegmentList& GetSegmentList() const{ return m_metaSegments; }
public:
	XE_USER_NODE_CAST(XESeqBindingCameraCuts)
	XE_USER_NODE_TYPE_DEF(NODE_TYPENAME)
	static const XString  NODE_TYPENAME;
private:
	void                                 SerializeMetaData(XMLElement* pEleNode, const MetaData& metaData);
	void                                 DerializeMetaData(const XMLElement* pEleNode, MetaData& metaData);
protected:
	MetaSegmentList                      m_metaSegments;//segments are discrete.
};

#endif // XE_SEQ_BINDING_CAMERA_CUTS_H
