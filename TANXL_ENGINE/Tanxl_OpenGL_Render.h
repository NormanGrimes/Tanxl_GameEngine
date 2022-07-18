//_VERSION_0_2_ UPDATE LOG
// LAST_UPDATE 2022-05-15 22:37
// 更名为OpenGL_Render
// 移除类的设计改为 仅函数调用
// 移除std的using语句

#ifndef GL_GLEW_H
#define GL_GLEW_H
#include <GL\glew.h>
#endif

#ifndef GLFW_GLFW3_H
#define GLFW_GLFW3_H
#include <GLFW\glfw3.h>
#endif

#ifndef SOIL2_SOIL2_H
#define SOIL2_SOIL2_H
#include <SOIL2\soil2.h>
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef FSTREAM
#define FSTREAM
#include <fstream>
#endif

#ifndef CMATH
#define CMATH
#include <cmath>
#endif

#ifndef VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef GLM_GLM_HPP
#define GLM_GLM_HPP
#include <glm\glm.hpp>
#endif

#ifndef GLM_GTC_TYPE_PTR_HPP
#define GLM_GTC_TYPE_PTR_HPP
#include <glm\gtc\type_ptr.hpp>
#endif

#ifndef GLM_GTC_MARTIX_TRANSFORM_HPP
#define GLM_GTC_MARTIX_TRANSFORM_HPP
#include <glm\gtc\matrix_transform.hpp>
#endif

std::string readShaderFile(const char* filePath);
void printShaderLog(GLuint shader);
void printProgramLog(int prog);
GLuint prepareShader(int shaderTYPE, const char* shaderPath);
int finalizeShaderProgram(GLuint sprogram);
bool checkOpenGLError();
GLuint createShaderProgram(const char* vp, const char* fp);


std::string readShaderFile(const char* filePath) {
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);
	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

bool checkOpenGLError() {
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		std::cout << "glError: " << glErr << std::endl;
		foundError = true;
		glErr = glGetError();
	}
	return foundError;
}

void printShaderLog(GLuint shader) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		std::cout << "Shader Info Log: " << log << std::endl;
		free(log);
	}
}

GLuint prepareShader(int shaderTYPE, const char* shaderPath)
{
	GLint shaderCompiled;
	std::string shaderStr = readShaderFile(shaderPath);
	const char* shaderSrc = shaderStr.c_str();
	GLuint shaderRef = glCreateShader(shaderTYPE);
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

void printProgramLog(int prog) {
	int len = 0;
	int chWrittn = 0;
	char* log;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char*)malloc(len);
		glGetProgramInfoLog(prog, len, &chWrittn, log);
		std::cout << "Program Info Log: " << log << std::endl;
		free(log);
	}
}

int finalizeShaderProgram(GLuint sprogram)
{
	GLint linked;
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

GLuint createShaderProgram(const char* vp, const char* fp) {
	GLuint vShader = prepareShader(GL_VERTEX_SHADER, vp);
	GLuint fShader = prepareShader(GL_FRAGMENT_SHADER, fp);
	GLuint vfprogram = glCreateProgram();
	glAttachShader(vfprogram, vShader);
	glAttachShader(vfprogram, fShader);
	finalizeShaderProgram(vfprogram);
	return vfprogram;
}
