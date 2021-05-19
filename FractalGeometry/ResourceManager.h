#pragma once
#include <string>
#include "GLTexture.h"
#include <FractalGeometry\TextureCache.h>
class ResourceManager
{
public:
	static GLTexture getTexture(std::string texturePath);
private:
	static TextureCache _textureCache;
};