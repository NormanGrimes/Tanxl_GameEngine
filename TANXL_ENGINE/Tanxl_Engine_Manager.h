//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2022-09-26 23:24
// 初始版本
// 2022/10/4加入两个State模块接口
// 2022/10/10更新地图数据编译接口 增加InsertBase的支持
// 2022/11/07引擎管理模块增加控制移动最大距离的接口
// 2022/12/27修改头文件包含方式

#pragma once

#ifndef _TANXL_ENGINE_MANAGER_
#define _TANXL_ENGINE_MANAGER_

#include "Tanxl_Console_List.h"
#include "Tanxl_DataBase.h"
#include "Tanxl_GameState.h"
#include "Tanxl_InsertAction.h"
#include "Tanxl_OpenGL_Draw.h"
#include "Tanxl_OpenGL_Render.h"

class Tanxl_Engine
{
public:
	//引擎初始化构造函数
	Tanxl_Engine() :Tanxl_Engine_Console_List(new CONSOLE),
		Tanxl_Engine_DataBase(new TANXL_DataBase(true)),
		Tanxl_Engine_GameEvent(&GameEventBase::GetEventBase()),
		Tanxl_Engine_GameState(&GameStateBase::Get_StateBase(5, 5)),
		Tanxl_Engine_OpenGL_Draw(&OpenGL_Draw::GetOpenGLBase()),
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

	//Enable_Adjust设置是否启用自动调整 Adjust_Value为单次调整的距离 Enable_While_Move为是否启用移动中调整 后两项需要第一项启动才会生效
	void Engine_Adjust_Multi_Set(bool Enable_Adjust, float Adjust_Value, bool Enable_While_Move)
	{
		Tanxl_Engine_GameState->Set_Enable_Adjust(Enable_Adjust);
		Tanxl_Engine_GameState->Set_Adjust(Adjust_Value);
		Tanxl_Engine_OpenGL_Draw->Set_Adjust_While_Move(Enable_While_Move);
	}

private:
	CONSOLE* Tanxl_Engine_Console_List;
	TANXL_DataBase* Tanxl_Engine_DataBase;
	GameEventBase* Tanxl_Engine_GameEvent;
	GameStateBase* Tanxl_Engine_GameState;
	OpenGL_Draw* Tanxl_Engine_OpenGL_Draw;
	InsertEventBase* Tanxl_Engine_InsertBase;
};

#endif