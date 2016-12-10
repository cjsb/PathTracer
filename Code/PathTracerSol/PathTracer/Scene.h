#ifndef _scene_h
#define _scene_h

#include "glm\glm\glm.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Material.h"
#include "Mesh.h"
#include "Light.h"
#include "Quadric.h"
#include "Camera.h"

#include <vector>

class Scene
{

public:

	std::vector<Mesh> meshes;
	std::vector<Quadric> quadrics;
	std::vector<Light> lights;
	std::vector<Camera> camera;

	double r, g, b, Ip;

	Scene(const std::vector<Mesh>& meshes, const	std::vector<Quadric>& quadrics, const std::vector<Light>& lights, const std::vector<Camera>& camera) :
		meshes(meshes), quadrics(quadrics), lights(lights), camera(camera)
	{}
	Scene(){}
	~Scene(){}

	void load();
};

#endif