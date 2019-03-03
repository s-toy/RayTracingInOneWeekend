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

static vec3 reflect(const vec3& vVector, const vec3& vNormal)
{
	return vVector - 2 * dot(vVector, vNormal) * vNormal;
}