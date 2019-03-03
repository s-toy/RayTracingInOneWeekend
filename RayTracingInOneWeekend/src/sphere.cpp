#include "sphere.h"

//***************************************************************************************
//FUNCTION:
bool CSphere::hitV(const CRay& vRay, float vMinT, float vMaxT, SHitRecord& voRec) const
{
	vec3 oc = vRay.origin() - m_Center;
	float a = dot(vRay.direction(), vRay.direction());
	float b = dot(oc, vRay.direction());
	float c = dot(oc, oc) - m_Radius * m_Radius;
	float discriminant = b * b - a * c;

	if (discriminant > 0)
	{
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp < vMaxT && temp > vMinT)
		{
			voRec.t = temp;
			voRec.p = vRay.pointAtParameter(voRec.t);
			voRec.normal = (voRec.p - m_Center) / m_Radius;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < vMaxT && temp > vMinT)
		{
			voRec.t = temp;
			voRec.p = vRay.pointAtParameter(voRec.t);
			voRec.normal = (voRec.p - m_Center) / m_Radius;
			return true;
		}
	}

	return false;
}