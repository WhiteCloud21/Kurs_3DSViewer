#include "main.h"

bool CullFaceFlag=false;
bool UseDestructors=true;

string ProgPath;
string LogFile;

int windowWidth, windowHeight;
bool UseOcclusionCulling;
unsigned int occludedCount;
int getQTime;
int frameSkipQuery;