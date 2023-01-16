#pragma once

#include "Tanxl_OpenGL_Draw.h"

OpenGL_Draw::OpenGL_Draw(int ScreenWidth, int ScreenHeight) :_HeightInt(0), _Position(0), _StateInfor(),
_WidthInt(0), _renderingProgram(0), _vao(), _ScreenWidth(ScreenWidth), _ScreenHeight(ScreenHeight),
_Clear_Function(false), _Is_State_Changed(false), _PreLoads(0) {}

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
	
	State->Set_Move_State(0, _HeightInt - 1 + _PreLoads, 0, _WidthInt - 1 + _PreLoads);

	_renderingProgram = OpenGL_Render::createShaderProgram("vertShader.glsl", "fragShader.glsl");
	glGenVertexArrays(1, _vao);
	glBindVertexArray(_vao[0]);
	_Position = glGetUniformLocation(_renderingProgram, "SHeight");
	glProgramUniform1f(_renderingProgram, _Position, static_cast<float>(State->Get_StateHeight()));
	_Position = glGetUniformLocation(_renderingProgram, "SWidth");
	glProgramUniform1f(_renderingProgram, _Position, static_cast<float>(State->Get_StateWidth()));

	_Position = glGetUniformLocation(_renderingProgram, "Margin");
	glProgramUniform1f(_renderingProgram, _Position, 1.0f);

	_Position = glGetUniformLocation(_renderingProgram, "PreLoads");
	glProgramUniform1i(_renderingProgram, _Position, _PreLoads);

	ReLoadState(State, (_HeightInt + _PreLoads) / 2, (_WidthInt + _PreLoads) / 2);
}

void OpenGL_Draw::ReLoadState(GameStateBase* State, int PosX, int PosY)
{
	UniqueIdBase* UIB{ &UniqueIdBase::GetIdGenerator() };

	int Move_NX = State->Get_Move_State()._Move_NX;
	int Move_PX = State->Get_Move_State()._Move_PX;
	int Move_NY = State->Get_Move_State()._Move_NY;
	int Move_PY = State->Get_Move_State()._Move_PY;

	std::cout << "Move_NX: " << Move_NX << "Move_PX: " << Move_PX << std::endl;
	std::cout << "Move_NY: " << Move_NY << "Move_PY: " << Move_PY << std::endl;

	if (State->Get_Compile_Status())
	{
		for (int i = 0; i < (State->Get_StateHeight() + _PreLoads) * (State->Get_StateWidth() + _PreLoads); i++)
		{
			if (Move_NX < 0 || (Move_NX >= 0 && Move_NX >(State->Get_DataWidth())) || 
				Move_NY < 0 || (Move_NY >= 0 && Move_NY >(State->Get_DataHeight())))
			{
				_StateInfor[i] = 3;
			}
			else
			{
				int x = Move_NX + Move_NY * 10;
				_StateInfor[i] = State->Get_GameState()->at(x % State->Get_GameState()->size())->Get_State_Id();
			}

			Move_NX++;
			if (Move_NX > Move_PX)//抵达尽头 重新获取初值
			{
				Move_NX = State->Get_Move_State()._Move_NX;
				Move_NY++;
			}
		}
	}
	else
	{
		for (int i = 0; i < (_HeightInt + _PreLoads) * (_WidthInt + _PreLoads); i++)
		{
			_StateInfor[i] = UIB->Random(0, 2) - 1;
		}
	}
	GLuint StatePos;
	for (int i = 0; i < (State->Get_StateHeight() + _PreLoads) * (State->Get_StateWidth() + _PreLoads) + 1; i++)
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

void OpenGL_Draw::Set_PreLoad(int PreLoads)
{
	this->_PreLoads = PreLoads;
}

void OpenGL_Draw::display(GLFWwindow* window, double currentTime, GameStateBase* State)
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
	glDrawArrays(GL_TRIANGLES, 0, (State->Get_StateHeight() + _PreLoads) * (State->Get_StateWidth() + _PreLoads) * 6 + 6);
}

