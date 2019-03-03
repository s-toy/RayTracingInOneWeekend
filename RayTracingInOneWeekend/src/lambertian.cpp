#include "lambertian.h"
#include "math.h"

//***************************************************************************************
//FUNCTION:
bool CLambertian::scatterV(const CRay& vIncidentRay, const SHitRecord& vHitRecord, vec3& voAttenuation, CRay& voScatteredRay) const
{
	vec3 target = vHitRecord.p + vHitRecord.normal + randomInUnitSphere();

	voScatteredRay = CRay(vHitRecord.p, target - vHitRecord.p);
	voAttenuation = m_Albedo;
	return true;
}
