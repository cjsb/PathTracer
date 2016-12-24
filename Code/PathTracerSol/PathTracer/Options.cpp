#include "Options.h"
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

void Options::readOptions(char* fileName, Scene &scene){
	
	ifstream is;
	is.open(fileName);

	objLight = new char[40];
	outputFileName = new char[40];
	fileName = new char[40];
	objName = new char[40];

	string stringvar, ignore;
	Light light;
	std::vector<Mesh> meshes;
	std::vector<Quadric> quadrics;
	std::vector<Light> lights;

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

			Mesh m;
			string filePath = "files/";
			filePath.append(objLight);
			readObj(filePath.c_str(), m);
			Light *li = new Light(m, light.r, light.g, light.b, light.Ip);
			scene.lights.push_back(li);

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
			is >> objMaterial.ri;
			Mesh m;
			string filePath = "files/";
			filePath.append(objName);
			readObj(filePath.c_str(), m);
			m.material = objMaterial;
			meshes.push_back(m);
			Mesh *mesh = new Mesh(m.triangles);
			mesh->material = m.material;
			scene.objects.push_back(mesh);
		}
		//objectquadric a b c d e f g h j k red green blue ka kd ks kt n
		else if (stringvar.compare("objectquadric") == 0){
			glm::vec3 bBoxMin;
			glm::vec3 bBoxMax;
			Material m;
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
			is >> m.r;
			is >> m.g;
			is >> m.b;
			is >> m.Ka;
			is >> m.Kd;
			is >> m.Ks;
			is >> m.Kt;
			is >> m.n;
			is >> m.ri;
			is >> bBoxMin.x;
			is >> bBoxMin.y;
			is >> bBoxMin.z;
			is >> bBoxMax.x;
			is >> bBoxMax.y;
			is >> bBoxMax.z;


			/*Quadric quad(objQuadric.a, objQuadric.b, objQuadric.c, objQuadric.d, objQuadric.e, objQuadric.f,
				objQuadric.g, objQuadric.h, objQuadric.j, objQuadric.k, objQuadric.material);
			quadrics.push_back(quad);*/
			
			Quadric *quad = new Quadric(objQuadric.a, objQuadric.b, objQuadric.c, objQuadric.d, objQuadric.e, objQuadric.f,
				objQuadric.g, objQuadric.h, objQuadric.j, objQuadric.k,bBoxMin, bBoxMax );
			quad->material = m;
			scene.objects.push_back(quad);

		}
		else if (stringvar.compare("output") == 0){
			is >> outputFileName;
			//string outputFile = "";
			//outputFile.append(outputFileName);
		}
		
	}

	//create scene

	Camera camera(eye, glm::vec3(0, 0, -11), glm::vec3(0, -1, 0));

	scene.camera = camera;
	/*scene.lights = lights;*/
	scene.meshes = meshes;
	scene.quadrics = quadrics;
}

void Options::readObj(const char *filename, Mesh &mesh){

	ifstream modelo(filename, ifstream::in);
	string type;

	//Tem que criar um vetor de vec3
	glm::vec3 vertex, faces;
	int face1, face2, face3;
	std::vector<glm::vec3> vertices;
	std::vector<Triangle> triangles;

	while ((modelo >> type)){
		if (type == "v"){

			modelo >> vertex.x >> vertex.y >> vertex.z;
			vertices.push_back(vertex);
		}else if (type == "f"){

			modelo >> face1 >> face2 >> face3;
			mesh.triangles.push_back(Triangle(vertices.at(face1 - 1), vertices.at(face2 - 1), vertices.at(face3 - 1)));
		}else {
			modelo.ignore(numeric_limits<streamsize>::max(), '\n');
		}

	}
	
}