//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2022-04-27 22:32
// »ù´¡°æ±¾
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

class Utils
{
private:
	static std::string readShaderFile(const char *filePath);
	static void printShaderLog(GLuint shader);
	static void printProgramLog(int prog);
	static GLuint prepareShader(int shaderTYPE, const char *shaderPath);
	static int finalizeShaderProgram(GLuint sprogram);

public:
	static bool checkOpenGLError();
	static GLuint createShaderProgram(const char *vp, const char *fp);
};