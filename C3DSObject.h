#pragma once
#include "main.h"
#include "Shader.h"
#include <fstream>

using namespace glm;

class C3DSObject
{
private:
	// имя объекта
	char name[256];
	// позиция объекта
	vec3 position;
	// цвет объекта
	vec3 color;
	// масштаб объекта
	GLfloat scale;
	// текстура
	Texture texture;
	// индексы буферов ARB
	GLuint Buffer;
	// количество текст. координат
	unsigned short TexVertCount;
	// список текст. координат
	GLfloat *TexVertList;
	// количество индексов
	unsigned short IndexCount;
	// список индексов
	unsigned short *IndexList;
	// количество вершин
	unsigned short VertexCount;
	// список вершин
	GLfloat *VertexList;
	// буфер VBO для вершин
	GLuint VertexVBO;
	// буфер VBO для индексов
	GLuint IndexVBO;
	// шейдер
	Shader *shader;
public:
	// установка позиции
	void SetPos(GLfloat x, GLfloat y, GLfloat z);
	// установка цвета
	void SetColor(GLfloat r, GLfloat g, GLfloat b);
	// установка масштаба
	void SetScale(GLfloat);
	// установка режима фильтрации
	void SetFilterMode(char);
	// очистка текстуры
	void ClearTexture();
	// установка текстуры
	void SetTexture(string);
	// загрузка файла 3ds и запись в буферы VBO
	bool Load (const char *FileName, Shader*);
	// вывод объекта на экран
	void Render (void);
	C3DSObject();
	~C3DSObject(void);
};
