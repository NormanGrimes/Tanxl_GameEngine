//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2022-09-26 23:24
// 初始版本
// 2022/10/4加入两个State模块接口

#pragma once

#ifndef TANXL_CONSOLE_LIST
#define TANXL_CONSOLE_LIST
#include "Tanxl_Console_List.h"
#endif

#ifndef TANXL_DATABASE
#define TANXL_DATABASE
#include "Tanxl_DataBase.h"
#endif

#ifndef TANXL_GAMESTATE
#define TANXL_GAMESTATE
#include "Tanxl_GameState.h"
#endif

#ifndef TANXL_INSERTACTION
#define TANXL_INSERTACTION
#include "Tanxl_InsertAction.h"
#endif

#ifndef TANXL_OPENGL_DRAW
#define TANXL_OPENGL_DRAW
#include "Tanxl_OpenGL_Draw.h"
#endif

#ifndef TANXL_OPENGL_RENDER
#define TANXL_OPENGL_RENDER
#include "Tanxl_OpenGL_Render.h"
#endif

class Tanxl_Engine
{
public:
	Tanxl_Engine() :Tanxl_Engine_Console_List(new CONSOLE), 
		Tanxl_Engine_DataBase(new TANXL_DataBase(true)), 
		Tanxl_Engine_GameEvent(&GameEventBase::GetEventBase()), 
		Tanxl_Engine_GameState(&GameStateBase::Get_StateBase(5, 5)),
		Tanxl_Engine_OpenGL_Draw(new OpenGL_Draw) 
	{
		if (!Tanxl_Engine_Console_List ||
			!Tanxl_Engine_DataBase ||
			!Tanxl_Engine_GameEvent ||
			!Tanxl_Engine_GameState ||
			!Tanxl_Engine_OpenGL_Draw)
		{
			std::cout << "Fail to start Engine !" << std::endl;
		}
	}

	//Game State Part

	void Engine_State_Set_Display(int Width, int Height)
	{
		static int ReservWidth = 5;
		static int ReservHeight = 5;
		Tanxl_Engine_GameState->Get_StateBase(ReservWidth, ReservHeight);

		if (ReservWidth != Width || ReservHeight != Height)
		{
			Tanxl_Engine_GameState->Set_Display_State(Width, Height);
			ReservWidth = Width;
			ReservHeight = Height;
		}
	}

	void Engine_State_Compile_Uints(std::string Infor)
	{
		Tanxl_Engine_GameState->CompileStateUnits(Infor);
	}

private:
	CONSOLE* Tanxl_Engine_Console_List;
	TANXL_DataBase* Tanxl_Engine_DataBase;
	GameEventBase* Tanxl_Engine_GameEvent;
	GameStateBase* Tanxl_Engine_GameState;
	OpenGL_Draw* Tanxl_Engine_OpenGL_Draw;
};