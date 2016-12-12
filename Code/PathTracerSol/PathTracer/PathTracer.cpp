#include "PathTracer.h"



glm::vec3 tracer(const Ray &ray, const Scene &scene, int &depth){
		
//<<<<<<< HEAD
//		bool intersected = false;
//		std::vector<bool> findLight;
//		for (auto &obj : scene.objects){
//
//			Intersection inter;
//			bool find = obj->intersect(ray, inter);
//			
//			if (find){
//				intersected = true;
//
//				std::vector<Ray> v0_iwp, v1_iwp, v2_iwp;
//				Intersection interLight;
//				
//				int cont = 0;
//				int a_limit = scene.lights.size();
//
//				for (int a = 0; a < a_limit; a++){ // Para cada fonte de luz 'a'
//					for (int b = 0; b < scene.lights.at(a).mesh.triangles.size(); b++){ // Para cada triangulo 'b' da fonte de luz 'a'
//						Ray auxRay_v1(inter.worldPosition, glm::normalize(-scene.lights.at(a).mesh.triangles.at(b).v1 + inter.worldPosition));
//						Ray auxRay_v2(inter.worldPosition, glm::normalize(-scene.lights.at(a).mesh.triangles.at(b).v2 + inter.worldPosition));
//						Ray auxRay_v0(inter.worldPosition, glm::normalize(-scene.lights.at(a).mesh.triangles.at(b).v0 + inter.worldPosition));
//
//						findLight.push_back(obj->intersect(auxRay_v0, interLight));
//						findLight.push_back(obj->intersect(auxRay_v1, interLight));
//						findLight.push_back(obj->intersect(auxRay_v2, interLight));
//					}
//				}
//
//		
//			}
//		}
//
//		for (int c = 0; c < findLight.size(); c++){
//			if (findLight.at(c) && intersected){
//				return glm::vec3(1, 1, 1);
//			}
//			else{
//				//return glm::vec3(0.5, 0.5, 0.5);
//				return glm::vec3(0.01, 0.01, 0.01);
//			}
//		}
//
//		if (intersected){
//			return glm::vec3(0, 0, 1);
//=======
	bool intersected = false;
	Intersection inter;
	intersected = rayCast(ray, scene, inter);
	std::vector<bool> findLight;

	if (intersected){

		std::vector<Ray> v0_iwp, v1_iwp, v2_iwp;
		Intersection interLight;

		int cont = 0;
		int a_limit = scene.lights.size();

		for (int a = 0; a < a_limit; a++){ // Para cada fonte de luz 'a'
			for (int b = 0; b < scene.lights.at(a)->mesh.triangles.size(); b++){ // Para cada triangulo 'b' da fonte de luz 'a'
				Ray auxRay_v0(inter.worldPosition, glm::normalize(scene.lights.at(a)->mesh.triangles.at(b).v0 - inter.worldPosition));
				Ray auxRay_v1(inter.worldPosition, glm::normalize(scene.lights.at(a)->mesh.triangles.at(b).v1 - inter.worldPosition));
				Ray auxRay_v2(inter.worldPosition, glm::normalize(scene.lights.at(a)->mesh.triangles.at(b).v2 - inter.worldPosition));


				rayCast(auxRay_v0, scene, interLight);
				if (interLight.objType == LIGHT) findLight.push_back(true);
				else findLight.push_back(false);
												
				rayCast(auxRay_v1, scene, interLight);
				if (interLight.objType == LIGHT) findLight.push_back(true);
				else findLight.push_back(false);

				rayCast(auxRay_v2, scene, interLight);
				if (interLight.objType == LIGHT) findLight.push_back(true);
				else findLight.push_back(false);
			}
		}


		if (inter.objType == LIGHT){
			return glm::vec3(scene.lights.at(inter.index)->r,
				scene.lights.at(inter.index)->g,
				scene.lights.at(inter.index)->b);

		}
		else{
			/*return glm::vec3(scene.objects.at(inter.index)->material.r,
				scene.objects.at(inter.index)->material.g,
				scene.objects.at(inter.index)->material.b);*/

			//bool foundLight = true;
			bool foundLight = findLight.at(0) || false;
			for (int c = 1; c < findLight.size(); c++){

				foundLight = foundLight || findLight.at(c);
				//if (!findLight.at(c)){
				//	//foundLight = false;
				//	//return glm::vec3(0.01, 0.01, 0.01);
				//}
				//else{
				//	//return glm::vec3(1, 1, 1);
				//}
			}

			if (!foundLight){
				return glm::vec3(0.01, 0.01, 0.01);
			}
			else{
				return glm::vec3(1, 1, 1);
			}
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


