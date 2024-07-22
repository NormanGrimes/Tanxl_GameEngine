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
// 2023/03/08 修复构建连接因接口变动导致的问题
// 2023/03/10 无限世界接口增加自定义数据的支持
// 2023/03/13 启用对STEAM_API的支持
// 2023/03/14 增加宏控制STEAM_API的启用
// 2023/03/20 扩展地图接口增加地图数据尺寸设置
// 2023/03/24 增加引擎状态与引擎状态获取函数
// 2023/03/28 增加坐标基类的支持
// 2023/04/03 增加更新移动与获取输入函数
// 2023/04/14 增加随机与坐标基类的版本信息
// 2023/04/17 修改编译地图数据接口的入参
// 2023/04/28 增加引擎基类的名称枚举
// 2023/05/09 引擎状态检查功能在初始化未完全时自动析构
// 2023/05/09 引擎初始化失败时返回出错组件信息
// 2023/05/09 增加扩展世界设置起始区域的功能
// 2023/05/24 优化引擎状态判断部分
// 2023/05/25 检测引擎状态功能可选是否关闭程序
// 2023/06/12 检测引擎状态功能增加信息显示
// 2023/06/15 增加连续调整多个按键单元的移动距离的接口
// 2023/06/27 无限扩展世界功能移除世界尺寸参数
// 2023/06/27 注册按键功能返回按键指针并增加默认参数
// 2023/06/27 注册按键功能增加非移动按钮注册功能
// 2023/06/30 信息输出功能增加游戏物品版本号输出
// 2023/07/03 设置地图起始区域的功能支持对其他区域进行修改
// 2023/07/03 无限世界设置功能中增加地图区块数量设置
// 2023/07/07 错误检测部分增加新的情况并优化代码
// 2023/07/13 增加对物品模块的支持

#pragma once

#ifndef _TANXL_ENGINE_MANAGER_
#define _TANXL_ENGINE_MANAGER_

#define _CRT_SECURE_NO_WARNINGS
# pragma warning (disable:4819)

#define _STEAM_ALPHA_TEST_EDITION_ 0

// mainCRTStartup

#include "Tanxl_Console_List.h"
#include "Tanxl_DataBase.h"
#include "Tanxl_GameEvent.h"
#include "Tanxl_GameObject.h"
#include "Tanxl_GameState.h"
#include "Tanxl_InsertAction.h"
#include "Tanxl_OpenGL_Draw.h"
#include "Tanxl_OpenGL_Render.h"
#include "Tanxl_RandomBase.h"
#include "Tanxl_LocationBase.h"
#include "Tanxl_SteamService.h"

#include "public/steam/steam_api.h"
#include "public/steam/isteamapps.h"

enum class EENGINE_BASES
{
	ENGINE_ALL_SELECTED  = 0,
	ENGINE_CONSOLE_LIST  = 1,
	ENGINE_DATABASE      = 2,
	ENGINE_GAMEEVENT     = 3,
	ENGINE_GAMESTATE     = 4,
	ENGINE_OPENGL_DRAW   = 5,
	ENGINE_INSERTBASE    = 6,
	ENGINE_RANDOMBASE    = 7,
	ENGINE_LOCATIONBASE  = 8,
	ENGINE_OBJECTBASE    = 9
};

class Tanxl_Engine
{
public:
	//引擎初始化构造函数
	Tanxl_Engine();

	//获取当前引擎状态
	unsigned Engine_Check_Engine_Status(bool ShutDown = false);

	//State Part

	//设置当前显示窗口中的XY轴矩阵数量 Width宽度 Height高度
	void Engine_State_Set_Display(int Width, int Height, int PreLoads);

	//根据一串合理的字符串对地图进行生成 Width预设宽度 Height预设高度 Infor地图数据 Extend指定编译的目标区块
	void Engine_State_Compile_Units(int Width, int Height, std::string Infor, EState_Extend Extend = STATE_EXTEND_MIDD);

	//在开启了扩展世界功能的情况下 State_Id用于选定起始区域的ID Cover_State用于标记是否使用State_Infor的信息覆盖指定ID下的信息
	void Engine_State_Set_Data(int State_Id, bool Cover_State, bool Is_Begin, std::string State_Infor);

	//Insert Part

