#ifndef __Material_h__
#define __Material_h__

#include "main.h"
#include "TextureMap.h"

using namespace glm;

class CMaterial
{
private:
	string name;
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat emission[4];
	GLfloat shininess;
	GLfloat shininessStrength;
	GLfloat selfIllum;
	GLfloat transparency;
public:
	CTextureMap texture1;
	CTextureMap textureSpecular;
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
	void SetTransparency(float transparency);
	bool IsTransparent();
	// установка режима фильтрации
	void SetFilterMode(char);
	void Apply(void*);
};
#endif