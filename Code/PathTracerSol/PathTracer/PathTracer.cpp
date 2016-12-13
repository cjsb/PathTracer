#include "PathTracer.h"


glm::vec3 phongShading(const Material& mat, const Light& light, const glm::vec3& L, const glm::vec3& N, const glm::vec3& V, const glm::vec3& R)
{
	/*auto lightColor = light.emissionColor();
	color c = black;*/
	glm::vec3 lightColor(light.r, light.g, light.b);
	glm::vec3 color(0, 0, 0);
	float NL = glm::dot(N, L);
	float LR = glm::dot(L, R);

	color += std::max(NL, 0.0f) * (float)mat.Kd * lightColor * glm::vec3(mat.r, mat.g, mat.b) * (float)light.Ip;
	color += (float)mat.Ks * float(pow(std::max(LR, 0.0f), mat.n)) * lightColor * (float)light.Ip;

	return color;
}

TYPERAY chooseRay(double Kd, double Ks, double Kt){

	double ktot = Kd + Ks + Kt;
	TYPERAY typeRay;
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_real_distribution<double> uni(0, ktot); // guaranteed unbiased

	auto randomNumber = uni(rng);

	if (randomNumber < Kd){
		typeRay = DIFFUSE;
	}
	else if (randomNumber < Kd+Ks){
		typeRay = SPECULAR;
	}
	else{
		typeRay = TRANSMITED;
	}

	return typeRay;
}

std::vector<bool> findLight(const Scene &scene, const Intersection &inter){
	Intersection interLight;
	std::vector<bool> FL;
	int lightLimit = scene.lights.size();
	int triangleLimit;

	for (int lights = 0; lights < lightLimit; lights++){ // Para cada fonte de luz 'lights'
		triangleLimit = scene.lights.at(lights)->mesh.triangles.size();

		for (int triangles = 0; triangles < triangleLimit; triangles++){ // Para cada triangulo 'triangles' da fonte de luz 'lights'
			Ray auxRay_v0(inter.worldPosition, glm::normalize(scene.lights.at(lights)->mesh.triangles.at(triangles).v0 - inter.worldPosition));
			Ray auxRay_v1(inter.worldPosition, glm::normalize(scene.lights.at(lights)->mesh.triangles.at(triangles).v1 - inter.worldPosition));
			Ray auxRay_v2(inter.worldPosition, glm::normalize(scene.lights.at(lights)->mesh.triangles.at(triangles).v2 - inter.worldPosition));


			rayCast(auxRay_v0, scene, interLight);
			if (interLight.objType == LIGHT) FL.push_back(true);
			else FL.push_back(false);

			rayCast(auxRay_v1, scene, interLight);
			if (interLight.objType == LIGHT) FL.push_back(true);
			else FL.push_back(false);

			rayCast(auxRay_v2, scene, interLight);
			if (interLight.objType == LIGHT) FL.push_back(true);
			else FL.push_back(false);
		}


		/*Ray auxRay(inter.worldPosition, glm::normalize(scene.lights.at(0)->mesh.triangles.at(0).v2 - inter.worldPosition));
		rayCast(auxRay, scene, interLight);
		if (interLight.objType == LIGHT) findLight.push_back(true);
		else findLight.push_back(false);*/
	}

	return FL;
}


