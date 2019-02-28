#pragma once
#include "external/vec3.h"

class CRay
{
public:
	CRay() {}
	CRay(const vec3& vOrigin, const vec3& vDirection) : m_Origin(vOrigin), m_Direction(vDirection) {}

	vec3 origin() const { return m_Origin; }
	vec3 direction() const { return m_Direction; }
	vec3 pointAtParameter(float t) const { return m_Origin + t * m_Direction; }

private:
	vec3 m_Origin;
	vec3 m_Direction;
};