#pragma once

#include "Tanxl_OpenGL_Draw.h"

#include <Windows.h>

static FontBase* Font{ &FontBase::GetFontBase() };

static GameObject* MC{ Main_Character::Get_Main_Character() };

static Tanxl_Inventory* TI{ &Tanxl_Inventory::Get_InventoryBase() };

OpenGL_Draw& OpenGL_Draw::GetOpenGLBase(int ScreenWidth, int ScreenHeight, bool Window_Adjust)
{
	static OpenGL_Draw* OGD{ new OpenGL_Draw(ScreenWidth, ScreenHeight, Window_Adjust) };
	if ((OGD->_Screen_Length._Coord_X != ScreenWidth) && (OGD->_Screen_Length._Coord_Y != ScreenHeight))
		OGD->Set_DisplaySize(ScreenWidth, ScreenHeight);
	return *OGD;
}

OpenGL_Draw::OpenGL_Draw(int ScreenWidth, int ScreenHeight, bool Window_Adjust) : _vao(), _vbo(), _Font_vbo(),
_Inst_vbo(), _Screen_Length(ScreenWidth, ScreenHeight), _Main_Window(nullptr), _Window_Adjust_Enable(Window_Adjust),
_Clear_Function(true), _Is_State_Changed(false), _PreLoads(0), _LCB(&LocationBase::GetLocationBase()), _StateInfor(), _StateOffSet()
{
	this->_State_Loc = this->_LCB->New_Location_set("State_Move_Location");
}

const std::string OpenGL_Draw::Get_Version()
{
	return this->_Version;
}

