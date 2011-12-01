#include "main.h"
#include <windows.h>

using namespace glm;

class CCamera
{
private:
	vec3 position;
	vec3 ViewPoint;
	vec3 right;
	vec3 up;
	vec3 forward;

	vec3 forwardFlat;
	vec3 rightFlat;

	GLdouble matrix[16];
public:
	CCamera(void);
	CCamera(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	~CCamera(void);
	void Reset(void);
	void Recalc(void);
	void ApplyCamera(void);
	void Forward(void);
	void Back(void);
	void Left(void);
	void Right(void);
	void Up(void);
	void Down(void);
	void LoadFromFile(void);
	void SaveToFile(void);
};