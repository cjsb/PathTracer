#ifndef _light_h
#define _light_h

class Light
{

public:

	double r, g, b, Ip;

	Light(){}
	~Light(){}

	void readOptions();
};

#endif