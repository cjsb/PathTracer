#ifndef _intersection_h
#define _intersection_h

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

enum ObjType { MESH, QUADRIC, LIGHT };

class Intersection
{

public:
	
	ObjType objType;
	glm::vec3 worldPosition;
	glm::vec3 normal;
	double t;
	int index;

	Intersection(const ObjType &objType, const glm::vec3 &worldPosition, const glm::vec3 &normal, const double &t, const int &index) :
	objType(objType), worldPosition(worldPosition), normal(normal), t(t), index(index){}
	Intersection(){}
	~Intersection(){}
};

#endif