#include "main.h"

int frameCount, oldTime;
char _outBuf[30];

// посимвольная отрисовка строки
void renderBitmapString(float x, float y, void *font, char *string)
{
	char *c;
	glRasterPos2f(x, y);
	for (c=string; *c != NULL; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}

// отрисовка fps
void DrawFps()
{
	frameCount++;
	int _time=glutGet(GLUT_ELAPSED_TIME);
	if (_time - oldTime > 1000) {
		sprintf_s(_outBuf,"%8d %10u OC",
			(int)(frameCount*1000.0/(_time-oldTime)), occludedCount);
		oldTime = _time;
		frameCount = 0;
	}

	// изменение проекции на ортографическую
	glMatrixMode(GL_PROJECTION);
	// сохранение предыдущей матрицы
	glPushMatrix();
	// сброс матрицы
	glLoadIdentity();
	// установка 2D ортографической проекции
	gluOrtho2D(0, windowWidth, windowHeight, 0);	
	// переход в режим ModelView
	glMatrixMode(GL_MODELVIEW);
	// сохранение предыдущей матрицы
	glPushMatrix();
	// сброс матрицы
	glLoadIdentity();

	// отрисовка строки
	glColor3f(1, 1, 1);
	renderBitmapString(10, 20, GLUT_BITMAP_HELVETICA_18, _outBuf);
	// восстановление MVM
	glPopMatrix();
	
	glMatrixMode(GL_PROJECTION);
	// восстановление PM
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
}