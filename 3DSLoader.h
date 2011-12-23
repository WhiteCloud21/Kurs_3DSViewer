#pragma once
#include "main.h"
#include "C3DSObject.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "VBOInfo.h"
#include "C3DS.h"
#include <fstream>

using namespace glm;

char* objectName;
bool meshFirst;
vec3 color;
float percent;
bool isSpotLight;
bool isLightEnabled;
CTextureMap* currentMap;