	//设置是否启用输入移动限制 Eanble启用/关闭自动移动限制 启用后不需要设置后续内容 Max_Height最大移动高度(绝对值) Max_Widtd最大移动宽度(绝对值)
	void Engine_Insert_State_Limit(bool Enable, float Max_Height = 0.0f, float Max_Widtd = 0.0f);

	//设置是否启用移动到达地图边缘化地图随着移动操作而移动 Enable启用/关闭此功能 Mode为true时根据程序中输入操作自动获取 为false时需要设置Compaer_Height/Width为触发的比较值
	void Engine_Insert_Satate_MoveWith(bool Enable, bool Mode, float Compare_Height = 0.0f, float Compare_Width = 1.0f);

	//提供更新绘制部分的手动移动距离值 以及输入按键检测
	void Engine_Insert_State_Update();

	//注册一个输入按键功能 此按键仅可用于控制物品的移动速度和移动方向 GLFW_KEY为OpenGL定义的按键 Width_Move/Height_Move标记是否在X/Y轴上移动 Move_Length为单次移动距离 返回此按键的ID
	Key_Unit* Engine_Insert_Regist_Move(int GLFW_KEY, bool Width_Move = false, bool Height_Move = false, double Move_Length = 3);

	//连续调整多个按键单元的移动距离 Start为其在已注册事件容器中的起始位置 End为其结束位置 Adjust_Value为调整的大小 会根据被调整值的正负情况进行对应的调整
	void Engine_Insert_Adjust_Speed(int Start, int End, double Adjust_Value);

	//Data Part

	//向指定文件名称中输出当前系统的综合信息 FileName为输出的目标文件名称 调用此函数后目标文件会被重置
	void Engine_Save_Source_Infor(std::string FileName = "Tanxl Engine VersionMe");

	//选定是否开启游戏世界无限扩展的功能 执行后会自动生成TANXL_STATE_DATA文件并存放256: 16X16个地图单元数据 Build_Connect为true时会额外构建各区块的连接ID
	void Engine_Save_Infinite_State(bool Build_Connect = true, int Width = 16, int Height = 16);

	//Other

	//Enable_Adjust设置是否启用自动调整 Adjust_Value为单次调整的距离 Enable_While_Move为是否启用移动中调整 后两项需要第一项启动才会生效
	void Engine_Adjust_Multi_Set(bool Enable_Adjust, float Adjust_Value, bool Enable_While_Move);

	//提供基本的绘制功能与预加载数据的调整功能 PreLoad_Adjust为预加载调整值
	void Engine_Draw_State_Adjust(int PreLoad_Adjust);

	//重置指定的引擎基类 将该引擎基类的数据恢复到初始状态 Engine_Class用于指定需要选择重置的基类
	void Engine_Reset_Engine_Base(EENGINE_BASES Engine_Class);

private:
	CONSOLE* Tanxl_Engine_Console_List;
	TANXL_DataBase* Tanxl_Engine_DataBase;
	GameEventBase* Tanxl_Engine_GameEvent;
	GameStateBase* Tanxl_Engine_GameState;
	OpenGL_Draw* Tanxl_Engine_OpenGL_Draw;
	InsertEventBase* Tanxl_Engine_InsertBase;
	RandomBase* Tanxl_Engine_RandomBase;
	LocationBase* Tanxl_Engine_LocationBase;
	GameObjectBase* Tanxl_Engine_ObjectBase;

	unsigned _Engine_Status;
	//Status :
	// 0x001 引擎组件控制台列表初始化失败
	// 0x002 引擎组件数据库初始化失败
	// 0x003 引擎组件游戏事件初始化失败
	// 0x004 引擎组件游戏地图初始化失败
	// 0x005 引擎组件绘制模块初始化失败
	// 0x006 引擎组件输入模块初始化失败
	// 0x007 引擎组件随机模块初始化失败
	// 0x008 引擎组件坐标模块初始化失败
	// 0x009 引擎组件物品模块初始化失败
	// 0x009 STEAM启动检测失败
	// 0x00A STEAM API初始化失败
	// 0x000 未启用扩展世界功能
	// 0x100 已启用扩展世界功能

	const std::string __ENGINE_VERSION__ = "0.2";
};

#endif