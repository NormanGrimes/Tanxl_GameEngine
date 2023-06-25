//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2022-09-26 23:24
// 初始版本
// 2022/10/4加入两个State模块接口
// 2022/10/10更新地图数据编译接口 增加InsertBase的支持
// 2022/11/07引擎管理模块增加控制移动最大距离的接口
// 2022/12/27修改头文件包含方式
// 2023/01/06增加引擎信息存储功能
// 2023/01/19增加随移动操作移动地图的功能
// 2023/01/29操作移动地图的功能增加自动获取的方式

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
	Tanxl_Engine();

	//设置当前显示窗口中的XY轴矩阵数量 Width宽度 Height高度
	void Engine_State_Set_Display(int Width, int Height);

	//根据一串合理的字符串对地图进行生成 Width预设宽度 Height预设高度 Infor地图数据
	void Engine_State_Compile_Uints(int Width, int Height, std::string Infor);

	//设置是否启用输入移动限制 Eanble启用/关闭自动移动限制 启用后不需要设置后续内容 Max_Height最大移动高度(绝对值) Max_Widtd最大移动宽度(绝对值)
	void Engine_Insert_State_Limit(bool Enable, float Max_Height = 0.0f, float Max_Widtd = 0.0f);

	//设置是否启用移动到达地图边缘化地图随着移动操作而移动 Enable启用/关闭此功能 Mode为true时根据程序中输入操作自动获取 为false时需要设置Compaer_Height/Width为触发的比较值
	void Engine_Insert_Satate_MoveWith(bool Enable, bool Mode, float Compare_Height = 0.0f, float Compare_Width = 1.0f);

	//Enable_Adjust设置是否启用自动调整 Adjust_Value为单次调整的距离 Enable_While_Move为是否启用移动中调整 后两项需要第一项启动才会生效
	void Engine_Adjust_Multi_Set(bool Enable_Adjust, float Adjust_Value, bool Enable_While_Move);

	//向指定文件名称中输出当前系统的综合信息 FileName为输出的目标文件名称 调用此函数后目标文件会被重置
	void Engine_Save_Source_Infor(std::string FileName);

private:
	CONSOLE* Tanxl_Engine_Console_List;
	TANXL_DataBase* Tanxl_Engine_DataBase;
	GameEventBase* Tanxl_Engine_GameEvent;
	GameStateBase* Tanxl_Engine_GameState;
	OpenGL_Draw* Tanxl_Engine_OpenGL_Draw;
	InsertEventBase* Tanxl_Engine_InsertBase;
};

#endif