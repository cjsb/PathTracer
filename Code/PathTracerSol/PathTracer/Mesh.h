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

	std::vector<Triangle> mesh;
	std::vector<int> test;
	Material material;

	Mesh(const std::vector<Triangle>& mesh, const Material &material, const std::vector<int>& test):
		mesh(mesh), material(material), test(test)
	{

	}
	
};

#endif