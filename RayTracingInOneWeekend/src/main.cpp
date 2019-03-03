#include <fstream>
#include <ctime>
#include "sphere.h"
#include "hitableList.h"
#include "camera.h"
#include "math.h"
#include "material.h"
#include "lambertian.h"
#include "metal.h"

#define NUM_HITABLE 4
#define MAX_SCATTER_DEPTH 50

vec3 color(const CRay& vRay, const CHitable* vWorld, int vScatterDepth)
{
	SHitRecord rec;
	if (vWorld->hitV(vRay, 0.001, FLT_MAX, rec))
	{
		CRay scattered;
		vec3 attenuation;

		if (vScatterDepth < MAX_SCATTER_DEPTH && rec.pMaterial->scatterV(vRay, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, vWorld, vScatterDepth + 1);
		}
		else
		{
			return vec3(0, 0, 0);
		}
	}
	else
	{
		vec3 unitDirection = unit_vector(vRay.direction());
		float t = 0.5 * (unitDirection.y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

int main()
{
	int nx = 200;
	int ny = 100;
	int ns = 100;

	std::ofstream ofs("output.ppm");
	ofs << "P3\n" << nx << " " << ny << "\n255\n";

	CHitable* pHitableSet[NUM_HITABLE];
	pHitableSet[0] = new CSphere(vec3(0, 0, -1), 0.5, new CLambertian(vec3(0.8, 0.3, 0.3)));
	pHitableSet[1] = new CSphere(vec3(0, -100.5, -1), 100, new CLambertian(vec3(0.8, 0.8, 0.0)));
	pHitableSet[2] = new CSphere(vec3(1, 0, -1), 0.5, new CMetal(vec3(0.8, 0.6, 0.2), 0.3));
	pHitableSet[3] = new CSphere(vec3(-1, 0, -1), 0.5, new CMetal(vec3(0.8, 0.8, 0.8), 1.0));

	CHitable* pWorld = new CHitableList(pHitableSet, NUM_HITABLE);

	CCamera camera;

	srand(time(NULL));

	for (int k = ny - 1; k >= 0; k--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; ++s)
			{
				float u = float(i + rand_0_1()) / float(nx);
				float v = float(k + rand_0_1()) / float(ny);

				CRay ray = camera.getRay(u, v);
				vec3 p = ray.pointAtParameter(2.0);
				col += color(ray, pWorld, 0);
			}

			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			ofs << ir << " " << ig << " " << ib << "\n";
		}
	}

	for (int i = 0; i < NUM_HITABLE; ++i) { delete pHitableSet[i]; }
	delete pWorld;

	return EXIT_SUCCESS;
}