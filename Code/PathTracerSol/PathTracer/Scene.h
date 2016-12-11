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
#include "Object.h"

#include <vector>

class Scene
{

public:

	std::vector<Object*> objects;
	std::vector<Mesh> meshes;
	std::vector<Quadric> quadrics;
	std::vector<Light> lights;
	Camera camera;

	Scene(const std::vector<Object*>& objects, const std::vector<Mesh>& meshes, const	std::vector<Quadric>& quadrics, const std::vector<Light>& lights, const Camera& camera) :
		objects(objects), meshes(meshes), quadrics(quadrics), lights(lights), camera(camera){}

	Scene(){}

	~Scene(){}

	void load();
};

#endif