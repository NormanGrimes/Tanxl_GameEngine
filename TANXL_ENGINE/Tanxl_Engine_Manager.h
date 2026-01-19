//_VERSION_0_3_ UPDATE LOG
// LAST_UPDATE 2023-08-23 18:50
// 2023/08/22 无限世界生成接口增加起始位置的设置功能
// 2023/08/31 修复无限世界生成接口需要宽度大于偏置的错误
// 2023/08/31 移除地图生成过程中的地图数据文件生成
// 2023/08/31 简化地图数据设置接口的参数
// 2023/10/12 引擎信息生成接口不再检查上次文件名称
// 2023/10/12 增加匿名结构体存储上次无限世界设置参数
// 2023/10/16 增加对音频模块的支持
// 2023/10/17 增加用于重新生成地图数据与引擎信息的接口
// 2023/10/25 支持STEAMWORKS158SDK
// 2023/11/09 引擎重置接口增加音频模块的操作
// 2023/11/10 增加字体模块的支持
// 2023/11/23 增加音频播放接口
// 2023/12/13 增加析构函数用于输出游戏数据
// 2023/12/13 增加接口用于检测是否需要关闭引擎并退出程序
// 2023/12/13 增加关闭程序后的即时游戏数据输出
// 2023/12/19 增加语言设置接口
// 2023/12/21 增加背景音乐添加和播放的接口
// 2023/12/22 用于接口输出游戏当前地图存档数据信息
// 2024/01/04 修复同时存在两处不同的地图数据的问题
// 2024/01/08 文件数据输出接口增加错误检查
// 2024/01/15 设置显示地图尺寸的接口增加绘制模块的初始化
// 2024/01/17 移除背景音乐正常播放时的无效播放功能调用
// 2024/01/19 增加地图事件与碰撞功能的检测接口
// 2024/01/19 增加接口用于初始化内置的八个按键

#pragma once

#ifndef _TANXL_ENGINE_MANAGER_
#define _TANXL_ENGINE_MANAGER_

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
#include "Tanxl_SoundBase.h"
#include "Tanxl_FontBase.h"

enum class EENGINE_BASES
{
	ENGINE_ALL_SELECTED  =  0,

	ENGINE_CONSOLE_LIST  =  1,
	ENGINE_DATABASE      =  2,
	ENGINE_GAMEEVENT     =  3,
	ENGINE_GAMESTATE     =  4,
	ENGINE_OPENGL_DRAW   =  5,
	ENGINE_INSERTBASE    =  6,
	ENGINE_RANDOMBASE    =  7,
	ENGINE_LOCATIONBASE  =  8,
	ENGINE_OBJECTBASE    =  9,
	ENGINE_FONTBASE      = 10,
	ENGINE_SOUNDBASE     = 11
};

class Tanxl_Engine
{
public:
	//引擎初始化构造函数
	Tanxl_Engine();

	//引擎析构函数
	~Tanxl_Engine();

	//获取当前引擎状态
	unsigned Engine_Check_Engine_Status(bool ShutDown = false);

	//State Part

	//设置当前显示窗口中的XY轴矩阵数量 Width宽度 Height高度
	void Engine_State_Set_Display(int Width, int Height, int PreLoads);

	//根据一串合理的字符串对地图进行生成 Width预设宽度 Height预设高度 Infor地图数据 Extend指定编译的目标区块
	void Engine_State_Compile_Units(int Width, int Height, std::string Infor, EState_Extend Extend = STATE_EXTEND_MIDD);

	//在开启了扩展世界功能的情况下 State_Id用于选定起始区域的ID Is_Begin用于记录是否为起始区块 使用State_Infor的信息覆盖指定ID下的信息
	void Engine_State_Set_Data(int State_Id, bool Is_Begin, std::string State_Infor = "NULL");

	//用于地图的事件与碰撞功能的检测
	void Engine_State_Event_Check();

	//Insert Part

	//设置是否启用输入移动限制 Eanble启用/关闭自动移动限制 启用后不需要设置后续内容 Max_Height最大移动高度(绝对值) Max_Widtd最大移动宽度(绝对值)
	void Engine_Insert_State_Limit(bool Enable, float Max_Height = 0.0f, float Max_Widtd = 0.0f);

	//设置是否启用移动到达地图边缘时地图随着移动操作而移动 Enable启用/关闭此功能 Mode为true时根据程序中输入操作自动获取 为false时需要设置Compaer_Height/Width为触发的比较值
	void Engine_Insert_State_MoveWith(bool Enable, float Compare_Ratio = 1.0f);

	//提供更新绘制部分的手动移动距离值 以及输入按键检测
	void Engine_Insert_State_Update();

	//初始化内置的八个按键功能
	void Engine_Insert_Default_Key();

