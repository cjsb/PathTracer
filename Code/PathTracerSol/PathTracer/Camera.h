#ifndef _camera_h
#define _camera_h

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

	glm::vec3 cameraDir;
	glm::vec3 camRight;
	glm::vec3 camDown;

	Camera(const glm::vec3 eye, const glm::vec3 lookAt, const glm::vec3 up) : zNear(0.1f), zFar(100.f), foV(glm::pi<float>() / 2.0f), eye(eye), lookAt(lookAt), up(up){
		
		glm::vec3 diff_btw = lookAt - eye;
		cameraDir = glm::normalize(diff_btw);
		camRight = glm::normalize(glm::cross(up, cameraDir));
		camDown = glm::cross(camRight, cameraDir);
	};
	
	Camera(){};

};
#endif