#include "PathTracer.h"



glm::vec3 tracer(const Ray &ray, const Scene &scene, int &depth){
		
	bool intersected = false;
	Intersection inter;
	intersected = rayCast(ray, scene, inter);
	/*for (auto &obj : scene.objects){

		Intersection inter;
		bool find = obj->intersect(ray, inter);
		if (find){
			intersected = true;
				
		}

	}*/
	if (intersected){
		if (inter.objType == LIGHT){
			return glm::vec3(scene.lights.at(inter.index)->r,
				scene.lights.at(inter.index)->g,
				scene.lights.at(inter.index)->b);
		}
		else{
			return glm::vec3(scene.objects.at(inter.index)->material.r,
				scene.objects.at(inter.index)->material.g,
				scene.objects.at(inter.index)->material.b);
		}
	}
	else{
		return glm::vec3(1, 1, 1);
	}
}


bool rayCast(const Ray &ray, const Scene &scene, Intersection &inter){

	inter.t = std::numeric_limits<double>::max();
	bool intersected = false;
	int index = 0;
	for (auto &obj : scene.objects){

		Intersection interLocal;
		bool find = obj->intersect(ray, interLocal);

		if (find){

			intersected = true;

			if (interLocal.t < inter.t){
				inter.t = interLocal.t;
				inter.worldPosition = interLocal.worldPosition;
				inter.objType = interLocal.objType;
				inter.index = index;
				

			}
		}

		index++;
	}
	index = 0;
	for (auto &light : scene.lights){

		Intersection interLocal;
		
		bool find = light->mesh.intersect(ray, interLocal);

		if (find){

			intersected = true;

			if (interLocal.t < inter.t){
				inter.t = interLocal.t;
				inter.worldPosition = interLocal.worldPosition;
				inter.objType = LIGHT;
				inter.index = index;


			}
		}

		index++;
	}
	

	return intersected;



}


