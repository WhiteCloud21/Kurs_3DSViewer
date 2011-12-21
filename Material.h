#ifndef __Material_h__
#define __Material_h__

#include "main.h"

using namespace glm;

class CMaterial
{
private:
	string name;
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
	GLfloat shininessStrength;
	GLfloat selfIllum;
public:
	CMaterial();
	~CMaterial();
	const char* GetName();
	void SetName(char* name);
	void SetAmbient(vec3 color);
	void SetDiffuse(vec3 color);
	void SetSpecular(vec3 color);
	void SetShininess(float shininess);
	void SetShininessStrength(float shininessStrength);
	void SetSelfIllum(float selfIllum);
	void Apply();
};
#endif