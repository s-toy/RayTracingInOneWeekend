#include "dielectric.h"
#include "math.h"

//**********************************************************************************************************************************
//FUNCTION:
bool CDielectric::scatterV(const CRay& vIncidentRay, const SHitRecord& vHitRecord, vec3& voAttenuation, CRay& voScatteredRay) const
{
	vec3 outwardNormal;
	vec3 reflected = reflect(vIncidentRay.direction(), vHitRecord.normal);
	float ni_over_nt;
	vec3 refracted;
	float reflectCoeff;
	float cosine;

	if (dot(vIncidentRay.direction(), vHitRecord.normal) > 0)
	{
		outwardNormal = -vHitRecord.normal;
		ni_over_nt = m_RefractionIndex;
		cosine = m_RefractionIndex * dot(vIncidentRay.direction(), vHitRecord.normal) / vIncidentRay.direction().length();
	}
	else
	{
		outwardNormal = vHitRecord.normal;
		ni_over_nt = 1.0 / m_RefractionIndex;
		cosine = -dot(vIncidentRay.direction(), vHitRecord.normal) / vIncidentRay.direction().length();
	}

	voAttenuation = vec3(1.0, 1.0, 1.0);

	if (refract(vIncidentRay.direction(), outwardNormal, ni_over_nt, refracted))
	{
		reflectCoeff = schlick(cosine, m_RefractionIndex);
	}
	else
	{
		voScatteredRay = CRay(vHitRecord.p, reflected);
		reflectCoeff = 1.0;
	}

	if (rand_0_1() < reflectCoeff)
	{
		voScatteredRay = CRay(vHitRecord.p, reflected);
	}
	else
	{
		voScatteredRay = CRay(vHitRecord.p, refracted);
	}

	return true;
}
