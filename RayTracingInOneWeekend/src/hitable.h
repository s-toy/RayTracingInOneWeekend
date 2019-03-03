#pragma once
#include "ray.h"

class CMaterial;

struct SHitRecord
{
	float t;
	vec3 p;
	vec3 normal;
	CMaterial* pMaterial = nullptr;
};

class CHitable
{
public:
	CHitable() {}
	virtual ~CHitable() {}

	virtual bool hitV(const CRay& vRay, float vMinT, float vMaxT, SHitRecord& voRec) const = 0;
};