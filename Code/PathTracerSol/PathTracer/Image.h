#include "glm\glm\glm.hpp"
#include "glm\glm\gtc\constants.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
class Image{

private:
	int width;
	int height;
	std::vector<glm::vec3> rgb;

	int PPMGammaEncode(float color, float displayCoonstant) const;

public:

	Image(int width, int height) : width(width), height(height), rgb(width*height){}
	void set(int x, int y, glm::vec3& value);
	const glm::vec3& get(int x, int y) const;
	void save(const std::string& filename, float displayConstant = 15.0f) const;

};