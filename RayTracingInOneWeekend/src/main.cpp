#include <fstream>
#include <ctime>
#include "sphere.h"
#include "hitableList.h"
#include "camera.h"

vec3 color(const CRay& vRay, const CHitable* vWorld)
{
	SHitRecord rec;
	if (vWorld->hitV(vRay, 0.0, FLT_MAX, rec))
	{
		return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
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

	CHitable* list[2];
	list[0] = new CSphere(vec3(0, 0, -1), 0.5);
	list[1] = new CSphere(vec3(0, -100.5, -1), 100);
	CHitable* world = new CHitableList(list, 2);

	CCamera camera;

	srand(time(NULL));

	auto rand_0_1 = []()->float {
		return (float)rand() / RAND_MAX;
	};

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
				col += color(ray, world);
			}

			col /= float(ns);

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			ofs << ir << " " << ig << " " << ib << "\n";
		}
	}

	return EXIT_SUCCESS;
}