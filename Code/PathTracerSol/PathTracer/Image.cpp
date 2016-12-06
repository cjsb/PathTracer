#define _CRT_SECURE_NO_DEPRECATE
#include "Image.h"

void Image::set(int x, int y, glm::vec3& value){

	rgb[x + y * width] = value;
}

const glm::vec3& Image::get(int x, int y) const{

	return rgb[x + y * width];
}

int Image::PPMGammaEncode(float color, float displayCoonstant) const{

	return int(pow(std::min(1.0f, std::max(0.0f, color*displayCoonstant)), 1.0f / 2.2f)*255.0f);

}

void Image::save(const std::string& filename, float displayConstant) const{

	FILE* file = fopen(filename.c_str(), "wt");
	fprintf(file, "P3 %d %d 255\n", width, height);
	for (int y = 0; y < height; ++y){
		fprintf(file, "\n# y = %d\n", y);
		for (int x = 0; x < width; ++x){
			const glm::vec3& c(get(x, y));
			fprintf(file, "%d %d %d\n", PPMGammaEncode(c.x, displayConstant), PPMGammaEncode(c.y, displayConstant), PPMGammaEncode(c.z, displayConstant));
		}


	}

}