
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>
#include <utility>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <cmath>
#include <limits>
#include <random>

#include "glm\glm\glm.hpp"

bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1)
{
	float discr = b * b - 4 * a * c;
	if (discr < 0) return false;
	else if (discr == 0) {
		x0 = x1 = -0.5 * b / a;
	}
	else {
		float q = (b > 0) ?
			-0.5 * (b + sqrt(discr)) :
			-0.5 * (b - sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}

	return true;
}

class Sphere
{
public:
	Sphere(const glm::vec3 &c, const float &r) : radius(r), radius2(r *r), center(c) {}
	// [comment]
	// Ray-sphere intersection test
	//
	// \param orig is the ray origin
	//
	// \param dir is the ray direction
	//
	// \param[out] is the distance from the ray origin to the intersection point
	//
	// [/comment]
	bool intersect(const glm::vec3 &orig, const glm::vec3 &dir, float &t) const
	{
		float t0, t1; // solutions for t if the ray intersects
#if 0
		// geometric solution
		Vec3f L = center - orig;
		float tca = L.dotProduct(dir);
		if (tca < 0) return false;
		float d2 = L.dotProduct(L) - tca * tca;
		if (d2 > radius2) return false;
		float thc = sqrt(radius2 - d2);
		t0 = tca - thc;
		t1 = tca + thc;
#else
		// analytic solution
		glm::vec3 L = orig - center;
		float a = glm::dot(dir, dir);
		float b = 2 * glm::dot(dir, L);
		float c = glm::dot(L, L)  - radius2;
	/*	float a = dir.dotProduct(dir);
		float b = 2 * dir.dotProduct(L);
		float c = L.dotProduct(L) - radius2;*/
		if (!solveQuadratic(a, b, c, t0, t1)) return false;
#endif
		if (t0 > t1) std::swap(t0, t1);

		if (t0 < 0) {
			t0 = t1; // if t0 is negative, let's use t1 instead
			if (t0 < 0) return false; // both t0 and t1 are negative
		}

		t = t0;

		return true;
	}
	
	float radius, radius2;
	glm::vec3 center;
};
