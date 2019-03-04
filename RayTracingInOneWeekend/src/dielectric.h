#pragma once
#include "material.h"

class CDielectric : public CMaterial
{
public:
	CDielectric(float vRefractionIndex) : m_RefractionIndex(vRefractionIndex) {}

	virtual bool scatterV(const CRay& vIncidentRay, const SHitRecord& vHitRecord, vec3& voAttenuation, CRay& voScatteredRay) const override;

private:
	float m_RefractionIndex;
};