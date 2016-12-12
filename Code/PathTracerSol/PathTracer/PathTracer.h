#ifndef _pathtracer_h
#define _pathtracer_h

#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\constants.hpp"
#include "Scene.h"
#include "Ray.h"
#include "Intersection.h"
#include "Light.h"
#include <algorithm>

	glm::vec3 phongShading(const Material& mat, const Light& light, const glm::vec3& L, const glm::vec3& N, const glm::vec3& V, const glm::vec3& R);

	std::vector<bool> findLight(const Scene &scene, const Intersection &inter);

	glm::vec3 tracer(const Ray &ray, const Scene &scene, int &depth);

	bool rayCast(const Ray &ray, const Scene &scene, Intersection &inter);



#endif