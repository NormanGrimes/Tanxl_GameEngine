#pragma once

#include "Tanxl_OpenGL_Render.h"

OpenGL_Render::OpenGL_Render():Tanxl_ClassBase("0.3") {}

std::string OpenGL_Render::readShaderFile(const char* filePath)
{
	std::string content{};
	std::ifstream fileStream(filePath, std::ios::in);
	std::string line{ "" };
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

void OpenGL_Render::printShaderLog(GLuint shader)
{
	int len{ 0 };
	int chWrittn{ 0 };
	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		std::cout << "Shader Info Log: " << log << std::endl;
		free(log);
	}
}

void OpenGL_Render::printProgramLog(int prog)
{
	int len{ 0 };
	int chWrittn{ 0 };
	char* log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		std::cout << "Program Info Log: " << log << std::endl;
		free(log);
	}
}

GLuint OpenGL_Render::prepareShader(int shaderTYPE, const char* shaderPath)
{
	GLint shaderCompiled{};
	std::string shaderStr{ readShaderFile(shaderPath) };
	const char* shaderSrc{ shaderStr.c_str() };
	GLuint shaderRef{ glCreateShader(shaderTYPE) };
	glShaderSource(shaderRef, 1, &shaderSrc, NULL);
	glCompileShader(shaderRef);
	checkOpenGLError();
	glGetShaderiv(shaderRef, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != 1)
	{
		if (shaderTYPE == 35633) std::cout << "Vertex ";
		if (shaderTYPE == 36488) std::cout << "Tess Control ";
		if (shaderTYPE == 36487) std::cout << "Tess Eval ";
		if (shaderTYPE == 36313) std::cout << "Geometry ";
		if (shaderTYPE == 35632) std::cout << "Fragment ";
		std::cout << "shader compilation error." << std::endl;
		printShaderLog(shaderRef);
	}
	return shaderRef;
}

GLuint OpenGL_Render::prepareShader(int shaderTYPE, std::string shaderStr)
{
	GLint shaderCompiled{};
	const char* shaderSrc{ shaderStr.c_str() };
	GLuint shaderRef{ glCreateShader(shaderTYPE) };
	glShaderSource(shaderRef, 1, &shaderSrc, NULL);
	glCompileShader(shaderRef);
	checkOpenGLError();
	glGetShaderiv(shaderRef, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != 1)
	{
		if (shaderTYPE == 35633) std::cout << "Vertex ";
		if (shaderTYPE == 36488) std::cout << "Tess Control ";
		if (shaderTYPE == 36487) std::cout << "Tess Eval ";
		if (shaderTYPE == 36313) std::cout << "Geometry ";
		if (shaderTYPE == 35632) std::cout << "Fragment ";
		std::cout << "shader compilation error." << std::endl;
		printShaderLog(shaderRef);
	}
	return shaderRef;
}

int OpenGL_Render::finalizeShaderProgram(GLuint sprogram)
{
	GLint linked{};
	glLinkProgram(sprogram);
	checkOpenGLError();
	glGetProgramiv(sprogram, GL_LINK_STATUS, &linked);
	if (linked != 1)
	{
		std::cout << "linking failed" << std::endl;
		printProgramLog(sprogram);
	}
	return sprogram;
}

bool OpenGL_Render::checkOpenGLError()
{
	bool foundError{ false };
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		std::cout << "glError: " << glErr << std::endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

GLuint OpenGL_Render::createShaderProgram(const char* vp, const char* fp)
{
	GLuint vShader{ prepareShader(GL_VERTEX_SHADER, vp) };
	GLuint fShader{ prepareShader(GL_FRAGMENT_SHADER, fp) };
	GLuint vfprogram{ glCreateProgram() };
	glAttachShader(vfprogram, vShader);
	glAttachShader(vfprogram, fShader);
	finalizeShaderProgram(vfprogram);
	return vfprogram;
}

GLuint OpenGL_Render::createShaderProgram(std::string vp, std::string fp)
{
	GLuint vShader{ prepareShader(GL_VERTEX_SHADER, vp) };
	GLuint fShader{ prepareShader(GL_FRAGMENT_SHADER, fp) };
	GLuint vfprogram{ glCreateProgram() };
	glAttachShader(vfprogram, vShader);
	glAttachShader(vfprogram, fShader);
	finalizeShaderProgram(vfprogram);
	return vfprogram;
}

GLuint OpenGL_Render::loadTexture(const char *texImagePath)
{
	GLuint textureRef{ SOIL_load_OGL_texture(texImagePath, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y) };
	if (textureRef == 0) std::cout << "didnt find texture file " << texImagePath << std::endl;
	// ----- mipmap/anisotroPIL section
	glBindTexture(GL_TEXTURE_2D, textureRef);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	if (glewIsSupported("GL_EXT_texture_filter_anisotroPIL")) {
		GLfloat anisoset{ 0.0f };
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &anisoset);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisoset);
	}
	// ----- end of mipmap/anisotroPIL section
	return textureRef;
}

const std::string OpenGL_Render::Get_Version()
{
	return Tanxl_ClassBase::Get_Version();
}
