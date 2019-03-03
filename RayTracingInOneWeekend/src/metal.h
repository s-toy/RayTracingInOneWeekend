#pragma once
#include "material.h"

class CMetal : public CMaterial
{
public:
	CMetal(const vec3& vAlbedo, float vFuzz);

	virtual bool scatterV(const CRay& vIncidentRay, const SHitRecord& vHitRecord, vec3& voAttenuation, CRay& voScatteredRay) const override;

private:
	vec3 m_Albedo;
	float m_Fuzz;
};