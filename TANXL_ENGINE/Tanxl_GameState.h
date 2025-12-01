//_VERSION_1_1_ UPDATE LOG
// LAST_UPDATE 2023-10-08 14:46
// 单一连接功能修复未能构建双向连接的问题
// 单一连接功能增加溢出的处理
// 移除获取地图尺寸获取功能
// 移除获取扩展世界是否开启的功能
// 序列号定位地图数据的功能增加错误处理
// 修复右边构建连接指向了错误坐标的问题
// 移除地图横向与纵向区块个数的获取接口
// 地图基础类改为继承自引擎基础类
// 移除扩展世界启用标记以及设置函数
// 移除无参数版本的地图生成函数
// 获取地图范围接口效率改进
// 将三个地图矩形区域设置接口移动到结构体中
// 矩形地图结构体增加地图宽度与高度的设置接口
// 增加无参数版本地图单元获取接口
// 地图精确坐标改为坐标模板实现
// 移除调整等待帧的所有设定
// 新增扩展地图替换接口
// 扩展地图结构体增加字符串数据获取接口
// 析构地图数据时保留对地图的更改
// 修复新添加的地图单元构建连接失败的问题
// 构建连接功能效率优化
// 单一连接接口不再返回连接对象的序列号
// 优化枚举设置显示矩阵的接口
// 合并获取地图需要绘制的高度与宽度接口
// 移动绘制模块部分代码组成检测是否到达边缘的接口
// 增加宏控制地图生成信息的输出
// 增加根据输入状态控制地图调整的功能
// 增加获取当前地图数据的接口
// 移除地图中心点的记录
// 多个接口性能优化
// 微调地图功能去掉一个参数
// 地图微调功能性能优化
// 单元检测接口修复一个可导致死循环的问题
// 提升碰撞功能动态计算的稳定性
// 效率改进并移除部分不必要的接口
// 地图微调接口改为私有
// 新增简化版自动调整接口
// 多个成员函数设为常量
// 屏幕边缘移动接口减少参数
// 去掉地图改变相关的参数
// 移除多个绘制模块相关的返回值

#pragma once

#ifndef _TANXL_GAMESTATE_
#define _TANXL_GAMESTATE_

#define _ENABLE_TANXL_GAMESTATE_CONSOLE_OUTPUT_ 0

#if _ENABLE_TANXL_GAMESTATE_CONSOLE_OUTPUT_

#define _TANXL_GAMESTATE_SETEXAC_LOCATION_OUTPUT_     0
#define _TANXL_GAMESTATE_UPDATE_MOVE_OUTPUT_          0
#define _TANXL_GAMESTATE_TRIGGER_LIMIT_CHECK_OUTPUT_  0
#define _TANXL_GAMESTATE_CONNECT_DEBUG_OUTPUT_        1
#define _TANXL_GAMESTATE_LINK_SEARCH_DATA_OUTPUT_     0
#define _TANXL_GAMESTATE_RELOAD_STATE_SQUARE_OUTPUT_  0
#define _TANXL_GAMESTATE_GENERATE_STATE_OUTPUT_       1
#define _TANXL_GAMESTATE_START_MOVEADJUST_OUTPUT_     0
#define _TANXL_GAMESTATE_EDGE_LOCATION_VALUE_OUTPUT_  0
#define _TANXL_GAMESTATE_EDGE_LIMIT_CHECK_OUTPUT_     0

#endif

#include <iostream>
#include <iomanip>

#include "Tanxl_GameEvent.h"
#include "Tanxl_DataBase.h"
#include "Tanxl_LocationBase.h"
#include "Tanxl_RandomBase.h"
#include "Tanxl_EngineBase.h"
#include "Tanxl_OpenGL_Render.h"
#include "Tanxl_GameObject.h"
#include "Tanxl_SoundBase.h"
#include "Tanxl_SteamService.h"
#include "Tanxl_GameObject.h"

class StateUnit;

enum EMove_State_EventId
{
	MoveToNO   = 0,
	MoveToNW   = 1,
	MoveToPW   = 2,
	MoveToNH   = 4,
	MoveToNWNH = 5,
	MoveToPWNH = 6,
	MoveToPH   = 8,
	MoveToNWPH = 9,
	MoveToPWPH = 10
};

