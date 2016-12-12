#include "PathTracer.h"



	glm::vec3 tracer(const Ray &ray, const Scene &scene, int &depth){
		
		bool intersected = false;
		for (auto &obj : scene.objects){

			Intersection inter;
			bool find = obj->intersect(ray, inter);
			if (find){
				intersected = true;
				
			}

		}
		if (intersected){
			return glm::vec3(0, 0, 1);
		}
		else{
			return glm::vec3(1, 1, 1);
		}
	}



