#ifndef _triangle_h
#define _triangle_h

#include <cmath>
#include "glm\glm\vec3.hpp"
#include "glm\glm\glm.hpp"
#include "Ray.h"
#include "Material.h"

class Material;

class Triangle
{

public:

	glm::vec3 v0, v1, v2, mid;		// Triangle's vertices
	glm::vec3 normal;
	double kEpsilon = 1e-8;

	Triangle(const glm::vec3 &Ver1, const glm::vec3 &Ver2, const glm::vec3 &Ver3) : v0(Ver1), v1(Ver2), v2(Ver3) {
		mid = (Ver1 + Ver2 + Ver3) / 3.0f;
	}
	~Triangle(){};

	bool rayTriangleIntersect(Ray ray, double &t, double &u, double &v);

};

#endif