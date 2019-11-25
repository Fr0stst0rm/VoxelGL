#include "TextureManager.h"

std::map<uint16_t, GLuint> TextureManager::m_textureLib;
std::map<uint16_t, GLuint> TextureManager::m_normalMapLib;

TextureManager::TextureManager() {
	std::cout << "Loding texture config from: " << m_pathToTextureConfigFile << "\n";

	//TODO
	loadTextureFile(0, "cheese_d.tga", m_textureLib);
	loadTextureFile(1, "VoxelTexture_d.tga", m_textureLib);
	loadTextureFile(2, "crate_d.tga", m_textureLib);
	loadTextureFile(3, "wall_d.tga", m_textureLib);

	loadTextureFile(0, "cheese_n.tga", m_normalMapLib);
	loadTextureFile(1, "VoxelTexture_n.tga", m_normalMapLib);
	loadTextureFile(2, "crate_n.tga", m_normalMapLib);
	loadTextureFile(3, "wall_n.tga", m_normalMapLib);
}

TextureManager::~TextureManager() {

}

TextureManager & TextureManager::getInstance()
{
	static TextureManager instance; // Guaranteed to be destroyed.
	return instance;
}

GLuint TextureManager::getTexture(uint16_t textureIndex)
{
	return getInstance().m_textureLib[textureIndex]; //TODO
}

bool TextureManager::containsTexture(uint16_t textureIndex)
{
	return (getInstance().m_textureLib.find(textureIndex) != getInstance().m_textureLib.end());
}

GLuint TextureManager::getNormalMap(uint16_t textureIndex)
{
	return getInstance().m_textureLib[textureIndex]; //TODO
}


void TextureManager::loadTextureFile(uint16_t index, const std::string path, std::map<uint16_t, GLuint>& texLib, bool generateMipMap)
{
	GLsizei w, h;
	tgaInfo *info = 0;
	int mode;

	info = tgaLoad((char *)path.c_str());

	if (info->status != TGA_OK) {
		fprintf(stderr, "error loading texture image: %d\n", info->status);

		return;
	}
	if (info->width != info->height) {
		fprintf(stderr, "Image size %d x %d is not rectangular, giving up.\n",
			info->width, info->height);
		return;
	}

	mode = info->pixelDepth / 8;  // will be 3 for rgb, 4 for rgba

	GLuint texture;

	glGenTextures(1, &texture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	// Upload the texture bitmap. 
	w = info->width;
	h = info->height;

	GLint format = (mode == 4) ? GL_RGBA : GL_RGB;
	if (generateMipMap) {
		gluBuild2DMipmaps(GL_TEXTURE_2D, format, w, h, format, GL_UNSIGNED_BYTE, info->imageData);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, info->imageData);
	}
	tgaDestroy(info);

	texLib[index] = texture;
}