#pragma once

#include "Tanxl_OpenGL_Draw.h"

OpenGL_Draw::OpenGL_Draw() :HeightInt(0), PosA(0), PosB(0), PosX(0), PosY(0), StateInfor(), WidthInt(0),
movex(0), movey(0), renderingProgram(0), vao() {}

void OpenGL_Draw::init(GLFWwindow* window, GameStateBase* State)
{
	//示例提供四个按键操作事件 （单例模式于其他地方定义）
	UniqueIdBase* UIB = &UniqueIdBase::GetIdGenerator();

	srand(static_cast<unsigned int>(time(0)));

	for (int i = 0; i < 101; i++)
		StateInfor[i] = UIB->Random(0, 2) - 1;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0f);

	HeightInt = State->GetStateHeight();
	WidthInt = State->GetStateWidth();
	renderingProgram = OR::createShaderProgram("vertShader.glsl", "fragShader.glsl");
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	PosA = glGetUniformLocation(renderingProgram, "SHeight");
	glProgramUniform1f(renderingProgram, PosA, static_cast<float>(HeightInt));
	PosB = glGetUniformLocation(renderingProgram, "SWidth");
	glProgramUniform1f(renderingProgram, PosB, static_cast<float>(WidthInt));
	for (int i = 0; i < HeightInt * WidthInt + 1; i++)
	{
		StateInfor[i];
	}
	GLuint StatePos[101]{};
	for (int i = 0; i < HeightInt * WidthInt + 1; i++)
	{
		std::string Tag = "State[" + std::to_string(i) + "]";
		StatePos[i] = glGetUniformLocation(renderingProgram, Tag.c_str());
		glProgramUniform1i(renderingProgram, StatePos[i], StateInfor[i]);
	}
}

void OpenGL_Draw::display(GLFWwindow* window, double currentTime)
{
	if (Clear_Function)
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	float SinCurrent = static_cast<float>(sin(currentTime)) * 0.5f;
	float CosCurrent = static_cast<float>(cos(currentTime)) * 0.5f;

	PosA = glGetUniformLocation(renderingProgram, "SinCurrentTime");
	glProgramUniform1f(renderingProgram, PosA, SinCurrent);
	PosB = glGetUniformLocation(renderingProgram, "CosCurrentTime");
	glProgramUniform1f(renderingProgram, PosB, CosCurrent);

	glUseProgram(renderingProgram);
	glDrawArrays(GL_TRIANGLES, 0, HeightInt * WidthInt * 6 + 6);
}

void OpenGL_Draw::mainLoop(GameStateBase* State)
{
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "Tanxl_Game TEST VERSION /// 0.00.00.09", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };//获取输入事件基类

	init(window, State);

	while (!glfwWindowShouldClose(window))
	{
		glClearDepth(1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		PosX = glGetUniformLocation(renderingProgram, "MoveX");//更新操作物品坐标
		glProgramUniform1f(renderingProgram, PosX, movex);
		PosY = glGetUniformLocation(renderingProgram, "MoveY");
		glProgramUniform1f(renderingProgram, PosY, movey);

		IEB->GetInsert(window, &movex, &movey);

		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}