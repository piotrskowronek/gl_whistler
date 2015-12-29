#include "stdafx.h"
#include "ObjLoader.h"
#include "Texture.h"
#include <vector>
#include <map>

using namespace std;

struct Material {
	string name;
	GLuint texture;
};

GLuint LoadObj(string file, GLuint textureId) {
	FILE * fp2;
	errno_t error2;

	error2 = fopen_s(&fp2, ("Resources\\" + file + ".mtl").c_str(), "r");

	if (error2 != 0) {
		printf("ERROR: Cannot read mtl file \"%s\".\n", file + ".mtl");
		return -1;
	}

	vector< pair< Material, vector < SFace > > > materials;

	char buf2[128];

	while (fgets(buf2, 128, fp2) != NULL) {
		if (buf2[0] == 'n' && buf2[1] == 'e') {
			char mtlName[50];
			sscanf(buf2, "newmtl %s", &mtlName);
			string str(mtlName);

			Material mtl = {str, 0};
			vector<SFace> v;
			pair< Material, vector< SFace > > p(mtl, v);
			materials.push_back(p);
		}
		if (buf2[0] == 'm' && buf2[1] == 'a' && buf2[1] == 'p' && buf2[1] == '_' && buf2[1] == 'K' && buf2[1] == 'd') {
			char texName[100];
			sscanf(buf2, "map_Kd %s", &texName);
			string str(texName);
			string texPath("Resources\\tex\\" + str + ".bmp");

			CTexture tex(&texPath[0u]);
			(*materials.end()).first.texture = tex.Load();
		}
	}

	fclose(fp2);

	FILE * fp;
	errno_t error;

	error = fopen_s(&fp, ("Resources\\" + file + ".obj").c_str(), "r");

	if (error != 0) {
		printf("ERROR: Cannot read model file \"%s\".\n", file + ".obj");
		return -1;
	}

	vector<vec3> * v = new vector<vec3>();
	vector<vec3> * n = new vector<vec3>();
	vector<vec3> * t = new vector<vec3>();
	vector<SFace> * f = new vector<SFace>();

	char buf[128];

	pair< Material, vector< SFace > >* currentPair;

	while (fgets(buf, 128, fp) != NULL) {
		if (buf[0] == 'v' && buf[1] == ' ') {
			vec3 * vertex = new vec3();
			sscanf(buf, "v %f %f %f", &vertex->x, &vertex->y, &vertex->z);
			v->push_back(*vertex);
		}
		if (buf[0] == 'v' && buf[1] == 't') {
			vec3 * vertex = new vec3();
			sscanf(buf, "vt %f %f", &vertex->x, &vertex->y);
			t->push_back(*vertex);
		}
		if (buf[0] == 'v' && buf[1] == 'n') {
			vec3 * vertex = new vec3();
			sscanf(buf, "vn %f %f %f", &vertex->x, &vertex->y, &vertex->z);
			n->push_back(*vertex);
		}
		if (buf[0] == 'f' && buf[1] == ' ') {
			SFace * face = new SFace();
			sscanf(buf, "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&face->v[0], &face->t[0], &face->n[0],
				&face->v[1], &face->t[1], &face->n[1],
				&face->v[2], &face->t[2], &face->n[2]
				);
			currentPair->second.push_back(*face);
		}
		if (buf[0] == 'u' && buf[1] == 's') {
			char mtlName[50];
			sscanf(buf, "usemtl %s", &mtlName);
			string str(mtlName);

			for (int i = 0; i < materials.size(); i++)
				if ( materials[i].first.name == str )
					currentPair = &materials[i];
		}
	}

	fclose(fp);

	GLuint dlId;
	dlId = glGenLists(1);
	glNewList(dlId, GL_COMPILE);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, textureId);

	glBegin(GL_TRIANGLES);
	GLuint texId = 0;
	for (int k = 0; k < materials.size(); k++)
		for (int i = 0; i < materials[k].second.size(); i++)
			for (int j = 0; j < 3; j++) {
				vec3 * cv = &(*v)[(materials[k].second[i].v[j] - 1)];
				vec3 * ct = &(*t)[(materials[k].second[i].t[j] - 1)];
				vec3 * cn = &(*n)[(materials[k].second[i].n[j] - 1)];
				glTexCoord2f(ct->x, ct->y);
				glNormal3f(cn->x, cn->y, cn->z);
				glVertex3f(cv->x, cv->y, cv->z);
			}
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glEndList();

	delete v;
	delete n;
	delete t;
	delete f;

	return dlId;

}