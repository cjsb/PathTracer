#ifndef _options_h
#define _options_h

#include "glm\glm\glm.hpp"
#include "Material.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Light.h"

using namespace glm;

class Options
{

public:
	
	int npaths, seed;
	double tonemapping, ambient;
	vec3 eye, background;
	vec2 size;
	char *objName, *fileName, *objLight;
	Light light;
	Material objMaterial;

	Options(){}
	~Options(){}

	void readOptions();
};

#endif