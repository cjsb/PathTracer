
#ifndef _object_h
#define _object_h

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
#include "Intersection.h"

class Material;

class Object
{

public:
	Material material;				// Surface's material properties

	Object(){};
	~Object(){};

	bool intersect(const Ray& ray, Intersection &inter);
};

#endif