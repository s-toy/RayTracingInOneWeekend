#pragma once
#include "hitable.h"

class CSphere : public CHitable
{
public:
	CSphere() {}
	CSphere(vec3 vCenter, float vRadius) : m_Center(vCenter), m_Radius(vRadius) {};

	virtual bool hitV(const CRay& vRay, float vMinT, float vMaxT, SHitRecord& voRec) const override;

private:
	float m_Radius;
	vec3 m_Center;
};