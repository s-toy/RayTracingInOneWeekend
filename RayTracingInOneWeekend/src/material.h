#pragma once
#include "ray.h"
#include "hitable.h"

class CMaterial
{
public:
	virtual bool scatterV(const CRay& vIncidentRay, const SHitRecord& vHitRecord, vec3& voAttenuation, CRay& voScatteredRay) const = 0;
};