#include "C3DS.h"
#include "Occluder.h"

extern C3DS scene;

extern GLuint occluderBufferVBOIndex;
// загрузка файла 3ds
extern bool Load3DSFile(const char *FileName, C3DS* scene);

// установка режима фильтрации
void C3DS::SetFilterMode(char mode)
{
	for (uint i = 0; i < materials.size(); i++)
		materials[i]->SetFilterMode(mode);
}

// Получение текущей камеры
CCamera* C3DS::GetCurrentCamera()
{
	return cameras[cameraIndex];
}

// Получение следующей камеры
CCamera* C3DS::GetNextCamera()
{
	SortObjects();
	return cameras[(++cameraIndex)%cameras.size()];
}

// Получение текущего источника света
CLight* C3DS::GetCurrentLight()
{
	if (lightIndex >= 0)
		return lights[lightIndex];
	else
		return NULL;
}

// Получение следующего источника света
CLight* C3DS::GetNextLight()
{
	if (lightIndex >= 0)
		return lights[(++lightIndex)%lights.size()];
	else
		return NULL;
}

// загрузка файла 3ds
bool C3DS::Load(const char *FileName, Shader* shader)
{
	bool _retBool = false;
	UseDestructors=false;
	cameraIndex = 0;
	lightIndex = -1;

	WriteLogF("Loading scene \"%s\"...", FileName);

	// Файл существует
	if (Load3DSFile(FileName, this)!=NULL)
	{
		this->shader = shader;
		if (cameras.size() == 0)
		{
			cameras.push_back(new CCamera());
			WriteLogF("Cameras not found. Created default camera.");
		}

		if (lights.size() > 0)
			lightIndex = 0;

		if (objects.size() > 0 && objects.back()->VertexCount == 0)
			objects.pop_back();

		for (uint _objNum = 0; _objNum < objects.size(); _objNum++)
		{
			C3DSObject * currentObject = objects[_objNum];
			// Преобразования систем координат
			//for(int i=0;i<currentObject->VertexCount;++i)
			//{
			//		//Надо сначала сдвинуть его назад, то есть на вектор
			//		//-offset (НЕ на offset),
			//		// x
			//		currentObject->VertexList[3*i]-=currentObject->LocalMatrix[9];
			//		// y
			//		currentObject->VertexList[3*i+1]-=currentObject->LocalMatrix[11];
			//		// z
			//		currentObject->VertexList[3*i+2]-=currentObject->LocalMatrix[10];
			//		//а потом применить матрицу поворота rotmatr
			//		//Матрица записана построчно
			//		//В ней y и z тоже везде обменены местами!
			//		GLfloat x=-currentObject->VertexList[3*i];
			//		GLfloat y=-currentObject->VertexList[3*i+1];
			//		GLfloat z=-currentObject->VertexList[3*i+2];
			//		currentObject->VertexList[3*i]=currentObject->LocalMatrix[0]*x+currentObject->LocalMatrix[2]*z+currentObject->LocalMatrix[1]*y;
			//		currentObject->VertexList[3*i+2]=currentObject->LocalMatrix[3]*x+currentObject->LocalMatrix[5]*z+currentObject->LocalMatrix[4]*y;
			//		currentObject->VertexList[3*i+1]=currentObject->LocalMatrix[6]*x+currentObject->LocalMatrix[8]*z+currentObject->LocalMatrix[7]*y;
			//}

			GLfloat _min[3], _max[3];
			for (int i = 0; i < 3; ++i)
			{
				_min[0] = 1E+37;
				_max[0] = -1E+37;
			}

			// дублирование вершин
			GLfloat *VertexListCopy=new GLfloat[currentObject->IndexCount*4*2];//+нормали+текстурные координаты
			for(unsigned int i=0;i<currentObject->IndexCount;++i)
			{
				for(int k=0;k<3;++k)	
				{
					VertexListCopy[3*i+k]=currentObject->VertexList[3*currentObject->IndexList[i]+k];
					if (_min[k] > VertexListCopy[3*i+k])
						_min[k] = VertexListCopy[3*i+k];
					else if (_max[k] < VertexListCopy[3*i+k])
						_max[k] = VertexListCopy[3*i+k];
				}
				if (currentObject->TexVertList != NULL)
				{
					for(int k=0;k<2;++k)	
						// добавление текстурных координат
						VertexListCopy[currentObject->IndexCount*3*2+2*i+k]=currentObject->TexVertList[2*currentObject->IndexList[i]+k];
				}
			}

			// Вычисление нормалей
			for(unsigned int i=0;i<currentObject->IndexCount/3;++i)
			{
				//A2A1
				vec3 a1=vec3(VertexListCopy[3*(3*i+2)]-VertexListCopy[3*(3*i+1)], VertexListCopy[3*(3*i+2)+1]-VertexListCopy[3*(3*i+1)+1], VertexListCopy[3*(3*i+2)+2]-VertexListCopy[3*(3*i+1)+2]);
				//A0A1
				vec3 a2=vec3(VertexListCopy[3*3*i]-VertexListCopy[3*(3*i+1)], VertexListCopy[3*3*i+1]-VertexListCopy[3*(3*i+1)+1], VertexListCopy[3*3*i+2]-VertexListCopy[3*(3*i+1)+2]);
				vec3 normal=normalize(-cross(a1, a2));
				//устанавливаем нормаль для каждой из 3 вершин
				for(int j=0;j<3;++j)
					for(int k=0;k<3;++k)
						VertexListCopy[currentObject->IndexCount*3+i*9+j*3+k]=normal[k];
			}
			// VBO
			// Получаем свободный идентификатор
			glGenBuffersARB(1, &currentObject->Buffer);

			// Выбираем буферы как текущие
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, currentObject->Buffer);
			//glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, Buffers[1]);

			// Заполнение буферов VBO
			glBufferDataARB(GL_ARRAY_BUFFER_ARB,sizeof(GLfloat)*6*currentObject->IndexCount+sizeof(GLfloat)*2*currentObject->IndexCount,VertexListCopy,GL_STATIC_DRAW_ARB);
			//glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB,sizeof(unsigned short)*IndexCount,IndexList,GL_STATIC_DRAW_ARB);

			// Устанавливаем текущие буферы VBO = 0
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);

			//printf("  Loading successful. Using buffers %u and %u\n", Buffers[0], Buffers[1]);
			currentObject->occluder = new COccluder(_min, _max);
			WriteLogF("  Object '%s': loading successful. Using buffer %u", currentObject->name.c_str(), currentObject->Buffer);
			delete[] VertexListCopy;
		}
		UseDestructors=true;
		_retBool = true;
		queries = new GLuint[objects.size()];
		SortObjects();
	}
	else
	{
		WriteLogF("  Error: File not found.\n");
		_retBool = false;
	}
	return _retBool;
}