void OpenGL_Draw::init(GameStateBase* State)
{
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	_Main_Window = glfwCreateWindow(_Screen_Length._Coord_X, _Screen_Length._Coord_Y, "Tanxl_GAME /// 0.2B67", NULL, NULL);
	if (_Main_Window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(_Main_Window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (_Window_Adjust_Enable)
		glfwSetFramebufferSizeCallback(_Main_Window, TanxlOD::framebuffer_size_callback);
	else
		glfwSetWindowSizeLimits(_Main_Window, 960, 800, 960, 800);

	glfwSwapInterval(1);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0f);

	this->_Scene_Int = State->Get_StateLength();

	this->_Each_Height = 2.0f / State->Get_StateLength()._Coord_Y;//10 0.2
	this->_Each_Width = 2.0f / State->Get_StateLength()._Coord_X;//10 0.2

	this->_Current_Move._Coord_Y = 0;
	this->_Current_Move._Coord_X = 0;

	this->_State_RenderingProgram = OpenGL_Render::createShaderProgram("Shader/Tanxl_State_01_VertShader.glsl", "Shader/Tanxl_Game_01_FragShader.glsl");
	this->_Adjst_RenderingProgram = OpenGL_Render::createShaderProgram("Shader/Tanxl_Player_01_VertShader.glsl", "Shader/Tanxl_Game_01_FragShader.glsl");
	this->_Start_RenderingProgram = OpenGL_Render::createShaderProgram("Shader/Tanxl_State_02_VertShader.glsl", "Shader/Tanxl_Game_01_FragShader.glsl");
	this->_Midle_RenderingProgram = OpenGL_Render::createShaderProgram("Shader/Tanxl_State_03_VertShader.glsl", "Shader/Tanxl_Game_01_FragShader.glsl");
	this->_Event_RenderingProgram = OpenGL_Render::createShaderProgram("Shader/Tanxl_State_04_VertShader.glsl", "Shader/Tanxl_Game_01_FragShader.glsl");
	this->_ITest_RenderingProgram = OpenGL_Render::createShaderProgram("Shader/Tanxl_Test_01_VertShader.glsl", "Shader/Tanxl_Game_01_FragShader.glsl");
	this->_Fonts_RenderingProgram = OpenGL_Render::createShaderProgram("Shader/Tanxl_Fonts_01_VertShader.glsl", "Shader/Tanxl_Fonts_01_FragShader.glsl");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(_Screen_Length._Coord_X), 0.0f, static_cast<GLfloat>(_Screen_Length._Coord_Y));
	glUseProgram(this->_Fonts_RenderingProgram);
	glUniformMatrix4fv(4, 1, GL_FALSE, glm::value_ptr(projection));

	Font->Set_Language(TI->Get_User_Language());
	Font->Comfirm_Language();

	static GameTips* Tips{ &GameTips::GetTipsBase() };
	Tips->ResetTips(TI->Get_User_Language());

	glGenVertexArrays(1, &_vao[0]);
	glGenBuffers(1, &_Font_vbo[0]);
	glBindVertexArray(_vao[0]);
	glBindBuffer(GL_ARRAY_BUFFER, _Font_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glUseProgram(this->_State_RenderingProgram);

	glGenVertexArrays(1, &_vao[1]);
	glGenBuffers(1, _vbo);
	glBindVertexArray(_vao[1]);
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glProgramUniform1i(this->_Adjst_RenderingProgram, 4, this->_Scene_Int._Coord_Y);//SHeight
	glProgramUniform1i(this->_Adjst_RenderingProgram, 5, this->_Scene_Int._Coord_X);//SWidth
	glProgramUniform1f(this->_Adjst_RenderingProgram, 6, 0.6f);//HP UI MoveX
	glProgramUniform1f(this->_Adjst_RenderingProgram, 7, 0.9f);//HP UI MoveY
	glProgramUniform1i(this->_Adjst_RenderingProgram, 8, MC->Get_MaxHealth() + 2);//Health Init
	glProgramUniform1f(this->_Adjst_RenderingProgram, 9, this->_Health_Image_Margin);
	glProgramUniform1i(this->_Adjst_RenderingProgram, 10, 0);//Insert Status

	glProgramUniform1i(this->_State_RenderingProgram, 2, this->_Scene_Int._Coord_Y);//SHeight
	glProgramUniform1i(this->_State_RenderingProgram, 3, this->_Scene_Int._Coord_X);//SWidth
	glProgramUniform1i(this->_State_RenderingProgram, 6, this->_PreLoads);//PreLoads

	glProgramUniform1i(this->_Event_RenderingProgram, 2, this->_Scene_Int._Coord_Y);//SHeight
	glProgramUniform1i(this->_Event_RenderingProgram, 3, this->_Scene_Int._Coord_X);//SWidth
	glProgramUniform1i(this->_Event_RenderingProgram, 6, this->_PreLoads);//PreLoads

	//State_Square Part 0~6  Adjust random range when number of textures change 
	Append_Texture(TanxlOD::TexGrass_01_128x128);
	Append_Texture(TanxlOD::TexGrass_02_128x128);
	Append_Texture(TanxlOD::TexGrass_Snowy_01_128x128);
	Append_Texture(TanxlOD::TexGrass_Snowy_02_128x128);
	Append_Texture(TanxlOD::TexOcean_01_128x128);
	Append_Texture(TanxlOD::TexDirt_01_128x128);
	Append_Texture(TanxlOD::TexCoin_01_64x64);

	int Tex_01{ Append_Texture(TanxlOD::TexPrincess_01_256x256)		};
	int Tex_02{ Append_Texture(TanxlOD::TexPrincess_02_256x256)		};
	int Tex_03{ Append_Texture(TanxlOD::TexPrincess_03_256x256)		};
	int Tex_04{ Append_Texture(TanxlOD::TexPrincess_04_256x256)		};
	int Tex_05{ Append_Texture(TanxlOD::TexHealth_01_32x32)			};
	int Tex_06{ Append_Texture(TanxlOD::TexPrincess_01_9x11)		};
	int Tex_07{ Append_Texture(TanxlOD::TexStartMenu_01_1024x1024)	};
	int Tex_08{ Append_Texture(TanxlOD::TexMedic_01_64x64)			};
	int Tex_09{ Append_Texture(TanxlOD::TexPrincess_01_Blink_01_256x256) };
	int Tex_10{ Append_Texture(TanxlOD::TexPrincess_01_Blink_02_256x256) };
	int Tex_11{ Append_Texture(TanxlOD::TexSecretCore_01_64x64)			 };

	glProgramUniform1i(this->_Adjst_RenderingProgram, 11, Tex_01);
	glProgramUniform1i(this->_Adjst_RenderingProgram, 12, Tex_02);
	glProgramUniform1i(this->_Adjst_RenderingProgram, 13, Tex_03);
	glProgramUniform1i(this->_Adjst_RenderingProgram, 14, Tex_04);
	glProgramUniform1i(this->_Adjst_RenderingProgram, 15, Tex_05);
	glProgramUniform1i(this->_Adjst_RenderingProgram, 16, Tex_06);
	glProgramUniform1i(this->_Adjst_RenderingProgram, 17, Tex_09);
	glProgramUniform1i(this->_Adjst_RenderingProgram, 18, Tex_10);

	glProgramUniform1i(this->_Start_RenderingProgram, 2, Tex_07);

	glProgramUniform1i(this->_Event_RenderingProgram, 7, Tex_08);
	glProgramUniform1i(this->_Event_RenderingProgram, 8, Tex_11);

	glBindVertexArray(0);

	glm::vec3 translations[30]{};
	int Instance_Cnt = 0;
	double BeginHeight{ ((this->_Scene_Int._Coord_Y) / 2.0f) * this->_Each_Height - this->_Each_Height / 2.0f };
	for (int Height{ 0 }; Height < (5); ++Height)
	{
		double BeginWidth{ -((this->_Scene_Int._Coord_X) / 2.0f) * this->_Each_Width + this->_Each_Width / 2.0f };
		for (int Width{ 0 }; Width < (6); ++Width)
		{
			translations[Instance_Cnt].x = static_cast<float>(BeginWidth);
			translations[Instance_Cnt].y = static_cast<float>(BeginHeight);

			if ((Instance_Cnt / 6) % 2 == 1)
				translations[Instance_Cnt].z = static_cast<float>((Instance_Cnt + 1) % 2);
			else
				translations[Instance_Cnt].z = static_cast<float>(Instance_Cnt % 2);

			++Instance_Cnt;
			BeginWidth += this->_Each_Width;
		}
		BeginHeight -= this->_Each_Height;
	}

	glGenBuffers(1, &_Inst_vbo[0]);
	glBindBuffer(GL_ARRAY_BUFFER, _Inst_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 30, &translations[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	float HalfW{ static_cast<float>(this->_Each_Width / 2) };
	float HalfH{ static_cast<float>(this->_Each_Height / 2) };

	float quadVertices[] = {
		// positions
		-HalfW,  HalfH,
		 HalfW, -HalfH,
		-HalfW, -HalfH,

		-HalfW,  HalfH,
		 HalfW, -HalfH,
		 HalfW,  HalfH,
	};
	glGenVertexArrays(1, &_vao[2]);
	glGenBuffers(1, &_Inst_vbo[1]);
	glBindVertexArray(_vao[2]);
	glBindBuffer(GL_ARRAY_BUFFER, _Inst_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);// Test VertShader uniform aPos
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(2);// Test VertShader uniform aOffset
	glBindBuffer(GL_ARRAY_BUFFER, _Inst_vbo[0]); // this attribute comes from a different vertex buffer
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.
	glBindVertexArray(0);

	std::cout << "___" << this->_Scene_Int._Coord_Y << "___" << this->_Scene_Int._Coord_X << "___" << this->_PreLoads << std::endl;

	float Half_Width{ (this->_Scene_Int._Coord_X - 1) / 2.0f };
	float Half_Height{ (this->_Scene_Int._Coord_Y - 1) / 2.0f };

	State->Get_Move_Distance()._Coord_X = (2.0f / this->_Scene_Int._Coord_X) * Half_Width + (1.0f / this->_Scene_Int._Coord_X) * (8 - this->_PreLoads);
	State->Get_Move_Distance()._Coord_Y = -(2.0f / this->_Scene_Int._Coord_Y) * Half_Height - (1.0f / this->_Scene_Int._Coord_Y) * (8 - this->_PreLoads);

	State->Get_Square_State().Set_State_Length(State->Get_StateLength()._Coord_X, State->Get_StateLength()._Coord_Y);
	State->Get_Square_State().Set_Move_State(_Pre_Move._Coord_X, _Pre_Move._Coord_Y, this->_PreLoads);

	this->_LCB->Get_LocationX(State->Get_Distance_Move_Id()) += static_cast<float>((_Pre_Move._Coord_X - 4) * this->_Each_Width);
	this->_LCB->Get_LocationY(State->Get_Distance_Move_Id()) -= static_cast<float>((_Pre_Move._Coord_Y - 4) * this->_Each_Height);

	this->_State_Length = (this->_Scene_Int._Coord_Y + this->_PreLoads * 2) * (this->_Scene_Int._Coord_X + this->_PreLoads * 2) + 1;

	this->Set_Max_Middle_Frame(200);

	for (int i{ 0 }; i < 400; ++i)
	{
		_StateOffSet[i].x = 0.0f;
		_StateOffSet[i].y = 0.0f;

		std::string Tag = "State_OffSet[" + std::to_string(i) + "]";
		GLuint StatePos = glGetUniformLocation(_Event_RenderingProgram, Tag.c_str());
		glProgramUniform2fv(_Event_RenderingProgram, StatePos, 1, glm::value_ptr(_StateOffSet[i]));
	}

	State->Reload_State_Data(this->_State_Length, this->_StateInfor);
	Update_VertData(this->_StateInfor);
}

void OpenGL_Draw::Update_VertData(glm::ivec2* StateInfor)
{
	GLuint StatePos;
	int State_Length{ (this->_Scene_Int._Coord_Y + this->_PreLoads * 2) * (this->_Scene_Int._Coord_X + this->_PreLoads * 2) + 1 };

	if (State_Length > 400)
		State_Length = 400;

	for (int i{ 0 }; i < State_Length; ++i)
	{
		std::string Tag = "Infor[" + std::to_string(i) + "]";
		StatePos = glGetUniformLocation(_State_RenderingProgram, Tag.c_str());
		glProgramUniform2iv(_State_RenderingProgram, StatePos, 1, glm::value_ptr(StateInfor[i]));

		Tag = "EventInfor[" + std::to_string(i) + "]";
		StatePos = glGetUniformLocation(_Event_RenderingProgram, Tag.c_str());
		glProgramUniform1i(_Event_RenderingProgram, StatePos, StateInfor[i].y);

#if _TANXL_OPENGLDRAW_RELOAD_STATE_DATA_OUTPUT_

		if (StateInfor[i].x != 0)
			Col(StateInfor[i].x);
		else
			Col(0x17);

		std::cout << StateInfor[i].x << "-" << StateInfor[i].y;
		Col();
		if (i % (this->_Scene_Int._Coord_X + this->_PreLoads * 2) == 0)
			std::cout << std::endl;
#endif
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
	this->_Pre_Move._Coord_X = PreMoveX;
	this->_Pre_Move._Coord_Y = PreMoveY;
}

void OpenGL_Draw::Set_DisplaySize(int WindowWidth, int WindowHeight)
{
	this->_Screen_Length._Coord_X = WindowHeight;
	this->_Screen_Length._Coord_Y = WindowWidth;
	glViewport(0, 0, this->_Screen_Length._Coord_X, this->_Screen_Length._Coord_Y);
}

void OpenGL_Draw::Set_Max_Middle_Frame(int Max_Middle_Frame)
{
	this->_Max_Middle_Frame = Max_Middle_Frame;
}

void OpenGL_Draw::Set_Game_Status(EGame_Status Game_Status)
{
	this->_Game_Status = Game_Status;
}

int OpenGL_Draw::Append_Texture(const char* Texture)
{
	const int OffSet{ 4 };
	static unsigned Id{ 0 };

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[Id]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(TanxlOD::textureCoordinates), TanxlOD::textureCoordinates, GL_STATIC_DRAW);

	glActiveTexture(GL_TEXTURE1 + Id + OffSet);

	glBindTexture(GL_TEXTURE_2D, OpenGL_Render::loadTexture(Texture));
	Id++;

	return Id + OffSet;
}

void OpenGL_Draw::HitEdge_Check(GameStateBase* State)
{
	//示例提供八个按键操作事件 （单例模式于其他地方定义）
	InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };

	static double State_Data_Width{ State->Get_DataWidth() * this->_Each_Width * 2 + this->_Each_Width };
	static double State_Data_Height{ State->Get_DataHeight() * this->_Each_Height * 2 + this->_Each_Height };

	static int Exac_Mov{ State->Get_Distance_Move_Id() };

	if (IEB->Get_LastMove_X() < 0)
	{
		if (this->_LCB->Get_LocationX(Exac_Mov) < -static_cast<int>(State->Get_DataWidth()) - 1)
		{
			State->Get_Screen_Distance()._Coord_X = this->_Location_Distance_Mid._Coord_X;
			State->Get_Move_Distance()._Coord_X = this->_Location_Distance_Mid._Coord_X;
#if _TANXL_OPENGLDRAW_EDGE_LIMIT_CHECK_OUTPUT_
			std::cout << "LEFT RES :" << this->_Location_Distance_Mid._Coord_X << "__" << this->_Location_Move_Distance._Coord_X << std::endl;
#endif
		}
		else
		{
			for (int i{ 0 }; i < 2; ++i)
			{
				State->Update_Move(IEB->Get_LastMove_X(), 0.0f, CHECK_EDGE_LEFT);

				if (State->Get_Exac_Location()._Coord_X >= -static_cast<int>(State->Get_DataWidth()) - 1)
					State_Check_Block(State, CHECK_EDGE_LEFT);
			}
		}
		this->_Insert_Status = 0;
		glProgramUniform1i(this->_Adjst_RenderingProgram, 10, this->_Insert_Status);
	}

	if (IEB->Get_LastMove_X() > 0)
	{
		if ((this->_LCB->Get_LocationX(Exac_Mov) > State_Data_Width))
		{
			State->Get_Screen_Distance()._Coord_X = this->_Location_Distance_Mid._Coord_X;
			State->Get_Move_Distance()._Coord_X = this->_Location_Distance_Mid._Coord_X;
#if _TANXL_OPENGLDRAW_EDGE_LIMIT_CHECK_OUTPUT_
			std::cout << "RIGH RES :" << this->_Location_Distance_Mid._Coord_X << "__" << this->_Location_Move_Distance._Coord_X << std::endl;
#endif
		}
		else
		{
			for (int i{ 0 }; i < 2; ++i)
			{
				State->Update_Move(IEB->Get_LastMove_X(), 0.0f, CHECK_EDGE_RIGH);

				if (State->Get_Exac_Location()._Coord_X <= static_cast<int>(State->Get_DataWidth()) * 2 + 1)
					State_Check_Block(State, CHECK_EDGE_RIGH);
			}
		}
		this->_Insert_Status = 1;
		glProgramUniform1i(this->_Adjst_RenderingProgram, 10, this->_Insert_Status);
	}

	if (IEB->Get_LastMove_Y() > 0)
	{
		if ((this->_LCB->Get_LocationY(Exac_Mov) > State->Get_DataHeight() + 1))
		{
			State->Get_Screen_Distance()._Coord_Y = this->_Location_Distance_Mid._Coord_Y;
			State->Get_Move_Distance()._Coord_Y = this->_Location_Distance_Mid._Coord_Y;
#if _TANXL_OPENGLDRAW_EDGE_LIMIT_CHECK_OUTPUT_
			std::cout << "ABOV RES :" << this->_Location_Distance_Mid._Coord_Y << "__" << this->_Location_Move_Distance._Coord_Y << std::endl;
#endif
		}
		else
		{
			for (int i{ 0 }; i < 2; ++i)
			{
				State->Update_Move(0.0f, IEB->Get_LastMove_Y(), CHECK_EDGE_ABOV);

				if (State->Get_Exac_Location()._Coord_Y >= -static_cast<int>(State->Get_DataHeight()) - 1)
					State_Check_Block(State, CHECK_EDGE_ABOV);
			}
		}
		this->_Insert_Status = 2;
		glProgramUniform1i(this->_Adjst_RenderingProgram, 10, this->_Insert_Status);
	}

	if (IEB->Get_LastMove_Y() < 0)
	{
		if (this->_LCB->Get_LocationY(Exac_Mov) < -State_Data_Height)
		{
			State->Get_Screen_Distance()._Coord_Y = this->_Location_Distance_Mid._Coord_Y;
			State->Get_Move_Distance()._Coord_Y = this->_Location_Move_Distance._Coord_Y;
#if _TANXL_OPENGLDRAW_EDGE_LIMIT_CHECK_OUTPUT_
			std::cout << "DOWN RES :" << this->_Location_Distance_Mid._Coord_Y << "__" << this->_Location_Move_Distance._Coord_Y << std::endl;
#endif
		}
		else
		{
			for (int i{ 0 }; i < 2; ++i)
			{
				State->Update_Move(0.0f, IEB->Get_LastMove_Y(), CHECK_EDGE_BELO);

				if (State->Get_Exac_Location()._Coord_Y <= static_cast<int>(State->Get_DataHeight()) * 2 + 1)
					State_Check_Block(State, CHECK_EDGE_BELO);
			}
		}
		this->_Insert_Status = 3;
		glProgramUniform1i(this->_Adjst_RenderingProgram, 10, this->_Insert_Status);
	}
}

void OpenGL_Draw::Move_Adjust(GameStateBase* State)
{
	if (!State->Get_Adjust_Flag() || State->Is_Adjust_While_Move())//Move Adjust Part
	{
		State->Set_Adjust_Flag(true);

		if (_New_Current_Loc._Coord_Y != _Current_Move._Coord_Y)
		{
#if _TANXL_OPENGLDRAW_START_MOVEADJUST_OUTPUT_
			std::cout << "NCUH __ " << _New_Current_Loc._Coord_Y << " CUH __ " << _Current_Move_._Coord_Y << std::endl;
#endif
			int TempVal{ _New_Current_Loc._Coord_Y };
#if _TANXL_OPENGLDRAW_START_MOVEADJUST_OUTPUT_
			std::cout << "NCUH != CUH !State->Get_Adjust_Flag() RELOAD" << std::endl;
#endif
			if (_New_Current_Loc._Coord_Y > _Current_Move._Coord_Y)
			{
				while (_New_Current_Loc._Coord_Y-- > _Current_Move._Coord_Y)
				{
#if _TANXL_OPENGLDRAW_START_MOVEADJUST_OUTPUT_
					std::cout << "Adjust_Flag() __HN---" << State->Get_Adjust_Flag() << std::endl;
#endif
					State->Get_Square_State().Set_Move_State(MoveToNH);
					this->_LCB->Get_LocationY(_State_Loc) -= static_cast<float>(_Each_Height);
				}
			}
			else if (_New_Current_Loc._Coord_Y < _Current_Move._Coord_Y)
			{
				while (_New_Current_Loc._Coord_Y++ < _Current_Move._Coord_Y)
				{
#if _TANXL_OPENGLDRAW_START_MOVEADJUST_OUTPUT_
					std::cout << "Adjust_Flag() __HP___" << State->Get_Adjust_Flag() << std::endl;
#endif
					State->Get_Square_State().Set_Move_State(MoveToPH);
					this->_LCB->Get_LocationY(_State_Loc) += static_cast<float>(_Each_Height);
				}
			}
			_Current_Move._Coord_Y = TempVal;
			_Is_State_Changed = true;
		}

		if (_New_Current_Loc._Coord_X != _Current_Move._Coord_X)
		{
#if _TANXL_OPENGLDRAW_START_MOVEADJUST_OUTPUT_
			std::cout << "NCUW __ " << _New_Current_Loc._Coord_X << " CUW __ " << _Current_Move_._Coord_X << std::endl;
#endif
			int TempVal{ _New_Current_Loc._Coord_X };
#if _TANXL_OPENGLDRAW_START_MOVEADJUST_OUTPUT_
			std::cout << "NCUW != CUW !State->Get_Adjust_Flag() RELOAD" << std::endl;
#endif
			if (_New_Current_Loc._Coord_X > _Current_Move._Coord_X)
			{
				while (_New_Current_Loc._Coord_X-- > _Current_Move._Coord_X)
				{
#if _TANXL_OPENGLDRAW_START_MOVEADJUST_OUTPUT_
					std::cout << "Adjust_Flag() __WN---" << State->Get_Adjust_Flag() << std::endl;
#endif
					State->Get_Square_State().Set_Move_State(MoveToPW);
					this->_LCB->Get_LocationX(_State_Loc) -= static_cast<float>(_Each_Width);
				}
			}
			else if (_New_Current_Loc._Coord_X < _Current_Move._Coord_X)
			{
				while (_New_Current_Loc._Coord_X++ < _Current_Move._Coord_X)
				{
#if _TANXL_OPENGLDRAW_START_MOVEADJUST_OUTPUT_
					std::cout << "Adjust_Flag() __WP---" << State->Get_Adjust_Flag() << std::endl;
#endif
					State->Get_Square_State().Set_Move_State(MoveToNW);
					this->_LCB->Get_LocationX(_State_Loc) += static_cast<float>(_Each_Width);
				}
			}
			_Current_Move._Coord_X = TempVal;
			_Is_State_Changed = true;
		}
	}
}

void OpenGL_Draw::Update_Current()
{
	static GameStateBase* GSB{ &GameStateBase::GetStateBase() };
	this->_New_Current_Loc._Coord_Y = -static_cast<int>((this->_LCB->Get_LocationY(GSB->Get_Distance_Move_Id()) + 2.0f) / _Each_Height);
	this->_New_Current_Loc._Coord_X = -static_cast<int>((this->_LCB->Get_LocationX(GSB->Get_Distance_Move_Id()) - 2.0f) / _Each_Width);
}

void OpenGL_Draw::Update_State(GameStateBase* State, ECheck_Edge Check_Direction)
{
	int State_Unit_Width{ static_cast<int>(State->Get_DataWidth()) + 1 };
	int State_Unit_Height{ static_cast<int>(State->Get_DataHeight()) + 1 };

	int Temp_Height{ this->_New_Current_Loc._Coord_Y };
	int Temp_Width{ this->_New_Current_Loc._Coord_X };

	Update_Current();

	switch (Check_Direction)
	{
	case CHECK_EDGE_LEFT:
		this->_Current_Move._Coord_Y -= (Temp_Height - this->_New_Current_Loc._Coord_Y);
		this->_Current_Move._Coord_X -= (Temp_Width - this->_New_Current_Loc._Coord_X + 1);

		State->Reload_Display_State(STATE_EXTEND_LEFT);
		this->Move_State(State, MoveToNW, State_Unit_Width);
		this->_Is_State_Changed = true;
		break;
	case CHECK_EDGE_RIGH:
		this->_Current_Move._Coord_Y -= (Temp_Height - this->_New_Current_Loc._Coord_Y);
		this->_Current_Move._Coord_X -= (Temp_Width - this->_New_Current_Loc._Coord_X - 1);

		State->Reload_Display_State(STATE_EXTEND_RIGH);
		this->Move_State(State, MoveToPW, State_Unit_Width);
		this->_Is_State_Changed = true;
		break;
	case CHECK_EDGE_BELO:
		this->_Current_Move._Coord_Y -= (Temp_Height - this->_New_Current_Loc._Coord_Y + 1);
		this->_Current_Move._Coord_X -= (Temp_Width - this->_New_Current_Loc._Coord_X);

		State->Reload_Display_State(STATE_EXTEND_BELO);
		this->Move_State(State, MoveToPH, State_Unit_Height);
		this->_Is_State_Changed = true;
		break;
	case CHECK_EDGE_ABOV:
		this->_Current_Move._Coord_Y -= (Temp_Height - this->_New_Current_Loc._Coord_Y - 1);
		this->_Current_Move._Coord_X -= (Temp_Width - this->_New_Current_Loc._Coord_X);

		State->Reload_Display_State(STATE_EXTEND_ABOV);
		this->Move_State(State, MoveToNH, State_Unit_Height);
		this->_Is_State_Changed = true;
		break;
	}
}

void OpenGL_Draw::Update_Last_Location(GameStateBase* State)
{
	static int Dist_Mid{ State->Get_Distance_Screen_Id() };
	this->_Location_Distance_Mid = this->_LCB->Get_LocationS(Dist_Mid);
	this->_Location_Move_Distance = State->Get_Move_Distance();
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
	static const float Check_Range{ 1.0f };
	static double LastTime{ glfwGetTime() };
	double DeltaTime{ glfwGetTime() - LastTime };
	LastTime = glfwGetTime();

	float Marg_Width{ static_cast<float>(this->_Each_Width * 10) };
	float Marg_Height{ static_cast<float>(this->_Each_Height * 10) };

	int State_Unit_Width{ static_cast<int>(State->Get_DataWidth()) + 1 };
	int State_Unit_Height{ static_cast<int>(State->Get_DataHeight()) + 1 };

	bool Reset{ State->Check_Edge_Reached(Check_Direction) };

	if ((State->Get_State() == nullptr) ||
		(State->Get_State()->Get_Extra_Status() == 1))
	{
		switch (Check_Direction)
		{
		case CHECK_EDGE_LEFT:
		case CHECK_EDGE_RIGH:
			State->Get_Screen_Distance()._Coord_X = this->_Location_Distance_Mid._Coord_X;
			State->Get_Move_Distance()._Coord_X = this->_Location_Move_Distance._Coord_X;
			break;
		case CHECK_EDGE_BELO:
		case CHECK_EDGE_ABOV:
			State->Get_Screen_Distance()._Coord_Y = this->_Location_Distance_Mid._Coord_Y;
			State->Get_Move_Distance()._Coord_Y = this->_Location_Move_Distance._Coord_Y;
			break;
		}

		while (true)
		{
			State->Update_Move(0.0f, 0.0f, Check_Direction);
			if ((State->Get_State() == nullptr) ||
				(State->Get_State()->Get_Extra_Status() == 1))
			{
				std::cout << "Adjusting" << std::endl;
				switch (Check_Direction)
				{
				case CHECK_EDGE_LEFT:
					this->_Location_Distance_Mid._Coord_X += static_cast<float>(Check_Range * DeltaTime);
					this->_Location_Move_Distance._Coord_X += static_cast<float>(Check_Range * DeltaTime);

					State->Get_Screen_Distance()._Coord_X = this->_Location_Distance_Mid._Coord_X;
					State->Get_Move_Distance()._Coord_X = this->_Location_Move_Distance._Coord_X;
					break;
				case CHECK_EDGE_RIGH:
					this->_Location_Distance_Mid._Coord_X -= static_cast<float>(Check_Range * DeltaTime);
					this->_Location_Move_Distance._Coord_X -= static_cast<float>(Check_Range * DeltaTime);

					State->Get_Screen_Distance()._Coord_X = this->_Location_Distance_Mid._Coord_X;
					State->Get_Move_Distance()._Coord_X = this->_Location_Move_Distance._Coord_X;
					break;
				case CHECK_EDGE_BELO:
					this->_Location_Distance_Mid._Coord_Y += static_cast<float>(Check_Range * DeltaTime);
					this->_Location_Move_Distance._Coord_Y += static_cast<float>(Check_Range * DeltaTime);

					State->Get_Screen_Distance()._Coord_Y = this->_Location_Distance_Mid._Coord_Y;
					State->Get_Move_Distance()._Coord_Y = this->_Location_Move_Distance._Coord_Y;
					break;
				case CHECK_EDGE_ABOV:
					this->_Location_Distance_Mid._Coord_Y -= static_cast<float>(Check_Range * DeltaTime);
					this->_Location_Move_Distance._Coord_Y -= static_cast<float>(Check_Range * DeltaTime);

					State->Get_Screen_Distance()._Coord_Y = this->_Location_Distance_Mid._Coord_Y;
					State->Get_Move_Distance()._Coord_Y = this->_Location_Move_Distance._Coord_Y;
					break;
				}
			}
			else
				break;
		}
	}
	else if (Reset)
	{
		std::cout << "Enter Adjust Map" << std::endl;

		switch (Check_Direction)
		{
		case CHECK_EDGE_LEFT:
			State->Get_Move_Distance()._Coord_X += Marg_Width;
			break;
		case CHECK_EDGE_RIGH:
			State->Get_Move_Distance()._Coord_X -= Marg_Width;
			break;
		case CHECK_EDGE_BELO:
			State->Get_Move_Distance()._Coord_Y += Marg_Height;
			break;
		case CHECK_EDGE_ABOV:
			State->Get_Move_Distance()._Coord_Y -= Marg_Height;
			break;
		}

		State->Update_Move(0.0f, 0.0f, Check_Direction);

		Update_State(State, Check_Direction);
	}
}

void OpenGL_Draw::State_Check_Event(GameStateBase* State)
{
	static SoundBase* SB{ &SoundBase::GetSoundBase() };
	static Tanxl_Achievement* AC{ &Tanxl_Achievement::Get_AchievementBase() };
	static bool Achievement{ true };
	State->Update_Move(0.0f, 0.0f, CHECK_EDGE_CURR);
	StateUnit* CheckUnit{ State->Get_State() };
	if (!CheckUnit)
		return;
	int Unit_State_Id{ CheckUnit->Get_Extra_Status()};

	AC->CheckAchievement(g_rgAchievements[1]);

	if ((MC->Get_Money() >= 100) && Achievement)
	{
		Achievement = false;
		if (AC->RequestStats())
		{
			std::cout << "Achievement Unlocked !" << std::endl;
			AC->UnlockAchievement(g_rgAchievements[1]);
			SB->Play_Sound(SOUND_ACHIEVEMENT);
		}
		else
		{
			std::cout << "Achievement Request Fail !" << std::endl;
		}
	}

	if (Unit_State_Id == 2)
	{
		if (MC->Get_Is_Alive())
		{
			SB->Play_Sound(SOUND_EVENT_START);
			MC->TakeDamage(1);
			MC->Add_Money(1);

			CheckUnit->Set_Status(0);
			State->Reload_State_Data(this->_State_Length, this->_StateInfor);
			Update_VertData(this->_StateInfor);
		}
	}
	else if (Unit_State_Id == 3)
	{
		SB->Play_Sound(SOUND_RESTORE_HEALTH);
		MC->Add_Money(5);

		CheckUnit->Set_Status(0);
		State->Reload_State_Data(this->_State_Length, this->_StateInfor);
		Update_VertData(this->_StateInfor);
	}
	else if (Unit_State_Id == 4)
	{
		if (MC->Check_Health() < MC->Get_MaxHealth())
		{
			SB->Play_Sound(SOUND_SYSTEM_CALL);
			MC->RestoreHealth(1);
			CheckUnit->Set_Status(0);
			State->Reload_State_Data(this->_State_Length, this->_StateInfor);
			Update_VertData(this->_StateInfor);
		}
	}
	else if (Unit_State_Id == 5)
	{
		static int Internal_Cnt{ 0 };
		Internal_Cnt++;
		SB->Play_Sound(SOUND_SECRET_CORE);
		CheckUnit->Set_Status(0);

		if (Internal_Cnt == 4)
		{
			Internal_Cnt = 0;
			std::cout << "Achievement Unlocked !" << std::endl;
			AC->UnlockAchievement(g_rgAchievements[0]);
			SB->Play_Sound(SOUND_ACHIEVEMENT);
		}

		State->Reload_State_Data(this->_State_Length, this->_StateInfor);
		Update_VertData(this->_StateInfor);

		std::cout << "Secret Core Found !" << std::endl;
	}
	//std::cout << "Health :" << MC->Check_Health() << std::endl;
}

void OpenGL_Draw::Move_State(GameStateBase* State, EMove_State_EventId Direction, int Times)
{
	while (Times--)
		State->Get_Square_State().Set_Move_State(Direction);
	this->_Is_State_Changed = true;
}

void OpenGL_Draw::RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color, int Font_Id)
{
	glUniform3f(0, color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_vao[0]);

	// Iterate through all characters
	for (std::string::const_iterator c{ text.begin() }; c != text.end(); ++c)
	{
		Character ch{ (Font->Get_Characters(Font_Id))[*c] };// Characters[*c];

		GLfloat xpos{ x + ch.Bearing.x * scale };
		GLfloat ypos{ y - (ch.Size.y - ch.Bearing.y) * scale };

		GLfloat w{ ch.Size.x * scale };
		GLfloat h{ ch.Size.y * scale };
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, _Font_vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
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

EGame_Status OpenGL_Draw::Get_Game_Status()
{
	return this->_Game_Status;
}

void OpenGL_Draw::display(GLFWwindow* window, double currentTime, GameStateBase* State)
{
	static GameTips* Tips{ &GameTips::GetTipsBase() };
	static double LastTime{ glfwGetTime() };
	static SoundBase* SB{ &SoundBase::GetSoundBase() };
	static InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };
	double DeltaTime{ glfwGetTime() - LastTime };
	static double Blink_Cnt{ 0 };
	static bool Is_Dead{ false };

	static float VersionFontSize{ 20.0f };

	LastTime = glfwGetTime();

	glBindVertexArray(_vao[1]);

	if (_Clear_Function)
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		this->_Clear_Function = false;
	}

	/*static int x = 0;
	if (x == 0)
	{
		x = 1;
		SB->Play_Sound(SOUND_BACKGROUND_01);
	}
	if(x == 1)
		if (!SB->Sound_Playing(SOUND_BACKGROUND_01))
		{
			SB->Play_Sound(SOUND_BACKGROUND_02);
			x = 2;
		}*/

	//std::cout << "_Draw_Status :" << _Draw_Status << std::endl;
	//std::cout << "_Game_Status :" << _Game_Status << std::endl << std::endl;

	if (_Draw_Status == 5)
	{
		if (this->_Middle_Frame == 0)
		{
			SB->Play_Sound(SOUND_GAME_START);
		}
		this->_Middle_Frame += DeltaTime * 100;
		if (VersionFontSize > -800.0f)
			VersionFontSize -= 6.0f;
		if (VersionFontSize < -800.0f)
			VersionFontSize = -800.0f;

		if (this->_Middle_Frame > this->_Max_Middle_Frame)
		{
			this->_Draw_Status = 1;
		}

		if (this->_Middle_Frame > this->_Max_Middle_Frame / 2.0f)
		{
			this->_Game_Status = GAME_PLAYER_ACTIVE;
			Is_Dead = false;
			glUseProgram(_State_RenderingProgram);
			glDrawArrays(GL_TRIANGLES, 0, (State->Get_StateLength()._Coord_Y + _PreLoads * 2) * (State->Get_StateLength()._Coord_X + _PreLoads * 2) * 6);

			glUseProgram(_Event_RenderingProgram);
			glDrawArrays(GL_TRIANGLES, 0, (State->Get_StateLength()._Coord_Y + _PreLoads * 2) * (State->Get_StateLength()._Coord_X + _PreLoads * 2) * 6);

			glUseProgram(_Adjst_RenderingProgram);
			glDrawArrays(GL_TRIANGLES, 0, (MC->Check_Health() + 2) * 6);
		}
		else
		{
			this->_Game_Status = GAME_START_MENU;
		}

		if (this->_Middle_Frame > this->_Max_Middle_Frame)
		{
			this->_Middle_Frame = 0;
		}
	}
	else if (_Draw_Status == 4)
	{
		if (this->_Middle_Frame > this->_Max_Middle_Frame)
		{
			this->_Draw_Status = 2;
			IEB->Set_Key_Enable(true);
		}

		if (this->_Middle_Frame > this->_Max_Middle_Frame / 2.0f)
		{
			State->Reload_State_Data(this->_State_Length, this->_StateInfor);
			Update_VertData(this->_StateInfor);
			MC->Set_Health(5);
			this->_Game_Status = GAME_START_MENU;
		}
		else
		{
			this->_Game_Status = GAME_PLAYER_ACTIVE;
			//Is_Dead = false;
			glUseProgram(_State_RenderingProgram);
			glDrawArrays(GL_TRIANGLES, 0, (State->Get_StateLength()._Coord_Y + _PreLoads * 2) * (State->Get_StateLength()._Coord_X + _PreLoads * 2) * 6);

			glUseProgram(_Event_RenderingProgram);
			glDrawArrays(GL_TRIANGLES, 0, (State->Get_StateLength()._Coord_Y + _PreLoads * 2) * (State->Get_StateLength()._Coord_X + _PreLoads * 2) * 6);

			glUseProgram(_Adjst_RenderingProgram);
			glDrawArrays(GL_TRIANGLES, 0, (MC->Check_Health() + 2) * 6);
		}

		this->_Middle_Frame += DeltaTime * 100;
	}
	else
	{
		if ((this->_Insert_Status == 3) && (this->_Game_Status == GAME_PLAYER_ACTIVE))
		{
			Blink_Cnt += DeltaTime * 100;
			if (Blink_Cnt > 400)
				Blink_Cnt = 0;
		}

		glProgramUniform1i(this->_Adjst_RenderingProgram, 19, static_cast<int>(Blink_Cnt));

		if (_Draw_Status == 3)
		{
			_Draw_Status = 4;
			this->_Game_Status = GAME_PLAYER_DEAD_STATUS;
			Is_Dead = true;
			SB->Play_Sound(SOUND_GAME_OVER);
			MC->Set_Health(5);
			Tips->Update_Count();
		}

		this->_Middle_Frame = 0;
		glUseProgram(_State_RenderingProgram);
		glDrawArrays(GL_TRIANGLES, 0, (State->Get_StateLength()._Coord_Y + _PreLoads * 2) * (State->Get_StateLength()._Coord_X + _PreLoads * 2) * 6);

		glUseProgram(_Event_RenderingProgram);
		glDrawArrays(GL_TRIANGLES, 0, (State->Get_StateLength()._Coord_Y + _PreLoads * 2) * (State->Get_StateLength()._Coord_X + _PreLoads * 2) * 6);

		glUseProgram(_Adjst_RenderingProgram);
		glDrawArrays(GL_TRIANGLES, 0, (MC->Check_Health() + 2) * 6);
	}

	if (this->_Game_Status == GAME_START_MENU)
	{
		glBindVertexArray(0);
		glBindVertexArray(_vao[2]);
		glUseProgram(_ITest_RenderingProgram);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 30);
		glBindVertexArray(0);
		glBindVertexArray(_vao[1]);

		glUseProgram(_Start_RenderingProgram);
		glProgramUniform1i(_Start_RenderingProgram, 3, this->_Game_Status);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	glProgramUniform1i(this->_Midle_RenderingProgram, 2, static_cast<int>(this->_Middle_Frame));
	glProgramUniform1i(this->_Midle_RenderingProgram, 3, this->_Max_Middle_Frame);

	glUseProgram(_Midle_RenderingProgram);
	glDrawArrays(GL_TRIANGLES, 0, 6 * 30);

	glBindVertexArray(0);

	glBindVertexArray(_vao[0]);

	glUseProgram(_Fonts_RenderingProgram);

	if ((this->_Game_Status == GAME_START_MENU) || (this->_Game_Status == GAME_PLAYER_DEAD_STATUS))
	{
		//std::cout << "Exac :" << IEB->Get_Mouse_Location()._Coord_X << " _ " << IEB->Get_Mouse_Location()._Coord_Y << std::endl;
		if ((IEB->Get_Mouse_Location()._Coord_X > 80) && (IEB->Get_Mouse_Location()._Coord_X < 880) &&
			(IEB->Get_Mouse_Location()._Coord_Y > 450) && (IEB->Get_Mouse_Location()._Coord_Y < 660))
			RenderText(Tips->GetTips(), 70.0f, 250.0f, 0.8f, glm::vec3(0.4, 0.7f, 0.9f));
		else
			RenderText(Tips->GetTips(), 100.0f, 250.0f, 0.7f, glm::vec3(0.3, 0.7f, 0.9f));
	}
	else if (this->_Game_Status == GAME_PLAYER_ACTIVE)
		RenderText("Coins: " + std::to_string(MC->Get_Money()), 750.0f, 630.0f, 0.7f, glm::vec3(0.3, 0.7f, 0.9f), 1);

	if(Is_Dead)
		RenderText("GAME OVER", 310.0f, 650.0f, 1.3f, glm::vec3(0.3, 0.7f, 0.9f), 2);

	if(VersionFontSize > -800.0f)
		RenderText("TANXL GAME VERSION 2.67", VersionFontSize, 10.0f, 1.0f, glm::vec3(
			static_cast<float>(sin(glfwGetTime())) * 0.5f + 0.5f,
			static_cast<float>(cos(glfwGetTime())) * 0.5f + 0.5f,
			0.5f));

	glBindVertexArray(0);
}

void OpenGL_Draw::Render_Once(GameStateBase* State)
{ 
	static InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };//获取输入事件基类
	static Key_Unit* OpenGL_Stop_Key{ new Key_Unit(GLFW_KEY_F) };

	static double LastTime{ glfwGetTime() };
	double MoveScale{ glfwGetTime() - LastTime };
	LastTime = glfwGetTime();

	if (this->_Is_Init_Need)
	{
		this->_Is_Init_Need = false;
		init(State);

		IEB->RegistEvent(OpenGL_Stop_Key);
	}

	glBindVertexArray(_vao[1]);

	if (_Draw_Status == 0)
	{
		if (Check_Key_Press())
		{
			IEB->Init_Default_Key();
			_Draw_Status = 5;
			this->_Middle_Frame = 0;
		}
	}
	else if (_Draw_Status == 2)
	{
		if (Check_Key_Press())
		{
			_Draw_Status = 5;
			this->_Middle_Frame = 0;
		}
	}

	if (!MC->Get_Is_Alive())
	{
		_Draw_Status = 3;
		IEB->Set_Key_Enable(false);
		MC->Pay_Money(MC->Get_Money());
	}

	static int Move_Loc{ this->_LCB->New_Location_set("Move_Adjust_Location") }; //记录手动移动状态的移动距离
	static int Dist_Mid{ State->Get_Distance_Screen_Id() };
	static int Exac_Mov{ State->Get_Distance_Move_Id() };

#if _TANXL_OPENGLDRAW_REALTIME_LOCATION_OUTPUT_
	std::cout << "Move_Loc " << this->_LCB->Get_LocationX(Move_Loc) << " -- " << this->_LCB->Get_LocationY(Move_Loc) << std::endl;
	std::cout << "Dist_Mid " << this->_LCB->Get_LocationX(Dist_Mid) << " -- " << this->_LCB->Get_LocationY(Dist_Mid) << std::endl;
	std::cout << "Exac_Mov " << this->_LCB->Get_LocationX(Exac_Mov) << " -- " << this->_LCB->Get_LocationY(Exac_Mov) << std::endl;// MAJOR
	std::cout << "Stat_Loc " << this->_LCB->Get_LocationX(_State_Loc) << " -- " << this->_LCB->Get_LocationY(_State_Loc) << std::endl << std::endl << std::endl;
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

		glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(_Screen_Length._Coord_X), 0.0f, static_cast<GLfloat>(_Screen_Length._Coord_Y));
		glUseProgram(this->_Fonts_RenderingProgram);
		glUniformMatrix4fv(4, 1, GL_FALSE, glm::value_ptr(projection));

		if ((OpenGL_Stop_Key->MoveToY == true) || (this->_Is_Adjust_Enable == false))
		{
			display(_Main_Window, glfwGetTime(), State);
			glfwSwapBuffers(_Main_Window);
			glfwPollEvents();
			_Current_Status = 1;
			return;
		}

