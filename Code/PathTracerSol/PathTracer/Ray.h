#ifndef _ray_h
#define _ray_h

#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\constants.hpp"

class Ray{

public:
	glm::vec3 origin;
	glm::vec3 direction;

	Ray(const glm::vec3 &org, const glm::vec3 &dir) : origin(org), direction(dir){}

};

#endif