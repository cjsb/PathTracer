#ifndef _light_h
#define _light_h

#include "Mesh.h"

class Light
{

public:

	Mesh mesh;
	double r, g, b, Ip;

	Light(const Mesh &mesh, const double &r, const double &g, const double &b, const double &Ip):
		mesh(mesh), r(r), g(g), b(b), Ip(Ip)
	{}
	Light(){}
	~Light(){}

	void readOptions();
};

#endif