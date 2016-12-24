
#ifndef _quadric_h
#define _quadric_h

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
#include "Material.h"
#include "Ray.h"
#include "Object.h"
#include "Intersection.h"

class Quadric : public Object
{

public:

	double  a, b, c, d, e;	// Surface coefficents
	double  f, g, h, j, k;
	//Material material;				// Surface's material properties
	glm::vec3 bBoxMin;
	glm::vec3 bBoxMax;

	Quadric(const double& a, const double& b, const double& c, const double& d, const double& e, const double& f, const double& g, const double& h,
		const double& j, const double& k, const glm::vec3 &bBoxMin, const glm::vec3 &bBoxMax)
		: a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), j(j), k(k), bBoxMin(bBoxMin), bBoxMax(bBoxMax){};
	
	Quadric(){};
	~Quadric(){};
	
	bool intersect(const Ray& ray, Intersection &inter);
};

#endif