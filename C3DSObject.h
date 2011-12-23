#pragma once
#include "main.h"
#include "Shader.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "VBOInfo.h"
#include <fstream>

using namespace glm;

class C3DSObject
{
	friend class C3DS;
	friend void ReadChunk(ifstream &, C3DS*);
private:
	// имя объекта
	string name;
	// текстура
	Texture texture;
	// индексы буферов ARB
	GLuint Buffer;
	// количество текст. координат
	unsigned short TexVertCount;
	// список текст. координат
	GLfloat *TexVertList;
	// количество индексов
	unsigned int IndexCount;
	// список индексов
	unsigned short *IndexList;
	// количество вершин
	unsigned short VertexCount;
	// список вершин
	GLfloat *VertexList;
	// буфер VBO для вершин
	GLuint VertexVBO;
	// буфер VBO для индексов
	vector<CVBOInfo> IndexVBO;
	// локальная матрица
	GLfloat LocalMatrix[12];
	// шейдер
	//Shader *shader;
	// конструктор
	C3DSObject();
	~C3DSObject(void);
public:
	// установка имени
	void SetName(char* name);
	// установка режима фильтрации
	void SetFilterMode(char);
	// очистка текстуры
	void ClearTexture();
	// установка текстуры
	void SetTexture(string);
	// вывод объекта на экран
	void Render (void);
};
