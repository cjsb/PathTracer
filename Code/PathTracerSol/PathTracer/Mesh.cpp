#include "Mesh.h"
#include <limits>       // std::numeric_limits

bool Mesh::intersect(const Ray& ray, Intersection& inter) 
{
	float closest_distance = FLT_MAX;
	bool any_intersection = false;

	for (const auto& tr : triangles) {
		float r, a, b;
		glm::vec3 u = tr.v1 - tr.v0;
		glm::vec3 v = tr.v2 - tr.v0;
		glm::vec3 n = glm::cross(u, v);

		glm::vec3 dir = ray.direction;
		glm::vec3 w0 = ray.origin - tr.v0;
		a = -glm::dot(n, w0);
		b = glm::dot(n, dir);

		if (fabs(b) < 0.00000001)
			continue;

		r = a / b;
		if (r < 0.0)
			continue;

		glm::vec3 i = ray.origin + r * dir; // ponto de intersecao

		float uu, uv, vv, wu, wv, D;
		uu = glm::dot(u, u);
		uv = glm::dot(u, v);
		vv = glm::dot(v, v);
		glm::vec3 w = i - tr.v0;
		wu = dot(w, u);
		wv = dot(w, v);
		D = uv * uv - uu * vv;

		float s, t;
		s = (uv * wv - vv * wu) / D;
		if (s < 0.0 || s > 1.0)
			continue;

		t = (uv * wu - uu * wv) / D;
		if (t < 0.0 || (s + t) > 1.0)
			continue;

		float d = glm::distance(i, ray.origin);
		if (d > closest_distance)
			continue;

		closest_distance = d;
		any_intersection = true;

		inter.normal = glm::normalize(n);

		inter.worldPosition = i;
		inter.t = r;
		inter.objType = MESH;
	}

	return any_intersection;
}

//bool Mesh::intersect(const Ray& ray, Intersection &inter){
//
//	double tInt= std::numeric_limits<double>::max();
//	bool intersected = false;
//	glm::vec3 normalTriangle;
//	for (int j = 0; j < triangles.size(); ++j){
//
//		double t = 0;
//		double u = 0;
//		double v = 0;
//
//		bool findTri = triangles.at(j).rayTriangleIntersect(ray, t, u, v);
//		//cout << t << endl;
//		//bool find = 
//
//		if (findTri){
//			intersected = true;
//			if (t < tInt){
//				tInt = t;
//				normalTriangle = triangles.at(j).normal;
//				intersected = true;
//			}
//			
//		}
//	}
//
//	if (intersected){
//		inter.t = tInt;
//		inter.worldPosition = ray.origin + (float)inter.t*ray.direction;
//		inter.objType = MESH;
//		inter.normal = glm::normalize(normalTriangle);
//
//	}
//	else{
//		inter.t = -1;
//	}
//
//	return intersected;
//}