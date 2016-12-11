#include "Mesh.h"
#include <limits>       // std::numeric_limits

bool Mesh::intersect(const Ray& ray, Intersection &inter){

	double tInt= std::numeric_limits<double>::max();
	bool intersected = false;
	for (int j = 0; j < triangles.size(); ++j){

		double t;
		double u;
		double v;

		bool findTri = triangles.at(j).rayTriangleIntersect(ray, t, u, v);
		//cout << t << endl;
		//bool find = 
		if (findTri){
			if (t < tInt){
				tInt = t;
				intersected = true;
			}
			
		}
	}

	if (intersected){
		inter.t = tInt;
	}
	else{
		inter.t = -1;
	}

	return intersected;
}