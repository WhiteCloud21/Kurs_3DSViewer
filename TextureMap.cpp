#include "TextureMap.h"

CTextureMap::CTextureMap(void)
{
	texture.imageData = NULL;
}

CTextureMap::~CTextureMap(void)
{
	clearTexture();
}

void CTextureMap::clearTexture()
{
	if (texture.imageData != NULL)
	{
		delete[] texture.imageData;
	}
	texture.imageData = NULL;
}

void CTextureMap::SetFileName(string filename)
{
	string _str = filename.substr(filename.length() - 4, 4);
	std::transform(_str.begin(), _str.end(), _str.begin(), ::toupper);
	size_t _index = filename.find_last_of('.');
	this->filename = filename;
	this->filename = this->filename.substr(0, _index) + ".TGA";

	clearTexture();
	WriteLogF("Loading texture \"%s\"...", this->filename.c_str());
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1,(GLuint *)&texture.texID);
	glBindTexture(GL_TEXTURE_2D, texture.texID);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_GENERATE_MIPMAP,GL_TRUE);

	string FullFileNameStr =ProgPath+"Textures\\"+this->filename; 
	char *FullFileName=const_cast<char*>(FullFileNameStr.c_str());

	if (LoadTGA(&texture,FullFileName))
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT,1);
		glTexImage2D (GL_TEXTURE_2D,0,GL_RGB,texture.width,texture.height,
			0,texture.type,GL_UNSIGNED_BYTE,texture.imageData);
		WriteLogF("  Texture succesfully loaded\n");
	}
	else
		texture.imageData = NULL;
}

Texture* CTextureMap::GetTexture()
{
	return &texture;
}