glm::vec3 tracer(const Ray &ray, const Scene &scene, const Options &options, int &depth){

	bool intersected = false;
	Intersection inter;
	intersected = rayCast(ray, scene, inter);
	//std::vector<bool> findLight;

	if (intersected){
		
		//Intersection interLight;
		//std::vector<bool> FL;
		//int a_limit = scene.lights.size();
		//int b_limit;

		//for (int a = 0; a < a_limit; a++){ // Para cada fonte de luz 'a'
		//	b_limit = scene.lights.at(a)->mesh.triangles.size();

		//	for (int b = 0; b < b_limit; b++){ // Para cada triangulo 'b' da fonte de luz 'a'
		//		Ray auxRay_v0(inter.worldPosition, glm::normalize(scene.lights.at(a)->mesh.triangles.at(b).v0 - inter.worldPosition));
		//		Ray auxRay_v1(inter.worldPosition, glm::normalize(scene.lights.at(a)->mesh.triangles.at(b).v1 - inter.worldPosition));
		//		Ray auxRay_v2(inter.worldPosition, glm::normalize(scene.lights.at(a)->mesh.triangles.at(b).v2 - inter.worldPosition));


		//		rayCast(auxRay_v0, scene, interLight);
		//		if (interLight.objType == LIGHT) FL.push_back(true);
		//		else FL.push_back(false);

		//		rayCast(auxRay_v1, scene, interLight);
		//		if (interLight.objType == LIGHT) FL.push_back(true);
		//		else FL.push_back(false);

		//		rayCast(auxRay_v2, scene, interLight);
		//		if (interLight.objType == LIGHT) FL.push_back(true);
		//		else FL.push_back(false);
		//	}

		//	for (int c = 0; c < FL.size(); c++){
		//		if (!FL.at(c)){
		//			//foundLight = false;
		//			return glm::vec3(0.01, 0.01, 0.01);
		//		}
		//		else{


		//			return glm::vec3(scene.objects.at(inter.index)->material.r,
		//				scene.objects.at(inter.index)->material.g,
		//				scene.objects.at(inter.index)->material.b);
		//		}
		//	}

			/*Ray auxRay(inter.worldPosition, glm::normalize(scene.lights.at(0)->mesh.triangles.at(0).v2 - inter.worldPosition));
			rayCast(auxRay, scene, interLight);
			if (interLight.objType == LIGHT) findLight.push_back(true);
			else findLight.push_back(false);*/
		// }

		if (inter.objType == LIGHT){
			return glm::vec3(scene.lights.at(inter.index)->r,
				scene.lights.at(inter.index)->g,
				scene.lights.at(inter.index)->b);
		}
		else{
			/*return glm::vec3(scene.objects.at(inter.index)->material.r,
				scene.objects.at(inter.index)->material.g,
				scene.objects.at(inter.index)->material.b);*/

			

			glm::vec3 N = inter.normal;
			glm::vec3 V = glm::normalize(ray.direction);
			glm::vec3 R = glm::reflect(V, N);

			// Para cada raio que não intersectou diretamente os vertices, pinta-se o objeto de cinza
			//for (int c = 0; c < FL.size(); c++){
			//	if (!FL.at(c)){
			//		//foundLight = false;
			//		//return glm::vec3(0.01, 0.01, 0.01);

			//		c += phongShading(mat, *light, L, N, V, R);
			//	}
			//	else{
			//		return glm::vec3(scene.objects.at(inter.index)->material.r,
			//			scene.objects.at(inter.index)->material.g,
			//			scene.objects.at(inter.index)->material.b);
			//	}
			//}

			/*if (!foundLight){
				return glm::vec3(0.01, 0.01, 0.01);
			}
			else{
				return glm::vec3(scene.objects.at(inter.index)->material.r,
				scene.objects.at(inter.index)->material.g,
				scene.objects.at(inter.index)->material.b);
			}*/

			

			glm::vec3 finalColor(0, 0, 0);
			int lightLimit = scene.lights.size();
			int triangleLimit;
			glm::vec3 objColor(scene.objects.at(inter.index)->material.r, scene.objects.at(inter.index)->material.g, scene.objects.at(inter.index)->material.b);

			for (int light = 0; light < lightLimit; light++){ // Para cada fonte de luz 'lights'
				//triangleLimit = scene.lights.at(light)->mesh.triangles.size();

				//for (int triangle = 0; triangle < triangleLimit; triangle++){ // Para cada triangulo 'triangles' da fonte de luz 'lights'
				//	Ray auxRay_v0(inter.worldPosition, glm::normalize(scene.lights.at(light)->mesh.triangles.at(triangle).v0 - inter.worldPosition));
				//	Ray auxRay_v1(inter.worldPosition, glm::normalize(scene.lights.at(light)->mesh.triangles.at(triangle).v1 - inter.worldPosition));
				//	Ray auxRay_v2(inter.worldPosition, glm::normalize(scene.lights.at(light)->mesh.triangles.at(triangle).v2 - inter.worldPosition));

				//	glm::vec3 color;
				//	color = phongShading(scene.objects.at(inter.index)->material, *scene.lights.at(light), glm::normalize(scene.lights.at(light)->mesh.triangles.at(triangle).v0 - inter.worldPosition), N, V, R);
				//	finalColor += objColor*(float)scene.objects.at(inter.index)->material.Kd* color;

				//	color = phongShading(scene.objects.at(inter.index)->material, *scene.lights.at(light), glm::normalize(scene.lights.at(light)->mesh.triangles.at(triangle).v1 - inter.worldPosition), N, V, R);
				//	finalColor += objColor*(float)scene.objects.at(inter.index)->material.Kd* color;

				//	color = phongShading(scene.objects.at(inter.index)->material, *scene.lights.at(light), glm::normalize(scene.lights.at(light)->mesh.triangles.at(triangle).v2 - inter.worldPosition), N, V, R);
				//	finalColor += objColor*(float)scene.objects.at(inter.index)->material.Kd* color;
				//}

				glm::vec3 color;
				color = phongShading(scene.objects.at(inter.index)->material, *scene.lights.at(light), glm::normalize(scene.lights.at(light)->centralPoint - inter.worldPosition), N, V, R);
				finalColor += objColor*(float)scene.objects.at(inter.index)->material.Kd* color;

			}
			
			return glm::vec3(finalColor.x / (finalColor.x + options.tonemapping), finalColor.y / (finalColor.y + options.tonemapping), finalColor.z / (finalColor.z + options.tonemapping));
		}
	}
	else{
		return options.background;
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
				inter.normal = interLocal.normal;
				

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


