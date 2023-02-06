//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2022-09-26 23:24
// ≥ı º∞Ê±æ

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
		Tanxl_Engine_OpenGL_Draw(new OpenGL_Draw) {}
private:
	CONSOLE* Tanxl_Engine_Console_List;
	TANXL_DataBase* Tanxl_Engine_DataBase;
	GameEventBase* Tanxl_Engine_GameEvent;
	GameStateBase* Tanxl_Engine_GameState;
	OpenGL_Draw* Tanxl_Engine_OpenGL_Draw;
};