#pragma once
#include "ray.h"
#include "math.h"

class CCamera
{
public:
	CCamera(vec3 vLookfrom, vec3 vLookat, vec3 vUp, float vFov, float vAspect, float vAperture, float vFocusDist)
	{
		m_LensRadius = vAperture / 2;

		float theta = vFov * PI / 180;
		float halfHeight = tan(theta / 2);
		float halfWidth = vAspect * halfHeight;

		m_Origin = vLookfrom;
		w = unit_vector(vLookfrom - vLookat);
		u = unit_vector(cross(vUp, w));
		v = cross(w, u);

		m_LowerLeftCorner = m_Origin - halfWidth * vFocusDist * u - halfHeight * vFocusDist * v - vFocusDist * w;
		m_Horizontal = 2 * halfWidth *vFocusDist * u;
		m_Vertical = 2 * halfHeight * vFocusDist * v;
	}

	CRay getRay(float s, float t)
	{
		vec3 rd = m_LensRadius * randomInUnitDisk();
		vec3 offset = u * rd.x() + v * rd.y();
		return CRay(m_Origin + offset, m_LowerLeftCorner + s * m_Horizontal + t * m_Vertical - m_Origin - offset);
	}

private:
	vec3 m_Origin;
	vec3 m_LowerLeftCorner;
	vec3 m_Horizontal;
	vec3 m_Vertical;
	vec3 u, v, w;
	float m_LensRadius;
};