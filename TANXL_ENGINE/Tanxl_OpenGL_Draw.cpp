#pragma once

#include "Tanxl_OpenGL_Draw.h"

OpenGL_Draw& OpenGL_Draw::GetOpenGLBase(int ScreenWidth, int ScreenHeight, bool Window_Adjust)
{
	static OpenGL_Draw* OGD{ new OpenGL_Draw(ScreenWidth, ScreenHeight, Window_Adjust) };
	return *OGD;
}

OpenGL_Draw::OpenGL_Draw(int ScreenWidth, int ScreenHeight, bool Window_Adjust) :_HeightInt(0), _StateInfor(),
_WidthInt(0), _State_RenderingProgram(0), _Adjst_RenderingProgram(0), _vao(), _vbo(), _ScreenWidth(ScreenWidth),
_ScreenHeight(ScreenHeight), _Main_Window(nullptr), _Window_Adjust_Enable(Window_Adjust), _Clear_Function(true),
_Is_State_Changed(false), _PreLoads(0), _First_Adjust(0) {}

const std::string OpenGL_Draw::Get_Version()
{
	return this->_Version;
}

void OpenGL_Draw::init(GameStateBase* State)
{
	//示例提供四个按键操作事件 （单例模式于其他地方定义）
	RandomBase* UIB{ &RandomBase::GetRandomBase() };

	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	_Main_Window = glfwCreateWindow(_ScreenWidth, _ScreenHeight, "Tanxl_Game TEST VERSION /// 0.00.00.17", NULL, NULL);

	if (_Main_Window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	if(_Window_Adjust_Enable)
		glfwSetFramebufferSizeCallback(_Main_Window, TanxlOD::framebuffer_size_callback);
	else
		glfwSetWindowSizeLimits(_Main_Window, 800, 800, 800, 800);

	glfwMakeContextCurrent(_Main_Window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }
	glfwSwapInterval(1);

	glEnable(GL_DEPTH_TEST);

	glDepthFunc(GL_LEQUAL);

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0f);

	this->_HeightInt = State->Get_StateHeight();
	this->_WidthInt = State->Get_StateWidth();

	this->_Each_Height = 2.0f / State->Get_StateHeight();//10 0.2
	this->_Each_Width = 2.0f / State->Get_StateWidth();//10 0.2

	this->_Current_Move_Height = 0;
	this->_Current_Move_Width = 0;
	
	State->Set_Move_State(0, this->_WidthInt - 1 + this->_PreLoads, 0, this->_HeightInt - 1 + this->_PreLoads);

	this->_State_RenderingProgram = OpenGL_Render::createShaderProgram("Tanxl_State_01_VertShader.glsl", "fragShader.glsl");
	this->_Adjst_RenderingProgram = OpenGL_Render::createShaderProgram("Tanxl_Player_01_VertShader.glsl", "fragShader.glsl");

	glGenVertexArrays(1, _vao);
	glBindVertexArray(_vao[0]);
	glGenBuffers(1, _vbo);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glUseProgram(this->_Adjst_RenderingProgram);
	glProgramUniform1i(this->_Adjst_RenderingProgram, 4, this->_HeightInt);//SHeight
	glProgramUniform1i(this->_Adjst_RenderingProgram, 5, this->_WidthInt);//SWidth
	glProgramUniform1f(this->_Adjst_RenderingProgram, 6, 0.6f);//State_MoveX
	glProgramUniform1f(this->_Adjst_RenderingProgram, 7, 0.9f);//State_MoveY
	glProgramUniform1i(this->_Adjst_RenderingProgram, 10, 2 + 3);//SWidth

	glUseProgram(this->_State_RenderingProgram);
	glProgramUniform1i(this->_State_RenderingProgram, 4, this->_HeightInt);//SHeight
	glProgramUniform1i(this->_State_RenderingProgram, 5, this->_WidthInt);//SWidth
	glProgramUniform1i(this->_State_RenderingProgram, 9, (this->_HeightInt + this->_PreLoads) * (this->_WidthInt + this->_PreLoads) * 6);
	glProgramUniform1i(this->_State_RenderingProgram, 8, this->_PreLoads);//PreLoads

    Append_Texture(TanxlOD::TexGrass_02_200x200);       //1 00
	Append_Texture(TanxlOD::TexGrass_Snowy_01_200x200); //2 01
	Append_Texture(TanxlOD::TexGrass_Snowy_02_200x200); //3 02
	Append_Texture(TanxlOD::TexOcean_01_200x200);       //4 03
	Append_Texture(TanxlOD::TexWood_01_32x32);          //5 04
	Append_Texture(TanxlOD::TexPrincess_01_32x32);		//6 05
	Append_Texture(TanxlOD::TexHealth_01_32x32);        //7 06
	Append_Texture(TanxlOD::TexPrincess_01_9x11);       //8 07

	std::cout << "___" << this->_HeightInt << "___" << this->_WidthInt << "___" << this->_PreLoads << std::endl;

	glDrawArrays(GL_TRIANGLES, 0, (this->_HeightInt + _PreLoads) * (this->_WidthInt + _PreLoads) * 6 + 30);

	Set_Trigger_Range(true, 0.6f, 0.6f);

	int Min{ this->_HeightInt > this->_WidthInt ? this->_WidthInt : this->_HeightInt };
	State->Get_Move_Distance()._Location_X = 2.0f / Min * (Min - 1);
	State->Get_Move_Distance()._Location_Y = -(2.0f / Min * (Min - 1));

	ReLoadState(State);
}

