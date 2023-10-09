#pragma once

#include "Tanxl_OpenGL_Draw.h"

OpenGL_Draw& OpenGL_Draw::GetOpenGLBase(int ScreenWidth, int ScreenHeight)
{
	static OpenGL_Draw* OGD{ new OpenGL_Draw(ScreenWidth, ScreenHeight) };
	return *OGD;
}

OpenGL_Draw::OpenGL_Draw(int ScreenWidth, int ScreenHeight) :_HeightInt(0), _StateInfor(), _WidthInt(0),
_renderingProgram(0), _vao(), _vbo(), _Texture(), _ScreenWidth(ScreenWidth), _ScreenHeight(ScreenHeight), _Main_Window(nullptr),
_Clear_Function(true), _Is_State_Changed(false), _PreLoads(0), _State_MoveX(0.0f), _State_MoveY(0.0f), _First_Adjust(0) {}

const std::string OpenGL_Draw::Get_Version()
{
	return this->_Version;
}

void OpenGL_Draw::init(GLFWwindow* window, GameStateBase* State)
{
	//示例提供四个按键操作事件 （单例模式于其他地方定义）
	RandomBase* UIB{ &RandomBase::GetRandomBase() };

	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	_Main_Window = glfwCreateWindow(_ScreenWidth, _ScreenHeight, "Tanxl_Game TEST VERSION /// 0.00.00.16", NULL, NULL);
	glfwMakeContextCurrent(_Main_Window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0f);

	this->_HeightInt = State->Get_StateHeight();
	this->_WidthInt = State->Get_StateWidth();

	this->_Auto_AdjustX = 0.0f;
	this->_Auto_AdjustY = 0.0f;

	this->_Move_AdjustX = 0.0f;
	this->_Move_AdjustY = 0.0f;

	this->_Each_Height = 2.0f / State->Get_StateHeight();//10 0.2
	this->_Each_Width = 2.0f / State->Get_StateWidth();//10 0.2

	this->_Current_Move_Height = 0;
	this->_Current_Move_Width = 0;
	
	State->Set_Move_State(0, this->_WidthInt - 1 + this->_PreLoads, 0, this->_HeightInt - 1 + this->_PreLoads);

	this->_renderingProgram = OpenGL_Render::createShaderProgram("vertShader.glsl", "fragShader.glsl");

	glGenVertexArrays(1, _vao);
	glBindVertexArray(_vao[0]);
	glGenBuffers(1, _vbo);

	glProgramUniform1i(this->_renderingProgram, 4, this->_HeightInt);//SHeight
	glProgramUniform1i(this->_renderingProgram, 5, this->_WidthInt);//SWidth
	glProgramUniform1i(this->_renderingProgram, 8, this->_PreLoads);//PreLoads

	Append_Texture(TanxlOD::TexGrass_01_200X200);       //1
	Append_Texture(TanxlOD::TexGrass_02_200X200);       //2
	Append_Texture(TanxlOD::TexGrass_Snowy_01_200X200); //3
	Append_Texture(TanxlOD::TexGrass_Snowy_02_200X200); //4
	Append_Texture(TanxlOD::TexOcean_01_200X200); //5
	Append_Texture(TanxlOD::TexForestDDPAT_01_200X200);  //6

	glDrawArrays(GL_TRIANGLES, 0, (State->Get_StateHeight() + _PreLoads)* (State->Get_StateWidth() + _PreLoads) * 6 + 6);

	Set_Trigger_Range(true, 0.6f, 0.6f);

	int Min{ State->Get_StateHeight() > State->Get_StateWidth() ? State->Get_StateWidth() : State->Get_StateHeight() };
	State->Get_Move_Distance()._LocX = 2.0f / Min * (Min - 1);//ORIGIN ((2.0f / Min) * 2) * ((Min - 1) / 2.0f)
	State->Get_Move_Distance()._LocY = -(2.0f / Min * (Min - 1));

	ReLoadState(State);
}

