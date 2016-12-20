#include "Quadric.h"
#include "Ray.h"

bool Quadric::intersect(const Ray& ray, Intersection &inter){

	double  acoef, bcoef, ccoef;// Intersection coefficents
	double  dx, dy, dz;// Direction - origin coordinates
	double  disc;// Distance to intersection
	double  root;// Root of distance to intersection
	double  x0, y0, z0;// Origin coordinates
	double t;

	dx = ray.direction.x;
	dy = ray.direction.y;
	dz = ray.direction.z;

	x0 = ray.origin.x;
	y0 = ray.origin.y;
	z0 = ray.origin.z;

	acoef = 2 * f * dx * dz + 2 * e * dy * dz + c * dz * dz + b * dy * dy +
		a * dx * dx + 2 * d * dx * dy;

	bcoef = 2 * b * y0 * dy + 2 * a * x0 * dx + 2 * c * z0 * dz +
		2 * h * dy + 2 * g * dx + 2 * j * dz + 2 * d * x0 * dy +
		2 * e * y0 * dz + 2 * e * z0 * dy + 2 * d * y0 * dx +
		2 * f * x0 * dz + 2 * f * z0 * dx;

	ccoef = a * x0 * x0 + 2 * g * x0 + 2 * f * x0 * z0 + b * y0 * y0 +
		2 * e * y0 * z0 + 2 * d * x0 * y0 + c * z0 * z0 + 2 * h * y0 +
		2 * j * z0 + k;

	//  The following was modified by David J. Brandow to allow for planar
	//  quadrics

	if (1.0 + acoef == 1.0) {
		if (1.0 + bcoef == 1.0) {
			return false;
		}

		t = (-ccoef) / (bcoef);

	}
	else {
		disc = bcoef * bcoef - 4 * acoef * ccoef;
		if (1.0 + disc < 1.0) {
			return false;
		}

		root = sqrt(disc);
		t = (-bcoef - root) / (acoef + acoef);
		if (t < 0.0) {
			t = (-bcoef + root) / (acoef + acoef);
		}
	}

	if (t < 0.001)
		return false;

	glm::vec3 wp = ray.origin + (float)t * ray.direction;
	const float x = wp.x;
	const float y = wp.y;
	const float z = wp.z;

	float gradx = 2 * a * x + d * y + e * z + g;
	float grady = 2 * b * y + d * x + f * z + h;
	float gradz = 2 * c * z + e * x + f * y + j;

	inter.t = t;
	glm::vec3 normal = glm::normalize(glm::vec3(gradx, grady, gradz));
	/*if (glm::dot(normal, ray.direction)>0){
	normal = -normal;
	}*/
	inter.normal = normal;
	inter.worldPosition = wp;
	inter.objType = QUADRIC;

	return true;
}