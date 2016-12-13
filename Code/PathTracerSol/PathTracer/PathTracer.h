#ifndef _pathtracer_h
#define _pathtracer_h
#define M_PI           3.14159265358979323846

#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\constants.hpp"
#include "Scene.h"
#include "Ray.h"
#include "Intersection.h"
#include "Light.h"
#include "Options.h"
#include <algorithm>
#include <random>

	enum TYPERAY{DIFFUSE, SPECULAR, TRANSMITED};

	glm::vec3 phongShading(const Material& mat, const Light& light, const glm::vec3& L, const glm::vec3& N, const glm::vec3& V, const glm::vec3& R);

	std::vector<bool> findLight(const Scene &scene, const Intersection &inter);

	glm::vec3 tracer(const Ray &ray, const Scene &scene, const Options &options, int depth);

	bool rayCast(const Ray &ray, const Scene &scene, Intersection &inter);

	TYPERAY chooseRay(double Kd, double Ks, double Kt);

	bool hitLight(const Scene &scene, const Intersection &inter);

#endif