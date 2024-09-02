#pragma once

#include "Tanxl_OpenGL_Draw.h"

unsigned int quadVAO, quadVBO;
unsigned int instanceVBO;

void delay(int misec)
{
	clock_t start = clock();
	clock_t lay = (clock_t)misec;
	while ((clock() - start) < lay);
}

OpenGL_Draw& OpenGL_Draw::GetOpenGLBase(int ScreenWidth, int ScreenHeight, bool Window_Adjust)
{
	static OpenGL_Draw* OGD{ new OpenGL_Draw(ScreenWidth, ScreenHeight, Window_Adjust) };
	if (OGD->_ScreenWidth != ScreenWidth && OGD->_ScreenHeight != ScreenHeight)
		OGD->Set_DisplaySize(ScreenWidth, ScreenHeight);
	return *OGD;
}

OpenGL_Draw::OpenGL_Draw(int ScreenWidth, int ScreenHeight, bool Window_Adjust) :_HeightInt(0), _WidthInt(0), _Midle_RenderingProgram(0),
_State_RenderingProgram(0), _Adjst_RenderingProgram(0), _Start_RenderingProgram(0), _vao(), _vbo(), _ScreenWidth(ScreenWidth), _ScreenHeight(ScreenHeight),
_Main_Window(nullptr), _Window_Adjust_Enable(Window_Adjust), _Clear_Function(true), _Is_State_Changed(false), _PreLoads(0),
_Wait_Frame(0), _Translation(), _LCB(&LocationBase::GetLocationBase()), _StateInfor(), _Main_Character(new GameObject(10, 10)) {}

const std::string OpenGL_Draw::Get_Version()
{
	return this->_Version;
}

