//_VERSION_0_3_ UPDATE LOG
// LAST_UPDATE 2023-01-16 09:50
// 简易效率更新
// 增加纹理获取功能
// 增加不需要文件的准备着色器重载版本
// 增加不需要文件的创建着色器重载版本

#pragma once

#ifndef _TANXL_OPENGL_RENDER_
#define _TANXL_OPENGL_RENDER_

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <SOIL2\soil2.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

class OpenGL_Render
{
public:
	static std::string readShaderFile(const char* filePath);
	static void printShaderLog(GLuint shader);
	static void printProgramLog(int prog);
	static GLuint prepareShader(int shaderTYPE, const char* shaderPath);
	static GLuint prepareShader(int shaderTYPE, std::string shaderStr);
	static int finalizeShaderProgram(GLuint sprogram);
	static bool checkOpenGLError();
	static GLuint createShaderProgram(const char* vp, const char* fp);
	static GLuint createShaderProgram(std::string vp, std::string fp);
	static GLuint loadTexture(const char *texImagePath);
	const std::string Get_Version();
private:
	const std::string _Version{ "0.3" };
};

#endif
