#ifndef _options_h
#define _options_h

#include "glm\glm\glm.hpp"
#include "Material.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Light.h"
#include "Quadric.h"
#include "Triangle.h"
#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"

using namespace glm;

class Options
{

public:
	
	int npaths, seed;
	double tonemapping, ambient;
	vec3 eye, background;
	vec2 size;
	char *objName, *objLight;
	char *outputFileName;
	Light light;
	Quadric objQuadric;
	Material objMaterial;
	

	Options(){}
	~Options(){}

	void readOptions(char* fileName, Scene &scene);
	void readObj(const char *filename, Mesh &mesh);
};

#endif