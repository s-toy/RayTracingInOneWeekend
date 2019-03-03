#pragma once
#include "hitable.h"

class CMaterial;

class CSphere : public CHitable
{
public:
	CSphere() {}
	CSphere(vec3 vCenter, float vRadius, CMaterial* vMaterial) : m_Center(vCenter), m_Radius(vRadius), m_pMaterial(vMaterial) {};

	~CSphere() { delete m_pMaterial; }

	virtual bool hitV(const CRay& vRay, float vMinT, float vMaxT, SHitRecord& voRec) const override;

private:
	float m_Radius;
	vec3 m_Center;
	CMaterial* m_pMaterial = nullptr;
};