void OpenGL_Draw::ReLoadState(GameStateBase* State)
{
	RandomBase* UIB{ &RandomBase::GetRandomBase() };

	int Move_NX{ State->Get_Move_State()._Move_NX };
	int Move_PX{ State->Get_Move_State()._Move_PX };
	int Move_NY{ State->Get_Move_State()._Move_NY };
	int Move_PY{ State->Get_Move_State()._Move_PY };

	int State_Length{ (this->_HeightInt + this->_PreLoads) * (this->_WidthInt + this->_PreLoads) + 1 };

	std::cout << "Move_NX: " << Move_NX << "Move_PX: " << Move_PX << std::endl;
	std::cout << "Move_NY: " << Move_NY << "Move_PY: " << Move_PY << std::endl;

	if (State->Get_Compile_Status())
	{
		for (int i{ 0 }; i < State_Length; ++i)
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

				_StateInfor[i] = State->Get_StateUnit(STATE_ORIGIN_MIDD, x % State->Get_GameState()->size())->Get_State_Id();//3/20 STATE_EXTEND_MIDD
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
		for (int i{ 0 }; i < State_Length; ++i)
		{
			_StateInfor[i] = UIB->Random(0, 3);
			std::cout << _StateInfor[i];
		}
	}
	GLuint StatePos;
	for (int i{ 0 }; i < State_Length; ++i)
	{
		std::string Tag{ "State[" + std::to_string(i) + "]" };
		StatePos = glGetUniformLocation(_State_RenderingProgram, Tag.c_str());
		glProgramUniform1i(_State_RenderingProgram, StatePos, _StateInfor[i]);
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
	static unsigned Id{ 0 };

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[Id]);

	if(_Advanced_Mode)
		glBufferData(GL_ARRAY_BUFFER, sizeof(TanxlOD::textureCoordinates), TanxlOD::textureCoordinates, GL_STATIC_DRAW);
	else
		glBufferData(GL_ARRAY_BUFFER, 0, 0, GL_STATIC_DRAW);

	glActiveTexture(GL_TEXTURE0 + Id);

	glBindTexture(GL_TEXTURE_2D, OpenGL_Render::loadTexture(Texture));
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

	glUseProgram(_State_RenderingProgram);
	glDrawArrays(GL_TRIANGLES, 0, (State->Get_StateHeight() + _PreLoads) * (State->Get_StateWidth() + _PreLoads) * 6);

	glUseProgram(_Adjst_RenderingProgram);
	glDrawArrays(GL_TRIANGLES, 0, 30);
}

