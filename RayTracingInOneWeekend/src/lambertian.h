#pragma once
#include "material.h"

class CLambertian : public CMaterial
{
public:
	CLambertian(const vec3& vAlbedo) : m_Albedo(vAlbedo) {}
	virtual bool scatterV(const CRay& vIncidentRay, const SHitRecord& vHitRecord, vec3& voAttenuation, CRay& voScatteredRay) const override;

private:
	vec3 m_Albedo;
};