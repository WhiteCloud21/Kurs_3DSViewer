#include <windows.h>
#include <fstream>
#include "Light.h"

CLight::~CLight(void)
{
}

// Конструкторы со списком параметров
CLight::CLight(bool enabled, vec3 position)
{
	this->isSpotLight = false;
	this->enabled = enabled;
	this->position[0] = position.x;
	this->position[1] = position.y;
	this->position[2] = position.z;
	this->position[3] = 1;

	this->color[0] = 0;
	this->color[1] = 0;
	this->color[2] = 0;
	this->color[3] = 1;

	this->CalculateDirectColor();
}

void CLight::CalculateDirectColor()
{
	if (isSpotLight)
	{
		for (int i = 0; i < 3; i++)
			this->directColor[i] = this->color[i]*2.5;
	}
	else
	{
		for (int i = 0; i < 3; i++)
			this->directColor[i] = this->color[i];
	}
	this->directColor[3] = 1;
}

// Установка направления
void CLight::SetTarget(vec3 target)
{
	this->isSpotLight = true;
	this->target = target;
	this->CalculateDirectColor();
}

// Установка цвета
void CLight::SetColor(vec3 color)
{
	this->color[0] = color.r;
	this->color[1] = color.g;
	this->color[2] = color.b;
	this->color[3] = 1;
	this->CalculateDirectColor();
}

// Применение источника света
void CLight::ApplyLight(void)
{
	glLightfv(GL_LIGHT0,GL_AMBIENT, color);
	glLightfv(GL_LIGHT0,GL_DIFFUSE, directColor);
	glLightfv(GL_LIGHT0,GL_SPECULAR, directColor);
	glLightfv(GL_LIGHT0,GL_POSITION, position);
}