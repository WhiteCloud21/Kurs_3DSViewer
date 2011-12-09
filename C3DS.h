#pragma once
#include "main.h"
#include "Shader.h"
#include "C3DSObject.h"
#include "Camera.h"
#include "Light.h"
#include <fstream>

using namespace glm;

class C3DS
{
private:
	vector<C3DSObject*> objects;
	vector<CCamera*> cameras;
	vector<CLight*> lights;
	int cameraIndex;
	int lightIndex;
public:
	void SetFilterMode(char);
	// Получение текущей камеры
	CCamera* GetCurrentCamera();
	// Получение следующей камеры
	CCamera* GetNextCamera();
	// Получение текущего источника света
	CLight* GetCurrentLight();
	// Получение следующего источника света
	CLight* GetNextLight();
	// загрузка файла 3ds
	bool Load (const char *FileName, Shader*);
	// вывод объекта на экран
	void Render (void);
	C3DS();
	~C3DS(void);
};
