//_VERSION_0_2_ UPDATE LOG
// LAST_UPDATE 2023-02-15 17:06
// 2023/02/15 随机模块纳入引擎管理模块
// 2023/02/15 增加随机地图数据生成功能
// 2023/02/17 增加简化输入按键注册功能
// 2023/02/17 无限世界生成接口默认加入数据整理
// 2023/02/17 设置显示窗口接口增加预载设置
// 2023/02/17 增加绘制窗口与调整预载功能
// 2023/02/21 无限世界生成接口增加数据清理
// 2023/02/22 输出系统信息后删除未整理文件
// 2023/03/01 无限世界接口生成增加一个区块
// 2023/03/01 无限世界接口增加构建连接选项
// 2023/03/08 修复构建连接因借口变动导致的问题
// 2023/03/10 无限世界接口增加自定义数据的支持
// 2023/03/13 启用对STEAM_API的支持
// 2023/03/14 增加宏控制STEAM_API的启用

#pragma once

#ifndef _TANXL_ENGINE_MANAGER_
#define _TANXL_ENGINE_MANAGER_

#define _CRT_SECURE_NO_WARNINGS
# pragma warning (disable:4819)

#define _STEAM_ALPHA_TEST_EDITION_ 0

#include "Tanxl_Console_List.h"
#include "Tanxl_DataBase.h"
#include "Tanxl_GameState.h"
#include "Tanxl_InsertAction.h"
#include "Tanxl_OpenGL_Draw.h"
#include "Tanxl_OpenGL_Render.h"
#include "Tanxl_RandomBase.h"

#include "public/steam/steam_api.h"
#include "public/steam/isteamapps.h"

class Tanxl_Engine
{
public:
	//引擎初始化构造函数
	Tanxl_Engine();

	//设置当前显示窗口中的XY轴矩阵数量 Width宽度 Height高度
	void Engine_State_Set_Display(int Width, int Height, int PreLoads);

	//根据一串合理的字符串对地图进行生成 Width预设宽度 Height预设高度 Infor地图数据
	void Engine_State_Compile_Units(int Width, int Height, std::string Infor);

	//设置是否启用输入移动限制 Eanble启用/关闭自动移动限制 启用后不需要设置后续内容 Max_Height最大移动高度(绝对值) Max_Widtd最大移动宽度(绝对值)
	void Engine_Insert_State_Limit(bool Enable, float Max_Height = 0.0f, float Max_Widtd = 0.0f);

	//设置是否启用移动到达地图边缘化地图随着移动操作而移动 Enable启用/关闭此功能 Mode为true时根据程序中输入操作自动获取 为false时需要设置Compaer_Height/Width为触发的比较值
	void Engine_Insert_Satate_MoveWith(bool Enable, bool Mode, float Compare_Height = 0.0f, float Compare_Width = 1.0f);

	//Enable_Adjust设置是否启用自动调整 Adjust_Value为单次调整的距离 Enable_While_Move为是否启用移动中调整 后两项需要第一项启动才会生效
	void Engine_Adjust_Multi_Set(bool Enable_Adjust, float Adjust_Value, bool Enable_While_Move);

	//向指定文件名称中输出当前系统的综合信息 FileName为输出的目标文件名称 调用此函数后目标文件会被重置
	void Engine_Save_Source_Infor(std::string FileName = "Tanxl Engine VersionMe");

	//选定是否开启游戏世界无限扩展的功能 执行后会自动生成TANXL_STATE_DATA文件并存放256: 16X16个地图单元数据 Build_Connect为true时会额外构建各区块的连接ID
	void Engine_Save_Infinite_State(bool Build_Connect = true, unsigned State_Size = 0xFF, int Width = 16, int Height = 16);

	//提供基本的绘制功能与预加载数据的调整功能 PreLoad_Adjust为预加载调整值
	void Engine_Draw_State_Adjust(int PreLoad_Adjust);

	//注册一个输入按键功能 此按键仅可用于控制物品的移动速度和移动方向 GLFW_KEY为OpenGL定义的按键 Width_Move/Height_Move标记是否在X/Y轴上移动 Move_Length为单次移动距离 返回此按键的ID
	std::string Engine_Insert_Regist_Move(int GLFW_KEY, bool Width_Move, bool Height_Move, double Move_Length);

private:
	CONSOLE* Tanxl_Engine_Console_List;
	TANXL_DataBase* Tanxl_Engine_DataBase;
	GameEventBase* Tanxl_Engine_GameEvent;
	GameStateBase* Tanxl_Engine_GameState;
	OpenGL_Draw* Tanxl_Engine_OpenGL_Draw;
	InsertEventBase* Tanxl_Engine_InsertBase;
	RandomBase* Tanxl_Engine_RandomBase;

	const std::string __ENGINE_VERSION__ = "0.2";
};

#endif