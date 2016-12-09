#ifndef _material_h
#define _material_h

class Material
{

public:
	double  r;// Red component
	double  b;// Blue component
	double  g;// Green component
	double  Ka;// Ambient reflection coefficent
	double  Kd;// Diffuse reflection coefficent
	double  Ks;// Specular reflection coefficent
	double  Kt;
	int  n;// Specular reflection exponent

	Material(){}
	~Material(){}
};

#endif