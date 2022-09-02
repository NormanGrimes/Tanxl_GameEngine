#pragma once

#include "Tanxl_OpenGL_Draw.h"

OpenGL_Draw::OpenGL_Draw(int ScreenWidth, int ScreenHeight) :_HeightInt(0), _Position(0), _StateInfor(), _WidthInt(0),
_MoveX(0.0f), _MoveY(0.0f), _renderingProgram(0), _vao(), _ScreenWidth(ScreenWidth), _ScreenHeight(ScreenHeight) {}

void OpenGL_Draw::init(GLFWwindow* window, GameStateBase* State)
{
	//示例提供四个按键操作事件 （单例模式于其他地方定义）
	UniqueIdBase* UIB{ &UniqueIdBase::GetIdGenerator() };

	srand(static_cast<unsigned int>(time(0)));

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0f);

	_HeightInt = State->Get_StateHeight();
	_WidthInt = State->Get_StateWidth();
	_renderingProgram = OR::createShaderProgram("vertShader.glsl", "fragShader.glsl");
	glGenVertexArrays(1, _vao);
	glBindVertexArray(_vao[0]);
	_Position = glGetUniformLocation(_renderingProgram, "SHeight");
	glProgramUniform1f(_renderingProgram, _Position, static_cast<float>(_HeightInt));
	_Position = glGetUniformLocation(_renderingProgram, "SWidth");
	glProgramUniform1f(_renderingProgram, _Position, static_cast<float>(_WidthInt));

	_Position = glGetUniformLocation(_renderingProgram, "Margin");
	glProgramUniform1f(_renderingProgram, _Position, 1.0f);

	if (State->Get_Compile_Status())
	{
		for (int i = 0; i < State->Get_GameState()->size(); i++)
		{
			_StateInfor[i] = State->Get_GameState()->at(i)->Get_State_Id();
		}
		_StateInfor[State->Get_GameState()->size() - 1] = 0;
	}
	else
	{
		for (int i = 0; i < _HeightInt * _WidthInt/* + 1*/; i++)
		{
			_StateInfor[i] = UIB->Random(0, 2) - 1;
		}
	}
	GLuint StatePos;
	for (int i = 0; i < _HeightInt * _WidthInt + 1; i++)
	{
		std::string Tag = "State[" + std::to_string(i) + "]";
		StatePos = glGetUniformLocation(_renderingProgram, Tag.c_str());
		glProgramUniform1i(_renderingProgram, StatePos, _StateInfor[i]);
	}
}

void OpenGL_Draw::UpdateMargin(float& Margin)
{
	_Position = glGetUniformLocation(_renderingProgram, "Margin");
	glProgramUniform1f(_renderingProgram, _Position, Margin);
}

void OpenGL_Draw::display(GLFWwindow* window, double currentTime)
{
	if (_Clear_Function)
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//float SinCurrent = static_cast<float>(sin(currentTime)) * 0.5f;
	//float CosCurrent = static_cast<float>(cos(currentTime)) * 0.5f;

	//PosA = glGetUniformLocation(renderingProgram, "SinCurrentTime");
	//glProgramUniform1f(renderingProgram, PosA, SinCurrent);
	//PosB = glGetUniformLocation(renderingProgram, "CosCurrentTime");
	//glProgramUniform1f(renderingProgram, PosB, CosCurrent);
	// 
	//std::cout << HeightInt * WidthInt;

	glUseProgram(_renderingProgram);
	glDrawArrays(GL_TRIANGLES, 0, _HeightInt * _WidthInt * 6 + 6);
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

		_Position = glGetUniformLocation(_renderingProgram, "MoveX");//更新操作物品坐标
		glProgramUniform1f(_renderingProgram, _Position, _MoveX);
		_Position = glGetUniformLocation(_renderingProgram, "MoveY");
		glProgramUniform1f(_renderingProgram, _Position, _MoveY);

		static float X = 0.0f;
		static float Y = 0.0f;

		static float MX = 0.0f;
		static float MY = 0.0f;

		IEB->GetInsert(window, &_MoveX, &_MoveY);//获取输入

		GSB->Set_CurrentLoc(_MoveX, _MoveY);//更新地图中心点/当前移动物品坐标

		X = _MoveX + MX;
		Y = _MoveY +  MY;

		std::cout << X << "_1_" << Y << "_" << _MoveX << "_" << _MoveY << "   ";

		if (X < 0.0f)
		{
			X += 0.01f;
			MX -= 0.01f;
		}
		else if (X > 0.0f)
		{
			X -= 0.01f;
			MX += 0.01f;
		}

		if (Y < 0.0f)
		{
			Y += 0.01f;
			MY -= 0.01f;
		}
		else if (Y > 0.0f)
		{
			Y -= 0.01f;
			MY += 0.01f;
		}
		std::cout << X << "_2_" << Y << "_" << _MoveX << "_" << _MoveY << "   ";

		_Position = glGetUniformLocation(_renderingProgram, "StateMoveX");
		glProgramUniform1f(_renderingProgram, _Position, X);
		_Position = glGetUniformLocation(_renderingProgram, "StateMoveY");
		glProgramUniform1f(_renderingProgram, _Position, Y);

		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}