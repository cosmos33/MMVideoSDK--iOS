/******************************************************************************

@File         XEGroundGridActor.h

@Version       1.0

@Created      2017, 6, 6

@Description  The class ids of each class in X Editor

@HISTORY:

******************************************************************************/

#ifndef _XE_GROUNDGRIDACTOR_H_
#define _XE_GROUNDGRIDACTOR_H_

#include "XEActor.h"
#include "XMath3D.h"
#include "XTypes.h"

#define X_STATIC_GROUND_GRID_NUM 32			// 保证有中间线就必须是偶数
#define X_STATIC_GROUND_GRID_SIZE 1.0f
#define X_DYNAMIC_GROUND_GRID_NUM 32
#define X_DYNAMIC_GROUND_SCALEPARAM 0.5f
#define X_DYNAMIC_GROUND_TOLERANCE 0.1f


class XEGroundGridActor : public XEActor
{
public:
	enum eGridType { EGRID_XZ = 0, EGRID_XY, EGRID_YZ, EGRID_NUM };

public:
	XE_ACTOR_CAST(XEGroundGridActor)
	XE_ACTOR_TYPE_DEF(ACTOR_TYPENAME)
	X_CLASS_DEF(XEGroundGridActor)
	static const XString	    ACTOR_TYPENAME;
	XEGroundGridActor();
	virtual					    ~XEGroundGridActor();
	virtual void			    Serialize(XFileBase *pFile) override {}
	virtual void                Deserialize(const XMLElement* pEleActor) override;
	virtual XMLElement*         Serialize(XMLElement* pEleParent) override;
	virtual void			    Tick(xfloat32 fDel, xbool bForceTick = xtrue) override {}
	virtual void			    Render(XEViewport* pViewport) override;
	virtual void                Initialize(XEWorld* pWorld) override;
	virtual xbool               RayPick(XEHitResult& hr) override;
	void				        SetDynamic(xbool bDynamic);
	inline xbool			    IsDynamic() const { return m_bDynamic; }
	void			            SetGridType(eGridType type);
	inline eGridType		    GetGridType() { return m_eGridType; }
	const XArray<XString>&      GetGridTypeDescs() const;
	XCOLORBASE                  GetColor(){ return m_Color; };
	void                        SetColor(const XCOLORBASE& color){ m_Color = color; };
#if X_PLATFORM_WIN_DESKTOP
	virtual XEPropertyObjectSet GetPropertyObjectSet(XEPropertyObjectProxy* pPropertyObjectProxy) override;
#endif // X_PLATFORM_WIN_DESKTOP
	void					    UpdateGrid();
protected:		
	xbool                       FixInversProjectOfXZ(XEViewport* pViewport, XEHitResult& hr);//ray-pick result need to be fixed.
	void					    RenderStatic();
	void					    RenderDynamic();
	void					    UpdateStatic();
	void					    UpdateDynamic();
	struct Vertex;			    
	void					    UpdateDynamicXZ(const XVECTOR3& vCamerapos, const XVECTOR3 &vCameraDir, xfloat32 fTolerance,
							    				xfloat32 fScaleParam, XArray<Vertex> &vVBPos, XArray<xint32> &vIndex);
							    
// 	XVECTOR3				    m_Rows[2][X_GROUND_GRID_NUM + 1];
// 	XVECTOR3				    m_Cols[2][X_GROUND_GRID_NUM + 1];
	XArray<XVECTOR3>	    m_vRows[2];
	XArray<XVECTOR3>	    m_vCols[2];

	struct Vertex
	{
		XVECTOR3 vPos;
		xfloat32 fA;
	};
	XArray<Vertex>		m_vVBPos;
	XArray<xint32>		m_vIndex;

	XVECTOR3				m_vCurCamerapos;
	XVECTOR3				m_vCurCameradir;
	XVECTOR3				m_vLastUpdatepos;
	xbool					m_bDynamic;	
	eGridType				m_eGridType;

	XCOLORBASE				m_Color;
	XCOLORBASE				m_CenterColor;

	xfloat32				m_fUpdateTag;
};

#endif



