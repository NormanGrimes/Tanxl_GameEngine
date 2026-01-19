#pragma once

#include "Tanxl_OpenGL_Draw.h"

#include <Windows.h>

const static std::string MainVersion{ "2" };
const static std::string SubVersion{ "87" };

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
_Clear_Function(true), _PreLoads(0), _StateInfor(), Tanxl_ClassBase("1.4") {}

const std::string OpenGL_Draw::Get_Version()
{
	return Tanxl_ClassBase::Get_Version();
}

void OpenGL_Draw::init(GameStateBase* State)
{
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	std::string VersionTag{ "Tanxl_GAME /// 0." + MainVersion + "B" + SubVersion };
	_Main_Window = glfwCreateWindow(_Screen_Length._Coord_X, _Screen_Length._Coord_Y, VersionTag.c_str(), NULL, NULL);
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

	this->_State_RenderingProgram = OpenGL_Render::createShaderProgram("Shader/Tanxl_State_01_VertShader.glsl", "Shader/Tanxl_Game_01_FragShader.glsl");
	this->_Adjst_RenderingProgram = OpenGL_Render::createShaderProgram("Shader/Tanxl_Player_01_VertShader.glsl", "Shader/Tanxl_Game_01_FragShader.glsl");
	this->_Start_RenderingProgram = OpenGL_Render::createShaderProgram("Shader/Tanxl_State_02_VertShader.glsl", "Shader/Tanxl_Game_01_FragShader.glsl");
	this->_Midle_RenderingProgram = OpenGL_Render::createShaderProgram("Shader/Tanxl_State_03_VertShader.glsl", "Shader/Tanxl_Game_01_FragShader.glsl");
	this->_ITest_RenderingProgram = OpenGL_Render::createShaderProgram("Shader/Tanxl_Inst_01_VertShader.glsl", "Shader/Tanxl_Game_01_FragShader.glsl");
	this->_Fonts_RenderingProgram = OpenGL_Render::createShaderProgram("Shader/Tanxl_Fonts_01_VertShader.glsl", "Shader/Tanxl_Fonts_01_FragShader.glsl");

	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(_Screen_Length._Coord_X), 0.0f, static_cast<GLfloat>(_Screen_Length._Coord_Y));
	glUseProgram(this->_Fonts_RenderingProgram);
	glUniformMatrix4fv(4, 1, GL_FALSE, glm::value_ptr(projection));

	Font->Set_Language(ECurren_Language::LANGUAGE_ENGLISH/*TI->Get_User_Language()*/);
	Font->Confirm_Language();

	static GameTips* Tips{ &GameTips::GetTipsBase() };
	//Tips->ResetFonts(ECurren_Language::LANGUAGE_CHINESE);

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

	//State_Square Part 0~6  Adjust random range when number of textures change 
	Append_Texture(TanxlOD::TexGrass_01);
	Append_Texture(TanxlOD::TexGrass_02);
	Append_Texture(TanxlOD::TexGrass_Snowy_01);
	Append_Texture(TanxlOD::TexGrass_Snowy_02);
	Append_Texture(TanxlOD::TexOcean_01);
	Append_Texture(TanxlOD::TexDirt_01);
	Append_Texture(TanxlOD::TexCoin_01_64x64);

	int Tex_01{ Append_Texture(TanxlOD::TexPrincess_01)			};
	int Tex_02{ Append_Texture(TanxlOD::TexHealth_01_32x32)		};
	int Tex_03{ Append_Texture(TanxlOD::TexPrincess_01_9x11)	};
	int Tex_04{ Append_Texture(TanxlOD::TexStartMenuLogo_01)	};
	int Tex_05{ Append_Texture(TanxlOD::TexMedic_01_64x64)		};
	int Tex_06{ Append_Texture(TanxlOD::TexSecretCore_01_64x64)	};

	this->_MotionS.push_back(new Motion_Cycle(Tex_01, this));
	this->_MotionS.at(0)->Append_Montion_Image(TanxlOD::TexPrincess_01_Blink_01, 15);
	this->_MotionS.at(0)->Append_Montion_Image(TanxlOD::TexPrincess_01_Blink_02, 10);
	this->_MotionS.at(0)->Append_Montion_Image(TanxlOD::TexPrincess_01_Blink_01, 15);
	this->_MotionS.at(0)->Append_Montion_Image(TanxlOD::TexPrincess_01, 250);

	this->_MotionS.push_back(new Motion_Cycle(Tex_01, this, true));
	this->_MotionS.at(1)->Append_Montion_Image(TanxlOD::TexPrincess_02_Run_01, 2);
	this->_MotionS.at(1)->Append_Montion_Image(TanxlOD::TexPrincess_02_Run_02, 2);
	this->_MotionS.at(1)->Append_Montion_Image(TanxlOD::TexPrincess_02_Run_03, 2);
	this->_MotionS.at(1)->Append_Montion_Image(TanxlOD::TexPrincess_02_Run_04, 2);
	this->_MotionS.at(1)->Append_Montion_Image(TanxlOD::TexPrincess_02_Run_05, 2);
	this->_MotionS.at(1)->Append_Montion_Image(TanxlOD::TexPrincess_02_Run_06, 2);
	this->_MotionS.at(1)->Append_Montion_Image(TanxlOD::TexPrincess_02_Run_07, 2);
	this->_MotionS.at(1)->Append_Montion_Image(TanxlOD::TexPrincess_02_Run_08, 2);
	this->_MotionS.at(1)->Append_Montion_Image(TanxlOD::TexPrincess_02_Run_09, 2);
	this->_MotionS.at(1)->Append_Montion_Image(TanxlOD::TexPrincess_02_Run_10, 2);
	this->_MotionS.at(1)->Append_Montion_Image(TanxlOD::TexPrincess_02_Run_11, 2);
	this->_MotionS.at(1)->Append_Montion_Image(TanxlOD::TexPrincess_02_Run_12, 2);
	this->_MotionS.at(1)->Append_Montion_Image(TanxlOD::TexPrincess_02_Run_13, 2);
	this->_MotionS.at(1)->Append_Montion_Image(TanxlOD::TexPrincess_02_Run_14, 2);
	this->_MotionS.at(1)->Append_Montion_Image(TanxlOD::TexPrincess_02_Run_15, 2);
	this->_MotionS.at(1)->Append_Montion_Image(TanxlOD::TexPrincess_02_Run_16, 2);
	this->_MotionS.at(1)->Append_Montion_Image(TanxlOD::TexPrincess_02_Run_17, 2);
	this->_MotionS.at(1)->Append_Montion_Image(TanxlOD::TexPrincess_02_Run_18, 2);
	this->_MotionS.at(1)->Set_Idle_Image(TanxlOD::TexPrincess_02);

	this->_MotionS.push_back(new Motion_Cycle(Tex_01, this));
	this->_MotionS.at(2)->Set_Idle_Image(TanxlOD::TexPrincess_03);

	this->_MotionS.push_back(new Motion_Cycle(Tex_01, this));
	this->_MotionS.at(3)->Set_Idle_Image(TanxlOD::TexPrincess_04);

	glProgramUniform1i(this->_Adjst_RenderingProgram, 10, Tex_01);
	glProgramUniform1i(this->_Adjst_RenderingProgram, 11, Tex_02);
	glProgramUniform1i(this->_Adjst_RenderingProgram, 12, Tex_03);

	glProgramUniform1i(this->_Start_RenderingProgram, 2, Tex_04);

	glProgramUniform1i(this->_State_RenderingProgram, 8, Tex_05);
	glProgramUniform1i(this->_State_RenderingProgram, 9, Tex_06);

	glBindVertexArray(0);

	glm::vec3 translations[30]{};
	glm::vec4 InstColorA[6]{
		glm::vec4(0.1f, 1.0f, 1.0f, 1.0),
		glm::vec4(0.6f, 0.7f, 1.0f, 1.0),
		glm::vec4(0.6f, 0.7f, 1.0f, 1.0),
		glm::vec4(0.1f, 1.0f, 1.0f, 1.0),
		glm::vec4(0.6f, 0.7f, 1.0f, 1.0),
		glm::vec4(0.6f, 0.7f, 1.0f, 1.0) };
	glm::vec4 InstColorB[6]{
		glm::vec4(1.0f, 1.0f, 0.1f, 1.0),
		glm::vec4(0.9f, 0.7f, 0.6f, 1.0),
		glm::vec4(0.9f, 0.7f, 0.6f, 1.0),
		glm::vec4(1.0f, 1.0f, 0.1f, 1.0),
		glm::vec4(0.9f, 0.7f, 0.6f, 1.0),
		glm::vec4(0.9f, 0.7f, 0.6f, 1.0) };

	int Instance_Cnt{ 0 };
	double BeginHeight{ ((this->_Scene_Int._Coord_Y) / 2.0f) * State->Get_Each_Height() - State->Get_Each_Height() / 2.0f};
	for (int Height{ 0 }; Height < (5); ++Height)
	{
		double BeginWidth{ -((this->_Scene_Int._Coord_X) / 2.0f) * State->Get_Each_Width() + State->Get_Each_Width() / 2.0f};
		for (int Width{ 0 }; Width < (6); ++Width)
		{
			translations[Instance_Cnt].x = static_cast<float>(BeginWidth);
			translations[Instance_Cnt].y = static_cast<float>(BeginHeight);

			if ((Instance_Cnt / 6) % 2 == 1)
				translations[Instance_Cnt].z = static_cast<float>((Instance_Cnt + 1) % 2);
			else
				translations[Instance_Cnt].z = static_cast<float>(Instance_Cnt % 2);

			++Instance_Cnt;
			BeginWidth += State->Get_Each_Width();
		}
		BeginHeight -= State->Get_Each_Height();
	}

	glGenBuffers(1, &_Inst_vbo[1]);
	glBindBuffer(GL_ARRAY_BUFFER, _Inst_vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * 30, &translations[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &_Inst_vbo[2]);
	glBindBuffer(GL_ARRAY_BUFFER, _Inst_vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * 6, &InstColorA[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &_Inst_vbo[3]);
	glBindBuffer(GL_ARRAY_BUFFER, _Inst_vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * 6, &InstColorB[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	float HalfW{ static_cast<float>(State->Get_Each_Width() / 2) };
	float HalfH{ static_cast<float>(State->Get_Each_Height() / 2) };

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
	glGenBuffers(1, &_Inst_vbo[0]);
	glBindVertexArray(_vao[2]);

	glBindBuffer(GL_ARRAY_BUFFER, _Inst_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);// Test VertShader uniform aPos
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(2);// Test VertShader uniform aOffset
	glBindBuffer(GL_ARRAY_BUFFER, _Inst_vbo[1]); // this attribute comes from a different vertex buffer
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(4);// Test VertShader uniform ColorA
	glBindBuffer(GL_ARRAY_BUFFER, _Inst_vbo[2]); // this attribute comes from a different vertex buffer
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(5);// Test VertShader uniform ColorB
	glBindBuffer(GL_ARRAY_BUFFER, _Inst_vbo[3]); // this attribute comes from a different vertex buffer
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1); // tell OpenGL this is an instanced vertex attribute.
	glBindVertexArray(0);

	std::cout << "___" << this->_Scene_Int._Coord_Y << "___" << this->_Scene_Int._Coord_X << "___" << this->_PreLoads << std::endl;

	float Half_Width{ (this->_Scene_Int._Coord_X - 1) / 2.0f };
	float Half_Height{ (this->_Scene_Int._Coord_Y - 1) / 2.0f };

	State->Get_Move_Distance()._Coord_X = (2.0f / this->_Scene_Int._Coord_X) * Half_Width + (1.0f / this->_Scene_Int._Coord_X) * (8 - this->_PreLoads);
	State->Get_Move_Distance()._Coord_Y = -(2.0f / this->_Scene_Int._Coord_Y) * Half_Height - (1.0f / this->_Scene_Int._Coord_Y) * (8 - this->_PreLoads);

	State->Get_Square_State().Set_State_Length(this->_Scene_Int._Coord_X, this->_Scene_Int._Coord_Y);
	State->Get_Square_State().Set_Move_State(this->_Pre_Move._Coord_X, this->_Pre_Move._Coord_Y, this->_PreLoads);

	State->Get_Move_Distance()._Coord_X += static_cast<float>((this->_Pre_Move._Coord_X - 4) * State->Get_Each_Width());
	State->Get_Move_Distance()._Coord_Y -= static_cast<float>((this->_Pre_Move._Coord_Y - 4) * State->Get_Each_Height());

	this->Set_Max_Middle_Frame(200);

	State->Reload_State_Data(this->_PreLoads, this->_StateInfor);
	Update_VertData(this->_StateInfor);
}

void OpenGL_Draw::Update_VertData(glm::ivec2* StateInfor)
{
	int State_Length{ (this->_Scene_Int._Coord_Y + this->_PreLoads * 2) * (this->_Scene_Int._Coord_X + this->_PreLoads * 2) + 1 };

	if (State_Length > 400)
		State_Length = 400;

	for (int i{ 0 }; i < State_Length; ++i)
	{
		std::string Tag{ "Infor[" + std::to_string(i) + "]" };
		GLint StatePos{ glGetUniformLocation(_State_RenderingProgram, Tag.c_str()) };
		glProgramUniform2iv(_State_RenderingProgram, StatePos, 1, glm::value_ptr(StateInfor[i]));

#if _TANXL_OPENGLDRAW_RELOAD_STATE_DATA_OUTPUT_

		if (StateInfor[i].x != 0)
			Col(StateInfor[i].x);
		else
			Col(0x17);

		if(StateInfor[i].y == 1)
			Col(0x04);

		std::cout << StateInfor[i].x << "-" << StateInfor[i].y;
		Col();
		if (i % (this->_Scene_Int._Coord_X + this->_PreLoads * 2) == 0)
			std::cout << std::endl;
#endif
	}
}

int OpenGL_Draw::Append_Texture(const char* Texture, bool InstanceUse)
{
	const int OffSet{ 4 };
	static unsigned Id{ 0 };

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[Id]);

	if (InstanceUse)
		glBufferData(GL_ARRAY_BUFFER, sizeof(TanxlOD::InstanceCoord), TanxlOD::InstanceCoord, GL_STATIC_DRAW);
	else
		glBufferData(GL_ARRAY_BUFFER, sizeof(TanxlOD::textureCoordinates), TanxlOD::textureCoordinates, GL_STATIC_DRAW);

	glActiveTexture(GL_TEXTURE1 + Id + OffSet);

	glBindTexture(GL_TEXTURE_2D, OpenGL_Render::loadTexture(Texture));
	Id++;

	return Id + OffSet;
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

void OpenGL_Draw::Reinit_Texture(int CurrentId, const char* Texture)
{
	const GLuint Id{ static_cast<GLuint>(CurrentId) };

	glDeleteTextures(1, &Id);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[CurrentId]);

	glBufferData(GL_ARRAY_BUFFER, sizeof(TanxlOD::textureCoordinates), TanxlOD::textureCoordinates, GL_STATIC_DRAW);

	glActiveTexture(GL_TEXTURE0 + CurrentId);

	glBindTexture(GL_TEXTURE_2D, OpenGL_Render::loadTexture(Texture));
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

int OpenGL_Draw::Get_Adjust_Status() const
{
	return this->_Current_Status;
}

int OpenGL_Draw::Get_PreLoad() const
{
	return this->_PreLoads;
}

double OpenGL_Draw::Get_DeltaTime() const
{
	return this->_Delta_Time;
}

EGame_Status OpenGL_Draw::Get_Game_Status() const
{
	return this->_Game_Status;
}

void OpenGL_Draw::display(GLFWwindow* window, GameStateBase* State)
{
	static GameTips* Tips{ &GameTips::GetTipsBase() };
	static SoundBase* SB{ &SoundBase::GetSoundBase() };
	static InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };

	static float VersionFontSize{ 20.0f };

	glBindVertexArray(_vao[1]);

	if (_Clear_Function)
	{
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		this->_Clear_Function = false;
	}

	if (_Draw_Status == 5)
	{
		if (this->_Middle_Frame == 0)
		{
			SB->Play_Sound(SOUND_GAME_START);
		}
		this->_Middle_Frame += this->_Delta_Time * 100;
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
			MC->Set_Health(5);

			glProgramUniform1i(this->_State_RenderingProgram, 7, 0);
			glUseProgram(_State_RenderingProgram);
			glDrawArrays(GL_TRIANGLES, 0, (this->_Scene_Int._Coord_Y + _PreLoads * 2) * (this->_Scene_Int._Coord_X + _PreLoads * 2) * 6);

			glProgramUniform1i(this->_State_RenderingProgram, 7, 1);
			glUseProgram(_State_RenderingProgram);
			glDrawArrays(GL_TRIANGLES, 0, (this->_Scene_Int._Coord_Y + _PreLoads * 2) * (this->_Scene_Int._Coord_X + _PreLoads * 2) * 6);

			glUseProgram(_Adjst_RenderingProgram);
			glDrawArrays(GL_TRIANGLES, 0, (MC->Check_Health() + 2) * 6);
		}
		else
		{
			this->_Game_Status = GAME_START_MENU;
		}

		if (this->_Middle_Frame > this->_Max_Middle_Frame)
		{
			VersionFontSize = -800.0f;
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
			State->Reload_State_Data(this->_PreLoads, this->_StateInfor);
			Update_VertData(this->_StateInfor);
			MC->Set_Health(5);
			this->_Game_Status = GAME_START_MENU;
		}
		else
		{
			this->_Game_Status = GAME_PLAYER_DEAD;
			
			glProgramUniform1i(this->_State_RenderingProgram, 7, 0);
			glUseProgram(_State_RenderingProgram);
			glDrawArrays(GL_TRIANGLES, 0, (this->_Scene_Int._Coord_Y + _PreLoads * 2) * (this->_Scene_Int._Coord_X + _PreLoads * 2) * 6);

			glProgramUniform1i(this->_State_RenderingProgram, 7, 1);
			glUseProgram(_State_RenderingProgram);
			glDrawArrays(GL_TRIANGLES, 0, (this->_Scene_Int._Coord_Y + _PreLoads * 2) * (this->_Scene_Int._Coord_X + _PreLoads * 2) * 6);

			glUseProgram(_Adjst_RenderingProgram);
			glDrawArrays(GL_TRIANGLES, 0, (MC->Check_Health() + 2) * 6);
		}

		this->_Middle_Frame += this->_Delta_Time * 100;
	}
	else
	{
		unsigned Insert_Status{ IEB->Get_Insert_Status() };
		if (this->_Game_Status == GAME_PLAYER_ACTIVE)
		{
			static unsigned LastStatus{ Insert_Status };

			if (Insert_Status & 0x01)
				this->_MotionS.at(0)->Start_Motion(this->_Delta_Time * 100);
			else if (Insert_Status & 0x02)
				this->_MotionS.at(1)->Start_Motion(this->_Delta_Time * 100);
			else if (Insert_Status & 0x04)
				this->_MotionS.at(2)->Idle_Image();
			else if (Insert_Status & 0x08)
				this->_MotionS.at(3)->Idle_Image();
			else
			{
				if (LastStatus & 0x01)
					this->_MotionS.at(0)->Start_Motion(this->_Delta_Time * 100);
				if (LastStatus & 0x02)
					this->_MotionS.at(1)->Idle_Image();
			}
			if (Insert_Status != 0)
				LastStatus = Insert_Status;
		}

		if (_Draw_Status == 3)
		{
			_Draw_Status = 4;
			this->_Game_Status = GAME_PLAYER_DEAD;
			SB->Play_Sound(SOUND_GAME_OVER);
			SB->Random_BackGround_Music();
			Tips->Update_Count();
		}

		this->_Middle_Frame = 0;

		glProgramUniform1i(this->_State_RenderingProgram, 7, 0);
		glUseProgram(_State_RenderingProgram);
		glDrawArrays(GL_TRIANGLES, 0, (this->_Scene_Int._Coord_Y + _PreLoads * 2)* (this->_Scene_Int._Coord_X + _PreLoads * 2) * 6);

		glProgramUniform1i(this->_State_RenderingProgram, 7, 1);
		glUseProgram(_State_RenderingProgram);
		glDrawArrays(GL_TRIANGLES, 0, (this->_Scene_Int._Coord_Y + _PreLoads * 2)* (this->_Scene_Int._Coord_X + _PreLoads * 2) * 6);

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

	Font->Bind_FontVAO(_vao[0], _Font_vbo[0]);

	Font->Set_FontColor(glm::vec3(0.3, 0.7f, 0.9f));

	if ((this->_Game_Status == GAME_START_MENU) || (this->_Game_Status == GAME_PLAYER_DEAD))
	{
		//std::cout << "Exac :" << IEB->Get_Mouse_Location()._Coord_X << " _ " << IEB->Get_Mouse_Location()._Coord_Y << std::endl;
		if ((IEB->Get_Mouse_Location()._Coord_X > 80) && (IEB->Get_Mouse_Location()._Coord_X < 880) &&
			(IEB->Get_Mouse_Location()._Coord_Y > 450) && (IEB->Get_Mouse_Location()._Coord_Y < 660))
			Font->RenderText(Tips->GetTips(), 70.0f, 250.0f, 0.8f);
		else
			Font->RenderText(Tips->GetTips(), 100.0f, 250.0f, 0.7f);
	}
	else if (this->_Game_Status == GAME_PLAYER_ACTIVE)
		Font->RenderText(Tips->Get_PlayerCoinName() + ": " + std::to_string(MC->Get_Money()), 750.0f, 630.0f, 0.7f, 1);

	if (!MC->Get_Is_Alive())
		Font->RenderText(Tips->Get_GameOverName(), 280.0f, 650.0f, 1.3f, 2);

	if (VersionFontSize > -800.0f)
	{
		Font->Set_FontColor(glm::vec3(
			static_cast<float>(sin(glfwGetTime())) * 0.5f + 0.5f,
			static_cast<float>(cos(glfwGetTime())) * 0.5f + 0.5f,
			0.5f));
		Font->RenderText(Tips->Get_DisplayVersion() + " " + MainVersion + "." + SubVersion, VersionFontSize, 10.0f, 1.0f);
	}

	glBindVertexArray(0);
}

void OpenGL_Draw::Render_Once(GameStateBase* State)
{
	static InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };//获取输入事件基类
	static Key_Unit* OpenGL_Stop_Key{ new Key_Unit(GLFW_KEY_F) };

	static double LastTime{ glfwGetTime() };
	this->_Delta_Time = glfwGetTime() - LastTime;
	LastTime = glfwGetTime();

	if (this->_Is_Init_Need)
	{
		this->_Is_Init_Need = false;
		IEB->RegistEvent(OpenGL_Stop_Key);
	}

	glBindVertexArray(_vao[1]);

	if (_Draw_Status == 0)
	{
		if (IEB->Check_Key_Press(this->_Main_Window))
		{
			_Draw_Status = 5;
			this->_Middle_Frame = 0;
		}
	}
	else if (_Draw_Status == 2)
	{
		if (IEB->Check_Key_Press(this->_Main_Window))
		{
			_Draw_Status = 5;
			this->_Middle_Frame = 0;
		}
	}

	if ((!MC->Get_Is_Alive()) && (_Draw_Status != 3) && (_Draw_Status != 4))
	{
		_Draw_Status = 3;
		IEB->Set_Key_Enable(false);
		MC->Pay_Money(MC->Get_Money());
	}

	if (!glfwWindowShouldClose(_Main_Window))
	{
		_Current_Status = 0;

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(1);

		glm::mat4 projection{ glm::ortho(0.0f, static_cast<GLfloat>(_Screen_Length._Coord_X), 0.0f, static_cast<GLfloat>(_Screen_Length._Coord_Y)) };
		glUseProgram(this->_Fonts_RenderingProgram);
		glUniformMatrix4fv(4, 1, GL_FALSE, glm::value_ptr(projection));

		if ((OpenGL_Stop_Key->MoveToY == true) || (this->_Is_Adjust_Enable == false))
		{
			display(_Main_Window, State);
			glfwSwapBuffers(_Main_Window);
			glfwPollEvents();
			_Current_Status = 1;
			return;
		}

#if _TANXL_OPENGLDRAW_REALTIME_LOCATION_OUTPUT_
		std::cout << "Limit " << State->Get_DataWidth() * this->_Each_Width << " -- "
			<< State->Get_DataHeight() * this->_Each_Height << std::endl;
#endif

		Tanxl_Coord<float> Temp_Move(State->Auto_Adjust(this->_Delta_Time));

		glProgramUniform1f(_Adjst_RenderingProgram, 2, Temp_Move._Coord_X);//Current_Move_LocationX
		glProgramUniform1f(_Adjst_RenderingProgram, 3, Temp_Move._Coord_Y);//

		State->Reload_State_Data(this->_PreLoads, this->_StateInfor);
		Update_VertData(this->_StateInfor);
		State->StateMove_Edge_Set(IEB->Get_Reach_Edge(), this->_Delta_Time);

		glProgramUniform1f(_State_RenderingProgram, 4, State->Get_State_Loc()._Coord_X);//State_MoveX
		glProgramUniform1f(_State_RenderingProgram, 5, State->Get_State_Loc()._Coord_Y);//State_MoveY

		glfwPollEvents();

		display(_Main_Window, State);

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

int Motion_Cycle::_SLastMotion_Id = 0;
int Motion_Cycle::_SMotions_Count = 0;

Motion_Cycle::Motion_Cycle(int Motion_Id, OpenGL_Draw* DrawEngine, bool Reverse_Cycle) :
	_Motion_Id(Motion_Id), _Motion_Count(0), _MotionS(), _Reverse_Cycle(Reverse_Cycle),
	_DrawEngine(DrawEngine), _Current_Motion_Id(0), _Idle_Image(), _Internal_Id(_SMotions_Count)
{
	this->_SMotions_Count++;
}

Motion_Cycle::~Motion_Cycle()
{
	std::vector<Montion_Struct*>().swap(this->_MotionS);
}

void Motion_Cycle::Append_Montion_Image(const char* Motion_Image, double Delta_Time)
{
	this->_MotionS.push_back(new Montion_Struct(Motion_Image, Delta_Time));
	this->_Motion_Count++;
}

void Motion_Cycle::Start_Motion(double Delta_Time)
{
	static double DeltaTime{};

	if (this->_Internal_Id != this->_SLastMotion_Id)
	{
		this->_Current_Motion_Id = 0;
		DeltaTime = 0;
		this->_DrawEngine->Reinit_Texture(this->_Motion_Id, this->_MotionS.at(this->_Current_Motion_Id)->_Image);
	}
	this->_SLastMotion_Id = this->_Internal_Id;

	DeltaTime += Delta_Time;
	this->_Idle_Status = false;
	if (DeltaTime > this->_MotionS.at(this->_Current_Motion_Id)->_Delta_Time)
	{
		DeltaTime = 0;
		if (this->_Reverse_Cycle)
		{
			if (this->_Direction)
			{
				this->_Current_Motion_Id++;
				if (this->_Current_Motion_Id > (this->_Motion_Count - 1))
				{
					this->_Current_Motion_Id--;
					this->_Direction = false;
				}
			}
			else
			{
				this->_Current_Motion_Id--;
				if (this->_Current_Motion_Id < 0)
				{
					this->_Current_Motion_Id++;
					this->_Direction = true;
				}
			}
		}
		else
		{
			this->_Current_Motion_Id++;
			if (this->_Current_Motion_Id > (this->_Motion_Count - 1))
				this->_Current_Motion_Id = 0;
		}
		this->_DrawEngine->Reinit_Texture(this->_Motion_Id, this->_MotionS.at(this->_Current_Motion_Id)->_Image);
	}
	//std::cout << "this->_Motion_Count :" << this->_Current_Motion_Id << " - " << DeltaTime << std::endl;
}

void Motion_Cycle::Set_Idle_Image(const char* Motion_Image)
{
	this->_Idle_Image = Motion_Image;
}

void Motion_Cycle::Idle_Image()
{
	if (this->_Internal_Id != this->_SLastMotion_Id)
	{
		this->_Idle_Status = false;
	}
	this->_SLastMotion_Id = this->_Internal_Id;

	if (!this->_Idle_Status)
	{
		this->_Idle_Status = true;
		this->_DrawEngine->Reinit_Texture(this->_Motion_Id, this->_Idle_Image);
	}
}

Montion_Struct::Montion_Struct(const char* Image, double Delta_Time) :_Image(Image), _Delta_Time(Delta_Time) {}
