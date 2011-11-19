#include <fstream>
#include "C3DSObject.h"
#include "Shader.h"

struct Vertex {
	GLfloat Coord[3];
	GLfloat TexCoord[2];
	GLfloat Color[3];
	GLfloat Normal[3];
};

char TextureFilter;

vector <C3DSObject> objects;
Vertex Plane[16];

Shader PlaneShader, ModelShader;

Texture texture0;

// Изменение режима фильтрации
void ChangeTextureFilter() 
{
	++TextureFilter;
	TextureFilter%=4;
	glBindTexture(GL_TEXTURE_2D,texture0.texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1);
	switch (TextureFilter)
	{
		case TEXTURE_FILTER_NEAREST:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			printf("Texture filter: Nearest\n");
			break;
		case TEXTURE_FILTER_LINEAR:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			printf("Texture filter: Linear\n");
			break;
		case TEXTURE_FILTER_MIPMAP_LINEAR:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			printf("Texture filter: MipMap Linear\n");
			break;
		case TEXTURE_FILTER_ANISOTROPY:
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8);
			printf("Texture filter: 8xAnisotropy\n");
			break;
	}
	for(unsigned int i=0;i<objects.size();++i)
	{
		objects[i].SetFilterMode(TextureFilter);
	}
}

// Установка источников света
void SetLightSources()
{
	GLfloat ambient[4]={0.2,0.2,0.2,1}, diffuse[4]={0.8,0.8,0.8,1}, specular[4]={0.8,0.8,0.8,1}, position[4]={6, 3.5, 6, 1};

	glLightfv(GL_LIGHT0,GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0,GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0,GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0,GL_POSITION, position);

	for (int i=0; i<3; ++i)
	{
		ambient[i]=0.2;
		diffuse[i]=0.8;
		specular[i]=0.8;
	}
	ambient[1]=0; diffuse[1]=0; specular[1]=0;
	ambient[2]=0; diffuse[2]=0; specular[2]=0;
	ambient[3]=1; diffuse[3]=1; specular[3]=1;
	position[0]=-6; position[1]=3.5; position[2]=-6; position[3]=1;

	glLightfv(GL_LIGHT1,GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1,GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1,GL_SPECULAR, specular);
	glLightfv(GL_LIGHT1,GL_POSITION, position);
}

// текстура плоскости
void SetPlaneTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1,(GLuint *)&texture0.texID);
	glBindTexture(GL_TEXTURE_2D,texture0.texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP,GL_TRUE);

	string FullFileNameStr =ProgPath+"Textures\\plane.tga";

	if (!LoadTGA(&texture0,const_cast<char*>(FullFileNameStr.c_str())))
	{
		MessageBox(0,"Plane texture was not found!","ERROR",0);
		exit(1);
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glTexImage2D (GL_TEXTURE_2D,0,GL_RGB,texture0.width,texture0.height,
		0,texture0.type,GL_UNSIGNED_BYTE,texture0.imageData);
}

// Загрузка объектов.
void LoadObjects()
{
	C3DSObject obj;
	obj.SetScale(1);

	const unsigned short CODE_MODEL_NO=0;
	const unsigned short CODE_MODEL_POSITION=1;
	const unsigned short CODE_MODEL_SCALE=2;
	const unsigned short CODE_MODEL_FILENAME=3;
	const unsigned short CODE_MODEL_COLOR=4;
	const unsigned short CODE_MODEL_TEXTURE=5;

	const char* NAME_MODEL_POSITION="v=(";
	const char* NAME_MODEL_SCALE="mscale=";
	const char* NAME_MODEL_COLOR="mcolor=(";
	const char* NAME_MODEL_TEXTURE="t=\"";
	const char* NAME_MODEL_FILENAME="m=\"";

	unsigned short code;	

	ifstream ConfigF(ConfigFile.c_str(), ios::in);
	// Временный буфер
	char str[MAX_CONFIG_LINE_LENGTH];
	string str2;

	int pos;

	vector<string> v;

	// Избегаем освобождения буферов при перемещении объектов в векторе
	UseDestructors=false;

	while (ConfigF.good())
	{
		v.clear();
		ConfigF.getline(str,MAX_CONFIG_LINE_LENGTH-1);
		str2=str;
		str2=StrToLower(remove_spaces(str2));
		
		// Имя параметра соответствует требуемому
		if (str2.find(NAME_MODEL_POSITION) != string::npos)
			code=CODE_MODEL_POSITION;
		else if (str2.find(NAME_MODEL_FILENAME) != string::npos)
			code=CODE_MODEL_FILENAME;
		else if (str2.find(NAME_MODEL_SCALE) != string::npos)
			code=CODE_MODEL_SCALE;
		else if (str2.find(NAME_MODEL_COLOR) != string::npos)
			code=CODE_MODEL_COLOR;
		else if (str2.find(NAME_MODEL_TEXTURE) != string::npos)
			code=CODE_MODEL_TEXTURE;
		else
			code=CODE_MODEL_NO;

		switch (code)
		{
		case CODE_MODEL_POSITION:
			pos=str2.find(NAME_MODEL_POSITION);
			split(str2.substr(pos+strlen(NAME_MODEL_POSITION)),",;)", v);
			if (v.size()>2)
				// установка позиции объекта
				obj.SetPos(atof(v[0].c_str()), atof(v[1].c_str()), atof(v[2].c_str()));
			break;
		case CODE_MODEL_COLOR:
			pos=str2.find(NAME_MODEL_COLOR);
			split(str2.substr(pos+strlen(NAME_MODEL_COLOR)),",;)", v);
			if (v.size()>2)
				// установка цвета объекта
				obj.SetColor(atof(v[0].c_str()), atof(v[1].c_str()), atof(v[2].c_str()));
			break;
		case CODE_MODEL_SCALE:
			pos=str2.find(NAME_MODEL_SCALE);
			obj.SetScale(atof(str2.substr(pos+strlen(NAME_MODEL_SCALE)).c_str()));
			break;
		case CODE_MODEL_TEXTURE:
			pos=str2.find(CODE_MODEL_TEXTURE);
			split(str2.substr(pos+strlen(NAME_MODEL_TEXTURE)),"\"", v);
			obj.SetTexture(v[0]);
			break;
		case CODE_MODEL_FILENAME:
			pos=str2.find(CODE_MODEL_FILENAME);
			split(str2.substr(pos+strlen(NAME_MODEL_FILENAME)),"\"", v);
			if (v.size()==1)
			{
				// Загрузка объекта
				objects.push_back(obj);
				if (!objects[objects.size()-1].Load((ProgPath+"Models\\"+v[0]).c_str(), &ModelShader))
					objects.pop_back();
				obj.ClearTexture();
				obj.SetScale(1);
				obj.SetColor(0.0, 0.0, 0.9);
			}
			break;
		}
	}
	ConfigF.close();
	WriteLogF("Total objects loaded: %d\n", objects.size());

	UseDestructors=true;

	// Загрузка шейдеров
	PlaneShader.LoadShader("Phong");
	ModelShader.LoadShader("Phong");
	SetPlaneTexture();
}


