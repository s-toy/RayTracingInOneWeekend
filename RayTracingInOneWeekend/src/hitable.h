#pragma once
#include "ray.h"

struct SHitRecord
{
	float t;
	vec3 p;
	vec3 normal;
};

class CHitable
{
public:
	virtual bool hitV(const CRay& vRay, float vMinT, float vMaxT, SHitRecord& voRec) const = 0;
};