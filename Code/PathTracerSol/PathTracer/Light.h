#ifndef _light_h
#define _light_h

#include "Mesh.h"

class Light
{

public:

	Mesh mesh;
	double r, g, b, Ip;

	glm::vec3 centralPoint;

	Light(const Mesh &mesh, const double &r, const double &g, const double &b, const double &Ip):
		mesh(mesh), r(r), g(g), b(b), Ip(Ip)
	{
		centralPoint = glm::vec3(0, 0, 0);
		for (int triangle = 0; triangle < mesh.triangles.size(); triangle++){
			centralPoint += mesh.triangles.at(triangle).v0;
			centralPoint += mesh.triangles.at(triangle).v1;
			centralPoint += mesh.triangles.at(triangle).v2;
		}
		centralPoint /= (mesh.triangles.size() * (float)3);
	
	}
	Light(){}
	~Light(){}

	void readOptions();
};

#endif