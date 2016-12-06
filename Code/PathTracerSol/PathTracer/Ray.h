//#include "glm\glm\vec3.hpp"
//#include "glm\glm\vec4.hpp"
//#include "glm\glm\mat4x4.hpp"
//#include "glm\glm\gtc\matrix_transform.hpp"
#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\constants.hpp"

class Ray{

public:
	glm::vec3 origin;
	glm::vec3 direction;

	Ray(const glm::vec3 org, const glm::vec3 dir) : origin(org), direction(dir){}

};