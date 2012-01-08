#include <fstream>
#include "Material.h"
#include "C3DS.h"

extern C3DS scene;

CMaterial::CMaterial()
{
	this->emission[0] = 0;
	this->emission[1] = 0;
	this->emission[2] = 0;
	this->emission[3] = 1;
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

void CMaterial::SetTransparency(float transparency)
{
	this->transparency = transparency;
	this->emission[3] = 1.0 - transparency / 100;
}

bool CMaterial::IsTransparent()
{
	return transparency > 5.0;
}

// установка режима фильтрации
void CMaterial::SetFilterMode(char mode)
{
	if (texture1.texture.imageData != NULL)
	{
		glBindTexture(GL_TEXTURE_2D,texture1.texture.texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
		switch (mode)
		{
			case TEXTURE_FILTER_NEAREST:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				break;
			case TEXTURE_FILTER_LINEAR:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;
			case TEXTURE_FILTER_MIPMAP_LINEAR:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;
			case TEXTURE_FILTER_ANISOTROPY:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8);
				break;
		}
	}
	if (textureSpecular.texture.imageData != NULL)
	{
		glBindTexture(GL_TEXTURE_2D,textureSpecular.texture.texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
		switch (mode)
		{
			case TEXTURE_FILTER_NEAREST:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				break;
			case TEXTURE_FILTER_LINEAR:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;
			case TEXTURE_FILTER_MIPMAP_LINEAR:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				break;
			case TEXTURE_FILTER_ANISOTROPY:
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8);
				break;
		}
	}
}

void CMaterial::Apply(void* texCoordPtr)
{
	GLfloat shininess=32.0;
	bool _useTex1 = false;
	bool _useTexSpec = false;

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, emission);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS, &shininess);

	//данные текстуры
	Texture* _tex = texture1.GetTexture();
	if (_tex->imageData != NULL)
	{
		_useTex1 = true;
		int _sampler = glGetUniformLocation(scene.shader->PShader, "tex1");

		// Установка текущего ТБ
		glUniform1i(_sampler,0);

		// Связывание ТБ с текстурой
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,_tex->texID);

		// Включение массива текстурных координат
		glClientActiveTexture(GL_TEXTURE0);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2,GL_FLOAT,0, texCoordPtr);
	}

	
	//данные текстуры
	_tex = textureSpecular.GetTexture();
	if (_tex->imageData != NULL)
	{
		_useTexSpec = true;

		int _sampler = glGetUniformLocation(scene.shader->PShader, "texSpec");

		// Установка текущего ТБ
		glUniform1i(_sampler,1);

		// Связывание ТБ с текстурой
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D,_tex->texID);

		// Включение массива текстурных координат
		glClientActiveTexture(GL_TEXTURE1);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2,GL_FLOAT,0, texCoordPtr);
	}

	glUniform1i(glGetUniformLocation(scene.shader->PShader, "useTex1"), _useTex1);
	glUniform1i(glGetUniformLocation(scene.shader->PShader, "useTexSpec"), _useTexSpec);
}