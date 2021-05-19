#pragma once
#include <string>
#include "GLTexture.h"
#include <map>
class TextureCache
{
public:
	TextureCache();
	~TextureCache();
	GLTexture getTexture(std::string texturePath);
private:
	std::map<std::string, GLTexture> _textureMap;
};

