#include <fstream>
#include "Material.h"

CMaterial::CMaterial()
{
}

CMaterial::~CMaterial()
{
}

void CMaterial::SetName(char* name)
{
	this->name = string(name);
}

const char* CMaterial::GetName()
{
	return name.c_str();
}

void CMaterial::SetAmbient(vec3 color)
{
	this->ambient[0] = color.r;
	this->ambient[1] = color.g;
	this->ambient[2] = color.b;
	this->ambient[3] = 1;
}

void CMaterial::SetDiffuse(vec3 color)
{
	this->diffuse[0] = color.r;
	this->diffuse[1] = color.g;
	this->diffuse[2] = color.b;
	this->diffuse[3] = 1;
}

void CMaterial::SetSpecular(vec3 color)
{
	this->specular[0] = color.r;
	this->specular[1] = color.g;
	this->specular[2] = color.b;
	this->specular[3] = 1;
}

void CMaterial::SetShininess(float shininess)
{
	this->shininess = shininess;
}

void CMaterial::SetShininessStrength(float shininessStrength)
{
	this->shininessStrength = shininessStrength;
}

void CMaterial::SetSelfIllum(float selfIllum)
{
	this->selfIllum = selfIllum;
	//this->emission[0] = color.r;
	//this->emission[1] = color.g;
	//this->emission[2] = color.b;
	//this->emission[3] = 1;
}

void CMaterial::Apply()
{
	GLfloat shininess=32.0;

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, specular);
	//glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, emission);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS, &shininess);
}