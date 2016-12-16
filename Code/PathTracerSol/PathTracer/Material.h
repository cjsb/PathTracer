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
	double ri;

	Material(const double &r, const double &b, const double &g,
		const double &Ka, const double &Kd, const double &Ks, const double &Kt, const int &n, const double &ri) :
	r(r), b(b), g(g), Ka(Ka), Kd(Kd), Ks(Ks), Kt(Kt), n(n), ri(ri) {}
	Material(){}
	~Material(){}
};

#endif