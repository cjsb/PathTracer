#include <iostream>
#include "Image.h"
#include "Sphere.h"
#include "Quadric.h"
#include "Ray.h"
#include "Triangle.h"
#include "Options.h"
#include "Mesh.h"
#include "scene.h"

using namespace std;

int main()
{

	cout << "Hello Path Tracer!" << endl;
	Scene scene;
	Options conf;
	//vector trian
	int i = 0;
	conf.readOptions("files/cornellroom.sdl", scene);
	cout << i << endl;
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
	Material m;
	Sphere sphere(glm::vec3(0, 0, 10), 1);
	Quadric quad(1,1,1,0,0,0,0,0,-10,99,m);
	double u = 0, v = 0;
	glm::vec3 ver1(10, 10, 40), ver2(-10, 10, 40), ver3(0, -10, 40);
	Triangle triangle(ver1, ver2, ver3);

	double invWidth = 1 / double(width), invHeight = 1 / double(height);
	double fov = 30, aspectratio = width / double(height);

	// Trace rays
	//for (unsigned y = 0; y < height; ++y) {
	//	for (unsigned x = 0; x < width; ++x) {
	//		float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
	//		float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
	//		glm::vec3 raydirX(xx, yy, 1);
	//		glm::vec3 raydir = glm::normalize(raydirX);
	//		Ray ray(glm::vec3(0,0,0), raydir);
	//		double t;
	//		bool find = quad.intersect(/*cam_ray_origin, cam_ray_direction*/ray, t);
	//		
	//		bool findTri = triangle.rayTriangleIntersect(orig, raydir, ver1, ver2, ver3, tri, u, v);
	//		//cout << t << endl;
	//		//bool find = 
	//		if (findTri){
	//			img.set(x, y, glm::vec3(0, 0, 1));
	//			//system("pause");
	//		}
	//		else{
	//			img.set(x, y, glm::vec3(1, 1, 1));
	//		}
	//	}
	//}




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
			double dirX = xamnt - 0.5;
			double dirY = yamnt - 0.5;
			glm::vec3 cam_ray_direction = glm::normalize(camdir + ((camright*(float)dirX) + (camdown*(float)dirY)));
			double t = 0;

			Ray ray(cam_ray_origin, cam_ray_direction);

			bool find = quad.intersect(/*cam_ray_origin, cam_ray_direction*/ray, t);
			bool findTri = triangle.rayTriangleIntersect(ray, t, u, v);
			//cout << t << endl;
			//bool find = 
			if (findTri){
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
