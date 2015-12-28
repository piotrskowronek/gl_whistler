#include "stdafx.h"
#include "ObjLoader.h"
#include "Texture.h"
#include <vector>
#include <map>

using namespace std;

struct Material {
	GLuint ambient;
	GLuint diffuse;
	GLuint specular;
};

GLuint LoadObj(string file, GLuint textureId) {
	FILE * fp2;
	errno_t error2;

	error2 = fopen_s(&fp2, ("Resources\\" + file + ".mtl").c_str(), "r");

	if (error2 != 0) {
		printf("ERROR: Cannot read mtl file \"%s\".\n", file + ".mtl");
		return -1;
	}

	map<string, Material> materials;
	string lastMaterialId = "";

	char buf2[128];

	while (fgets(buf2, 128, fp2) != NULL) {
		if (buf2[0] == 'n' && buf2[1] == 'e') {
			char mtlName[50];
			sscanf(buf2, "newmtl %s", &mtlName);
			string str(mtlName);

			lastMaterialId = str;
			Material mtl = {0, 0, 0};
			materials[str] = mtl;
		}
		if (buf2[0] == 'm' && buf2[1] == 'a' && buf2[1] == 'p' && buf2[1] == '_' && buf2[1] == 'K' && buf2[1] == 'd') {
			char texName[100];
			sscanf(buf2, "map_Kd %s", &texName);
			string str(texName);
			string texPath("Resources\\tex\\" + str + ".bmp");

			CTexture tex(&texPath[0u]);
			materials[lastMaterialId].diffuse = tex.Load();
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
	vector< pair< int, string > > pairsPosMaterial;

	char buf[128];

	int fsOccured = 0;

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
			f->push_back(*face);
			fsOccured++;
		}
		if (buf[0] == 'u' && buf[1] == 's') {
			char mtlName[50];
			sscanf(buf, "usemtl %s", &mtlName);
			string str(mtlName);

			pair< int, string > p(fsOccured, str);
			pairsPosMaterial.push_back(p);
		}
	}

	fclose(fp);

	GLuint dlId;
	dlId = glGenLists(1);
	glNewList(dlId, GL_COMPILE);

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBegin(GL_TRIANGLES);
	GLuint texId = materials[pairsPosMaterial[0].second].diffuse;
	for (int i = 0; i < f->size(); ++i) {
		for (int k = 0; k < pairsPosMaterial.size(); k++)
		{
			if ( pairsPosMaterial[k].first > i )
				texId = materials[pairsPosMaterial[k].second].diffuse;
		}

		glBindTexture(GL_TEXTURE_2D, texId);
		for (int j = 0; j < 3; ++j) {
			vec3 * cv = &(*v)[((*f)[i].v[j] - 1)];
			vec3 * ct = &(*t)[((*f)[i].t[j] - 1)];
			vec3 * cn = &(*n)[((*f)[i].n[j] - 1)];
			glTexCoord2f(ct->x, ct->y);
			glNormal3f(cn->x, cn->y, cn->z);
			glVertex3f(cv->x, cv->y, cv->z);
		}
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