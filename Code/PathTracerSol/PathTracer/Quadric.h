#include "Material.h"

//class Material;

class Quadric
{

public:
	double  a, b, c, d, e;// Surface coefficents
	double  f, g, h, j, k;
	Material m;// Surface's material properties
	Quadric(double Radius);
	~Quadric();
	double intersect();
};
