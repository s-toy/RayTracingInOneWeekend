#pragma once
#include "external/vec3.h"

static inline float rand_0_1() { return (float)rand() / RAND_MAX; };

static vec3 randomInUnitSphere()
{
	vec3 p;
	do {
		p = 2.0 * vec3(rand_0_1(), rand_0_1(), rand_0_1()) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;
}

static vec3 reflect(const vec3& vIncidentVec, const vec3& vNormal)
{
	return vIncidentVec - 2 * dot(vIncidentVec, vNormal) * vNormal;
}

static bool refract(const vec3& vIncidentVec, const vec3& vNormal, float vEta, vec3& voRefracted)
{
	vec3 uv = unit_vector(vIncidentVec);
	float dt = dot(uv, vNormal);
	float discriminant = 1.0 - vEta * vEta * (1 - dt * dt);

	if (discriminant > 0)
	{
		voRefracted = vEta * (uv - vNormal * dt) - vNormal * sqrt(discriminant);
		return true;
	}
	else
	{
		return false;
	}
}

static float schlick(float vCosine, float vRefractionIndex)
{
	float r0 = (1 - vRefractionIndex) / (1 + vRefractionIndex);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - vCosine), 5);
}