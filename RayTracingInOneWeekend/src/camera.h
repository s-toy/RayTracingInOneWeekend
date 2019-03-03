#pragma once
#include "ray.h"

class CCamera
{
public:
	CCamera()
	{
		m_Origin = vec3(0.0, 0.0, 0.0);
		m_LowerLeftCorner = vec3(-2.0, -1.0, -1.0);
		m_Horizontal = vec3(4.0, 0.0, 0.0);
		m_Vertical = vec3(0.0, 2.0, 0.0);
	}

	CRay getRay(float u, float v) { return CRay(m_Origin, m_LowerLeftCorner + u * m_Horizontal + v * m_Vertical - m_Origin); }

private:
	vec3 m_Origin;
	vec3 m_LowerLeftCorner;
	vec3 m_Horizontal;
	vec3 m_Vertical;
};