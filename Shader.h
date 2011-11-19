#pragma once
#include "main.h"
#include "fstream"

class Shader
{
	// Загружен ли шейдер
	bool Loaded;
	// Идентификаторы ШО
	GLuint VShader;
	GLuint FShader;
public:
	// Идентификатор ШП
	GLuint PShader;
private:
	// Загрузка шейдера из файла и компиляция
	bool Load(unsigned int Shader, string FileName);
public:
	// Загрузка шейдера
	void LoadShader(string Name);
	// Активация шейдера
	void Activate();
	Shader(void);
	~Shader(void);
};
