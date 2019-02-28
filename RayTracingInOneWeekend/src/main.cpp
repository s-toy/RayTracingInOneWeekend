#include <fstream>
#include "ray.h"

bool hitSphere(const vec3& vCenter, float vRadius, const CRay& vRay)
{
	vec3 p = vRay.origin() - vCenter;
	float a = dot(vRay.direction(), vRay.direction());
	float b = 2.0 * dot(p, vRay.direction());
	float c = dot(p, p) - vRadius * vRadius;
	float discriminant = b * b - 4 * a * c;
	return (discriminant > 0);
}

vec3 color(const CRay& vRay)
{
	if (hitSphere(vec3(0, 0, -1), 0.5, vRay))
		return vec3(1, 0, 0);

	vec3 unitDirection = unit_vector(vRay.direction());
	float t = 0.5 * (unitDirection.y() + 1.0);
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main()
{
	int nx = 200;
	int ny = 100;

	std::ofstream ofs("output.ppm");
	ofs << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lowerleftCorner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);

	for (int k = ny - 1; k >= 0; k--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(k) / float(ny);

			CRay ray(origin, lowerleftCorner + u * horizontal + v * vertical);
			vec3 col = color(ray);

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			ofs << ir << " " << ig << " " << ib << "\n";
		}
	}
}