void OpenGL_Draw::ReLoadState(GameStateBase* State)
{
	RandomBase* UIB{ &RandomBase::GetRandomBase() };

	int Move_NX{ State->Get_Move_State()._Move_NX };
	int Move_PX{ State->Get_Move_State()._Move_PX };
	int Move_NY{ State->Get_Move_State()._Move_NY };
	int Move_PY{ State->Get_Move_State()._Move_PY };

	std::cout << "Move_NX: " << Move_NX << "Move_PX: " << Move_PX << std::endl;
	std::cout << "Move_NY: " << Move_NY << "Move_PY: " << Move_PY << std::endl;

	if (State->Get_Compile_Status())
	{
		for (int i{ 0 }; i < (State->Get_StateHeight() + _PreLoads) * (State->Get_StateWidth() + _PreLoads); ++i)
		{
			if ((Move_PX < 0) || (static_cast<unsigned>(Move_NX) > State->Get_DataWidth()) || //现阶段Data宽度不可能导致转换溢出
				(Move_PY < 0) || (static_cast<unsigned>(Move_NY) > State->Get_DataHeight()))
			{
				_StateInfor[i] = 3;
			}
			else
			{
				int x = Move_NX + Move_NY * (State->Get_DataWidth() + 1);
				if (State->Get_GameState()->size() == 0)
					return;

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
		for (int i{ 0 }; i < (_HeightInt + _PreLoads) * (_WidthInt + _PreLoads); ++i)
		{
			_StateInfor[i] = UIB->Random(0, 3);
			std::cout << _StateInfor[i];
		}
	}
	GLuint StatePos;
	for (int i{ 0 }; i < (State->Get_StateHeight() + _PreLoads) * (State->Get_StateWidth() + _PreLoads) + 1; ++i)
	{
		std::string Tag{ "State[" + std::to_string(i) + "]" };
		StatePos = glGetUniformLocation(_renderingProgram, Tag.c_str());
		glProgramUniform1i(_renderingProgram, StatePos, _StateInfor[i]);
	}
}

GLFWwindow* OpenGL_Draw::Get_Window()const
{
	return this->_Main_Window;
}

void OpenGL_Draw::Set_PreLoad(int PreLoads)
{
	this->_PreLoads = PreLoads;
}

void OpenGL_Draw::Set_WaitFra(int First_Adjust)
{
	this->_First_Adjust = First_Adjust;
}

void OpenGL_Draw::Set_Clear(bool Clear)
{
	this->_Clear_Function = Clear;
}

void OpenGL_Draw::Set_Trigger_Mode(bool Mode)
{
	this->_Trigger_Mode = Mode;
}

void OpenGL_Draw::Set_Trigger_Range(bool Enable, float Height, float Width)
{
	this->_Is_Trigger_Enable = Enable;
	this->_Trigger_Height = Height;
	this->_Trigger_Width = Width;
}

void OpenGL_Draw::Append_Texture(const char* Texture)
{
	static int Id{ 0 };

	_Texture.push_back(OpenGL_Render::loadTexture(Texture));

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[Id]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TanxlOD::textureCoordinates), TanxlOD::textureCoordinates, GL_STATIC_DRAW);

	glActiveTexture(GL_TEXTURE0 + Id);

	glBindTexture(GL_TEXTURE_2D, _Texture.at(Id));
	Id++;
}

int OpenGL_Draw::Get_PreLoad()
{
	return this->_PreLoads;
}

EMove_State_EventId OpenGL_Draw::Auto_Update_Trigger(float Height, float Width)
{
	if (_Is_Trigger_Enable)
	{
		EMove_State_EventId Value{ MoveToNO };
		if ((Height > 0) && (Height > _Trigger_Height))
			Value = MoveToPH;
		if ((Height < 0) && (_Trigger_Height + Height < 0))
			Value = MoveToNH;
		if ((Width > 0) && (Width > _Trigger_Width))
		{
			if (Value == MoveToPH)
				Value = MoveToPWPH;
			else if(Value == MoveToNH)
				Value = MoveToPWNH;
			else
				Value = MoveToPW;
		}
		if ((Width < 0) && (_Trigger_Width + Width < 0))
		{
			if (Value == MoveToPH)
				Value = MoveToNWPH;
			else if (Value == MoveToNH)
				Value = MoveToNWNH;
			else
				Value = MoveToNW;
		}
		return Value;
	}
	return MoveToNO;
}

EMove_State_EventId OpenGL_Draw::Auto_Update_Trigger(short Edge)
{
	return static_cast<EMove_State_EventId>(Edge);
}

void OpenGL_Draw::display(GLFWwindow* window, double currentTime, GameStateBase* State)
{
	if (_Clear_Function)
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		this->_Clear_Function = false;
	}

	glUseProgram(_renderingProgram);
	glDrawArrays(GL_TRIANGLES, 0, (State->Get_StateHeight() + _PreLoads) * (State->Get_StateWidth() + _PreLoads) * 6 + 6);
}

