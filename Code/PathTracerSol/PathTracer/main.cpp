#include <iostream>
#include "Image.h"

using namespace std;

int main()
{

	cout << "Hello Path Tracer!" << endl;


	//test image
	Image img(500, 500);
	for (int i = 0; i < 500; ++i){
		for (int j = 0; j < 500; ++j){

			img.set(i, j, glm::vec3(0, 0, 1));

		}


	}


	img.save("testeImage.ppm");




	return 0;

}
