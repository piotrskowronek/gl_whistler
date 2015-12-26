#include "stdafx.h"
#include "ObjLoader.h"
#include <vector>

GLuint LoadObj(string file, GLuint textureId) {

	FILE * fp;
	errno_t error;

	error = fopen_s(&fp, file.c_str(), "r");

	if (error != 0) {
		printf("ERROR: Cannot read model file \"%s\".\n", file);
		return -1;
	}

	std::vector<vec3> * v = new std::vector<vec3>();
	std::vector<vec3> * n = new std::vector<vec3>();
	std::vector<vec3> * t = new std::vector<vec3>();
	std::vector<SFace> * f = new std::vector<SFace>();

	char buf[128];

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
	for (int i = 0; i < f->size(); ++i) {
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