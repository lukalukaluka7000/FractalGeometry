#pragma once
#include<string>
#include"GLTexture.h"
static class ImageLoader
{
public:
	static GLTexture loadPNG(std::string filePath);
};