#if _TANXL_OPENGLDRAW_REALTIME_LOCATION_OUTPUT_
		std::cout << "Limit " << State->Get_DataWidth() * this->_Each_Width << " -- "
			<< State->Get_DataHeight() * this->_Each_Height << std::endl;
#endif

		HitEdge_Check(State);

		State_Check_Event(State);

		State->Check_Adjust_Status(IEB->Get_Key_Pressed());

		double Current_Height{ (static_cast<double>(this->_LCB->Get_LocationY(Dist_Mid)) * 2 + 1) / (_Each_Height) };
		double Current_Width{ (static_cast<double>(this->_LCB->Get_LocationX(Dist_Mid)) * 2 + 1) / (_Each_Width) };

		if (State->Get_Adjust_Flag())//Auto Adjust Part
		{
			Temp_MoveY = State->Set_ExacHeight(Current_Height, this->_LCB->Get_LocationY(Dist_Mid), this->_LCB->Get_LocationY(_State_Loc), MoveScale);
			Temp_MoveX = State->Set_ExacWidth(Current_Width, this->_LCB->Get_LocationX(Dist_Mid), this->_LCB->Get_LocationX(_State_Loc), MoveScale);
		}
		
		Move_Adjust(State);

		glProgramUniform1f(_Adjst_RenderingProgram, 2, this->_LCB->Get_LocationX(Dist_Mid) + Temp_MoveX);//Current_Move_LocationX
		glProgramUniform1f(_Adjst_RenderingProgram, 3, this->_LCB->Get_LocationY(Dist_Mid) + Temp_MoveY);//

		if (_Is_State_Changed)
		{
			State->Reload_State_Data(this->_State_Length, this->_StateInfor);
			Update_VertData(this->_StateInfor);
			_Is_State_Changed = false;
		}

		State->StateMove_Edge_Set(Dist_Mid, _State_Loc, Move_Loc, IEB->Get_Reach_Edge(), MoveScale);

		glProgramUniform1f(_State_RenderingProgram, 4, this->_LCB->Get_LocationX(_State_Loc));//State_MoveX
		glProgramUniform1f(_State_RenderingProgram, 5, this->_LCB->Get_LocationY(_State_Loc));//State_MoveY

		glProgramUniform1f(_Event_RenderingProgram, 4, this->_LCB->Get_LocationX(_State_Loc));//State_MoveX
		glProgramUniform1f(_Event_RenderingProgram, 5, this->_LCB->Get_LocationY(_State_Loc));//State_MoveY

		glfwPollEvents();

		display(_Main_Window, glfwGetTime(), State);

		glfwSwapBuffers(_Main_Window);

		glBindVertexArray(0);
	}
	else
	{
		glfwTerminate();
		Destroy_Window();
	}
}

void TanxlOD::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}