#ifndef _pathtracer_h
#define _pathtracer_h

#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\constants.hpp"
#include "Scene.h"
#include "Ray.h"
#include "Intersection.h"
#include "Light.h"



	glm::vec3 tracer(const Ray &ray, const Scene &scene, int &depth);

	bool rayCast(const Ray &ray, const Scene &scene, Intersection &inter);



#endif