void OpenGL_Draw::Render_Once(GameStateBase* State)
{
	static bool First_Time{ true };

	float Temp_MoveX{ 0.0f };
	float Temp_MoveY{ 0.0f };

	if (First_Time)
	{
		First_Time = false;
		init(_Main_Window, State);
	}

	InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };//获取输入事件基类
	GameStateBase* GSB{ &GameStateBase::Get_StateBase() };

	if (!glfwWindowShouldClose(_Main_Window))
	{
		glClearDepth(1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		int NCUH{ static_cast<int>(_Move_AdjustY / _Each_Height) };
		int NCUW{ static_cast<int>(_Move_AdjustX / _Each_Width) };

		static int ACUH{ static_cast<int>(_Auto_AdjustY / _Each_Height) };
		static int ACUW{ static_cast<int>(_Auto_AdjustX / _Each_Width) };

		static int ANCUH{ static_cast<int>(_Auto_AdjustY / _Each_Height) };
		static int ANCUW{ static_cast<int>(_Auto_AdjustX / _Each_Width) };

		int TOCUH{ static_cast<int>((static_cast<double>(_Move_AdjustY) * 2) / _Each_Height) };
		int TOCUW{ static_cast<int>((static_cast<double>(_Move_AdjustX) * 2) / _Each_Width) };

		if (State->Get_Adjust_Flag())
		{
			ANCUH = static_cast<int>(_Auto_AdjustY / _Each_Height);
			ANCUW = static_cast<int>(_Auto_AdjustX / _Each_Width);
		}

		static int Wait_Frame{ 0 };
		bool Press_Flg{ false };

		//std::cout << "FLAG ----------------------------B"<< State->Get_Adjust_Flag() << std::endl;
		float Res_SCDX = State->Get_Screen_Distance()._LocX;
		float Res_SCDY = State->Get_Screen_Distance()._LocY;
		float Res_SMDX = State->Get_Move_Distance()._LocX;
		float Res_SMDY = State->Get_Move_Distance()._LocY;

		IEB->GetInsert(_Main_Window, State);//获取输入

		//std::cout << "DEPT -----------------------------" << MDeptVX << "____" << MDeptVY << std::endl;
		//std::cout << "REAL -----------------------------" << MoveX << "____" << MoveY << std::endl;
		//std::cout << "FLAG ----------------------------A" << State->Get_Adjust_Flag() << std::endl;

		State->Update_Move(0.0f, 0.0f, CHECK_EDGE_LA);
		int Current_LX = State->Get_LocationX();
		int Current_AY = State->Get_LocationY();
		//State->Update_Move(0.0f, 0.0f, CHECK_EDGE_RB);
		//int Current_RX = State->Get_LocationX();
		//int Current_BY = State->Get_LocationY();

		if (IEB->Get_Margin_X() < 0)
		{
			State->Update_Move(IEB->Get_Margin_X(), IEB->Get_Margin_Y(), CHECK_EDGE_LA);
			//State->Update_Move(IEB->Get_Margin_X(), IEB->Get_Margin_Y(), CHECK_EDGE_LB);
			if (Current_LX != State->Get_LocationX())
			{
				if (State->Get_LocationX() > 0 && State->Get_LocationY() > 0 && 
					State->Get_LocationX() < static_cast<int>(State->Get_DataWidth()) && State->Get_LocationY() < static_cast<int>(State->Get_DataHeight()) &&
					(State->Get_LocationX() <= static_cast<int>(State->Get_DataWidth() + 1)) && (State->Get_LocationY() <= static_cast<int>(State->Get_DataHeight() + 1)))
				{
					std::cout << "STATUS A :" << State->Get_StateUnit(State->Get_LocationY() * State->Get_DataWidth() + State->Get_LocationX())->Get_State_Id() << std::endl;
					if (State->Get_StateUnit(State->Get_LocationY() * (State->Get_DataWidth() + 1) + State->Get_LocationX())->Get_State_Id() == 3)
					{
						State->Get_Screen_Distance()._LocX = Res_SCDX;
						State->Get_Screen_Distance()._LocY = Res_SCDY;
						State->Get_Move_Distance()._LocX = Res_SMDX;
						State->Get_Move_Distance()._LocY = Res_SMDY;
					}
				}
				else
				{
					State->Get_Screen_Distance()._LocX = Res_SCDX;
					State->Get_Screen_Distance()._LocY = Res_SCDY;
					State->Get_Move_Distance()._LocX = Res_SMDX;
					State->Get_Move_Distance()._LocY = Res_SMDY;
				}
			}
		}
		else if (IEB->Get_Margin_X() > 0)
		{
			State->Update_Move(IEB->Get_Margin_X(), IEB->Get_Margin_Y(), CHECK_EDGE_LA);
			//State->Update_Move(IEB->Get_Margin_X(), IEB->Get_Margin_Y(), CHECK_EDGE_RB);
			if (Current_LX != State->Get_LocationX())
			{
				if (State->Get_LocationX() > 0 && State->Get_LocationY() > 0 && 
					State->Get_LocationX() < static_cast<int>(State->Get_DataWidth()) && State->Get_LocationY() < static_cast<int>(State->Get_DataHeight()) &&
					(State->Get_LocationX() <= static_cast<int>(State->Get_DataWidth() + 1)) && (State->Get_LocationY() <= static_cast<int>(State->Get_DataHeight() + 1)))
				{
					std::cout << "STATUS B :" << State->Get_StateUnit(State->Get_LocationY() * State->Get_DataWidth() + State->Get_LocationX())->Get_State_Id() << std::endl;
					if (State->Get_StateUnit(State->Get_LocationY() * (State->Get_DataWidth() + 1) + State->Get_LocationX())->Get_State_Id() == 3)
					{
						State->Get_Screen_Distance()._LocX = Res_SCDX;
						State->Get_Screen_Distance()._LocY = Res_SCDY;
						State->Get_Move_Distance()._LocX = Res_SMDX;
						State->Get_Move_Distance()._LocY = Res_SMDY;
					}
				}
				else
				{
					State->Get_Screen_Distance()._LocX = Res_SCDX;
					State->Get_Screen_Distance()._LocY = Res_SCDY;
					State->Get_Move_Distance()._LocX = Res_SMDX;
					State->Get_Move_Distance()._LocY = Res_SMDY;
				}
			}
		}

		if (IEB->Get_Margin_Y() < 0)
		{
			State->Update_Move(IEB->Get_Margin_X(), IEB->Get_Margin_Y(), CHECK_EDGE_LA);
			//State->Update_Move(IEB->Get_Margin_X(), IEB->Get_Margin_Y(), CHECK_EDGE_RA);
			if (Current_AY != State->Get_LocationY())
			{
				if (State->Get_LocationX() > 0 && State->Get_LocationY() > 0 && 
					State->Get_LocationX() < static_cast<int>(State->Get_DataWidth()) && State->Get_LocationY() < static_cast<int>(State->Get_DataHeight()) &&
					(State->Get_LocationX() <= static_cast<int>(State->Get_DataWidth() + 1)) && (State->Get_LocationY() <= static_cast<int>(State->Get_DataHeight() + 1)))
				{
					std::cout << "STATUS C :" << State->Get_StateUnit(State->Get_LocationY() * State->Get_DataWidth() + State->Get_LocationX())->Get_State_Id() << std::endl;
					if (State->Get_StateUnit(State->Get_LocationY() * (State->Get_DataWidth() + 1) + State->Get_LocationX())->Get_State_Id() == 3)
					{
						State->Get_Screen_Distance()._LocX = Res_SCDX;
						State->Get_Screen_Distance()._LocY = Res_SCDY;
						State->Get_Move_Distance()._LocX = Res_SMDX;
						State->Get_Move_Distance()._LocY = Res_SMDY;
					}
				}
				else
				{
					State->Get_Screen_Distance()._LocX = Res_SCDX;
					State->Get_Screen_Distance()._LocY = Res_SCDY;
					State->Get_Move_Distance()._LocX = Res_SMDX;
					State->Get_Move_Distance()._LocY = Res_SMDY;
				}
			}
		}
		else if (IEB->Get_Margin_Y() > 0)
		{
			State->Update_Move(IEB->Get_Margin_X(), IEB->Get_Margin_Y(), CHECK_EDGE_LA);
			//State->Update_Move(IEB->Get_Margin_X(), IEB->Get_Margin_Y(), CHECK_EDGE_RB);
			if (Current_AY != State->Get_LocationY())
			{
				if (State->Get_LocationX() > 0 && State->Get_LocationY() > 0 && 
					State->Get_LocationX() < static_cast<int>(State->Get_DataWidth()) && State->Get_LocationY() < static_cast<int>(State->Get_DataHeight()) &&
					(State->Get_LocationX() <= static_cast<int>(State->Get_DataWidth() + 1)) && (State->Get_LocationY() <= static_cast<int>(State->Get_DataHeight() + 1)))
				{
					std::cout << "STATUS D :" << State->Get_StateUnit(State->Get_LocationY() * State->Get_DataWidth() + State->Get_LocationX())->Get_State_Id() << std::endl;
					if (State->Get_StateUnit(State->Get_LocationY() * (State->Get_DataWidth() + 1) + State->Get_LocationX())->Get_State_Id() == 3)
					{
						State->Get_Screen_Distance()._LocX = Res_SCDX;
						State->Get_Screen_Distance()._LocY = Res_SCDY;
						State->Get_Move_Distance()._LocX = Res_SMDX;
						State->Get_Move_Distance()._LocY = Res_SMDY;
					}
				}
				else
				{
					State->Get_Screen_Distance()._LocX = Res_SCDX;
					State->Get_Screen_Distance()._LocY = Res_SCDY;
					State->Get_Move_Distance()._LocX = Res_SMDX;
					State->Get_Move_Distance()._LocY = Res_SMDY;
				}
			}
		}

		//std::cout << "X " << State->Get_LocationX() << " -- Y " << State->Get_LocationY() << std::endl;

		if (IEB->Get_Key_Pressed())
		{
			Press_Flg = true;
		}

		if (!State->Get_Adjust_While_Move())
		{
			if (Press_Flg)
			{
				State->Set_Adjust_Flag(false);
			}
			else
				State->Set_Adjust_Flag(true);
		}

		//GSB->Set_CurrentLoc(MoveX, MoveY);//更新地图中心点/当前移动物品坐标

		double Current_Height{ (static_cast<double>(State->Get_Screen_Distance()._LocY) * 2 + 1) / (_Each_Height) };
		double Current_Width{ (static_cast<double>(State->Get_Screen_Distance()._LocX) * 2 + 1) / (_Each_Width) };

		if (State->Get_Adjust_Flag())
		{
			Temp_MoveY = State->Set_ExacHeight(Current_Height, State->Get_Screen_Distance()._LocY, _State_MoveY, _Auto_AdjustY);
			Temp_MoveX = State->Set_ExacWidth(Current_Width, State->Get_Screen_Distance()._LocX, _State_MoveX, _Auto_AdjustX);
			Wait_Frame = 0;
			
			if (ANCUH != ACUH)
			{
				std::cout << "ANCUH __ " << ANCUH << " ACUH __ " << ACUH << std::endl;
				int TempVal{ ANCUH };
				std::cout << "ANCUH != ACUH State->Get_Adjust_Flag() RELOAD" << std::endl;
				if (ANCUH < ACUH)
				{
					while (ANCUH++ < ACUH)
					{
						State->Set_Move_State(MoveToPH);
						_State_MoveY += static_cast<float>(_Each_Height);
					}
				}
				else if (ANCUH > ACUH)
				{
					while (ANCUH-- > ACUH)
					{
						State->Set_Move_State(MoveToNH);
						_State_MoveY -= static_cast<float>(_Each_Height);
					}
				}
				ACUH = TempVal;
				_Is_State_Changed = true;
			}

			if (ANCUW != ACUW)
			{
				std::cout << "ANCUW __ " << ANCUW << " CUW __ " << ACUW << std::endl;
				int TempVal{ ANCUW };
				std::cout << "ANCUW != ACUW State->Get_Adjust_Flag() RELOAD" << std::endl;
				if (ANCUW < ACUW)
				{
					while (ANCUW++ < ACUW)
					{
						State->Set_Move_State(MoveToNW);
						_State_MoveX += static_cast<float>(_Each_Width);
					}
				}
				else if (ANCUW > ACUW)
				{
					while (ANCUW-- > ACUW)
					{
						State->Set_Move_State(MoveToPW);
						_State_MoveX -= static_cast<float>(_Each_Width);
					}
				}
				ACUW = TempVal;
				_Is_State_Changed = true;
			}
		}
		
		if(!State->Get_Adjust_Flag() || State->Get_Adjust_While_Move())
		{
			//std::cout << "Counts First_Adjust __" << First_Adjust << std::endl;
			if (Wait_Frame == _First_Adjust)
			{
				State->Set_Adjust_Flag(true);
				Wait_Frame = 0;
			}
			else
				Wait_Frame++;

			if (NCUH != _Current_Move_Height)
			{
				std::cout << "NCUH __ " << NCUH << " CUH __ " << _Current_Move_Height << std::endl;
				int TempVal{ NCUH };
				std::cout << "NCUH != CUH !State->Get_Adjust_Flag() RELOAD" << std::endl;
				if (NCUH > _Current_Move_Height)
				{
					while (NCUH-- > _Current_Move_Height)
					{
						//std::cout << "Adjust_Flag() __N---" << State->Get_Adjust_Flag() << std::endl;
						State->Set_Move_State(MoveToNH);
						_State_MoveY -= static_cast<float>(_Each_Height);
					}
				}
				else if (NCUH < _Current_Move_Height)
				{
					while (NCUH++ < _Current_Move_Height)
					{
						//std::cout << "Adjust_Flag() __P___" << State->Get_Adjust_Flag() << std::endl;
						State->Set_Move_State(MoveToPH);
						_State_MoveY += static_cast<float>(_Each_Height);
					}
				}
				_Current_Move_Height = TempVal;
				_Is_State_Changed = true;
			}

			if (NCUW != _Current_Move_Width)
			{
				std::cout << "NCUW __ " << NCUW << " CUW __ " << _Current_Move_Width << std::endl;
				int TempVal{ NCUW };
				std::cout << "NCUW != CUW !State->Get_Adjust_Flag() RELOAD" << std::endl;
				if (NCUW > _Current_Move_Width)
				{
					while (NCUW-- > _Current_Move_Width)
					{
						//std::cout << "Adjust_Flag() __P---" << State->Get_Adjust_Flag() << std::endl;
						State->Set_Move_State(MoveToPW);
						_State_MoveX -= static_cast<float>(_Each_Width);
					}
				}
				else if (NCUW < _Current_Move_Width)
				{
					while (NCUW++ < _Current_Move_Width)
					{
						//std::cout << "Adjust_Flag() __N---" << State->Get_Adjust_Flag() << std::endl;
						State->Set_Move_State(MoveToNW);
						_State_MoveX += static_cast<float>(_Each_Width);
					}
				}
				_Current_Move_Width = TempVal;
				_Is_State_Changed = true;
			}
			
		}
		//std::cout << State->Get_Screen_Distance()._LocX + Temp_MoveX << "__" << State->Get_Screen_Distance()._LocY + Temp_MoveY << std::endl;
		glProgramUniform1f(_renderingProgram, 2, State->Get_Screen_Distance()._LocX + Temp_MoveX);//Current_Move_LocationX
		glProgramUniform1f(_renderingProgram, 3, State->Get_Screen_Distance()._LocY + Temp_MoveY);//





		if (_Is_State_Changed)
		{
			ReLoadState(State);
			_Is_State_Changed = false;
		}

		if (Press_Flg)
		{
			int Moves{};
			_Trigger_Mode = true;
			if (_Trigger_Mode)
				Moves = Auto_Update_Trigger(IEB->Get_Reach_Edge());//TODO
			else
				Moves = Auto_Update_Trigger(State->Get_Screen_Distance()._LocY, State->Get_Screen_Distance()._LocX);

			if ((Moves & MoveToNH) == MoveToNH)
			{
				_State_MoveY += 0.01f;
				_Move_AdjustY += 0.01f;
			}
			if ((Moves & MoveToPH) == MoveToPH)
			{
				_State_MoveY -= 0.01f;
				_Move_AdjustY -= 0.01f;
			}
			if ((Moves & MoveToNW) == MoveToNW)
			{
				_State_MoveX += 0.01f;
				_Move_AdjustX += 0.01f;
			}
			if ((Moves & MoveToPW) == MoveToPW)
			{
				_State_MoveX -= 0.01f;
				_Move_AdjustX -= 0.01f;
			}
		}

		glProgramUniform1f(_renderingProgram, 6, _State_MoveX);//State_MoveX
		glProgramUniform1f(_renderingProgram, 7, _State_MoveY);//State_MoveY

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