// сортировка объектов
void C3DS::SortObjects(void)
{
	if (UseDestructors)
	{
		UseDestructors=false;
		if (objects.size() > 1)
			sort(objects.begin(), objects.end(), ObjectsComparer);
		UseDestructors=true;
	}
}

// вывод на экран
void C3DS::Render(void)
{
	occludedCount = 0;
	GLuint sampleCount;

	GLuint N = objects.size();

	if (UseOcclusionCulling)
	{
		// Проверка результатов предыдущего кадра
		for (uint i = 0; i < N; i++)
		{
			C3DSObject* _obj = objects[i];

			glGetQueryObjectuivARB(queries[i], GL_QUERY_RESULT_ARB, &sampleCount);
			if (sampleCount == 0)
			{
				occludedCount++;
				_obj->wasDrawn = false;
			}
			else
			{
				_obj->wasDrawn = true;
			}
		}

		glGenQueriesARB(N, queries);
		for (uint i = 0; i < N; i++)
		{
			C3DSObject* _obj = objects[i];

			glBeginQueryARB(GL_SAMPLES_PASSED_ARB, queries[i]);
			if (_obj->wasDrawn)
			{
				_obj->Render();
			}
			else
			{
				_obj->occluder->Render();
			}
			glEndQueryARB(GL_SAMPLES_PASSED_ARB);
		}
	}
	// Без OC
	else
	{
		for (uint i = 0; i < N; i++)
		{
			objects[i]->Render();
		}
	}
}

C3DS::C3DS()
{
	queries = NULL;
}

C3DS::~C3DS(void)
{
	if (queries != NULL)
		delete[] queries;

	glDeleteBuffersARB(1, &occluderBufferVBOIndex);

	for (uint i = 0; i < objects.size(); i++)
		delete objects[i];
	for (uint i = 0; i < cameras.size(); i++)
		delete cameras[i];
	for (uint i = 0; i < lights.size(); i++)
		delete lights[i];
	for (uint i = 0; i < materials.size(); i++)
		delete materials[i];

	objects.clear();
	cameras.clear();
	lights.clear();
	materials.clear();
}

bool ObjectsComparer(C3DSObject *obj1, C3DSObject *obj2)
{
	if (obj1->isTransparent && obj2->isTransparent)
	{
		float _len1 = length(obj1->occluder->center - scene.GetCurrentCamera()->GetPos());
		float _len2 = length(obj2->occluder->center - scene.GetCurrentCamera()->GetPos());
		return (_len1 < _len2);
	}
	else if (!obj1->isTransparent && !obj2->isTransparent)
	{
		float _len1 = length(obj1->occluder->center - scene.GetCurrentCamera()->GetPos());
		float _len2 = length(obj2->occluder->center - scene.GetCurrentCamera()->GetPos());
		return (_len1 > _len2);
	}
	else if (obj1->isTransparent)
	{
		return false;
	}
	return true;
}
