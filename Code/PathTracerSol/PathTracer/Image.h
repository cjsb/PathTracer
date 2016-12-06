#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\constants.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
class Image{

private:
	
	std::vector<glm::vec3> rgb;

	int PPMGammaEncode(float color, float displayCoonstant) const;

public:
	int width;
	int height;
	float aspectRatio;
	Image(int width, int height) : width(width), height(height), rgb(width*height){

		aspectRatio = float(width) / float(height);
	}
	void set(int x, int y, glm::vec3& value);
	const glm::vec3& get(int x, int y) const;
	void save(const std::string& filename, float displayConstant = 15.0f) const;

};