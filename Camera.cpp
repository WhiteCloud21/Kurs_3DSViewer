#include <windows.h>
#include <fstream>
#include "Camera.h"
#include "C3DS.h"

extern C3DS scene;

// Конструктор по умолчанию
CCamera::CCamera(void)
{
	positionDefault=vec3((GLfloat)15,15,15);
	ViewPoint=vec3((GLfloat)0,0,0);
	Reset();
}

CCamera::~CCamera(void)
{
	//SaveToFile();
}

// Конструктор со списком параметров
CCamera::CCamera(GLfloat x, GLfloat y, GLfloat z, GLfloat lx, GLfloat ly, GLfloat lz)
{
	positionDefault=vec3(x,y,z);
	ViewPoint=vec3(lx,ly,lz);
	Reset();
}

// Получение позиции
vec3 CCamera::GetPos()
{
	return position;
}

// Сброс камеры
void CCamera::Reset(void)
{
	position=positionDefault;
	//ViewPoint.x=0;
	//ViewPoint.y=0;
	//ViewPoint.z=0;
	//SaveToFile();
	Recalc();
}

// Пересчет матрицы камеры
void CCamera::Recalc(void)
{
	// пересчет векторов
	forward = ViewPoint - position;
	forward = normalize(forward);

	right = cross(forward, vec3(0,1,0));
	right = normalize(right);

	up = cross(right, forward);
	up = normalize(up);

	// вектор вправо
	matrix[0]=right.x;
	matrix[4]=right.y;
	matrix[8]=right.z;
	matrix[12]=0;
	// вектор вверх
	matrix[1]=up.x;
	matrix[5]=up.y;
	matrix[9]=up.z;
	matrix[13]=0;
	// вектор -вперед
	matrix[2]=-forward.x;
	matrix[6]=-forward.y;
	matrix[10]=-forward.z;
	matrix[14]=0;
	// последняя строка
	matrix[3]=0;
	matrix[7]=0;
	matrix[11]=0;
	matrix[15]=1;

	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0,((float)windowWidth)/windowHeight,1.0,sqrt(position.x * position.x + position.y * position.y + position.z * position.z)*4);

	scene.SortObjects();
}

// Пересчет матрицы камеры и ее применение
void CCamera::ApplyCamera(void)
{
	GLdouble m[16];

	// ориентация камеры
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixd(matrix);
	// позиция камеры
	m[0]=1;	m[1]=0;	m[2]=0;	m[3]=0;
	m[4]=0;	m[5]=1;	m[6]=0;	m[7]=0;
	m[8]=0;	m[9]=0;	m[10]=1;m[11]=0;
	m[12]=-position.x; 
	m[13]=-position.y; 
	m[14]=-position.z; 
	m[15]=1;
	glMultMatrixd(m);
}

// Перемещение камеры вперед
void CCamera::Forward(void)
{
	double r=length(ViewPoint - position);
	if (r>4)
	{
		position=position+forward*r/20;
	}
	Recalc();
}

// Перемещение камеры назад
void CCamera::Back(void)
{
	double r=length(ViewPoint - position);
	//if (r<60)
	{
		position=position-forward*r/20;
	}
	Recalc();
}

// Перемещение камеры влево
void CCamera::Left(void)
{
	double r=length(ViewPoint - position);
	position=position+(-right+forward*(sqrt(r*r+1)-r))*r/20;
	Recalc();
}

// Перемещение камеры вправо
void CCamera::Right(void)
{
	double r=length(ViewPoint - position);
	position=position+(right+forward*(sqrt(r*r+1)-r))*r/20;
	Recalc();
}

// Перемещение камеры вверх
void CCamera::Up(void)
{
	double r=length(ViewPoint - position);
	if (asin((position.y - ViewPoint.y)/r)<1.4)
	{
		position=position+(up+forward*(sqrt(r*r+1)-r))*r/20;
	}
	Recalc();
}

// Перемещение камеры вниз
void CCamera::Down(void)
{
	double r=length(ViewPoint - position);
	if (asin((position.y - ViewPoint.y)/r)>-1.4)
	{
		position=position+(-up+forward*(sqrt(r*r+1)-r))*r/20;
	}
	Recalc();
}