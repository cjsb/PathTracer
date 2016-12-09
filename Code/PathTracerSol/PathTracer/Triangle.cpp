#include "Triangle.h"

using namespace glm;

bool Triangle::rayTriangleIntersect(Ray ray, double &t, double &u, double &v)
{
#ifdef MOLLER_TRUMBORE 
	Vec3f v0v1 = triangle.v1 - triangle.v0;
	Vec3f v0v2 = triangle.v2 - triangle.v0;
	Vec3f pvec = dir.crossProduct(v0v2);
	float det = v0v1.dotProduct(pvec);
#ifdef CULLING 
	// if the determinant is negative the triangle is backfacing
	// if the determinant is close to 0, the ray misses the triangle
	if (det < kEpsilon) return false;
#else 
	// ray and triangle are parallel if det is close to 0
	if (fabs(det) < kEpsilon) return false;
#endif 
	float invDet = 1 / det;

	Vec3f tvec = ray.origin - triangle.v0;
	u = tvec.dotProduct(pvec) * invDet;
	if (u < 0 || u > 1) return false;

	Vec3f qvec = tvec.crossProduct(v0v1);
	v = dir.dotProduct(qvec) * invDet;
	if (v < 0 || u + v > 1) return false;

	t = v0v2.dotProduct(qvec) * invDet;

	return true;
#else 
	
	// compute plane's normal
	vec3 v0v1 = v1 - v0;
	vec3 v0v2 = v2 - v0;
	// no need to normalize
	vec3 N = cross(v0v1, v0v2);  //v0v1.crossProduct(v0v2); // N 

	float denom = dot(N, N);  // N.dotProduct(N);

	// Step 1: finding P

	// check if ray and plane are parallel ?
	float NdotRayDirection = dot(N, ray.direction);  //N.dotProduct(dir);
	if (fabs(NdotRayDirection) < kEpsilon) // almost 0 
		return false; // they are parallel so they don't intersect ! 

	// compute d parameter using equation 2
	float d = dot(N, v0);  //N.dotProduct(v0);

	// compute t (equation 3)
	t = (dot(N, ray.origin) + d) / NdotRayDirection;  //(N.dotProduct(orig) + d) / NdotRayDirection;
	// check if the triangle is in behind the ray
	if (t < 0) return false; // the triangle is behind 

	// compute the intersection point using equation 1

	vec3 P = ray.origin + (float)t * ray.direction;

	// Step 2: inside-outside test
	vec3 C; // vector perpendicular to triangle's plane 

	// edge 0
	vec3 edge0 = v1 - v0;
	vec3 vp0 = P - v0;
	C = cross(edge0, vp0);//edge0.crossProduct(vp0);
	if (dot(N, C) /*N.dotProduct(C)*/ < 0) return false; // P is on the right side 

	// edge 1
	vec3 edge1 = v2 - v1;
	vec3 vp1 = P - v1;
	C = cross(edge1, vp1);//edge1.crossProduct(vp1);
	if ((u = dot(N, C)/*N.dotProduct(C)*/) < 0)  return false; // P is on the right side 

	// edge 2
	vec3 edge2 = v0 - v2;
	vec3 vp2 = P - v2;
	C = cross(edge2, vp2);//edge2.crossProduct(vp2);
	if ((v = dot(N, C)/*N.dotProduct(C)*/) < 0) return false; // P is on the right side; 

	u /= denom;
	v /= denom;

	return true; // this ray hits the triangle 
#endif 
}