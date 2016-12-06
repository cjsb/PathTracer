#include "Material.h"

#include "glm\glm\vec3.hpp"
//#include <glm/vec3.hpp> // glm::vec3


class Material;

class Triangle
{

public:

	glm::vec3 Ver1, Ver2, Ver3;		// Triangle's vertices
	Material m;

};