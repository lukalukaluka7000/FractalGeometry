#include "ImageLoader.h"
#include<vector>
#include"picoPNG.h"
#include <FractalGeometry\IOManager.h>
#include <iostream>

GLTexture ImageLoader::loadPNG(std::string filePath) {
	GLTexture texture = {};

	std::vector<unsigned char> in;
	std::vector<unsigned char> out;

	unsigned long width;
	unsigned long height;

	if (IOManager::readPngToBuffer(filePath, in) == false) {
		std::cout << "Failed to load PNG to vector of chars!" << std::endl;
		exit(69);
	}

	int errorCode = decodePNG(out, width, height, &(in[0]), in.size());// ovaj in moram dat pointer na prvi element a kako radimo sa vektorima onda ovo sta pise

	if (errorCode != 0) { //zero no error
		std::cout << "DecodePNG failed with error" + std::to_string(errorCode) << std::endl;
		exit(69);
	}

	glGenTextures(1, &(texture.id));
	glBindTexture(GL_TEXTURE_1D, texture.id);

	//upload to opengl gpu
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, width, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // set texture filtering to nearest neighbor to clearly see the texels/pixels
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//glGenerateMipmap(GL_TEXTURE_1D);
	glBindTexture(GL_TEXTURE_1D, texture.id);

	texture.width = width;
	texture.height = height;

	return texture;
}