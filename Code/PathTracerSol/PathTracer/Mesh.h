#ifndef _mesh_h
#define _mesh_h

#include <cmath>
#include "glm\glm\vec3.hpp"
#include "glm\glm\glm.hpp"
#include "Ray.h"
#include "Material.h"
#include "Triangle.h"
#include <iostream>
#include <vector>
#include "Object.h"

class Material;
class Triangle;

class Mesh : public Object
{

public:

	std::vector<Triangle> triangles;
	/*Material material;*/

	Mesh(const std::vector<Triangle>& triangles) :
		triangles(triangles)
	{

	}
	Mesh(){}

	glm::vec3 samplePosition();

	bool intersect(const Ray& ray, Intersection &inter);
};

#endif