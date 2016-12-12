#include "Mesh.h"
#include <limits>       // std::numeric_limits

bool Mesh::intersect(const Ray& ray, Intersection &inter){

	double tInt= std::numeric_limits<double>::max();
	bool intersected = false;
	for (int j = 0; j < triangles.size(); ++j){

		double t = 0;
		double u = 0;
		double v = 0;

		bool findTri = triangles.at(j).rayTriangleIntersect(ray, t, u, v);
		//cout << t << endl;
		//bool find = 

		if (findTri){
			intersected = true;
			if (t < tInt){
				tInt = t;
				intersected = true;
			}
			
		}
	}

	if (intersected){
		inter.t = tInt;
		inter.worldPosition = ray.origin + (float)inter.t * ray.direction;
	}
	else{
		inter.t = -1;
	}

	return intersected;
}