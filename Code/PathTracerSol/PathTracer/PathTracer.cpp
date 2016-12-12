#include "PathTracer.h"



	glm::vec3 tracer(const Ray &ray, const Scene &scene, int &depth){
		
		bool intersected = false;
		std::vector<bool> findLight;
		for (auto &obj : scene.objects){

			Intersection inter;
			bool find = obj->intersect(ray, inter);
			
			if (find){
				intersected = true;

				std::vector<Ray> v0_iwp, v1_iwp, v2_iwp;
				Intersection interLight;
				
				int cont = 0;
				int a_limit = scene.lights.size();

				for (int a = 0; a < a_limit; a++){ // Para cada fonte de luz 'a'
					for (int b = 0; b < scene.lights.at(a).mesh.triangles.size(); b++){ // Para cada triangulo 'b' da fonte de luz 'a'
						Ray auxRay_v1(inter.worldPosition, glm::normalize(-scene.lights.at(a).mesh.triangles.at(b).v1 + inter.worldPosition));
						Ray auxRay_v2(inter.worldPosition, glm::normalize(-scene.lights.at(a).mesh.triangles.at(b).v2 + inter.worldPosition));
						Ray auxRay_v0(inter.worldPosition, glm::normalize(-scene.lights.at(a).mesh.triangles.at(b).v0 + inter.worldPosition));

						findLight.push_back(obj->intersect(auxRay_v0, interLight));
						findLight.push_back(obj->intersect(auxRay_v1, interLight));
						findLight.push_back(obj->intersect(auxRay_v2, interLight));
					}
				}

		
			}
		}

		for (int c = 0; c < findLight.size(); c++){
			if (findLight.at(c) && intersected){
				return glm::vec3(1, 1, 1);
			}
			else{
				//return glm::vec3(0.5, 0.5, 0.5);
				return glm::vec3(0.01, 0.01, 0.01);
			}
		}

		if (intersected){
			return glm::vec3(0, 0, 1);
		}
		else{
			return glm::vec3(1, 1, 1);
		}
	}



