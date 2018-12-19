
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H 

#include "Tga.h"
#include <string>
#include <GL/glut.h>
#include <iostream>
#include <map>

class TextureManager
{
public:

	const std::string m_pathToTextureConfigFile = "textures.conf";

	static TextureManager& getInstance();

	static GLuint getTexture(uint16_t textureIndex);
	static bool containsTexture(uint16_t textureIndex);

	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;

private:
	TextureManager();
	~TextureManager();

	void addTexture(uint16_t index, const std::string path, bool generateMipMap = true);

	static std::map<uint16_t, GLuint> m_textureLib;
};

#endif // !TEXTURE_MANAGER_H