void OpenGL_Draw::Render_Once(GameStateBase* State)
{
	static bool First_Time{ true };

	float Temp_MoveX{ 0.0f };
	float Temp_MoveY{ 0.0f };

	if (First_Time)
	{
		First_Time = false;
		init(State);
	}

	InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };//获取输入事件基类
	GameStateBase* GSB{ &GameStateBase::GetStateBase() };
	LocationBase* LCB{ &LocationBase::GetLocationBase() };

	static int Auto_Loc = LCB->New_Location_set("Auto_Adjust_Location"); //记录自动调整状态的移动距离
	static int Move_Loc = LCB->New_Location_set("Move_Adjust_Location"); //记录手动移动状态的移动距离
	static int Stat_Loc = LCB->New_Location_set("State_Move_Location");  //记录地图场景移动距离
	static int Dist_Mid = State->Get_Distance_Screen_Id();
	static int Exac_Mov = State->Get_Distance_Move_Id();

#if _TANXL_DATABASE_OPENGLDRAW_REALTIME_LOCATION_
	std::cout << "Auto_Loc " << LCB->Get_LocationX(Auto_Loc) << " -- " << LCB->Get_LocationY(Auto_Loc) << std::endl;
	std::cout << "Move_Loc " << LCB->Get_LocationX(Move_Loc) << " -- " << LCB->Get_LocationY(Move_Loc) << std::endl;
	std::cout << "Dist_Mid " << LCB->Get_LocationX(Dist_Mid) << " -- " << LCB->Get_LocationY(Dist_Mid) << std::endl;
	std::cout << "Exac_Mov " << LCB->Get_LocationX(Exac_Mov) << " -- " << LCB->Get_LocationY(Exac_Mov) << std::endl;// MAJOR
	std::cout << "Stat_Loc " << LCB->Get_LocationX(Stat_Loc) << " -- " << LCB->Get_LocationY(Stat_Loc) << std::endl << std::endl << std::endl;
#endif
	
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

		int NCUH{ static_cast<int>(LCB->Get_LocationY(Move_Loc) / _Each_Height) };
		int NCUW{ static_cast<int>(LCB->Get_LocationX(Move_Loc) / _Each_Width) };

		static int ACUH{ static_cast<int>(LCB->Adjust_Location(Auto_Loc, MARKING_DIV, static_cast<float>(_Each_Height), 0)) };
		static int ACUW{ static_cast<int>(LCB->Adjust_Location(Auto_Loc, MARKING_DIV, static_cast<float>(_Each_Width), 1)) };

		static int ANCUH{ static_cast<int>(LCB->Adjust_Location(Auto_Loc, MARKING_DIV, static_cast<float>(_Each_Height), 0)) };
		static int ANCUW{ static_cast<int>(LCB->Adjust_Location(Auto_Loc, MARKING_DIV, static_cast<float>(_Each_Width), 1)) };

		int TOCUH{ static_cast<int>((static_cast<double>(LCB->Get_LocationY(Move_Loc)) * 2) / _Each_Height) };
		int TOCUW{ static_cast<int>((static_cast<double>(LCB->Get_LocationX(Move_Loc)) * 2) / _Each_Width) };

		if (State->Get_Adjust_Flag())
		{
			ANCUH = static_cast<int>(LCB->Adjust_Location(Auto_Loc, MARKING_DIV, static_cast<float>(_Each_Height), 0));
			ANCUW = static_cast<int>(LCB->Adjust_Location(Auto_Loc, MARKING_DIV, static_cast<float>(_Each_Width), 1));
		}

		static int Wait_Frame{ 0 };
		bool Press_Flg{ false };

		//std::cout << "FLAG ----------------------------B"<< State->Get_Adjust_Flag() << std::endl;
		float Res_SCDX = LCB->Get_LocationX(Dist_Mid);
		float Res_SCDY = LCB->Get_LocationY(Dist_Mid);
		float Res_SMDX = State->Get_Move_Distance()._Location_X;
		float Res_SMDY = State->Get_Move_Distance()._Location_Y;

		IEB->GetInsert(_Main_Window, State);//获取输入

		static double State_Data_Width = State->Get_DataWidth() * this->_Each_Width;
		static double State_Data_Height = State->Get_DataHeight() * this->_Each_Height;

#if _TANXL_DATABASE_OPENGLDRAW_REALTIME_LOCATION_
		std::cout << "Limit " << State_Data_Width << " -- " << State_Data_Height << std::endl;
