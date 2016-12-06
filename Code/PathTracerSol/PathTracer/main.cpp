#include <iostream>
#include "Image.h"

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

	glm::vec3 camPos(0, 0, 0);
	glm::vec3 lookAt(0, 0, 1);

	int pixel = 0;
	double xamnt, yamnt;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			pixel = y*width + x;



		}
	}

	return 0;

}
