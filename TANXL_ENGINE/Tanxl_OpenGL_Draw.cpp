#pragma once

#include "Tanxl_OpenGL_Draw.h"

OpenGL_Draw::OpenGL_Draw(int ScreenWidth, int ScreenHeight) :HeightInt(0), Position(0), StateInfor(), WidthInt(0),
_MoveX(0.0f), _MoveY(0.0f), renderingProgram(0), vao(), _ScreenWidth(ScreenWidth), _ScreenHeight(ScreenHeight) {}

void OpenGL_Draw::init(GLFWwindow* window, GameStateBase* State)
{
	//示例提供四个按键操作事件 （单例模式于其他地方定义）
	UniqueIdBase* UIB{ &UniqueIdBase::GetIdGenerator() };

	srand(static_cast<unsigned int>(time(0)));

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0f);

	HeightInt = State->Get_StateHeight();
	WidthInt = State->Get_StateWidth();
	renderingProgram = OR::createShaderProgram("vertShader.glsl", "fragShader.glsl");
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	Position = glGetUniformLocation(renderingProgram, "SHeight");
	glProgramUniform1f(renderingProgram, Position, static_cast<float>(HeightInt));
	Position = glGetUniformLocation(renderingProgram, "SWidth");
	glProgramUniform1f(renderingProgram, Position, static_cast<float>(WidthInt));

	Position = glGetUniformLocation(renderingProgram, "Margin");
	glProgramUniform1f(renderingProgram, Position, 1.0f);

	if (State->Get_Compile_Status())
	{
		for (int i = 0; i < State->Get_GameState()->size(); i++)
		{
			StateInfor[i] = State->Get_GameState()->at(i)->Get_State_Id();
		}
		StateInfor[State->Get_GameState()->size() - 1] = 0;
	}
	else
	{
		for (int i = 0; i < HeightInt * WidthInt/* + 1*/; i++)
		{
			StateInfor[i] = UIB->Random(0, 2) - 1;
		}
	}
	GLuint StatePos;
	for (int i = 0; i < HeightInt * WidthInt + 1; i++)
	{
		std::string Tag = "State[" + std::to_string(i) + "]";
		StatePos = glGetUniformLocation(renderingProgram, Tag.c_str());
		glProgramUniform1i(renderingProgram, StatePos, StateInfor[i]);
	}
}

void OpenGL_Draw::UpdateMargin(float& Margin)
{
	Position = glGetUniformLocation(renderingProgram, "Margin");
	glProgramUniform1f(renderingProgram, Position, Margin);
}

void OpenGL_Draw::display(GLFWwindow* window, double currentTime)
{
	if (Clear_Function)
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//float SinCurrent = static_cast<float>(sin(currentTime)) * 0.5f;
	//float CosCurrent = static_cast<float>(cos(currentTime)) * 0.5f;

	//PosA = glGetUniformLocation(renderingProgram, "SinCurrentTime");
	//glProgramUniform1f(renderingProgram, PosA, SinCurrent);
	//PosB = glGetUniformLocation(renderingProgram, "CosCurrentTime");
	//glProgramUniform1f(renderingProgram, PosB, CosCurrent);
	// 
	//std::cout << HeightInt * WidthInt;

	glUseProgram(renderingProgram);
	glDrawArrays(GL_TRIANGLES, 0, HeightInt * WidthInt * 6 + 6);
}

void OpenGL_Draw::mainLoop(GameStateBase* State)
{
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(_ScreenWidth, _ScreenHeight, "Tanxl_Game TEST VERSION /// 0.00.00.09", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };//获取输入事件基类
	GameStateBase* GSB{ &GameStateBase::Get_StateBase() };

	init(window, State);

	while (!glfwWindowShouldClose(window))
	{
		glClearDepth(1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		Position = glGetUniformLocation(renderingProgram, "MoveX");//更新操作物品坐标
		glProgramUniform1f(renderingProgram, Position, _MoveX);
		Position = glGetUniformLocation(renderingProgram, "MoveY");
		glProgramUniform1f(renderingProgram, Position, _MoveY);

		IEB->GetInsert(window, &_MoveX, &_MoveY);//获取输入
		
		GSB->Set_CurrentLoc(_MoveX, _MoveY);//更新地图中心点/当前移动物品坐标

		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}