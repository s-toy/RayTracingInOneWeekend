#include <fstream>
#include <ctime>
#include <omp.h>
#include "sphere.h"
#include "hitableList.h"
#include "camera.h"
#include "math.h"
#include "material.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

#define NUM_HITABLE 5
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

CHitable* randomScene()
{
	int n = 500;
	CHitable** ppList = new CHitable*[n + 1];
	ppList[0] = new CSphere(vec3(0, -1000, 0), 1000, new CLambertian(vec3(0.5, 0.5, 0.5)));

	int i = 1;

#pragma omp parallel for
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float chooseMat = rand_0_1();
			vec3 center(a + 0.9 * rand_0_1(), 0.2, b + 0.9 * rand_0_1());
			if ((center - vec3(4, 0.2, 0)).length() > 0.9)
			{
				if (chooseMat < 0.5)
				{
					ppList[i++] = new CSphere(center, 0.2, new CLambertian(vec3(rand_0_1()*rand_0_1(), rand_0_1()*rand_0_1(), rand_0_1()*rand_0_1())));
				}
				else if (chooseMat < 0.8)
				{
					ppList[i++] = new CSphere(center, 0.2, new CMetal(vec3(0.5*(1 + rand_0_1()), 0.5*(1 + rand_0_1()), 0.5*(1 + rand_0_1())), 0.5 * rand_0_1()));
				}
				else
				{
					ppList[i++] = new CSphere(center, 0.2, new CDielectric(1.5));
				}
			}
		}
	}

	ppList[i++] = new CSphere(vec3(0, 1, 0), 1.0, new CDielectric(1.5));
	ppList[i++] = new CSphere(vec3(-4, 1, 0), 1.0, new CLambertian(vec3(0.4, 0.2, 0.1)));
	ppList[i++] = new CSphere(vec3(4, 1, 0), 1.0, new CMetal(vec3(0.7, 0.6, 0.5), 0.0));

	return new CHitableList(ppList, i);
}

int main()
{
	srand(time(NULL));

	int nx = 1200 / 3;
	int ny = 800 / 3;
	int ns = 10;

	std::ofstream ofs("output.ppm");
	ofs << "P3\n" << nx << " " << ny << "\n255\n";

	CHitable* pWorld = randomScene();

	CCamera camera(vec3(13, 2, 3), vec3(0, 0, 0), vec3(0, 1, 0), 20, float(nx) / float(ny), 0.1, 10.0);

	time_t startTime = clock();

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

	time_t endTime = clock();
	float deltaTime = (float)(endTime - startTime) / CLOCKS_PER_SEC;
	std::cout << "time: " << deltaTime << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}