void OpenGL_Draw::init(GameStateBase* State)
{
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	_Main_Window = glfwCreateWindow(_ScreenWidth, _ScreenHeight, "Tanxl_Game TEST VERSION /// 0.2B21 TURBO", NULL, NULL);

	if (_Main_Window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	if (_Window_Adjust_Enable)
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

	this->_State_RenderingProgram = OpenGL_Render::createShaderProgram("Tanxl_State_01_VertShader.glsl", "Tanxl_Game_01_FragShader.glsl");
	this->_Adjst_RenderingProgram = OpenGL_Render::createShaderProgram("Tanxl_Player_01_VertShader.glsl", "Tanxl_Game_01_FragShader.glsl");
	this->_Start_RenderingProgram = OpenGL_Render::createShaderProgram("Tanxl_State_02_VertShader.glsl", "Tanxl_Game_01_FragShader.glsl");
	this->_Midle_RenderingProgram = OpenGL_Render::createShaderProgram("Tanxl_State_03_VertShader.glsl", "Tanxl_Game_01_FragShader.glsl");

	float BeginHeight{ (this->_HeightInt + this->_PreLoads - 1) * (1.0f / this->_HeightInt) };
	for (int Height{ 0 }; Height < (this->_Each_Height + this->_PreLoads * 2); ++Height)
	{
		float BeginWidth{ -(this->_WidthInt + this->_PreLoads - 1) * (1.0f / this->_WidthInt) };
		for (int Width{ 0 }; Width < (this->_Each_Width + this->_PreLoads * 2); ++Width)
		{
			BeginWidth += ((1.0f / this->_WidthInt) * 2);
			this->_Translation[Height * this->_WidthInt + Width].x = 0;// BeginWidth;
			this->_Translation[Height * this->_WidthInt + Width].y = 0;// BeginHeight;
		}
		BeginHeight -= ((1.0f / this->_HeightInt) * 2);
		BeginWidth = -(this->_WidthInt + this->_PreLoads - 1) * (1.0f / this->_WidthInt);
	}

	glGenVertexArrays(1, _vao);
	glBindVertexArray(_vao[0]);
	glGenBuffers(1, _vbo);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glProgramUniform1i(this->_Adjst_RenderingProgram, 4, this->_HeightInt);//SHeight
	glProgramUniform1i(this->_Adjst_RenderingProgram, 5, this->_WidthInt);//SWidth
	glProgramUniform1f(this->_Adjst_RenderingProgram, 6, 0.6f);//State_MoveX
	glProgramUniform1f(this->_Adjst_RenderingProgram, 7, 0.9f);//State_MoveY
	glProgramUniform1i(this->_Adjst_RenderingProgram, 8, _Main_Character->Check_Health());//Health Init
	glProgramUniform1f(this->_Adjst_RenderingProgram, 9, this->_Health_Image_Margin);
	glProgramUniform1i(this->_Adjst_RenderingProgram, 10, 0);//Insert Status

	glProgramUniform1i(this->_State_RenderingProgram, 4, this->_HeightInt);//SHeight
	glProgramUniform1i(this->_State_RenderingProgram, 5, this->_WidthInt);//SWidth
	glProgramUniform1i(this->_State_RenderingProgram, 8, this->_PreLoads);//PreLoads

	Append_Texture(TanxlOD::TexGrass_02_200x200);       // 1 00
	Append_Texture(TanxlOD::TexGrass_Snowy_01_200x200); // 2 01
	Append_Texture(TanxlOD::TexGrass_Snowy_02_200x200); // 3 02
	Append_Texture(TanxlOD::TexOcean_01_200x200);       // 4 03
	Append_Texture(TanxlOD::TexDirt_01_200x200);        // 5 04
	Append_Texture(TanxlOD::TexPrincess_01_256x256);	// 6 05
	Append_Texture(TanxlOD::TexPrincess_02_256x256);	// 6 05
	Append_Texture(TanxlOD::TexPrincess_03_256x256);	// 6 05
	Append_Texture(TanxlOD::TexPrincess_04_256x256);	// 6 05
	Append_Texture(TanxlOD::TexHealth_01_32x32);        // 7 06
	Append_Texture(TanxlOD::TexPrincess_01_9x11);       // 8 07
	Append_Texture(TanxlOD::TexStartMenu_01_1024x1024); // 9 08

	std::cout << "___" << this->_HeightInt << "___" << this->_WidthInt << "___" << this->_PreLoads << std::endl;

	float Half_Width{ (this->_WidthInt - 1) / 2.0f };
	float Half_Height{ (this->_HeightInt - 1) / 2.0f };

	State->Get_Move_Distance()._Location_X = (2.0f / this->_WidthInt) * Half_Width + (1.0f / this->_WidthInt) * (this->_PreLoads);
	State->Get_Move_Distance()._Location_Y = -(2.0f / this->_HeightInt) * Half_Height - (1.0f / this->_HeightInt) * (this->_PreLoads);

	State->Set_Move_State(
		0 - this->_PreLoads + _Pre_MoveX,
		this->_WidthInt - 1 + this->_PreLoads + _Pre_MoveX,
		0 - this->_PreLoads + _Pre_MoveY,
		this->_HeightInt - 1 + this->_PreLoads + _Pre_MoveY);

	this->_LCB->Get_LocationX(State->Get_Distance_Move_Id()) += static_cast<float>((_Pre_MoveX - 4) * this->_Each_Width);
	this->_LCB->Get_LocationY(State->Get_Distance_Move_Id()) -= static_cast<float>((_Pre_MoveY - 4) * this->_Each_Height);

	this->Set_Max_Middle_Frame(200);

	ReLoadState(State);
}

void OpenGL_Draw::ReLoadState(GameStateBase* State)//NEXT
{
	int Move_NX{ State->Get_Square_State()._Move_NX };
	int Move_PX{ State->Get_Square_State()._Move_PX };
	int Move_NY{ State->Get_Square_State()._Move_NY };
	int Move_PY{ State->Get_Square_State()._Move_PY };

	int State_Length{ (this->_HeightInt + this->_PreLoads * 2) * (this->_WidthInt + this->_PreLoads * 2) + 1 };

#if _TANXL_OPENGLDRAW_RELOAD_STATE_SQUARE_OUTPUT_
	std::cout << "Move_NX: " << Move_NX << "Move_PX: " << Move_PX << std::endl;
	std::cout << "Move_NY: " << Move_NY << "Move_PY: " << Move_PY << std::endl;
#endif

	if (State->Get_Compile_Status())
	{
		if (State->Get_GameState()->size() == 0)
			return;

		for (int i{ 0 }; i < State_Length; ++i)
		{
			this->_StateInfor[i].x = 3;
			this->_StateInfor[i].y = 1;

			if (Move_NX > static_cast<int>(State->Get_DataWidth()))//RIGH AREA
			{
				if (Move_NY > static_cast<int>(State->Get_DataHeight()))
				{
					if (State->Is_State_Exist(STATE_EXTEND_RIGH_BELO))
					{
						unsigned x{ Move_NX - State->Get_DataWidth() - 1 + (Move_NY - State->Get_DataHeight() - 1) * (State->Get_DataWidth() + 1) };
						StateUnit* Unit{ State->Get_StateUnit(STATE_EXTEND_RIGH_BELO, x % State->Get_GameState(STATE_EXTEND_RIGH_BELO)->size()) };
						this->_StateInfor[i].x = Unit->Get_State_Id();
						this->_StateInfor[i].y = Unit->Get_Move_Status();
					}
				}
				else if (Move_NY >= 0)
				{
					if (State->Is_State_Exist(STATE_EXTEND_RIGH))
					{
						unsigned x{ Move_NX - State->Get_DataWidth() - 1 + Move_NY * (State->Get_DataWidth() + 1) };
						StateUnit* Unit{ State->Get_StateUnit(STATE_EXTEND_RIGH, x % State->Get_GameState(STATE_EXTEND_RIGH)->size()) };
						this->_StateInfor[i].x = Unit->Get_State_Id();
						this->_StateInfor[i].y = Unit->Get_Move_Status();
					}
				}
				else if (Move_NY >= -static_cast<int>(State->Get_DataHeight()))
				{
					if (State->Is_State_Exist(STATE_EXTEND_RIGH_ABOV))
					{
						unsigned x{ Move_NX - State->Get_DataWidth() - 1 + (Move_NY + State->Get_DataHeight() + 1) * (State->Get_DataWidth() + 1) };
						StateUnit* Unit{ State->Get_StateUnit(STATE_EXTEND_RIGH_ABOV, x % State->Get_GameState(STATE_EXTEND_RIGH_ABOV)->size()) };
						this->_StateInfor[i].x = Unit->Get_State_Id();
						this->_StateInfor[i].y = Unit->Get_Move_Status();
					}
				}
			}
			else if (Move_NX >= 0)//MID AREA
			{
				if (Move_NY > static_cast<int>(State->Get_DataHeight()))
				{
					if (State->Is_State_Exist(STATE_EXTEND_BELO))
					{
						unsigned x{ Move_NX + (Move_NY - State->Get_DataHeight() - 1) * (State->Get_DataWidth() + 1) };
						StateUnit* Unit{ State->Get_StateUnit(STATE_EXTEND_BELO, x % State->Get_GameState(STATE_EXTEND_BELO)->size()) };
						this->_StateInfor[i].x = Unit->Get_State_Id();
						this->_StateInfor[i].y = Unit->Get_Move_Status();
					}
				}
				else if (Move_NY >= 0)
				{
					if (State->Is_State_Exist(STATE_EXTEND_MIDD))
					{
						unsigned x{ Move_NX + Move_NY * (State->Get_DataWidth() + 1) };
						StateUnit* Unit{ State->Get_StateUnit(STATE_EXTEND_MIDD, x % State->Get_GameState(STATE_EXTEND_MIDD)->size()) };
						this->_StateInfor[i].x = Unit->Get_State_Id();
						this->_StateInfor[i].y = Unit->Get_Move_Status();
					}
				}
				else if (Move_NY >= -static_cast<int>(State->Get_DataHeight()))
				{
					if (State->Is_State_Exist(STATE_EXTEND_ABOV))
					{
						unsigned x{ Move_NX + (Move_NY + State->Get_DataHeight() + 1) * (State->Get_DataWidth() + 1) };
						StateUnit* Unit{ State->Get_StateUnit(STATE_EXTEND_ABOV, x % State->Get_GameState(STATE_EXTEND_ABOV)->size()) };
						this->_StateInfor[i].x = Unit->Get_State_Id();
						this->_StateInfor[i].y = Unit->Get_Move_Status();
					}
				}
			}
			else if (Move_NX >= -static_cast<int>(State->Get_DataWidth()))//LEFT AREA
			{
				if (Move_NY > static_cast<int>(State->Get_DataHeight()))
				{
					if (State->Is_State_Exist(STATE_EXTEND_LEFT_BELO))
					{
						unsigned x{ Move_NX + State->Get_DataWidth() + 1 + (Move_NY - State->Get_DataHeight() - 1) * (State->Get_DataWidth() + 1) };
						StateUnit* Unit{ State->Get_StateUnit(STATE_EXTEND_LEFT_BELO, x % State->Get_GameState(STATE_EXTEND_BELO)->size()) };
						this->_StateInfor[i].x = Unit->Get_State_Id();
						this->_StateInfor[i].y = Unit->Get_Move_Status();
					}
				}
				else if (Move_NY >= 0)
				{
					if (State->Is_State_Exist(STATE_EXTEND_LEFT))
					{
						unsigned x{ Move_NX + State->Get_DataWidth() + 1 + Move_NY * (State->Get_DataWidth() + 1) };
						StateUnit* Unit{ State->Get_StateUnit(STATE_EXTEND_LEFT, x % State->Get_GameState(STATE_EXTEND_MIDD)->size()) };
						this->_StateInfor[i].x = Unit->Get_State_Id();
						this->_StateInfor[i].y = Unit->Get_Move_Status();
					}
				}
				else if (Move_NY >= -static_cast<int>(State->Get_DataHeight()))
				{
					if (State->Is_State_Exist(STATE_EXTEND_LEFT_ABOV))
					{
						unsigned x{ Move_NX + State->Get_DataWidth() + 1 + (Move_NY + State->Get_DataHeight() + 1) * (State->Get_DataWidth() + 1) };
						StateUnit* Unit{ State->Get_StateUnit(STATE_EXTEND_LEFT_ABOV, x % State->Get_GameState(STATE_EXTEND_ABOV)->size()) };
						this->_StateInfor[i].x = Unit->Get_State_Id();
						this->_StateInfor[i].y = Unit->Get_Move_Status();
					}
				}
			}

			Move_NX++;
			if (Move_NX > Move_PX)//抵达尽头 重新获取初值
			{
				Move_NX = State->Get_Square_State()._Move_NX;
				Move_NY++;
			}
		}
	}
	else
	{
		RandomBase* UIB{ &RandomBase::GetRandomBase() };
		for (int i{ 0 }; i < State_Length; ++i)
		{
			this->_StateInfor[i].x = UIB->RandomAutoSeed(0, 4);
			std::cout << this->_StateInfor[i].x;
		}
	}
	GLuint StatePos;
	for (int i{ 0 }; i < State_Length; ++i)
	{
		std::string Tag{ "State[" + std::to_string(i) + "]" };
		StatePos = glGetUniformLocation(_State_RenderingProgram, Tag.c_str());
		glProgramUniform2fv(_State_RenderingProgram, StatePos, 1, glm::value_ptr(this->_Translation[i]));

		Tag = "Infor[" + std::to_string(i) + "]";
		StatePos = glGetUniformLocation(_State_RenderingProgram, Tag.c_str());
		glProgramUniform2iv(_State_RenderingProgram, StatePos, 1, glm::value_ptr(this->_StateInfor[i]));

		std::cout << this->_StateInfor[i].x << " ";
		if (i % (this->_WidthInt + this->_PreLoads * 2) == 0)
			std::cout << std::endl;
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

void OpenGL_Draw::Set_WaitFrame(int First_Adjust)
{
	this->_Wait_Frame = First_Adjust;
}

void OpenGL_Draw::Set_Clear(bool Clear)
{
	this->_Clear_Function = Clear;
}

void OpenGL_Draw::Set_Trigger_Range(float Ratio)
{
	this->_Trigger_Ratio = Ratio;
}

void OpenGL_Draw::Set_PreMove(int PreMoveX, int PreMoveY)
{
	this->_Pre_MoveX = PreMoveX;
	this->_Pre_MoveY = PreMoveY;
}

void OpenGL_Draw::Set_DisplaySize(int WindowWidth, int WindowHeight)
{
	this->_ScreenHeight = WindowHeight;
	this->_ScreenWidth = WindowWidth;
	glViewport(0, 0, this->_ScreenWidth, this->_ScreenHeight);
}

void OpenGL_Draw::Set_Max_Middle_Frame(int Max_Middle_Frame)
{
	this->_Max_Middle_Frame = Max_Middle_Frame;
}

void OpenGL_Draw::Append_Texture(const char* Texture)
{
	static unsigned Id{ 0 };

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[Id]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(TanxlOD::textureCoordinates), TanxlOD::textureCoordinates, GL_STATIC_DRAW);

	glActiveTexture(GL_TEXTURE0 + Id);

	glBindTexture(GL_TEXTURE_2D, OpenGL_Render::loadTexture(Texture));
	Id++;
}

void OpenGL_Draw::HitEdge_Check(GameStateBase* State)
{
	//示例提供八个按键操作事件 （单例模式于其他地方定义）
	InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };

	static double State_Data_Width{ State->Get_DataWidth() * this->_Each_Width * 2 + this->_Each_Width };
	static double State_Data_Height{ State->Get_DataHeight() * this->_Each_Height * 2 + this->_Each_Height };

	static int Dist_Mid{ State->Get_Distance_Screen_Id() };
	static int Exac_Mov{ State->Get_Distance_Move_Id() };

	int State_Width{ static_cast<int>(State->Get_DataWidth()) + 1 };
	int State_Height{ static_cast<int>(State->Get_DataHeight()) + 1 };

	float Marg_Width{ static_cast<float>(this->_Each_Width * 10) };
	float Marg_Height{ static_cast<float>(this->_Each_Height * 10) };

	if (IEB->Get_Margin_X() < 0)
	{
		if (this->_LCB->Get_LocationX(Exac_Mov) < -static_cast<int>(State->Get_DataWidth()) - 1)
		{
			State->Get_Screen_Distance()._Location_X = this->_Location_Distance_MidX;
			State->Get_Move_Distance()._Location_X = this->_Location_Move_DistanceX;
#if _TANXL_OPENGLDRAW_EDGE_LIMIT_CHECK_OUTPUT_
			std::cout << "LEFT RES :" << this->_Location_Distance_MidX << "__" << this->_Location_Move_DistanceX << std::endl;
#endif
		}
		else
		{
			int State_Check = 0;
			for (int i{ 0 }; i < 2; ++i)
			{
				State->Update_Move(IEB->Get_Margin_X(), 0.0f, CHECK_EDGE_LEFT);

				if (State->Get_LocationX() >= -static_cast<int>(State->Get_DataWidth()) - 1)
					State_Check_Block(State, CHECK_EDGE_LEFT);
			}
		}
		glProgramUniform1i(this->_Adjst_RenderingProgram, 10, 0);//Insert Status
	}

	if (IEB->Get_Margin_X() > 0)
	{
		if ((this->_LCB->Get_LocationX(Exac_Mov) > State_Data_Width))
		{
			State->Get_Screen_Distance()._Location_X = this->_Location_Distance_MidX;
			State->Get_Move_Distance()._Location_X = this->_Location_Move_DistanceX;
#if _TANXL_OPENGLDRAW_EDGE_LIMIT_CHECK_OUTPUT_
			std::cout << "RIGH RES :" << this->_Location_Distance_MidX << "__" << this->_Location_Move_DistanceX << std::endl;
#endif
		}
		else
		{
			int State_Check = 0;
			for (int i{ 0 }; i < 2; ++i)
			{
				State->Update_Move(IEB->Get_Margin_X(), 0.0f, CHECK_EDGE_RIGH);

				if (State->Get_LocationX() <= static_cast<int>(State->Get_DataWidth()) * 2 + 1)
					State_Check_Block(State, CHECK_EDGE_RIGH);
			}
		}
		glProgramUniform1i(this->_Adjst_RenderingProgram, 10, 1);//Insert Status
	}

	if (IEB->Get_Margin_Y() > 0)
	{
		if ((this->_LCB->Get_LocationY(Exac_Mov) > State->Get_DataHeight() + 1))
		{
			State->Get_Screen_Distance()._Location_Y = this->_Location_Distance_MidY;
			State->Get_Move_Distance()._Location_Y = this->_Location_Move_DistanceY;
#if _TANXL_OPENGLDRAW_EDGE_LIMIT_CHECK_OUTPUT_
			std::cout << "ABOV RES :" << this->_Location_Distance_MidY << "__" << this->_Location_Move_DistanceY << std::endl;
#endif
		}
		else
		{
			int State_Check = 0;
			for (int i{ 0 }; i < 2; ++i)
			{
				State->Update_Move(0.0f, IEB->Get_Margin_Y(), CHECK_EDGE_ABOV);

				if (State->Get_LocationY() >= -static_cast<int>(State->Get_DataHeight()) - 1)
					State_Check_Block(State, CHECK_EDGE_ABOV);
			}
		}
		glProgramUniform1i(this->_Adjst_RenderingProgram, 10, 2);//Insert Status
	}

	if (IEB->Get_Margin_Y() < 0)
	{
		if (this->_LCB->Get_LocationY(Exac_Mov) < -State_Data_Height)
		{
			State->Get_Screen_Distance()._Location_Y = this->_Location_Distance_MidY;
			State->Get_Move_Distance()._Location_Y = this->_Location_Move_DistanceY;
#if _TANXL_OPENGLDRAW_EDGE_LIMIT_CHECK_OUTPUT_
			std::cout << "DOWN RES :" << this->_Location_Distance_MidY << "__" << this->_Location_Move_DistanceY << std::endl;
#endif
		}
		else
		{
			int State_Check = 0;
			for (int i{ 0 }; i < 2; ++i)
			{
				State->Update_Move(0.0f, IEB->Get_Margin_Y(), CHECK_EDGE_BELO);

				if (State->Get_LocationY() <= static_cast<int>(State->Get_DataHeight()) * 2 + 1)
					State_Check_Block(State, CHECK_EDGE_BELO);
			}
		}
		glProgramUniform1i(this->_Adjst_RenderingProgram, 10, 3);//Insert Status
	}
}

void OpenGL_Draw::Update_Current()
{
	static GameStateBase* GSB{ &GameStateBase::GetStateBase() };
	this->_New_Current_Height = -static_cast<int>((this->_LCB->Get_LocationY(GSB->Get_Distance_Move_Id()) + 2.0f) / _Each_Height);
	this->_New_Current_Width = -static_cast<int>((this->_LCB->Get_LocationX(GSB->Get_Distance_Move_Id()) - 2.0f) / _Each_Width);
}

void OpenGL_Draw::Update_Last_Location(GameStateBase* State)
{
	static int Dist_Mid{ State->Get_Distance_Screen_Id() };
	this->_Location_Distance_MidX = this->_LCB->Get_LocationX(Dist_Mid);
	this->_Location_Distance_MidY = this->_LCB->Get_LocationY(Dist_Mid);
	this->_Location_Move_DistanceX = State->Get_Move_Distance()._Location_X;
	this->_Location_Move_DistanceY = State->Get_Move_Distance()._Location_Y;
}

void OpenGL_Draw::Destroy_Window()
{
	glfwDestroyWindow(_Main_Window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void OpenGL_Draw::Enable_State_Adjust(bool Enable)
{
	this->_Is_Adjust_Enable = Enable;
}

int OpenGL_Draw::Get_Adjust_Status()
{
	return this->_Current_Status;
}

int OpenGL_Draw::Get_PreLoad()
{
	return this->_PreLoads;
}

void OpenGL_Draw::State_Check_Block(GameStateBase* State, ECheck_Edge Check_Direction)
{
	static int Status{ 0 };
	float Marg_Width{ static_cast<float>(this->_Each_Width * 10) };
	float Marg_Height{ static_cast<float>(this->_Each_Height * 10) };

	int State_Unit_Width{ static_cast<int>(State->Get_DataWidth()) + 1 };
	int State_Unit_Height{ static_cast<int>(State->Get_DataHeight()) + 1 };

	bool Reset{ false };

	switch (Check_Direction)
	{
	case CHECK_EDGE_LEFT:
		if (State->Get_LocationX() < 0)
			Reset = true;
		break;
	case CHECK_EDGE_RIGH:
		if (State->Get_LocationX() > 10)
			Reset = true;
		break;
	case CHECK_EDGE_BELO:
		if (State->Get_LocationY() > 10)
			Reset = true;
		break;
	case CHECK_EDGE_ABOV:
		if (State->Get_LocationY() < 0)
			Reset = true;
		break;
	}

	if ((State->Get_State(State->Get_LocationX(), State->Get_LocationY()) == nullptr) ||
		(State->Get_State(State->Get_LocationX(), State->Get_LocationY())->Get_Move_Status() == 1))
	{
		Status = 0;

		switch (Check_Direction)
		{
		case CHECK_EDGE_LEFT:
		case CHECK_EDGE_RIGH:
			State->Get_Screen_Distance()._Location_X = this->_Location_Distance_MidX;
			State->Get_Move_Distance()._Location_X = this->_Location_Move_DistanceX;
			break;
		case CHECK_EDGE_BELO:
		case CHECK_EDGE_ABOV:
			State->Get_Screen_Distance()._Location_Y = this->_Location_Distance_MidY;
			State->Get_Move_Distance()._Location_Y = this->_Location_Move_DistanceY;
			break;
		}
		std::cout << "Return" << std::endl;
	}
	else if (Reset)
	{
		Status = 0;
		switch (Check_Direction)
		{
		case CHECK_EDGE_LEFT:
			State->Get_Move_Distance()._Location_X += Marg_Width;
			break;
		case CHECK_EDGE_RIGH:
			State->Get_Move_Distance()._Location_X -= Marg_Width;
			break;
		case CHECK_EDGE_BELO:
			State->Get_Move_Distance()._Location_Y += Marg_Height;
			break;
		case CHECK_EDGE_ABOV:
			State->Get_Move_Distance()._Location_Y -= Marg_Height;
			break;
		}

		State->Update_Move(0.0f, 0.0f, Check_Direction);

		int Temp_Height = this->_New_Current_Height;
		int Temp_Width = this->_New_Current_Width;

		Update_Current();

		switch (Check_Direction)
		{
		case CHECK_EDGE_LEFT:
			this->_Current_Move_Height -= (Temp_Height - this->_New_Current_Height);
			this->_Current_Move_Width -= (Temp_Width - this->_New_Current_Width + 1);

			State->Reload_State(STATE_EXTEND_LEFT);
			this->Move_State(State, MoveToNW, State_Unit_Width);
			break;
		case CHECK_EDGE_RIGH:
			this->_Current_Move_Height -= (Temp_Height - this->_New_Current_Height);
			this->_Current_Move_Width -= (Temp_Width - this->_New_Current_Width - 1);

			State->Reload_State(STATE_EXTEND_RIGH);
			this->Move_State(State, MoveToPW, State_Unit_Width);
			break;
		case CHECK_EDGE_BELO:
			this->_Current_Move_Height -= (Temp_Height - this->_New_Current_Height + 1);
			this->_Current_Move_Width -= (Temp_Width - this->_New_Current_Width);

			State->Reload_State(STATE_EXTEND_BELO);
			this->Move_State(State, MoveToPH, State_Unit_Height);
			break;
		case CHECK_EDGE_ABOV:
			this->_Current_Move_Height -= (Temp_Height - this->_New_Current_Height - 1);
			this->_Current_Move_Width -= (Temp_Width - this->_New_Current_Width);

			State->Reload_State(STATE_EXTEND_ABOV);
			this->Move_State(State, MoveToNH, State_Unit_Height);
			break;
		}
		this->_Is_State_Changed = true;
	}
}

void OpenGL_Draw::State_Check_Event(GameStateBase* State)
{
	StateUnit* CheckUnit{ State->Get_State(State->Get_LocationX(), State->Get_LocationY()) };
	if (!CheckUnit)
		return;

	if (CheckUnit->Get_State_Id() == 4)
	{
		if (_Main_Character->Check_Health() <= 2)
		{
			_Main_Character->Set_Health(2, 10);
		}
		else
		{
			_Main_Character->TakeDamage(1);
			CheckUnit->Set_State_Id(1);
			ReLoadState(State);
		}
	}
}

void OpenGL_Draw::Move_State(GameStateBase* State, EMove_State_EventId Direction, int Times)
{
	while (Times--)
		State->Set_Move_State(Direction);
	this->_Is_State_Changed = true;
}

float OpenGL_Draw::Get_Trigger_Ratio()
{
	return this->_Trigger_Ratio;
}

bool OpenGL_Draw::Check_Key_Press()
{
	for (int i{ 32 }; i < 96; ++i)
		if (glfwGetKey(Get_Window(), i) == GLFW_PRESS)
			return true;
	for (int i{ 256 }; i < 348; ++i)
		if (glfwGetKey(Get_Window(), i) == GLFW_PRESS)
			return true;
	return false;
}

void OpenGL_Draw::display(GLFWwindow* window, double currentTime, GameStateBase* State)
{
	static SoundBase* SB{ &SoundBase::GetSoundBase() };
	if (_Clear_Function)
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		this->_Clear_Function = false;
	}

	std::cout << "_Draw_Status :" << _Draw_Status << std::endl;

	if ((_Draw_Status == 0) || (_Draw_Status == 2))
	{
		this->_Middle_Frame = 0;
		glUseProgram(_Start_RenderingProgram);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	else if (_Draw_Status == 5)
	{
		if (this->_Middle_Frame == 0)
		{
			SB->Play_Sound("music/Game_Start.wav");
		}
		this->_Middle_Frame++;

		if (this->_Middle_Frame > this->_Max_Middle_Frame)
		{
			this->_Draw_Status = 1;
		}

		if (this->_Middle_Frame > this->_Max_Middle_Frame / 2)
		{
			glUseProgram(_State_RenderingProgram);
			glDrawArrays(GL_TRIANGLES, 0, (State->Get_StateHeight() + _PreLoads * 2) * (State->Get_StateWidth() + _PreLoads * 2) * 6);

			glUseProgram(_Adjst_RenderingProgram);
			glDrawArrays(GL_TRIANGLES, 0, _Main_Character->Check_Health() * 6);
		}
		else
		{
			glUseProgram(_Start_RenderingProgram);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		std::cout << "Middle_Frame :" << _Middle_Frame << std::endl;
		glProgramUniform1i(this->_Midle_RenderingProgram, 2, this->_Middle_Frame);
		glProgramUniform1i(this->_Midle_RenderingProgram, 3, this->_Max_Middle_Frame);

		if (this->_Middle_Frame > this->_Max_Middle_Frame)
		{
			this->_Middle_Frame = 0;
		}

		glUseProgram(_Midle_RenderingProgram);
		glDrawArrays(GL_TRIANGLES, 0, 6 * 25);
	}
	else if (_Draw_Status == 6)
	{
		this->_Middle_Frame++;

		if (this->_Middle_Frame > this->_Max_Middle_Frame)
		{
			this->_Draw_Status = 2;
		}

		if (this->_Middle_Frame > this->_Max_Middle_Frame / 2)
		{
			glUseProgram(_Start_RenderingProgram);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		else
		{
			glUseProgram(_State_RenderingProgram);
			glDrawArrays(GL_TRIANGLES, 0, (State->Get_StateHeight() + _PreLoads * 2) * (State->Get_StateWidth() + _PreLoads * 2) * 6);

			glUseProgram(_Adjst_RenderingProgram);
			glDrawArrays(GL_TRIANGLES, 0, _Main_Character->Check_Health() * 6);
		}

		std::cout << "Middle_Frame :" << _Middle_Frame << std::endl;
		glProgramUniform1i(this->_Midle_RenderingProgram, 2, this->_Middle_Frame);
		glProgramUniform1i(this->_Midle_RenderingProgram, 3, this->_Max_Middle_Frame);

		if (this->_Middle_Frame > this->_Max_Middle_Frame)
		{
			this->_Middle_Frame = 0;
		}

		glUseProgram(_Midle_RenderingProgram);
		glDrawArrays(GL_TRIANGLES, 0, 6 * 25);
	}
	else
	{
		if (_Draw_Status == 3)
		{
			_Draw_Status = 6;
			SB->Play_Sound("music/Game_Over.wav");
			this->_Main_Character->Set_Health(10);
		}

		this->_Middle_Frame = 0;
		glUseProgram(_State_RenderingProgram);
		glDrawArrays(GL_TRIANGLES, 0, (State->Get_StateHeight() + _PreLoads * 2) * (State->Get_StateWidth() + _PreLoads * 2) * 6);

		//glUseProgram(_State_RenderingProgram);
		//glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 400);

		glUseProgram(_Adjst_RenderingProgram);
		glDrawArrays(GL_TRIANGLES, 0, _Main_Character->Check_Health() * 6);
	}
}

void OpenGL_Draw::Render_Once(GameStateBase* State)
{
	static InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };//获取输入事件基类

	static Key_Unit* OpenGL_Stop_Key{ new Key_Unit(GLFW_KEY_F) };

	if (this->_Is_Init_Need)
	{
		this->_Is_Init_Need = false;
		init(State);

		IEB->RegistEvent(OpenGL_Stop_Key);
	}

	if (_Draw_Status == 0)
	{
		if (Check_Key_Press())
		{
			IEB->Init_Default_Key();
			_Draw_Status = 5;
		}
	}
	else if (_Draw_Status == 2)
	{
		if (Check_Key_Press())
			_Draw_Status = 5;
	}

	if (this->_Main_Character->Check_Health() == 2)
	{
		_Draw_Status = 3;
	}

	static int Move_Loc{ this->_LCB->New_Location_set("Move_Adjust_Location") }; //记录手动移动状态的移动距离
	static int Stat_Loc{ this->_LCB->New_Location_set("State_Move_Location") };  //记录地图场景移动距离
	static int Dist_Mid{ State->Get_Distance_Screen_Id() };
	static int Exac_Mov{ State->Get_Distance_Move_Id() };

#if _TANXL_OPENGLDRAW_REALTIME_LOCATION_OUTPUT_
	std::cout << "Move_Loc " << this->_LCB->Get_LocationX(Move_Loc) << " -- " << this->_LCB->Get_LocationY(Move_Loc) << std::endl;
	std::cout << "Dist_Mid " << this->_LCB->Get_LocationX(Dist_Mid) << " -- " << this->_LCB->Get_LocationY(Dist_Mid) << std::endl;
	std::cout << "Exac_Mov " << this->_LCB->Get_LocationX(Exac_Mov) << " -- " << this->_LCB->Get_LocationY(Exac_Mov) << std::endl;// MAJOR
	std::cout << "Stat_Loc " << this->_LCB->Get_LocationX(Stat_Loc) << " -- " << this->_LCB->Get_LocationY(Stat_Loc) << std::endl << std::endl << std::endl;
#endif

	if (!glfwWindowShouldClose(_Main_Window))
	{
		float Temp_MoveX{ 0.0f };
		float Temp_MoveY{ 0.0f };
		_Current_Status = 0;

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);

		if ((OpenGL_Stop_Key->MoveToY == true) || (this->_Is_Adjust_Enable == false))
		{
			std::cout << "ENABLE" << std::endl;
			display(_Main_Window, glfwGetTime(), State);
			glfwSwapBuffers(_Main_Window);
			glfwPollEvents();
			_Current_Status = 1;
			return;
		}

		static int Wait_Frame{ 0 };

#if _TANXL_OPENGLDRAW_REALTIME_LOCATION_OUTPUT_
		std::cout << "Limit " << State->Get_DataWidth() * this->_Each_Width << " -- "
			<< State->Get_DataHeight() * this->_Each_Height << std::endl;
#endif

		HitEdge_Check(State);

		State_Check_Event(State);

		if (!State->Get_Adjust_While_Move())
		{
			if (IEB->Get_Key_Pressed())
				State->Set_Adjust_Flag(false);
			else
				State->Set_Adjust_Flag(true);
		}

		double Current_Height{ (static_cast<double>(this->_LCB->Get_LocationY(Dist_Mid)) * 2 + 1) / (_Each_Height) };
		double Current_Width{ (static_cast<double>(this->_LCB->Get_LocationX(Dist_Mid)) * 2 + 1) / (_Each_Width) };

		if (State->Get_Adjust_Flag())//Auto Adjust Part
		{
			Temp_MoveY = State->Set_ExacHeight(Current_Height, this->_LCB->Get_LocationY(Dist_Mid), this->_LCB->Get_LocationY(Stat_Loc));
			Temp_MoveX = State->Set_ExacWidth(Current_Width, this->_LCB->Get_LocationX(Dist_Mid), this->_LCB->Get_LocationX(Stat_Loc));
		}
		if (!State->Get_Adjust_Flag() || State->Get_Adjust_While_Move())//Move Adjust Part
		{
			if (Wait_Frame == this->_Wait_Frame)
			{
				State->Set_Adjust_Flag(true);
				Wait_Frame = 0;
			}
			else
				Wait_Frame++;

			if (_New_Current_Height != _Current_Move_Height)
			{
#if _TANXL_OPENGLDRAW_START_MOVEADJUST_OUTPUT_
				std::cout << "NCUH __ " << _New_Current_Height << " CUH __ " << _Current_Move_Height << std::endl;
#endif
				int TempVal{ _New_Current_Height };
#if _TANXL_OPENGLDRAW_START_MOVEADJUST_OUTPUT_
				std::cout << "NCUH != CUH !State->Get_Adjust_Flag() RELOAD" << std::endl;
#endif
				if (_New_Current_Height > _Current_Move_Height)
				{
					while (_New_Current_Height-- > _Current_Move_Height)
					{
#if _TANXL_OPENGLDRAW_START_MOVEADJUST_OUTPUT_
						std::cout << "Adjust_Flag() __HN---" << State->Get_Adjust_Flag() << std::endl;
#endif
						State->Set_Move_State(MoveToNH);
						this->_LCB->Get_LocationY(Stat_Loc) -= static_cast<float>(_Each_Height);
					}
				}
				else if (_New_Current_Height < _Current_Move_Height)
				{
					while (_New_Current_Height++ < _Current_Move_Height)
					{
#if _TANXL_OPENGLDRAW_START_MOVEADJUST_OUTPUT_
						std::cout << "Adjust_Flag() __HP___" << State->Get_Adjust_Flag() << std::endl;
#endif
						State->Set_Move_State(MoveToPH);
						this->_LCB->Get_LocationY(Stat_Loc) += static_cast<float>(_Each_Height);
					}
				}
				_Current_Move_Height = TempVal;
				_Is_State_Changed = true;
			}

			if (_New_Current_Width != _Current_Move_Width)
			{
#if _TANXL_OPENGLDRAW_START_MOVEADJUST_OUTPUT_
				std::cout << "NCUW __ " << _New_Current_Width << " CUW __ " << _Current_Move_Width << std::endl;
#endif
				int TempVal{ _New_Current_Width };
#if _TANXL_OPENGLDRAW_START_MOVEADJUST_OUTPUT_
				std::cout << "NCUW != CUW !State->Get_Adjust_Flag() RELOAD" << std::endl;
#endif
				if (_New_Current_Width > _Current_Move_Width)
				{
					while (_New_Current_Width-- > _Current_Move_Width)
					{
#if _TANXL_OPENGLDRAW_START_MOVEADJUST_OUTPUT_
						std::cout << "Adjust_Flag() __WN---" << State->Get_Adjust_Flag() << std::endl;
#endif
						State->Set_Move_State(MoveToPW);
						this->_LCB->Get_LocationX(Stat_Loc) -= static_cast<float>(_Each_Width);
					}
				}
				else if (_New_Current_Width < _Current_Move_Width)
				{
					while (_New_Current_Width++ < _Current_Move_Width)
					{
#if _TANXL_OPENGLDRAW_START_MOVEADJUST_OUTPUT_
						std::cout << "Adjust_Flag() __WP---" << State->Get_Adjust_Flag() << std::endl;
#endif
						State->Set_Move_State(MoveToNW);
						this->_LCB->Get_LocationX(Stat_Loc) += static_cast<float>(_Each_Width);
					}
				}
				_Current_Move_Width = TempVal;
				_Is_State_Changed = true;
			}
		}

		glProgramUniform1f(_State_RenderingProgram, 2, this->_LCB->Get_LocationX(Dist_Mid) + Temp_MoveX);//Current_Move_LocationX
		glProgramUniform1f(_State_RenderingProgram, 3, this->_LCB->Get_LocationY(Dist_Mid) + Temp_MoveY);//

		glProgramUniform1f(_Adjst_RenderingProgram, 2, this->_LCB->Get_LocationX(Dist_Mid) + Temp_MoveX);//Current_Move_LocationX
		glProgramUniform1f(_Adjst_RenderingProgram, 3, this->_LCB->Get_LocationY(Dist_Mid) + Temp_MoveY);//

		if (_Is_State_Changed)
		{
			ReLoadState(State);
			_Is_State_Changed = false;
		}

		State->StateMove_Edge_Set(Dist_Mid, Stat_Loc, Move_Loc, IEB->Get_Reach_Edge());

		glProgramUniform1f(_State_RenderingProgram, 6, this->_LCB->Get_LocationX(Stat_Loc));//State_MoveX
		glProgramUniform1f(_State_RenderingProgram, 7, this->_LCB->Get_LocationY(Stat_Loc));//State_MoveY

		display(_Main_Window, glfwGetTime(), State);
		glfwSwapBuffers(_Main_Window);
		glfwPollEvents();
	}
	else
		Destroy_Window();
}

void TanxlOD::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}