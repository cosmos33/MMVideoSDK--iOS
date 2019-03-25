/******************************************************************************

 @File         XMeshRenderBase.h

 @Version       1.0

 @Created      2017, 3, 6

 @Description  The interface of IXMeshRenderBase.

 @HISTORY:

******************************************************************************/

#ifndef _X_MESH_RENDER_BASE_H_
#define _X_MESH_RENDER_BASE_H_

#include "XTypes.h"
#include "XBase3DTypes.h"
#include "XMemBase.h"

class IXVertexDesc;
class IXIndexBuffer;
class IXMaterialInstance;
class XMATRIX4;
class XVECTOR3;
class XCusAABB;

enum XRenderMeshType
{
	XRMT_TRIANGLE_LIST,
	XRMT_LINE_LIST,
	XRMT_TRIANGLE_FAN,
};

class IXMeshRenderBase : public XMemBase
{
public:
	virtual					~IXMeshRenderBase() {};
	virtual void			RenderMesh(IXMaterialInstance* pMaterialInstance,
										IXVertexDesc* pVertexDescription,
										IXIndexBuffer* pIndexBuffer,
										xint32 iFirstIndex,
										xint32 iPrimitiveNum,
										xint32 iPrimitiveType = XRMT_TRIANGLE_LIST) = 0;
};


#endif //_X_MESH_RENDER_BASE_H_