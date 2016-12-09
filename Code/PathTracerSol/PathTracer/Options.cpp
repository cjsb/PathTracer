#include "Options.h"
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

void Options::readOptions(){

	ifstream is;
	is.open("C:\\Users\\Andre Luiz\\Desktop\\Projeto CG\\PathTracer\\Code\\PathTracerSol\\PathTracer\\input.txt");
	Light light;
	objLight = new char[40];
	fileName = new char[40];
	objName = new char[40];
	string stringvar, ignore;

	while (!is.eof()){

		is >> stringvar;


		if (stringvar.compare("#") == 0 || stringvar.compare("ortho") == 0){
			getline(is, ignore);
		}
		else if(stringvar.compare("eye") == 0){
			is >> eye.x;
			is >> eye.y;
			is >> eye.z;
		}
		else if (stringvar.compare("size") == 0){
			is >> size.x;
			is >> size.y;
		}
		else if (stringvar.compare("background") == 0){
			is >> background.x;
			is >> background.y;
			is >> background.z;
		}
		else if (stringvar.compare("ambient") == 0){
			is >> ambient;
		}
		else if (stringvar.compare("light") == 0){
			is >> objLight;
			is >> light.r;
			is >> light.g;
			is >> light.b;
			is >> light.Ip;
		}
		else if (stringvar.compare("npaths") == 0){
			is >> npaths;
		}
		else if (stringvar.compare("tonemapping") == 0){
			is >> tonemapping;
		}
		else if (stringvar.compare("seed") == 0){
			is >> seed;
		}
		else if (stringvar.compare("object") == 0){
			is >> objName;
			is >> objMaterial.r;
			is >> objMaterial.g;
			is >> objMaterial.b;
			is >> objMaterial.Ka;
			is >> objMaterial.Kd;
			is >> objMaterial.Ks;
			is >> objMaterial.Kt;
			is >> objMaterial.n;
		}
		else if (stringvar.compare("output") == 0){
			is >> fileName;
		}
		
	}
}