enum EState_Point
{
	STATE_ID_LEFT_ABOVE  = 0,
	STATE_ID_ABOVE       = 1,
	STATE_ID_RIGHT_ABOVE = 2,
	STATE_ID_LEFT        = 3,
	STATE_ID_MID         = 4,
	STATE_ID_RIGHT       = 5,      
	STATE_ID_LEFT_BELOW  = 6,
	STATE_ID_BELOW       = 7,
	STATE_ID_RIGHT_BELOW = 8
};

enum ECheck_Edge
{
	CHECK_EDGE_CURR,
	CHECK_EDGE_LEFT,
	CHECK_EDGE_RIGH,
	CHECK_EDGE_BELO,
	CHECK_EDGE_ABOV
};

enum EState_Extend
{
	STATE_EXTEND_SPEC      = 0,

	STATE_EXTEND_MIDD      = 1,
	STATE_EXTEND_LEFT      = 2,
	STATE_EXTEND_RIGH      = 3,
	STATE_EXTEND_ABOV      = 4,
	STATE_EXTEND_BELO	   = 5,
	STATE_EXTEND_LEFT_ABOV = 6,
	STATE_EXTEND_LEFT_BELO = 7,
	STATE_EXTEND_RIGH_ABOV = 8,
	STATE_EXTEND_RIGH_BELO = 9
};

enum EState_Current
{
	STATE_LEFT = 3,
	STATE_RIGH = 2,
	STATE_ABOV = 5,
	STATE_BELO = 4,
	STATE_LEFT_ABOV = 9,
	STATE_LEFT_BELO = 8,
	STATE_RIGH_ABOV = 7,
	STATE_RIGH_BELO = 6
};

struct Square_State
{
public:
	Square_State(int NX = 0, int PX = 0, int NY = 0, int PY = 0, int StateWidth = 0, int StateHeight = 0);

	//↓Set_Move_State : 设置在绘制时显示的矩阵区域
	void Set_Move_State(int PreSetX, int PreSetY, int PreLoad);
	void Set_Move_State(int NX, int PX, int NY, int PY);
	void Set_Move_State(EMove_State_EventId Event_Id, int Multi_Set = 1);

	void Set_State_Length(int Width, int Height);

	int _Move_NX;
	int _Move_PX;
	int _Move_NY;
	int _Move_PY;
private:
	int _State_Width;
	int _State_Height;
};

struct State_Policy
{
	State_Policy(std::string Name, int State_Status);
	std::string _Name;
	int _State_Status;
};

struct SExtend_State
{
	SExtend_State(std::string Id = "NULL", std::vector<StateUnit*>* Data = nullptr);

	std::string Get_Stand_Data();
	std::string _Id;
	std::vector<StateUnit*>* _Data;
};

class StateEvent
{
public:
	StateEvent(int State_Id, int Counts);
	bool Check_State_Id(int State_Id);
	bool Check_Event_Status() const;
private:
	int _State_Id;
	int _Trigger_Counts;

	bool _Event_Enable;
};

//StateUnit CLASS

class StateUnit
{
public:
	StateUnit(GameEvent* GE = nullptr, int State_Id = 0, int Move_Status = 0);
	void SetEvent(std::string GameEventName, int State_Id = -1);
	int Get_Extra_Status() const;
	int Get_State_Id() const;
	void Set_State_Id(int State_Id);
	void Set_Status(int Extra_Status);
private:
	GameEvent* _GameEvents;
	int _Extra_Status;
	int _State_Id;
};

//GameStateBase CLASS

class GameStateBase : public Tanxl_ClassBase
{
public:
	