	//注册一个输入按键功能 此按键仅可用于控制物品的移动速度和移动方向 GLFW_KEY为OpenGL定义的按键 Width_Move/Height_Move标记是否在X/Y轴上移动 Move_Length为单次移动距离 返回此按键的ID
	Key_Unit* Engine_Insert_Regist_Move(int GLFW_KEY, bool Width_Move = false, bool Height_Move = false, double Move_Length = 3);

	//连续调整多个按键单元的移动距离 Start为其在已注册事件容器中的起始位置 End为其结束位置 Adjust_Value为调整的大小 会根据被调整值的正负情况进行对应的调整
	void Engine_Insert_Adjust_Speed(int Start, int End, double Adjust_Value);

	//Data Part

	//向指定文件名称中输出当前系统的综合信息 FileName为输出的目标文件名称 调用此函数后目标文件会被重置
	void Engine_Save_Source_Infor(std::string FileName = "Tanxl Engine VersionMe");

	//选定是否开启游戏世界无限扩展的功能 执行后会自动生成TANXL_STATE_DATA文件并存放256: 16X16个地图单元数据 Build_Connect为true时会额外构建各区块的连接ID Begin_PosX/Y为地图起始左上角坐标
	void Engine_Save_Infinite_State(bool Build_Connect = true, int Width = 16, int Height = 16, int Begin_PosX = 0, int Begin_PosY = 0);

	//用于输出游戏当前地图存档数据信息
	void Engine_Save_Instant_Output();
	
	//用于重新生成地图数据与引擎信息 仅在内存中已有数据时会生效 返回false时清理并生成失败
	bool Engine_Save_Reset_Data();

	//Other

	//Enable_Adjust设置是否启用自动调整 Adjust_Value为单次调整的距离 Enable_While_Move为是否启用移动中调整 后两项需要第一项启动才会生效
	void Engine_Adjust_Multi_Set(bool Enable_Adjust, float Adjust_Value, bool Enable_While_Move);

	//提供基本的绘制功能与预加载数据的调整功能 PreLoad_Adjust为预加载调整值
	void Engine_Draw_State_Adjust(int PreLoad_Adjust);

	//重置指定的引擎基类 将该引擎基类的数据恢复到初始状态 Engine_Class用于指定需要选择重置的基类
	void Engine_Reset_Engine_Base(EENGINE_BASES Engine_Class);
	
	//用于更新STEAM库存并同时检测是否满足掉落条件
	void Engine_Invent_Update_Drop();

	//用于注册移动指定区域触发的地图替换功能 Name为事件名称 LocationX/LocationY为替换的区域坐标 Cover_String为替换的地图数据
	void Engine_Event_State_Regist(std::string Name, int LocationX, int LocationY, std::string Cover_String);

	//用于播放指定的内部音乐 Enable_Current用于启用或关闭音乐 SoundName为选择的音乐枚举
	void Engine_Sound_Play_Sound(bool Enable_Current, ESound_WAV SoundName);

	//用于添加指定的内部音乐作为背景音乐 Enable_Play用于启用或关闭背景音乐的播放
	void Engine_Sound_Add_BackGround(ESound_WAV SoundName, bool Enable_Play = false);

	//设置当前系统显示语言 Language用于指定语言枚举
	void Engine_System_Set_Language(ECurren_Language Language);

	//用于检测是否需要关闭引擎并退出程序
	bool Engine_Should_Shut_Down();

private:
	CONSOLE* Tanxl_Engine_Console_List;
	TANXL_DataBase* Tanxl_Engine_DataBase;
	GameEventBase* Tanxl_Engine_GameEvent;
	GameStateBase* Tanxl_Engine_GameState;
	OpenGL_Draw* Tanxl_Engine_OpenGL_Draw;
	InsertEventBase* Tanxl_Engine_InsertBase;
	LocationBase* Tanxl_Engine_LocationBase;
	GameObjectBase* Tanxl_Engine_ObjectBase;
	Tanxl_Inventory* Tanxl_Engine_Inventory;
	SoundBase* Tanxl_Engine_SoundBase;
	FontBase* Tanxl_Engine_FontBase;

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
	// 0x00A 引擎组件音频模块初始化失败
	// 0x000 未启用扩展世界功能
	// 0x100 已启用扩展世界功能
	unsigned _Engine_Status;

	std::string _Engine_InforFile_Name{ "" };

	struct
	{
		bool _Is_State_Set{ false };
		int _Last_Range_Width{};
		int _Last_Range_Height{};
		int _Last_Begin_Width{};
		int _Last_Begin_Height{};
	}_Engine_Infinite_State_Set;

	const std::string __ENGINE_VERSION__{ "0.3" };
};

#endif