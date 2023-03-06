//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2022-09-26 23:24
// 初始版本
// 2022/10/4加入两个State模块接口
// 2022/10/10更新地图数据编译接口 增加InsertBase的支持
// 2022/11/07引擎管理模块增加控制移动最大距离的接口

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
	//引擎初始化构造函数
	Tanxl_Engine() :Tanxl_Engine_Console_List(new CONSOLE),
		Tanxl_Engine_DataBase(new TANXL_DataBase(true)),
		Tanxl_Engine_GameEvent(&GameEventBase::GetEventBase()),
		Tanxl_Engine_GameState(&GameStateBase::Get_StateBase(5, 5)),
		Tanxl_Engine_OpenGL_Draw(new OpenGL_Draw),
		Tanxl_Engine_InsertBase(&InsertEventBase::GetInsertBase())
	{
		if (!Tanxl_Engine_Console_List ||
			!Tanxl_Engine_DataBase ||
			!Tanxl_Engine_GameEvent ||
			!Tanxl_Engine_GameState ||
			!Tanxl_Engine_OpenGL_Draw||
			!Tanxl_Engine_InsertBase)
		{
			std::cout << "Fail to start Engine !" << std::endl;
		}
	}

	//Game State Part

	//设置当前显示窗口中的XY轴矩阵数量 Width宽度 Height高度
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

	//根据一串合理的字符串对地图进行生成 Width预设宽度 Height预设高度 Infor地图数据
	void Engine_State_Compile_Uints(int Width, int Height, std::string Infor)
	{
		Tanxl_Engine_GameState->CompileStateUnits(Infor);
		Tanxl_Engine_GameState->Set_DataAll_State(Width, Height);
	}

	//设置是否启用输入移动限制 Eanble启用/关闭自动移动限制 启用后不需要设置后续内容 Max_Height最大移动高度(绝对值) Max_Widtd最大移动宽度(绝对值)
	void Engine_Insert_State_Limit(bool Enable, float Max_Height = 0.0f, float Max_Widtd = 0.0f)
	{
		Tanxl_Engine_InsertBase->Set_StateRange(Enable);
		if (Enable)
		{
			Tanxl_Engine_InsertBase->Set_MaxFloat_Height(Tanxl_Engine_InsertBase->Get_AutoFloat(Tanxl_Engine_GameState->Get_StateHeight()));
			Tanxl_Engine_InsertBase->Set_MaxFloat_Width(Tanxl_Engine_InsertBase->Get_AutoFloat(Tanxl_Engine_GameState->Get_StateWidth()));
		}
		else
		{
			Tanxl_Engine_InsertBase->Set_MaxFloat_Height(Max_Height);
			Tanxl_Engine_InsertBase->Set_MaxFloat_Width(Max_Widtd);
		}
	}

private:
	CONSOLE* Tanxl_Engine_Console_List;
	TANXL_DataBase* Tanxl_Engine_DataBase;
	GameEventBase* Tanxl_Engine_GameEvent;
	GameStateBase* Tanxl_Engine_GameState;
	OpenGL_Draw* Tanxl_Engine_OpenGL_Draw;
	InsertEventBase* Tanxl_Engine_InsertBase;
};