#pragma once
#include "main.h"
#include "Shader.h"
#include "C3DSObject.h"
#include <fstream>

using namespace glm;

class C3DS
{
private:
	vector<C3DSObject*> objects;
public:
	void SetFilterMode(char);
	// очистка текстуры
	void ClearTexture();
	// установка текстуры
	void SetTexture(string);
	// загрузка файла 3ds
	bool Load (const char *FileName, Shader*);
	// вывод объекта на экран
	void Render (void);
	C3DS();
	~C3DS(void);
};
