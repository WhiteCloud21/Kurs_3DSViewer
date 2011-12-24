#pragma once
#include <windows.h>
#include "glee.h"
#include "glm/glm.hpp"
#include "glut.h"
#include "texture.h" 

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "macro.h"

using namespace std;

// Данные
typedef vector<GLfloat> vect;

const char TEXTURE_FILTER_NEAREST = 0;
const char TEXTURE_FILTER_LINEAR = 1;
const char TEXTURE_FILTER_MIPMAP_LINEAR = 2;
const char TEXTURE_FILTER_ANISOTROPY = 3;

const int MAX_CONFIG_LINE_LENGTH=500;

extern bool UseDestructors;
extern bool UseOcclusionCulling;
extern bool CullFaceFlag;

extern string ProgPath;
extern string LogFile;
extern unsigned int occludedCount;
extern int getQTime;
extern int frameSkipQuery;

extern int windowWidth, windowHeight;

// Функции
extern bool FileExists (const char *fname);
extern string getNowToString();

extern void ChangeTextureFilter();
extern void LoadObjects(char* filename);
extern void RenderObjects();

extern bool LoadTGA(Texture * texture, char * filename);