#include <iostream>
#include "Image.h"
#include "Sphere.h"
using namespace std;

int main()
{

	cout << "Hello Path Tracer!" << endl;


	//test image
	/*Image img(500, 500);
	for (int i = 0; i < 500; ++i){
		for (int j = 0; j < 500; ++j){

			img.set(i, j, glm::vec3(0, 0, 1));

		}


	}


	img.save("testeImage.ppm");*/
	//

	//test ray cast
	int width = 500;
	int height = 500;
	Image img(width, height);

	glm::vec3 O(0, 0, 0);
	glm::vec3 X(1, 0, 0);
	glm::vec3 Y(0, 1, 0);
	glm::vec3 Z(0, 0, 1);
	
	glm::vec3 camPos(0, 0, 0);
	glm::vec3 lookAt(0, 0, 1);
	glm::vec3 diff_btw = lookAt - camPos;
	
	glm::vec3 camdir = glm::normalize(diff_btw); //diff_btw.negative().normalize();
	glm::vec3 camright = glm::normalize(glm::cross(Y, camdir));
	glm::vec3 camdown = glm::cross(camright, camdir);

	Sphere sphere(glm::vec3(0, 0, 1), 0.3);

	int pixel = 0;
	double xamnt, yamnt;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			pixel = y*width + x;

			// start with no anti-aliasing
			if (width > height) {
				// the image is wider than it is tall
				xamnt = ((x + 0.5) / width)*img.aspectRatio - (((width - height) / (double)height) / 2);
				yamnt = ((height - y) + 0.5) / height;
			}
			else if (height > width) {
				// the imager is taller than it is wide
				xamnt = (x + 0.5) / width;
				yamnt = (((height - y) + 0.5) / height) / img.aspectRatio - (((height - width) / (double)width) / 2);
			}
			else {
				// the image is square
				xamnt = (x + 0.5) / width;
				yamnt = ((height - y) + 0.5) / height;
			}

			glm::vec3 cam_ray_origin = camPos;
			//glm::vec3 cam_ray_direction = camdir.vectAdd(camright.vectMult(xamnt - 0.5).vectAdd(camdown.vectMult(yamnt - 0.5))).normalize();
			float dirX = xamnt - 0.5;
			float dirY = yamnt - 0.5;
			glm::vec3 cam_ray_direction = glm::normalize(camdir + ((camright*dirX) + (camdown*dirY)));
			float t = 0;

			bool find = sphere.intersect(cam_ray_origin, cam_ray_direction, t);
			if (find){
				img.set(x, y, glm::vec3(0, 0, 1));
			}
			else{
				img.set(x, y, glm::vec3(1, 1, 1));
			}
		}
	}
	img.save("testeImage.ppm"); 
	return 0;

}
