#pragma once

#include "Tanxl_OpenGL_Draw.h"

OpenGL_Draw::OpenGL_Draw(int ScreenWidth, int ScreenHeight) :_HeightInt(0), _Position(0), _StateInfor(),
_WidthInt(0), _renderingProgram(0), _vao(), _ScreenWidth(ScreenWidth), _ScreenHeight(ScreenHeight),
_Clear_Function(false), _Is_State_Changed(false) {}

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

	ReLoadState(State, _HeightInt / 2, _WidthInt / 2);
}

void OpenGL_Draw::ReLoadState(GameStateBase* State, int PosX, int PosY)
{
	UniqueIdBase* UIB{ &UniqueIdBase::GetIdGenerator() };

	static int Last_PosX = PosX;
	static int Last_PosY = PosY;

	if (State->Get_Compile_Status())
	{
		for (int i = 0; i < _HeightInt * _WidthInt; i += 4)
		{
			_StateInfor[i] = State->Get_GameState()->at((PosX * _HeightInt + PosY - 2)% State->Get_GameState()->size())->Get_State_Id();
			_StateInfor[i + 1] = State->Get_GameState()->at((PosX * _HeightInt + PosY - 1) % State->Get_GameState()->size())->Get_State_Id();
			_StateInfor[i + 2] = State->Get_GameState()->at((PosX * _HeightInt + PosY) % State->Get_GameState()->size())->Get_State_Id();
			_StateInfor[i + 3] = State->Get_GameState()->at((PosX * _HeightInt + PosY + 1) % State->Get_GameState()->size())->Get_State_Id();
			_StateInfor[i + 4] = State->Get_GameState()->at((PosX * _HeightInt + PosY + 2) % State->Get_GameState()->size())->Get_State_Id();
		}
	}
	else
	{
		for (int i = 0; i < _HeightInt * _WidthInt; i++)
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

	Last_PosX = PosX;
	Last_PosY = PosY;
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
	GLFWwindow* window = glfwCreateWindow(_ScreenWidth, _ScreenHeight, "Tanxl_Game TEST VERSION /// 0.00.00.10", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };//获取输入事件基类
	GameStateBase* GSB{ &GameStateBase::Get_StateBase() };

	init(window, State);

	float MoveX = 0.0f;
	float MoveY = 0.0f;

	double Each_Half_Height = 2.0f / (_HeightInt * 2);//10 0.2
	double Each_Half_Width = 2.0f / (_WidthInt * 2);//10 0.2

	while (!glfwWindowShouldClose(window))
	{
		glClearDepth(1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		_Position = glGetUniformLocation(_renderingProgram, "MoveX");//更新操作物品坐标
		glProgramUniform1f(_renderingProgram, _Position, MoveX);
		_Position = glGetUniformLocation(_renderingProgram, "MoveY");
		glProgramUniform1f(_renderingProgram, _Position, MoveY);

		static float X = 0.0f;
		static float Y = 0.0f;

		IEB->GetInsert(window, &MoveX, &MoveY, &X, &Y);//获取输入

		GSB->Set_CurrentLoc(MoveX, MoveY);//更新地图中心点/当前移动物品坐标

		std::cout << "MXP/MYP" << (MoveX + 1.0f) << "__" << (MoveY + 1.0f) << std::endl;

		double Current_Height = (MoveY + 1.0f) / (Each_Half_Height * 2);
		double Current_Width = (MoveX + 1.0f) / (Each_Half_Width * 2);

		int CUH = static_cast<int>(Current_Height) / 1;
		int CUW = static_cast<int>(Current_Width) / 1;

		std::cout << "Current BLOCK : " << CUH << " " << CUW <<std::endl;

		_Position = glGetUniformLocation(_renderingProgram, "StateMoveX");
		glProgramUniform1f(_renderingProgram, _Position, X);
		_Position = glGetUniformLocation(_renderingProgram, "StateMoveY");
		glProgramUniform1f(_renderingProgram, _Position, Y);

		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();

		ReLoadState(State, CUH, CUW);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}