// материал плоскости
void SetPlaneMaterial()
{
	int sampler = glGetUniformLocation(PlaneShader.PShader,"MyTex");
	glUniform1i(sampler,0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,texture0.texID);
	/*GLfloat ambient[4]={1,1,1,1}, diffuse[4]={0.8,0.8,0.8,1}, specular[4]={0.9,0.9,0.9,1}, shininess=32.0;

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS, &shininess);*/
}

// материал моделей
void SetModelMaterial()
{
	
	GLfloat ambient[4]={1,1,1,1}, diffuse[4]={0.8,0.8,0.8,1}, specular[4]={0.0,0.0,0.0,1}, shininess=32.0;

	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS, &shininess);
}

void DrawPlane(GLfloat x, GLfloat y, GLfloat z, GLfloat r=0.5, GLfloat g=0.1, GLfloat b=0.1)
{
	GLfloat ModelMatrix[16]={
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	GLuint Indexes[18*3]={
		0,4,5,
		0,5,1,
		1,5,6,
		1,6,2,
		2,6,7,
		2,7,3,
		4,8,9,
		4,9,5,
		5,9,10,
		5,10,6,
		6,10,11,
		6,11,7,
		8,12,13,
		8,13,9,
		9,13,14,
		9,14,10,
		10,14,15,
		10,15,11
	};

	ModelMatrix[12]=x;
	ModelMatrix[13]=y;
	ModelMatrix[14]=z;

	for (int i=0; i<16; ++i)
	{
		Plane[i].Color[0]=r;
		Plane[i].Color[1]=g;
		Plane[i].Color[2]=b;

		Plane[i].Normal[0]=0;
		Plane[i].Normal[1]=1;
		Plane[i].Normal[2]=0;
	}

	glPushMatrix();
	// умножаем матрицу камеры на матрицу трансформации объекта
	glMultMatrixf(ModelMatrix);
	// выводим модель
	// используем шейдер
	PlaneShader.Activate();
	SetPlaneMaterial();
	// включаем массивы
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	// указываем данные для массивов
	glVertexPointer(3,GL_FLOAT,sizeof(Vertex),Plane[0].Coord);
	glColorPointer(3,GL_FLOAT,sizeof(Vertex),Plane[0].Color);
	glNormalPointer(GL_FLOAT,sizeof(Vertex),Plane[0].Normal);
	glTexCoordPointer(2,GL_FLOAT,sizeof(Vertex),Plane[0].TexCoord);
	// вывод полигонов
	glDrawElements(GL_TRIANGLES,18*3,GL_UNSIGNED_INT,Indexes);
	// выключение массивов
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	// востанавливаем матрицу камеры
	glPopMatrix();
}

void RenderObjects()
{
	SetLightSources();
	SetModelMaterial();

	// используем шейдер
	ModelShader.Activate();
	// Вывод объектов
	for(unsigned int i=0;i<objects.size();++i)
	{
		objects[i].Render();
	}

	DrawPlane(0.0,0.0,0.0);
}

// Вычисления, выполняемые в начале программы.
void PreCalcObjects()
{
	for (int i=0; i<16; ++i)
	{
		Plane[i].Coord[0]=-6+4*(i%4);
		Plane[i].Coord[1]=0;
		Plane[i].Coord[2]=-6+4*(i/4);

		Plane[i].Color[0]=0.1;
		Plane[i].Color[1]=0.1;
		Plane[i].Color[2]=0.1;

		Plane[i].TexCoord[0]=1-(i%2);
		Plane[i].TexCoord[1]=1-(i/4)%2;
	}

	TextureFilter = TEXTURE_FILTER_NEAREST;
}