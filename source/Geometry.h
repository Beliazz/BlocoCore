#pragma once

#include "BlocoCore.h"

#define VEC_UP				Vec(0.0f, 1.0f, 0.0f)
#define VEC_RIGHT			Vec(1.0f, 0.0f, 0.0f)
#define VEC_FORWARD			Vec(0.0f, 0.0f, 1.0f)



////////////////////////////////////////////////////
//
// Frustum Definition
//
////////////////////////////////////////////////////

class BLOCOCORE_API Frustum
{
public:
	enum Side { Near, Far, Top, Right, Bottom, Left, NumPlanes };

	Plane m_Planes[NumPlanes];	// planes of the frusum in camera space
	Vec m_NearClip[4];			// verts of the near clip plane in camera space
	Vec m_FarClip[4];			// verts of the far clip plane in camera space

	float m_Fov;				// field of view in radians
	float m_Aspect;				// aspect ratio - width divided by height
	float m_Near;				// near clipping distance
	float m_Far;				// far clipping distance

public:
	Frustum();

	bool Inside(Vec &point) const;
	bool Inside(Vec &point, float radius) const;
	void Init(const float fov, const float aspect, const float near, const float far);

	const Plane &Get(Side side)		{ return m_Planes[side]; }
	void SetFOV(float fov)			{ m_Fov=fov; Init(m_Fov, m_Aspect, m_Near, m_Far); }
	void SetAspect(float aspect)	{ m_Aspect=aspect; Init(m_Fov, m_Aspect, m_Near, m_Far); }
	void SetNear(float nearClip)	{ m_Near=nearClip; Init(m_Fov, m_Aspect, m_Near, m_Far); }
	void SetFar(float farClip)		{ m_Far=farClip; Init(m_Fov, m_Aspect, m_Near, m_Far); }
	
	// void Render();
};

// converts Barycentric coordinates to world coordinates
// inputs are the 3 verts of the triangle, and the u,v barycentric coordinates
extern Vec  BLOCOCORE_API  BarycentricToVec3(Vec v0, Vec v1, Vec v2, float u, float v);
extern bool BLOCOCORE_API IntersectTriangle( Vec orig, Vec dir, Vec v0, Vec v1, Vec v2, FLOAT &t, FLOAT &u, FLOAT &v );