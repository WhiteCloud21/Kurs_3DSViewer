#pragma once
#include "main.h"
#include "Shader.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "VBOInfo.h"
#include "Occluder.h"
#include <fstream>

using namespace glm;

class C3DSObject
{
	friend class C3DS;
	friend bool ObjectsComparer(C3DSObject *obj1, C3DSObject *obj2);
	friend void ReadChunk(ifstream &, C3DS*);
private:
	// имя объекта
	string name;
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
	// буферы VBO для индексов
	vector<CVBOInfo> IndexVBO;
	// локальная матрица
	GLfloat LocalMatrix[12];
	// Occluder
	COccluder* occluder;
	// Был ли отрисован на последнем кадре
	bool wasDrawn;
	// Прозрачный ли
	bool isTransparent;
	// конструктор
	C3DSObject();
	~C3DSObject(void);
public:
	// установка имени
	void SetName(char* name);
	// вывод объекта на экран
	void Render (void);
};
