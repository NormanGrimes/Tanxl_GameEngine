#pragma once

#include "Tanxl_OpenGL_Draw.h"

GLuint vbo[1];

GLuint brickTexture;

OpenGL_Draw& OpenGL_Draw::GetOpenGLBase(int ScreenWidth, int ScreenHeight)
{
	static OpenGL_Draw* OGD = new OpenGL_Draw(ScreenWidth, ScreenHeight);
	return *OGD;
}

OpenGL_Draw::OpenGL_Draw(int ScreenWidth, int ScreenHeight) :_HeightInt(0), _StateInfor(),_WidthInt(0),
_renderingProgram(0), _vao(), _ScreenWidth(ScreenWidth), _ScreenHeight(ScreenHeight), _Main_Window(NULL),
_Clear_Function(true), _Is_State_Changed(false), _PreLoads(0), _State_MoveX(0.0f), _State_MoveY(0.0f), _First_Adjust(0){}

const std::string OpenGL_Draw::Get_Version()
{
	return this->_Version;
}

void OpenGL_Draw::init(GLFWwindow* window, GameStateBase* State)
{
	//示例提供四个按键操作事件 （单例模式于其他地方定义）
	UniqueIdBase* UIB{ &UniqueIdBase::GetIdGenerator() };

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

	_HeightInt = State->Get_StateHeight();
	_WidthInt = State->Get_StateWidth();

	_Auto_AdjustX = 0.0f;
	_Auto_AdjustY = 0.0f;

	_Move_AdjustX = 0.0f;
	_Move_AdjustY = 0.0f;

	_Each_Height = 2.0f / State->Get_StateHeight();//10 0.2
	_Each_Width = 2.0f / State->Get_StateWidth();//10 0.2

	_Current_Move_Height = 0;
	_Current_Move_Width = 0;
	
	State->Set_Move_State(0, _HeightInt - 1 + _PreLoads, 0, _WidthInt - 1 + _PreLoads);

	_renderingProgram = OpenGL_Render::createShaderProgram("vertShader.glsl", "fragShader.glsl");
	glGenVertexArrays(1, _vao);
	glBindVertexArray(_vao[0]);
	glGenBuffers(1, vbo);

	glProgramUniform1i(_renderingProgram, 6, _HeightInt);//SHeight
	glProgramUniform1i(_renderingProgram, 7, _WidthInt);//SWidth
	glProgramUniform1f(_renderingProgram, 3, 1.0f);//Margin
	glProgramUniform1i(_renderingProgram, 10, _PreLoads);//PreLoads

	float textureCoordinates[] =
	{	
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 1.0f,
	};
	
	brickTexture = OpenGL_Render::loadTexture("Texture/grass.jpg");

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordinates), textureCoordinates, GL_STATIC_DRAW);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, brickTexture);

	glDrawArrays(GL_TRIANGLES, 0, (State->Get_StateHeight() + _PreLoads)* (State->Get_StateWidth() + _PreLoads) * 6 + 6);

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
			if (Move_PX < 0 || static_cast<unsigned>(Move_NX) > State->Get_DataWidth() || //现阶段Data宽度不可能导致转换溢出
				Move_PY < 0 || static_cast<unsigned>(Move_NY) > State->Get_DataHeight())
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
		for (int i = 0; i < (_HeightInt + _PreLoads) * (_WidthInt + _PreLoads); ++i)
		{
			_StateInfor[i] = UIB->Random(0, 2) - 1;
		}
	}
	GLuint StatePos;
	for (int i = 0; i < (State->Get_StateHeight() + _PreLoads) * (State->Get_StateWidth() + _PreLoads) + 1; ++i)
	{
		std::string Tag = "State[" + std::to_string(i) + "]";
		StatePos = glGetUniformLocation(_renderingProgram, Tag.c_str());
		glProgramUniform1i(_renderingProgram, StatePos, _StateInfor[i]);
	}
}

GLFWwindow* OpenGL_Draw::Get_Window()const
{
	return this->_Main_Window;
}