	StateUnit* Get_StateUnit(EState_Extend State, int Pos);
	//↓Get_State : 指定坐标获取地图单元
	StateUnit* Get_State(int LocationX, int LocationY);
	StateUnit* Get_State();
	Id_Link* Locate_Link(std::string Link_Name);
	//↓Get_StateBase : 返回State单例类 注意！其中的Height和Width仅用于指定绘制显示的区域大小
	static GameStateBase& GetStateBase(int Width = 0, int Height = 0);
	Square_State& Get_Square_State();
	Tanxl_Coord<float>& Get_State_Loc() const;
	Tanxl_Coord<float>& Get_Screen_Distance() const;
	Tanxl_Coord<float>& Get_Move_Distance() const;
	Tanxl_Coord<float>& Get_Last_Move() const;
	Tanxl_Coord<float> Auto_Adjust(double Move_Scale);
	double Get_Each_Width() const;
	double Get_Each_Height() const;
	std::vector<StateUnit*>* Get_GameState(EState_Extend State_Id = STATE_EXTEND_MIDD) const;
	const std::string Get_Version();
	std::string Get_State_Id(int Location);
	TANXL_DataBase* Get_Data_Source();
	void Clear_Display_Vector(EState_Extend Clear_Id = STATE_EXTEND_SPEC) const;
	void Set_Display_State(int Width, int Height);
	void Set_Data_Length(unsigned Width, unsigned Height);
	void Set_Adjust_Flag(bool Adjust_Flag);
	void Check_Adjust_Status(bool Is_Key_Pressed);
	//↓CompileStateUnits : 使用一个字符串来完成整个地图单元的设计 以英文逗号(,)为间断 以英文句号(.)为结尾
	void CompileStateUnits(std::string Infor, EState_Extend Extend = STATE_EXTEND_MIDD);
	//↓Set_StartState : 设置起始区域并构建初始连接编译周围区域 State_Id起始区域Id Cover_String不为NULL时覆盖起始区域内容
	void Set_StartState(int State_Id, std::string Cover_String = "NULL");
	//↓Set_State : 仅修改指定区域的地图数据 State_Id 指定区域Id Cover_String为覆盖的内容
	void Set_State(int State_Id, std::string Cover_String);
	void Set_State_Counts(int Width, int Height);
	void Set_Adjust(float Adjust);
	void Set_Adjust_While_Move(bool Enable);
	void Set_Enable_Adjust(bool Enable);
	void Set_CurrentLoc(float& CurrentX, float& CurrentY) const;
	void Set_Compile_Policy(std::string State_Name, int Set_To_Status);
	void Set_Data_Size(int Size);
	void Reload_Display_State(EState_Extend Extend_Dire);
	void Reload_State_Data(int State_Length, glm::ivec2* StateInfor);
	void Update_Move(float MoveX, float MoveY, ECheck_Edge Check = CHECK_EDGE_CURR);
	void StateMove_Edge_Set(short Edge = 0, double Scale = 1);
	void Set_Trigger_Mode(bool Mode);
	void Generate_StateBlock(int State_Id);
	//↓Build_Connect : 一对多构建连接 State_Id为EXAC编号
	void Build_Connect(int State_Id);
	void Replace_State(int Cover_Id, SExtend_State& State_Target, SExtend_State& State_Id);
	//↓Move_State : 将需要绘制的地图区域整体沿Direction方向移动Times个地图单元长度
	void Move_State(EMove_State_EventId Direction, int Times);
	void Update_Last_Location();
	void State_Check_Event();
	void HitEdge_Check();
	void Move_Adjust();
	bool Is_State_Exist(EState_Extend State_Id = STATE_EXTEND_MIDD);
	bool Get_Compile_Status() const;
	bool Get_Engine_File();
	bool Check_Edge_Reached(ECheck_Edge Check) const;
	bool Update_State(ECheck_Edge Check_Direction);
	bool State_Check_Block(ECheck_Edge Check_Direction);
	Tanxl_Coord<int> Get_Exac_Location() const;
	int Get_Distance_Screen_Id() const;
	int Get_Distance_Move_Id() const;
	//↓HitEdge_Check 返回最后一次的按键状态
	// 获取上次移动触发的边沿
	EMove_State_EventId Auto_Update_Trigger(short Edge);
	//↓Get_DataHeight : 获取单个地图区块纵向包含的单元个数
	unsigned Get_DataHeight()const;
	//↓Get_DataWidth : 获取单个地图区块横向包含的单元个数
	unsigned Get_DataWidth()const;
	//↓Get_StateHeight : 获取当前需要绘制的State的高/宽度值
	Tanxl_Coord<int> Get_StateLength()const;
private:
	float Set_ExacHeight(double Current, float& MoveState, double Scale = 1.0);//可选功能 对2D棋盘上的物品微调位置
	float Set_ExacWidth(double Current, float& MoveState, double Scale = 1.0);
	std::string Locate_Extend_State(std::string State_Id);
	void Single_Connect(std::vector<Data_Unit*>* Build_Target, EState_Current CurrentState, int State_Id, int OffSet = 0);
	
