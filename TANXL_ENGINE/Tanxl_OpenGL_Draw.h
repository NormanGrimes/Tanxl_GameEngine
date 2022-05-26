//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2022-04-27 22:32
// »ù´¡°æ±¾

#include "Tanxl_DataBase.h"
#include "Tanxl_GameState.h"
#ifndef TANXL_INSERTACTION_H
#define TANXL_INSERTACTION_H
#include "Tanxl_InsertAction.h"
#endif

#ifndef GL_GLEW_H
#define GL_GLEW_H
#include <GL\glew.h>
#endif

#ifndef GLFW_GLFW3_H
#define GLFW_GLFW3_H
#include <GLFW\glfw3.h>
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef STRING
#define STRING
#include <string>
#endif

#ifndef MATH_H
#define MATH_H
#include <math.h>
#endif

#ifndef UTILS_H
#define UTILS_H
#include "Utils.h"
#endif

#define numVAOs 1

GLuint PosA, PosB;
GLuint PosX, PosY;
GLuint Height, Width;
GLuint StatePos;

GLint StateInfor[100];

bool Clear_Function = false;

float movex;
float movey;

float movespeed = 0.01f;

GLuint renderingProgram;
GLuint vao[numVAOs];

int HeightInt;
int WidthInt;

void init(GLFWwindow* window, GameStateBase* State) {
	HeightInt = State->GetStateHeight();
	WidthInt = State->GetStateWidth();
	renderingProgram = Utils::createShaderProgram("StatevertShader.glsl", "StatefragShader.glsl");
	glGenVertexArrays(numVAOs, vao);
	glBindVertexArray(vao[0]);
	Height = glGetUniformLocation(renderingProgram, "SHeight");
	glProgramUniform1f(renderingProgram, Height, static_cast<float>(HeightInt));
	Width = glGetUniformLocation(renderingProgram, "SWidth");
	glProgramUniform1f(renderingProgram, Width, static_cast<float>(WidthInt));

	GLuint StatePos[100]{};
	for (int i = 0; i < HeightInt * WidthInt; i++)
	{
		std::string Tag = "State[" + std::to_string(i) + "]";
		StatePos[0] = glGetUniformLocation(renderingProgram, Tag.c_str());
		glProgramUniform1i(renderingProgram, StatePos[0], StateInfor[0]);
	}
}

void display(GLFWwindow* window, double currentTime) {

	if (Clear_Function)
	{
		glClear(GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	float SinCurrent = static_cast<float>(sin(currentTime)) * 0.5f;
	float CosCurrent = static_cast<float>(cos(currentTime)) * 0.5f;

	PosA = glGetUniformLocation(renderingProgram, "SinCurrentTime");
	glProgramUniform1f(renderingProgram, PosA, SinCurrent);
	PosB = glGetUniformLocation(renderingProgram, "CosCurrentTime");
	glProgramUniform1f(renderingProgram, PosB, CosCurrent);

	glUseProgram(renderingProgram);
	glDrawArrays(GL_TRIANGLES, 0, HeightInt * WidthInt * 6);
}

int mainLoop(GameStateBase* State)
{
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Tanxl_Game TEST VERSION /// 0.00.00.08", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	init(window, State);

	bool SpeedFlag = false;

	int i{ 0 };

	while (!glfwWindowShouldClose(window))
	{
		PosX = glGetUniformLocation(renderingProgram, "MoveX");
		glProgramUniform1f(renderingProgram, PosX, movex);
		PosY = glGetUniformLocation(renderingProgram, "MoveY");
		glProgramUniform1f(renderingProgram, PosY, movey);
		//KeyEventBase* KEB = &KeyEventBase::GetKeyEventBase(&movex, &movey, &movespeed);
		//KEB->GetKeys(window);
		/*i++;
		if (i == 6)
		{
			i = 0;
			KEB->ProcessKeys();
		}*/
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			std::cout << "LEFT_PUSHED! CurrentLOC: x_" << movex << " y_" << movey << std::endl;
			movex -= movespeed;
			if (SpeedFlag)
				SpeedFlag = false;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			std::cout << "RIGHT_PUSHED! CurrentLOC: x_" << movex << " y_" << movey << std::endl;
			movex += movespeed;
			if (SpeedFlag)
				SpeedFlag = false;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			std::cout << "DOWN_PUSHED! CurrentLOC: x_" << movex << " y_" << movey << std::endl;
			movey -= movespeed;
			if (SpeedFlag)
				SpeedFlag = false;
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			std::cout << "UP_PUSHED! CurrentLOC: x_" << movex << " y_" << movey << std::endl;
			movey += movespeed;
			if (SpeedFlag)
				SpeedFlag = false;
		}
		if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS && !SpeedFlag)
		{
			std::cout << "MoveSpeed minu_PUSHED! Speed: " << movespeed << std::endl;
			SpeedFlag = true;
			movespeed += 0.01f;
		}
		if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && !SpeedFlag)
		{
			std::cout << "MoveSpeed plus_PUSHED! Speed: " << movespeed << std::endl;
			SpeedFlag = true;
			movespeed -= 0.01f;
		}
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS && !SpeedFlag)
		{
			Clear_Function = Clear_Function == true ? false : true;
			std::cout << "GLCLEAR FUNCTION CALLED! Clear: " << Clear_Function << std::endl;
			SpeedFlag = true;

		}
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}