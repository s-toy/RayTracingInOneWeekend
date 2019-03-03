#include "metal.h"
#include "math.h"

CMetal::CMetal(const vec3& vAlbedo, float vFuzz) : m_Albedo(vAlbedo)
{
	m_Fuzz = vFuzz < 1 ? vFuzz : 1;
}

//***************************************************************************************
//FUNCTION:
bool CMetal::scatterV(const CRay& vIncidentRay, const SHitRecord& vHitRecord, vec3& voAttenuation, CRay& voScatteredRay) const
{
	vec3 reflected = reflect(unit_vector(vIncidentRay.direction()), vHitRecord.normal);

	voScatteredRay = CRay(vHitRecord.p, reflected + m_Fuzz * randomInUnitSphere());
	voAttenuation = m_Albedo;

	return (dot(voScatteredRay.direction(), vHitRecord.normal) > 0);
}