#include "BlocoCore.h"
//
// Frustum::Frustum					- Chapter 14, page 465
//
 Frustum::Frustum()
{
	m_Fov = D3DX_PI/4.0f;		// default field of view is 90 degrees
	m_Aspect = 1.0f;			// default aspect ratio is 1:1
	m_Near = 1.0f;				// default near clip plane is 1m away from the camera
	m_Far = 1000.0f;				// default near clip plane is 100m away from the camera
}


//
// Frustum::Inside					- Chapter 14, page 466
//
bool Frustum::Inside(Vec &point) const
{
	for (int i=0; i<NumPlanes; ++i)
	{
		Plane plane = m_Planes[i];
		if ( !PlaneInside(plane, point) )
			return false;
	}

	return true;
}


//
// Frustum::Frustum					- Chapter 14, page 466
//
bool Frustum::Inside(Vec &point, float radius) const
{
	for(int i = 0; i < NumPlanes; ++i) 
	{
		Plane plane = m_Planes[i];
		if ( !PlaneInside(plane, point, radius) )
			return false;
	}	

	// otherwise we are fully in view
	return true;
}

//
// Frustum::Frustum					- Chapter 14, page 466
//
void Frustum::Init(const float fov, const float aspect, const float nearClip, const float farClip)
{
	m_Fov = fov;
	m_Aspect = aspect;
	m_Near = nearClip;
	m_Far = farClip;

	double tanFovOver2 = tan(m_Fov/2.0f);
	Vec nearRight = (float)(m_Near * tanFovOver2) * m_Aspect * VEC_RIGHT;
	Vec farRight = (float)(m_Far * tanFovOver2) * m_Aspect * VEC_RIGHT;
	Vec nearUp = (float)(m_Near * tanFovOver2 ) * VEC_UP;
	Vec farUp = (float)(m_Far * tanFovOver2)  * VEC_UP;

	// points start in the upper right and go around clockwise
	m_NearClip[0] = (m_Near * VEC_FORWARD) - nearRight + nearUp;
	m_NearClip[1] = (m_Near * VEC_FORWARD) + nearRight + nearUp;
	m_NearClip[2] = (m_Near * VEC_FORWARD) + nearRight - nearUp;
	m_NearClip[3] = (m_Near * VEC_FORWARD) - nearRight - nearUp;

	m_FarClip[0] = (m_Far * VEC_FORWARD) - farRight + farUp;
	m_FarClip[1] = (m_Far * VEC_FORWARD) + farRight + farUp;
	m_FarClip[2] = (m_Far * VEC_FORWARD) + farRight - farUp;
	m_FarClip[3] = (m_Far * VEC_FORWARD) - farRight - farUp;

	// now we have all eight points. Time to construct 6 planes.
	// the normals point away from you if you use counter clockwise verts.

	Vec origin(0.0f, 0.0f, 0.0f);
	m_Planes[Near]	 = PlaneFromPoints(m_NearClip[2], m_NearClip[1], m_NearClip[0]);
	m_Planes[Far]	 = PlaneFromPoints(m_FarClip[0], m_FarClip[1], m_FarClip[2]);
	m_Planes[Right]  = PlaneFromPoints(m_FarClip[2], m_FarClip[1], origin);
	m_Planes[Top]	 = PlaneFromPoints(m_FarClip[1], m_FarClip[0], origin);
	m_Planes[Left]	 = PlaneFromPoints(m_FarClip[0], m_FarClip[3], origin);
	m_Planes[Bottom] = PlaneFromPoints(m_FarClip[3], m_FarClip[2], origin);
}


Vec BLOCOCORE_API BarycentricToVec3(Vec v0, Vec v1, Vec v2, float u, float v)
{
	//V1 + U(V2 - V1) + V(V3 - V1).
	return Vec( v0 + u * (v1  - v0) + v * (v2 - v0) );
}

bool BLOCOCORE_API IntersectTriangle( Vec orig, Vec dir, Vec v0, Vec v1, Vec v2, FLOAT &t, FLOAT &u, FLOAT &v )
{
	// Find vectors for two edges sharing vert0
	Vec edge1 = v1 - v0;
	Vec edge2 = v2 - v0;

	// Begin calculating determinant - also used to calculate U parameter
	Vec pvec = VecCross(dir,edge2);

	// If determinant is near zero, ray lies in plane of triangle
	FLOAT det = VecDot(edge1,pvec).GetX();

	Vec tvec;
	if( det > 0 )
	{
		tvec = orig - v0;
	}
	else
	{
		tvec = v0 - orig;
		det = -det;
	}

	if( det < 0.0001f )
		return FALSE;

	// Calculate U parameter and test bounds
	u = VecDot( tvec, pvec ).GetX();
	if( u < 0.0f || u > det )
		return FALSE;

	// Prepare to test V parameter
	Vec qvec = VecCross( tvec, edge1 );

	// Calculate V parameter and test bounds
	v = VecDot( dir, qvec ).GetX();
	if( v < 0.0f || u + v > det )
		return FALSE;

	// Calculate t, scale parameters, ray intersects triangle
	t = VecDot( edge2, qvec ).GetX();
	FLOAT fInvDet = 1.0f / det;
	t *= fInvDet;
	u *= fInvDet;
	v *= fInvDet;


	return TRUE;
}