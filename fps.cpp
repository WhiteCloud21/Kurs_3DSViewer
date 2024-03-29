#include "main.h"

int frameCount, oldTime;
char _outBuf[50];

// ������������ ��������� ������
void renderBitmapString(float x, float y, void *font, char *string)
{
	char *c;
	glRasterPos2f(x, y);
	for (c=string; *c != NULL; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}

// ��������� fps
void DrawFps()
{
	frameCount++;
	int _time=glutGet(GLUT_ELAPSED_TIME);
	if (_time - oldTime > 1000) {
		//sprintf_s(_outBuf,"FPS: %6d Occluded: %10u",
		//	(int)(frameCount*1000.0/(_time-oldTime)), occludedCount);
		sprintf_s(_outBuf,"FPS: %6d",
			(int)(frameCount*1000.0/(_time-oldTime)));
		oldTime = _time;
		frameCount = 0;
	}

	// ��������� �������� �� ���������������
	glMatrixMode(GL_PROJECTION);
	// ���������� ���������� �������
	glPushMatrix();
	// ����� �������
	glLoadIdentity();
	// ��������� 2D ��������������� ��������
	gluOrtho2D(0, windowWidth, windowHeight, 0);	
	// ������� � ����� ModelView
	glMatrixMode(GL_MODELVIEW);
	// ���������� ���������� �������
	glPushMatrix();
	// ����� �������
	glLoadIdentity();

	// ��������� ������
	glColor3f(1, 1, 1);
	renderBitmapString(10, 20, GLUT_BITMAP_HELVETICA_18, _outBuf);
	// �������������� MVM
	glPopMatrix();
	
	glMatrixMode(GL_PROJECTION);
	// �������������� PM
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
}