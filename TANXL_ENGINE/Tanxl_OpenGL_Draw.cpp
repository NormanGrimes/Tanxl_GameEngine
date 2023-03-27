#pragma once

#include "Tanxl_OpenGL_Draw.h"

OpenGL_Draw& OpenGL_Draw::GetOpenGLBase(int ScreenWidth, int ScreenHeight)
{
	static OpenGL_Draw* OGD = new OpenGL_Draw(ScreenWidth, ScreenHeight);
	return *OGD;
}

OpenGL_Draw::OpenGL_Draw(int ScreenWidth, int ScreenHeight) :_HeightInt(0), _Position(0), _StateInfor(),
_WidthInt(0), _renderingProgram(0), _vao(), _ScreenWidth(ScreenWidth), _ScreenHeight(ScreenHeight), _Main_Window(NULL),
_Clear_Function(false), _Is_State_Changed(false), _PreLoads(0), _State_MoveX(0.0f), _State_MoveY(0.0f), _First_Adjust(0),
_Adjust_While_Move(false){}

void OpenGL_Draw::init(GLFWwindow* window, GameStateBase* State)
{
	//示例提供四个按键操作事件 （单例模式于其他地方定义）
	UniqueIdBase* UIB{ &UniqueIdBase::GetIdGenerator() };
	srand(static_cast<unsigned int>(time(0)));

	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	_Main_Window = glfwCreateWindow(_ScreenWidth, _ScreenHeight, "Tanxl_Game TEST VERSION /// 0.00.00.14", NULL, NULL);
	glfwMakeContextCurrent(_Main_Window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

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

	ReLoadState(State);
}

void OpenGL_Draw::ReLoadState(GameStateBase* State)
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
			if (Move_PX < 0 || Move_NX >(State->Get_DataWidth()) || 
				Move_PY < 0 || Move_NY >(State->Get_DataHeight()))
			{
				_StateInfor[i] = 3;
			}
			else
			{
				int x = Move_NX + Move_NY * (State->Get_DataWidth() + 1);
				
				//std::cout << "Init Data: " << x % State->Get_GameState()->size() <<" __ " 
				//	<< State->Get_GameState()->at(x % State->Get_GameState()->size())->Get_State_Id() << std::endl;
				_StateInfor[i] = State->Get_StateUnit(x % State->Get_GameState()->size())->Get_State_Id();
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

void OpenGL_Draw::Set_WaitFra(int First_Adjust)
{
	this->_First_Adjust = First_Adjust;
}

void OpenGL_Draw::Set_Adjust(bool Enable)
{
	this->_Adjust_While_Move = Enable;
}

void OpenGL_Draw::display(GLFWwindow* window, double currentTime, GameStateBase* State)
{
	if (_Clear_Function)
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glUseProgram(_renderingProgram);
	glDrawArrays(GL_TRIANGLES, 0, (State->Get_StateHeight() + _PreLoads) * (State->Get_StateWidth() + _PreLoads) * 6 + 6);
}

void OpenGL_Draw::Render_Once(GameStateBase* State)
{
	static bool First_Time = true;
	if (First_Time)
	{
		First_Time = false;
		init(_Main_Window, State);
	}

	static float MoveX = 0.0f;
	static float MoveY = 0.0f;

	static double Each_Half_Height = 2.0f / (State->Get_StateHeight() * 2);//10 0.2
	static double Each_Half_Width = 2.0f / (State->Get_StateWidth() * 2);//10 0.2

	InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };//获取输入事件基类
	GameStateBase* GSB{ &GameStateBase::Get_StateBase() };

	if (!glfwWindowShouldClose(_Main_Window))
	{
		glClearDepth(1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		_Position = glGetUniformLocation(_renderingProgram, "MoveX");//更新操作物品坐标
		glProgramUniform1f(_renderingProgram, _Position, MoveX);
		_Position = glGetUniformLocation(_renderingProgram, "MoveY");
		glProgramUniform1f(_renderingProgram, _Position, MoveY);

		static float DeptVX = ((float)State->Get_StateWidth()) / 2;
		static float DeptVY = ((float)State->Get_StateHeight()) / 2;

		static float MDeptVX = ((float)State->Get_StateWidth()) / 2;
		static float MDeptVY = ((float)State->Get_StateHeight()) / 2;

		static int CUH = MDeptVY / (Each_Half_Height * 2);
		static int CUW = MDeptVX / (Each_Half_Width * 2);

		int NCUH = MDeptVY / (Each_Half_Height * 2);
		int NCUW = MDeptVX / (Each_Half_Width * 2);

		static int ACUH = DeptVY / (Each_Half_Height * 2);
		static int ACUW = DeptVX / (Each_Half_Width * 2);

		static int ANCUH = DeptVY / (Each_Half_Height * 2);
		static int ANCUW = DeptVX / (Each_Half_Width * 2);

		if (State->Get_Adjust_Flag())
		{
			ANCUH = DeptVY / (Each_Half_Height * 2);
			ANCUW = DeptVX / (Each_Half_Width * 2);
		}

		static int Wait_Frame = 0;

		//std::cout << "FLAG ----------------------------B"<< State->Get_Adjust_Flag() << std::endl;

		IEB->GetInsert(_Main_Window, &MoveX, &MoveY, &_State_MoveX, &_State_MoveY, &MDeptVX, &MDeptVY);//获取输入

		//std::cout << "DEPT -----------------------------" << MDeptVX << "____" << MDeptVY << std::endl;
		//std::cout << "REAL -----------------------------" << MoveX << "____" << MoveY << std::endl;
		//std::cout << "FLAG ----------------------------A" << State->Get_Adjust_Flag() << std::endl;

		if (!_Adjust_While_Move)
		{
			if (IEB->Get_Key_Pressed())
				State->Set_Adjust_Flag(false);
			else
				State->Set_Adjust_Flag(true);
		}

		GSB->Set_CurrentLoc(MoveX, MoveY);//更新地图中心点/当前移动物品坐标

		//std::cout << "MXP/MYP" << (MoveX/* + 1.0f*/) << "__" << (MoveY/* + 1.0f*/) << std::endl;

		double Current_Height = (MoveY * 2 + 1) / (Each_Half_Height * 2);
		double Current_Width = (MoveX * 2 + 1) / (Each_Half_Width * 2);

		//std::cout << "CUH/CUW" << Current_Height << "__" << Current_Width << std::endl;

		if (State->Get_Adjust_Flag())
		{
			State->Set_ExacHeight(Current_Height, &MoveY, &_State_MoveY, &DeptVY);
			State->Set_ExacWidth(Current_Width, &MoveX, &_State_MoveX, &DeptVX);
			Wait_Frame = 0;
			
			int Diff_Cnt = 0;

			if (ANCUH != ACUH)
			{
				if (ANCUH < ACUH)
				{
					State->Set_Move_State(MoveToPH);
					_State_MoveY += static_cast<float>(Each_Half_Height) * 2;
				}
				else if (ANCUH > ACUH)
				{
					State->Set_Move_State(MoveToNH);
					_State_MoveY -= static_cast<float>(Each_Half_Height) * 2;
				}
				Diff_Cnt++;
				std::cout << "ANCUH __ " << ANCUH << "ACUH __ " << ACUH << std::endl;
				ACUH = ANCUH;
				std::cout << "ANCUH != ACUH State->Get_Adjust_Flag() RELOAD" << std::endl;
			}

			if (ANCUW != ACUW)
			{
				if (ANCUW < ACUW)
				{
					State->Set_Move_State(MoveToNW);
					_State_MoveX += static_cast<float>(Each_Half_Width) * 2;
				}
				else if (ANCUW > ACUW)
				{
					State->Set_Move_State(MoveToPW);
					_State_MoveX -= static_cast<float>(Each_Half_Width) * 2;
				}
				Diff_Cnt++;
				std::cout << "ANCUW __ " << ANCUW << "CUW __ " << ACUW << std::endl;
				ACUW = ANCUW;
				std::cout << "ANCUW != ACUW State->Get_Adjust_Flag() RELOAD" << std::endl;
			}

			if (Diff_Cnt != 0)
				ReLoadState(State);
		}
		else
		{
			//std::cout << "Counts First_Adjust __" << First_Adjust << std::endl;
			if (Wait_Frame == _First_Adjust)
			{
				State->Set_Adjust_Flag(true);
			}
			else
				Wait_Frame++;

			int Diff_Cnt = 0;

			if (NCUH != CUH)
			{
				if (NCUH > CUH)
				{
					//std::cout << "Adjust_Flag() __N---" << State->Get_Adjust_Flag() << std::endl;
					State->Set_Move_State(MoveToNH);
					_State_MoveY -= static_cast<float>(Each_Half_Height) * 2;
				}
				else if (NCUH < CUH)
				{
					//std::cout << "Adjust_Flag() __P___" << State->Get_Adjust_Flag() << std::endl;
					State->Set_Move_State(MoveToPH);
					_State_MoveY += static_cast<float>(Each_Half_Height) * 2;
				}
				Diff_Cnt++;
				std::cout << "NCUH __ " << NCUH << "CUH __ " << CUH << std::endl;
				CUH = NCUH;
				std::cout << "NCUH != CUH !State->Get_Adjust_Flag() RELOAD" << std::endl;
			}

			if (NCUW != CUW)
			{
				if (NCUW > CUW)
				{
					//std::cout << "Adjust_Flag() __P---" << State->Get_Adjust_Flag() << std::endl;
					State->Set_Move_State(MoveToPW);
					_State_MoveX -= static_cast<float>(Each_Half_Width) * 2;
				}
				else if (NCUW < CUW)
				{
					//std::cout << "Adjust_Flag() __N---" << State->Get_Adjust_Flag() << std::endl;
					State->Set_Move_State(MoveToNW);
					_State_MoveX += static_cast<float>(Each_Half_Width) * 2;
				}
				Diff_Cnt++;
				std::cout << "NCUW __ " << NCUW << "CUW __ " << CUW << std::endl;
				CUW = NCUW;
				std::cout << "NCUW != CUW !State->Get_Adjust_Flag() RELOAD" << std::endl;
			}
			if (Diff_Cnt != 0)
				ReLoadState(State);
		}



		//std::cout << "DeptVX / DeptVY" << DeptVX << "__" << DeptVY << std::endl;
		//std::cout << "MDeptVX / MDeptVY" << MDeptVX << "__" << MDeptVY << std::endl;

		//std::cout << "Current BLOCK : " << CUH << " " << CUW << std::endl;
		//std::cout << "Exac Location : " << MoveX * 2 << " " << MoveY * 2 << std::endl;//REAL LOCATION

		_Position = glGetUniformLocation(_renderingProgram, "StateMoveX");
		glProgramUniform1f(_renderingProgram, _Position, _State_MoveX);
		_Position = glGetUniformLocation(_renderingProgram, "StateMoveY");
		glProgramUniform1f(_renderingProgram, _Position, _State_MoveY);

		display(_Main_Window, glfwGetTime(), State);
		glfwSwapBuffers(_Main_Window);
		glfwPollEvents();
	}
	else
	{
		glfwDestroyWindow(_Main_Window);
		glfwTerminate();
		exit(EXIT_SUCCESS);
	}
}