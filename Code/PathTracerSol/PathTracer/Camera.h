#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\constants.hpp"

class Camera{

public:

	float zNear;
	float zFar;
	float foV;

	glm::vec3 eye;
	glm::vec3 lookAt;
	glm::vec3 up;

	Camera(const glm::vec3 eye, const glm::vec3 lookAt, const glm::vec3 up) : zNear(0.1f), zFar(100.f), foV(glm::pi<float>() / 2.0f), eye(eye), lookAt(lookAt), up(up){
	};

};