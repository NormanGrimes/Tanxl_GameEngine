//_VERSION_0_2_ UPDATE LOG
// LAST_UPDATE 2022-05-15 22:37
// 更名为OpenGL_Render
// 移除std的using语句
// 重新修订重复包含检查

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
	static int finalizeShaderProgram(GLuint sprogram);
	static bool checkOpenGLError();
	static GLuint createShaderProgram(const char* vp, const char* fp);
};

#endif