void OpenGL_Draw::mainLoop(GameStateBase* State)
{
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(_ScreenWidth, _ScreenHeight, "Tanxl_Game TEST VERSION /// 0.00.00.12", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };//获取输入事件基类
	GameStateBase* GSB{ &GameStateBase::Get_StateBase() };

	init(window, State);

	float MoveX = 0.0f;
	float MoveY = 0.0f;

	double Each_Half_Height = 2.0f / (State->Get_StateHeight() * 2);//10 0.2
	double Each_Half_Width = 2.0f / (State->Get_StateWidth() * 2);//10 0.2

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

		static float VX = 0.0f;
		static float VY = 0.0f;

		static int First_Adjust = 0;

		//std::cout << "FLAG ----------------------------B"<< State->Get_Adjust_Flag() << std::endl;

		IEB->GetInsert(window, &MoveX, &MoveY, &X, &Y);//获取输入

		//std::cout << "FLAG ----------------------------A" << State->Get_Adjust_Flag() << std::endl;

		if (IEB->Get_Key_Pressed())
		{
			First_Adjust = 0;
			std::cout << "TRUE -----------------------------T"<< std::endl;
			State->Set_Adjust_Flag(false);
		}
		else
			std::cout << "FALSE-----------------------------X" << std::endl;

		GSB->Set_CurrentLoc(MoveX, MoveY);//更新地图中心点/当前移动物品坐标

		//std::cout << "MXP/MYP" << (MoveX + 1.0f) << "__" << (MoveY + 1.0f) << std::endl;

		double Current_Height = (MoveY * 2 + 1) / (Each_Half_Height * 2);
		double Current_Width = (MoveX * 2 + 1) / (Each_Half_Width * 2);

		//std::cout << "CUH/CUW" << Current_Height << "__" << Current_Width << std::endl;
		
		State->Set_Adjust(0.002f);

		if (State->Get_Adjust_Flag())
		{
			State->Set_ExacHeight(Current_Height, VY, &MoveY, &Y);
			State->Set_ExacWidth(Current_Width, VX, &MoveX, &X);
			First_Adjust = 0;
		}
		else
		{
			std::cout << "Counts First_Adjust __" << First_Adjust << std::endl;

			if (First_Adjust == 300)
			{
				State->Set_Adjust_Flag(true);
			}
			else
				First_Adjust++;
		}

		static int CUH = static_cast<int>(Current_Height) / 1;
		static int CUW = static_cast<int>(Current_Width) / 1;

		int NCUH = static_cast<int>(Current_Height) / 1;
		int NCUW = static_cast<int>(Current_Width) / 1;

		std::cout << "X" << X << "__" << Y << std::endl;
		std::cout << "Y" << MoveX << "__" << MoveY << std::endl;

		if (Current_Height < 0)
			NCUH -= 1;
		if (Current_Width < 0)
			NCUW -= 1;

		if (NCUH != CUH)
		{
			if (NCUH < CUH)
			{
				if (!State->Get_Adjust_Flag())
				{
					State->Set_Move_State(MoveToNH);
					Y -= static_cast<float>(Each_Half_Width) * 2;
				}
				else
				{
					State->Set_Move_State(MoveToPH);
					Y += static_cast<float>(Each_Half_Width) * 2;
				}
			}
			else
			{
				if (!State->Get_Adjust_Flag())
				{
					State->Set_Move_State(MoveToPH);
					Y += static_cast<float>(Each_Half_Width) * 2;
				}
				else
				{
					State->Set_Move_State(MoveToNH);
					Y -= static_cast<float>(Each_Half_Width) * 2;
				}
			}
			CUH = NCUH;
			ReLoadState(State, CUH, CUW);
		}

		if (NCUW != CUW)
		{
			if (NCUW < CUW)
			{
				if (!State->Get_Adjust_Flag())
				{
					State->Set_Move_State(MoveToPW);
					X -= static_cast<float>(Each_Half_Height) * 2;
				}
				else
				{
					State->Set_Move_State(MoveToNW);
					X += static_cast<float>(Each_Half_Height) * 2;
				}
			}
			else
			{
				if (!State->Get_Adjust_Flag())
				{
					State->Set_Move_State(MoveToNW);
					X += static_cast<float>(Each_Half_Height) * 2;
				}
				else
				{
					State->Set_Move_State(MoveToPW);
					X -= static_cast<float>(Each_Half_Height) * 2;
				}
			}
			CUW = NCUW;
			ReLoadState(State, CUH, CUW);
		}

		//std::cout << "Current BLOCK : " << CUH << " " << CUW << std::endl;
		//std::cout << "Exac Location : " << MoveX * 2 << " " << MoveY * 2 << std::endl;//REAL LOCATION

		_Position = glGetUniformLocation(_renderingProgram, "StateMoveX");
		glProgramUniform1f(_renderingProgram, _Position, X);
		_Position = glGetUniformLocation(_renderingProgram, "StateMoveY");
		glProgramUniform1f(_renderingProgram, _Position, Y);

		_Position = glGetUniformLocation(_renderingProgram, "VisionMoveX");
		glProgramUniform1f(_renderingProgram, _Position, VX);
		_Position = glGetUniformLocation(_renderingProgram, "VisionMoveY");
		glProgramUniform1f(_renderingProgram, _Position, VY);

		display(window, glfwGetTime(), State);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}