void OpenGL_Draw::UpdateMargin(float& Margin)
{
	glProgramUniform1f(_renderingProgram, 3, Margin);//Margin
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
	static bool First_Time = true;

	float Temp_MoveX = 0.0f;
	float Temp_MoveY = 0.0f;

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

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, brickTexture);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		int NCUH = static_cast<int>(_Move_AdjustY / _Each_Height);
		int NCUW = static_cast<int>(_Move_AdjustX / _Each_Width);

		static int ACUH = static_cast<int>(_Auto_AdjustY / _Each_Height);
		static int ACUW = static_cast<int>(_Auto_AdjustX / _Each_Width);

		static int ANCUH = static_cast<int>(_Auto_AdjustY / _Each_Height);
		static int ANCUW = static_cast<int>(_Auto_AdjustX / _Each_Width);

		int TOCUH = static_cast<int>((_Move_AdjustY * 2) / _Each_Height);
		int TOCUW = static_cast<int>((_Move_AdjustX * 2) / _Each_Height);

		//std::cout << "TOUCH " << TOCUH << " -- TOCUW " << TOCUW << std::endl;

		if (State->Get_Adjust_Flag())
		{
			ANCUH = static_cast<int>(_Auto_AdjustY / _Each_Height);
			ANCUW = static_cast<int>(_Auto_AdjustX / _Each_Width);
		}

		static int Wait_Frame = 0;

		//std::cout << "FLAG ----------------------------B"<< State->Get_Adjust_Flag() << std::endl;

		IEB->GetInsert(_Main_Window, State->Get_Current_Distance()._LocX, State->Get_Current_Distance()._LocY, _State_MoveX, _State_MoveY, _Move_AdjustX, _Move_AdjustY);//获取输入

		//std::cout << "DEPT -----------------------------" << MDeptVX << "____" << MDeptVY << std::endl;
		//std::cout << "REAL -----------------------------" << MoveX << "____" << MoveY << std::endl;
		//std::cout << "FLAG ----------------------------A" << State->Get_Adjust_Flag() << std::endl;

		if (!State->Get_Adjust_While_Move())
		{
			if (IEB->Get_Key_Pressed())
				State->Set_Adjust_Flag(false);
			else
				State->Set_Adjust_Flag(true);
		}

		//GSB->Set_CurrentLoc(MoveX, MoveY);//更新地图中心点/当前移动物品坐标

		double Current_Height = (State->Get_Current_Distance()._LocY * 2 + 1) / (_Each_Height);
		double Current_Width = (State->Get_Current_Distance()._LocX * 2 + 1) / (_Each_Width);

		//std::cout << "CUH/CUW" << State->Get_Current_Distance()._LocY << "__" << State->Get_Current_Distance()._LocX << std::endl;

		if (State->Get_Adjust_Flag())
		{
			Temp_MoveY = State->Set_ExacHeight(Current_Height, &State->Get_Current_Distance()._LocY, &_State_MoveY, &_Auto_AdjustY);
			Temp_MoveX = State->Set_ExacWidth(Current_Width, &State->Get_Current_Distance()._LocX, &_State_MoveX, &_Auto_AdjustX);
			Wait_Frame = 0;
			
			if (ANCUH != ACUH)
			{
				std::cout << "ANCUH __ " << ANCUH << " ACUH __ " << ACUH << std::endl;
				int TempVal = ANCUH;
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
				int TempVal = ANCUW;
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
				int TempVal = NCUH;
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
				int TempVal = NCUW;
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

		glProgramUniform1f(_renderingProgram, 4, State->Get_Current_Distance()._LocX + Temp_MoveX);//Current_Move_LocationX
		glProgramUniform1f(_renderingProgram, 5, State->Get_Current_Distance()._LocY + Temp_MoveY);//Current_Move_LocationY

		if (_Is_State_Changed)
		{
			ReLoadState(State);
			_Is_State_Changed = false;
		}
		//std::cout << "Current BLOCK : " << CUH << " " << CUW << std::endl;
		//std::cout << "Exac Location : " << MoveX * 2 << " " << MoveY * 2 << std::endl;//REAL LOCATION

		glProgramUniform1f(_renderingProgram, 8, _State_MoveX);//State_MoveX
		glProgramUniform1f(_renderingProgram, 9, _State_MoveY);//State_MoveY

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