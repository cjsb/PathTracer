#include "Options.h"
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

void Options::readOptions(char* fileName, Scene &scene){
	
	ifstream is;
	is.open(fileName);

	objLight = new char[40];
	fileName = new char[40];
	objName = new char[40];

	Light light;
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
			readObj(objName, objMaterial);
		}
		//objectquadric a b c d e f g h j k red green blue ka kd ks kt n
		else if (stringvar.compare("objectquadric") == 0){
			is >> objQuadric.a;
			is >> objQuadric.b;
			is >> objQuadric.c;
			is >> objQuadric.d;
			is >> objQuadric.e;
			is >> objQuadric.f;
			is >> objQuadric.g;
			is >> objQuadric.h;
			is >> objQuadric.j;
			is >> objQuadric.k;
			is >> objQuadric.material.r;
			is >> objQuadric.material.g;
			is >> objQuadric.material.b;
			is >> objQuadric.material.Ka;
			is >> objQuadric.material.Kd;
			is >> objQuadric.material.Ks;
			is >> objQuadric.material.Kt;
			is >> objQuadric.material.n;
		}
		else if (stringvar.compare("output") == 0){
			is >> fileName;
		}
		
	}
}

void Options::readObj(char *filename, Material m){

	ifstream modelo(filename, ifstream::in);
	string type;

	//Tem que criar um vetor de vec3
	vec3 vertices, faces;

	while ((modelo >> type)){
		if (type == "v"){

			modelo >> vertices.x >> vertices.y >> vertices.z;
		}else if (type == "f"){

			modelo >> faces.x >> faces.y >> faces.z;
		}else {
			modelo.ignore(numeric_limits<streamsize>::max(), '\n');
		}

	}
	//Triangle t(vertices[0], vertices[1], vertices[2], m)
}