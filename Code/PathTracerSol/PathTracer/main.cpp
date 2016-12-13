#include <iostream>
#include "Image.h"
#include "Sphere.h"
#include "Quadric.h"
#include "Ray.h"
#include "Triangle.h"
#include "Options.h"
#include "Mesh.h"
#include "Scene.h"
#include "Object.h"
#include "PathTracer.h"

using namespace std;

int main()
{
	cout << "Hello Path Tracer!" << endl;
	Scene scene;
	Options conf;
	//vector trian
	cout << "sdl loading..." << endl;
	conf.readOptions("files/cornellroomV2.sdl", scene);
	cout << "sdl loaded" << endl;
	//test ray cast
	Image img(conf.size.x, conf.size.y);
		
	for (int x = 0; x < img.width; x++) {
		for (int y = 0; y < img.height; y++) {
			for (int z = 0; z < conf.npaths; z++){
				double xamnt, yamnt;
				// start with no anti-aliasing
				if (img.width > img.height) {
					// the image is wider than it is tall
					xamnt = ((x + 0.5) / img.width)*img.aspectRatio - (((img.width - img.height) / (double)img.height) / 2);
					yamnt = ((img.height - y) + 0.5) / img.height;
				}
				else if (img.height > img.width) {
					// the imager is taller than it is wide
					xamnt = (x + 0.5) / img.width;
					yamnt = (((img.height - y) + 0.5) / img.height) / img.aspectRatio - (((img.height - img.width) / (double)img.width) / 2);
				}
				else {
					// the image is square
					xamnt = (x + 0.5) / img.width;
					yamnt = ((img.height - y) + 0.5) / img.height;
				}

				glm::vec3 cam_ray_origin = scene.camera.eye;
				//glm::vec3 cam_ray_direction = camdir.vectAdd(camright.vectMult(xamnt - 0.5).vectAdd(camdown.vectMult(yamnt - 0.5))).normalize();
				double dirX = xamnt - 0.5;
				double dirY = yamnt - 0.5;
				//glm::vec3 cam_ray_direction = glm::normalize(camdir + ((camright*(float)dirX) + (camdown*(float)dirY)));
				glm::vec3 cam_ray_direction = glm::normalize(scene.camera.cameraDir + ((scene.camera.camRight*(float)dirX) + (scene.camera.camDown*(float)dirY)));

				Ray ray(cam_ray_origin, cam_ray_direction);
				int depth = 5;
				img.set(x, y, tracer(ray, scene, conf, depth));
				/*img.set(x, y, glm::vec3(1, 1, 1));
				Intersection inter;
				for (int i = 0; i < scene.objects.size(); ++i){

				bool find = scene.objects.at(i)->intersect(ray, inter);
				if (find){
				img.set(x, y, glm::vec3(0, 0, 1));
				}



				}*/
			}
		}
	}

	img.save("testeImage.ppm"); 
	return 0;

}