	struct State_Extend
	{
		SExtend_State _MIDD{ SExtend_State() };

		SExtend_State _LEFT{ SExtend_State() };
		SExtend_State _RIGH{ SExtend_State() };
		SExtend_State _ABOV{ SExtend_State() };
		SExtend_State _BELO{ SExtend_State() };

		SExtend_State _LEFT_ABOV{ SExtend_State() };
		SExtend_State _LEFT_BELO{ SExtend_State() };
		SExtend_State _RIGH_ABOV{ SExtend_State() };
		SExtend_State _RIGH_BELO{ SExtend_State() };
	}_GameState_Extend;

	//地图初始化默认构造函数 采用单例模式进行第一次初始化
	GameStateBase(int Width = 0, int Height = 0);
	~GameStateBase();
	GameStateBase(const GameStateBase&);
	GameStateBase& operator=(const GameStateBase&);
	TANXL_DataBase _Data_Base{};
	// _Data_Width 单个地图区块横向包含的单元个数
	unsigned _Data_Width;
	// _Data_Height 单个地图区块纵向包含的单元个数
	unsigned _Data_Height;
	//_Each_Height 记录地图场景基本矩形的高度值
	double _Each_Height{ 0 };
	//_Each_Width 记录地图场景基本矩形的宽度值
	double _Each_Width{ 0 };
	// _State_WidthS 地图区块在横向的个数
	int _State_WidthS{ 0 };
	// _State_HeightS 地图区块在纵向的个数
	int _State_HeightS{ 0 };
	//_Current_Move 记录手动移动指定的当前坐标高度值
	Tanxl_Coord<int> _Current_Move{ 0, 0 };
	//_New_Current_Loc 移动导致改变的新坐标高度值
	Tanxl_Coord<int> _New_Current_Loc{ 0, 0 };
	// _Half_State_Length 半个地图单元的长度
	Tanxl_Coord<float> _Half_State_Length{ 0.0f, 0.0f };
	// _Exac_Location 玩家方块经过计算后的实际坐标
	Tanxl_Coord<int> _Exac_Location;
	//_GameState_Length 用于控制当前地图的显示宽/高度
	Tanxl_Coord<int> _GameState_Length;
	//_Location_Distance_Mid 方块离中心点的距离
	Tanxl_Coord<float> _Location_Distance_Mid{ 0.0f, 0.0f };
	//_Location_Move_Distance 方块移动的距离
	Tanxl_Coord<float> _Location_Move_Distance{ 0.0f, 0.0f };
	//_GameState_Adjust 用于记录每次自动调整的距离
	float _GameState_Adjust;
	//_Is_Data_Set 用于标记是否从文件中获取到了地图数据
	bool _Is_Data_Set;
	//_Adjust_Enable 用于标记是否启用了自动调整
	bool _Adjust_Enable;
	//_Adjust_Enable 用于标记是否启用了移动中自动调整
	bool _Adjust_While_Move{ false };
	//_Is_Adjusting 用于标记是否正处于调整坐标中
	bool _Is_Adjusting;
	//_Compile_Success 用于标记输入的地图数据是否编译成功
	bool _Compile_Success;
	//_Trigger_Mode 用以标记是否启用了移动到地图边缘触发地图跟随移动的功能
	bool _Trigger_Mode{ false };
	//_MState 用于记录当前加载地图区域
	Square_State _MState;
	//_Distance_Screen_Mid 用于记录当前距离屏幕显示区域地图中心点的距离 取值范围0.0 ~ 1.0
	int _Distance_Screen_Mid;
	//_Distance_Move 用于记录当前相对于原点的移动距离
	int _Distance_Move;
	//_Last_Move 用于记录上次移动距离
	int _Last_Move;
	//_State_Loc 记录地图场景移动距离
	int _State_Loc{};
	//_Extend_Mid_Id 记录当前扩展世界中心点的编号
	int _Extend_Mid_Id;
	//_Data_Size 地图数据大小
	int _Data_Size{ 0 };
	std::vector<State_Policy*> _Policy;
};

#endif