
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

class Material;

class Quadric
{

public:

	double  a, b, c, d, e;	// Surface coefficents
	double  f, g, h, j, k;
	Material material;				// Surface's material properties

	Quadric(const double& a, const double& b, const double& c, const double& d, const double& e, const double& f, const double& g, const double& h,
		const double& j, const double& k, const Material& material)
		: a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), j(j), k(k), material(material) {};
	
	~Quadric(){};
	
	bool intersect(const Ray& ray, double &t);
};

#endif