#endif

		/*if (((LCB->Get_LocationX(Exac_Mov) < 0) && IEB->Get_Margin_X() < 0) ||
			((LCB->Get_LocationX(Exac_Mov) > State_Data_Width) && IEB->Get_Margin_X() > 0))
		{
			State->Get_Screen_Distance()._Location_X = Res_SCDX;
			State->Get_Move_Distance()._Location_X = Res_SMDX;
		}
		if (((LCB->Get_LocationY(Exac_Mov) > 0) && (IEB->Get_Margin_Y() > 0)) ||
			((LCB->Get_LocationY(Exac_Mov) < -State_Data_Height) && (IEB->Get_Margin_Y() < 0)))
		{
			State->Get_Screen_Distance()._Location_Y = Res_SCDY;
			State->Get_Move_Distance()._Location_Y = Res_SMDY;
		}*/

		//std::cout << State->Get_LocationX() << " -- " << State->Get_LocationY() << std::endl;

		if (IEB->Get_Margin_X() < 0)
		{
			if ((LCB->Get_LocationX(Exac_Mov) < 0))
			{
				State->Get_Screen_Distance()._Location_X = Res_SCDX;
				State->Get_Move_Distance()._Location_X = Res_SMDX;
			}
			else
			{
				State->Update_Move(0.0f, 0.0f, CHECK_EDGE_LEFT);
				int Current_LX = State->Get_LocationX();
				State->Update_Move(IEB->Get_Margin_X(), IEB->Get_Margin_Y(), CHECK_EDGE_LEFT);
				if (Current_LX != State->Get_LocationX())
				{
					if (State->Get_LocationX() >= 0)
					{
						int X = State->Get_LocationX();
						int Y = State->Get_LocationY();
						if (X < 0)
							X = 0;
						if (X > static_cast<int>(State->Get_DataWidth()))
							X = State->Get_DataWidth();
						if (Y < 0)
							Y = 0;
						if (Y > static_cast<int>(State->Get_DataHeight()))
							Y = State->Get_DataHeight();
						std::cout << "STATUS A :" << State->Get_StateUnit(Y * State->Get_DataWidth() + X)->Get_State_Id() << std::endl;
						if (State->Get_StateUnit(Y * State->Get_DataWidth() + X)->Get_State_Id() == 3)
						{
							State->Get_Screen_Distance()._Location_X = Res_SCDX;
							State->Get_Move_Distance()._Location_X = Res_SMDX;
							Press_Flg = false;
						}
					}
				}
			}
		}

		if (IEB->Get_Margin_X() > 0)
		{
			if ((LCB->Get_LocationX(Exac_Mov) > State_Data_Width))
			{
				State->Get_Screen_Distance()._Location_X = Res_SCDX;
				State->Get_Move_Distance()._Location_X = Res_SMDX;
			}
			else
			{
				State->Update_Move(0.0f, 0.0f, CHECK_EDGE_RIGH);
				int Current_LX = State->Get_LocationX();
				State->Update_Move(IEB->Get_Margin_X(), IEB->Get_Margin_Y(), CHECK_EDGE_RIGH);
				if (Current_LX != State->Get_LocationX())
				{
					std::cout << static_cast<int>(State->Get_DataWidth()) << std::endl;
					if (State->Get_LocationX() < static_cast<int>(State->Get_DataWidth()))
					{
						int X = State->Get_LocationX();
						int Y = State->Get_LocationY();
						if (X < 0)
							X = 0;
						if (X > static_cast<int>(State->Get_DataWidth()))
							X = State->Get_DataWidth();
						if (Y < 0)
							Y = 0;
						if (Y > static_cast<int>(State->Get_DataHeight()))
							Y = State->Get_DataHeight();
						std::cout << "STATUS A :" << State->Get_StateUnit(Y * State->Get_DataWidth() + X)->Get_State_Id() << std::endl;
						if (State->Get_StateUnit(Y * State->Get_DataWidth() + X)->Get_State_Id() == 3)
						{
							State->Get_Screen_Distance()._Location_X = Res_SCDX;
							State->Get_Move_Distance()._Location_X = Res_SMDX;
							Press_Flg = false;
						}
					}
				}
			}
		}

		if (IEB->Get_Margin_Y() > 0)
		{
			if ((LCB->Get_LocationY(Exac_Mov) > 0))
			{
				State->Get_Screen_Distance()._Location_Y = Res_SCDY;
				State->Get_Move_Distance()._Location_Y = Res_SMDY;
			}
			else
			{
				State->Update_Move(0.0f, 0.0f, CHECK_EDGE_ABOV);
				int Current_LX = State->Get_LocationY();
				State->Update_Move(IEB->Get_Margin_X(), IEB->Get_Margin_Y(), CHECK_EDGE_ABOV);
				if (Current_LX != State->Get_LocationY())
				{
					std::cout << static_cast<int>(State->Get_DataHeight()) << std::endl;
					if (State->Get_LocationY() >= 0)
					{
						int X = State->Get_LocationX();
						int Y = State->Get_LocationY();
						if (X < 0)
							X = 0;
						if (X > static_cast<int>(State->Get_DataWidth()))
							X = State->Get_DataWidth();
						if (Y < 0)
							Y = 0;
						if (Y > static_cast<int>(State->Get_DataHeight()))
							Y = State->Get_DataHeight();
						std::cout << "STATUS A :" << State->Get_StateUnit(Y * State->Get_DataWidth() + X)->Get_State_Id() << std::endl;
						if (State->Get_StateUnit(Y * State->Get_DataWidth() + X)->Get_State_Id() == 3)
						{
							State->Get_Screen_Distance()._Location_Y = Res_SCDY;
							State->Get_Move_Distance()._Location_Y = Res_SMDY;
							Press_Flg = false;
						}
					}
				}
			}
		}

		if (IEB->Get_Margin_Y() < 0)
		{
			if (LCB->Get_LocationY(Exac_Mov) < -State_Data_Height)
			{
				State->Get_Screen_Distance()._Location_Y = Res_SCDY;
				State->Get_Move_Distance()._Location_Y = Res_SMDY;
			}
			else
			{
				State->Update_Move(0.0f, 0.0f, CHECK_EDGE_BELO);
				int Current_LX = State->Get_LocationY();
				State->Update_Move(IEB->Get_Margin_X(), IEB->Get_Margin_Y(), CHECK_EDGE_BELO);
				if (Current_LX != State->Get_LocationY())
				{
					std::cout << static_cast<int>(State->Get_DataHeight()) << std::endl;
					if (State->Get_LocationY() < static_cast<int>(State->Get_DataHeight()))
					{
						int X = State->Get_LocationX();
						int Y = State->Get_LocationY();
						if (X < 0)
							X = 0;
						if (X > static_cast<int>(State->Get_DataWidth()))
							X = State->Get_DataWidth();
						if (Y < 0)
							Y = 0;
						if (Y > static_cast<int>(State->Get_DataHeight()))
							Y = State->Get_DataHeight();
						std::cout << "STATUS A :" << State->Get_StateUnit(Y * State->Get_DataWidth() + X)->Get_State_Id() << std::endl;
						if (State->Get_StateUnit(Y * State->Get_DataWidth() + X)->Get_State_Id() == 3)
						{
							State->Get_Screen_Distance()._Location_Y = Res_SCDY;
							State->Get_Move_Distance()._Location_Y = Res_SMDY;
							Press_Flg = false;
						}
					}
				}
			}
		}

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

		double Current_Height{ (static_cast<double>(LCB->Get_LocationY(Dist_Mid)) * 2 + 1) / (_Each_Height) };
		double Current_Width{ (static_cast<double>(LCB->Get_LocationX(Dist_Mid)) * 2 + 1) / (_Each_Width) };

		if (State->Get_Adjust_Flag())
		{
			Temp_MoveY = State->Set_ExacHeight(Current_Height, LCB->Get_LocationY(Dist_Mid), LCB->Get_LocationY(Stat_Loc), LCB->Get_LocationY(Auto_Loc));
			Temp_MoveX = State->Set_ExacWidth(Current_Width, LCB->Get_LocationX(Dist_Mid), LCB->Get_LocationX(Stat_Loc), LCB->Get_LocationX(Auto_Loc));
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
						LCB->Get_LocationY(Stat_Loc) += static_cast<float>(_Each_Height);
					}
				}
				else if (ANCUH > ACUH)
				{
					while (ANCUH-- > ACUH)
					{
						State->Set_Move_State(MoveToNH);
						LCB->Get_LocationY(Stat_Loc) -= static_cast<float>(_Each_Height);
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
						LCB->Get_LocationX(Stat_Loc) += static_cast<float>(_Each_Width);
					}
				}
				else if (ANCUW > ACUW)
				{
					while (ANCUW-- > ACUW)
					{
						State->Set_Move_State(MoveToPW);
						LCB->Get_LocationX(Stat_Loc) -= static_cast<float>(_Each_Width);
					}
				}
				ACUW = TempVal;
				_Is_State_Changed = true;
			}
		}

		if (!State->Get_Adjust_Flag() || State->Get_Adjust_While_Move())
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
						LCB->Get_LocationY(Stat_Loc) -= static_cast<float>(_Each_Height);
					}
				}
				else if (NCUH < _Current_Move_Height)
				{
					while (NCUH++ < _Current_Move_Height)
					{
						//std::cout << "Adjust_Flag() __P___" << State->Get_Adjust_Flag() << std::endl;
						State->Set_Move_State(MoveToPH);
						LCB->Get_LocationY(Stat_Loc) += static_cast<float>(_Each_Height);
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
						LCB->Get_LocationX(Stat_Loc) -= static_cast<float>(_Each_Width);
					}
				}
				else if (NCUW < _Current_Move_Width)
				{
					while (NCUW++ < _Current_Move_Width)
					{
						//std::cout << "Adjust_Flag() __N---" << State->Get_Adjust_Flag() << std::endl;
						State->Set_Move_State(MoveToNW);
						LCB->Get_LocationX(Stat_Loc) += static_cast<float>(_Each_Width);
					}
				}
				_Current_Move_Width = TempVal;
				_Is_State_Changed = true;
			}
		}

		//std::cout << State->Get_Screen_Distance()._LocX + Temp_MoveX << "__" << State->Get_Screen_Distance()._LocY + Temp_MoveY << std::endl;
		glProgramUniform1f(_State_RenderingProgram, 2, LCB->Get_LocationX(Dist_Mid) + Temp_MoveX);//Current_Move_LocationX
		glProgramUniform1f(_State_RenderingProgram, 3, LCB->Get_LocationY(Dist_Mid) + Temp_MoveY);//

		glProgramUniform1f(_Adjst_RenderingProgram, 2, LCB->Get_LocationX(Dist_Mid) + Temp_MoveX);//Current_Move_LocationX
		glProgramUniform1f(_Adjst_RenderingProgram, 3, LCB->Get_LocationY(Dist_Mid) + Temp_MoveY);//

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
				Moves = Auto_Update_Trigger(LCB->Get_LocationY(Dist_Mid), LCB->Get_LocationX(Dist_Mid));

			if ((Moves & MoveToNH) == MoveToNH)
			{
				std::cout << "FLAG ----------------------------A" << std::endl;
				LCB->Get_LocationY(Stat_Loc) += 0.01f;
				LCB->Get_LocationY(Move_Loc) += 0.01f;
				State->Get_Move_Distance()._Location_Y -= 0.01f;
			}
			if ((Moves & MoveToPH) == MoveToPH)
			{
				std::cout << "FLAG ----------------------------B" << std::endl;
				LCB->Get_LocationY(Stat_Loc) -= 0.01f;
				LCB->Get_LocationY(Move_Loc) -= 0.01f;
				State->Get_Move_Distance()._Location_Y += 0.01f;
			}
			if ((Moves & MoveToNW) == MoveToNW)
			{
				std::cout << "FLAG ----------------------------C" << std::endl;
				LCB->Get_LocationX(Stat_Loc) += 0.01f;
				LCB->Get_LocationX(Move_Loc) += 0.01f;
				State->Get_Move_Distance()._Location_X -= 0.01f;
			}
			if ((Moves & MoveToPW) == MoveToPW)
			{
				std::cout << "FLAG ----------------------------D" << std::endl;
				LCB->Get_LocationX(Stat_Loc) -= 0.01f;
				LCB->Get_LocationX(Move_Loc) -= 0.01f;
				State->Get_Move_Distance()._Location_X += 0.01f;
			}
		}

		glProgramUniform1f(_State_RenderingProgram, 6, LCB->Get_LocationX(Stat_Loc));//State_MoveX
		glProgramUniform1f(_State_RenderingProgram, 7, LCB->Get_LocationY(Stat_Loc));//State_MoveY

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

void TanxlOD::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}