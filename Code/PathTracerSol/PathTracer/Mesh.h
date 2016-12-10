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

class Material;
class Triangle;

class Mesh
{

public:

	std::vector<Triangle> triangles;
	Material material;

	Mesh(const std::vector<Triangle>& triangles, const Material &material) :
		triangles(triangles), material(material)
	{

	}
	Mesh(){}
};

#endif