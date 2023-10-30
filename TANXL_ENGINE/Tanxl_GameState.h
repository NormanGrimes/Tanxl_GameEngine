//_VERSION_0_8_ UPDATE LOG
// LAST_UPDATE 2023-02-20 10:57
// 增加变量记录各方向总移动距离
// 增加变量记录各单元的半宽高
// 增加根据中点计算当前单元格的功能
// 增加方格多个点的边缘检测枚举
// 边缘检查枚举减少到五个
// 增加地图扩展结构体
// 地图单元编译功能增加对扩展地图的支持
// 获取区域是否可移动功能性能优化
// 设置当前坐标接口移除未使用代码
// 增加通过编号定位地图数据的接口
// 增加根据内置数据库内容生成地图的功能
// 增加内置的地图属性结构体
// 地图单元编译功能增加地图属性结构体的支持

#pragma once

#ifndef _TANXL_GAMESTATE_
#define _TANXL_GAMESTATE_

#include <iostream>
#include "Tanxl_GameEvent.h"
#include "Tanxl_DataBase.h"

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
	STATE_ORIGIN_MIDD,

	STATE_EXTEND_MIDD,
	STATE_EXTEND_LEFT,
	STATE_EXTEND_RIGH,
	STATE_EXTEND_ABOV,
	STATE_EXTEND_BELO,
	STATE_EXTEND_LEFT_ABOV,
	STATE_EXTEND_LEFT_BELO,
	STATE_EXTEND_RIGH_ABOV,
	STATE_EXTEND_RIGH_BELO
};

struct Move_State
{
	Move_State(int NX = 0, int PX = 0, int NY = 0, int PY = 0);
	int _Move_NX;
	int _Move_PX;
	int _Move_NY;
	int _Move_PY;
};

struct SLocation
{
	SLocation(float LocX, float LocY);
	float _LocX;
	float _LocY;
};

//StateUnit CLASS

class StateUnit
{
public:
	StateUnit(GameEvent* GE = nullptr, int State_Id = 0, bool MoveTarget = true);
	void SetEvent(std::string GameEventName, int State_Id = -1);
	bool GetMoveAble();
	int Get_State_Id();
	void Set_State_Id(int State_Id);
private:
	GameEvent* _GameEvents;
	bool _Is_Move_Target;
	int _State_Id;
};

//GameStateBase CLASS

class GameStateBase
{
public:
	
	size_t Get_StateSize();
	StateUnit* Get_StateUnit(int Pos);
	//↓Get_StateBase : 返回State单例类 注意！其中的Height和Width仅用于指定绘制显示的区域大小
	static GameStateBase& Get_StateBase(int Width = 0, int Height = 0);
	Move_State Get_Move_State();
	SLocation& Get_Screen_Distance();
	SLocation& Get_Move_Distance();
	std::vector<StateUnit*>* Get_GameState();
	std::vector<bool>* Get_GameState_MoveAble();
	const std::string Get_Version();
	std::string Locate_Extend_State(std::string State_Id);
	void Clear_Display_Vector();
	void Set_Move_State(int NX, int PX, int NY, int PY);
	void Set_Move_State(int Event_Id);
	void Set_Display_State(int Width, int Height);
	void Set_DataAll_State(unsigned Width, unsigned Height);
	void Set_Adjust_Flag(bool Adjust_Flag);
	//↓CompileStateUnits : 使用一个字符串来完成整个地图单元的设计 以英文逗号(,)为间断 以英文句号(.)为结尾
	void CompileStateUnits(std::string Infor, EState_Extend Extend = STATE_ORIGIN_MIDD);
	//↓CompileStateEvent : 使用一个字符串来完成整个地图状态的设计 以英文逗号(,)为间断 以英文句号(.)为结尾
	void CompileStateEvent(std::string Infor);
	void Set_SquareState(std::string State_Id);
	void Set_Adjust(float Adjust);
	void Set_Adjust_While_Move(bool Enable);
	void Set_Enable_Adjust(bool Enable);
	void Set_Adjust_Frequency(int Frame);
	void Set_CurrentLoc(float& CurrentX, float& CurrentY);
	void Reload_State(float& CurrentX, float& CurrentY);
	void Update_Move(float MoveX, float MoveY, ECheck_Edge Check = CHECK_EDGE_CURR);
	bool Get_Compile_Status();
	bool Get_Adjust_Flag();
	bool Get_Adjust_While_Move();
	int Get_LocationX();
	int Get_LocationY();
	float Set_ExacHeight(double Current, float& MoveState, float& State_MoveY, float& Auto_Adjust_Length);//可选功能 对2D棋盘上的物品微调位置
	float Set_ExacWidth(double Current, float& MoveState, float& State_MoveX, float& Auto_Adjust_Length);
	unsigned Get_DataHeight()const;
	unsigned Get_DataWidth()const;
	//↓Get_StateHeight : 获取当前需要绘制的State的高度值
	int Get_StateHeight()const;
	//↓Get_StateWidth : 获取当前需要绘制的State的宽度值
	int Get_StateWidth()const;
private:
	struct State_Extend
	{		
		std::vector<StateUnit*>* _MIDD{ nullptr };

		std::vector<StateUnit*>* _LEFT{ nullptr };
		std::vector<StateUnit*>* _RIGH{ nullptr };
		std::vector<StateUnit*>* _ABOV{ nullptr };
		std::vector<StateUnit*>* _BELO{ nullptr };

		std::vector<StateUnit*>* _LEFT_ABOV{ nullptr };
		std::vector<StateUnit*>* _LEFT_BELO{ nullptr };
		std::vector<StateUnit*>* _RIGH_ABOV{ nullptr };
		std::vector<StateUnit*>* _RIGH_BELO{ nullptr };
	}_GameState_Extend;

	struct State_Extend_Id
	{
		std::string _MIDD{ "NULL" };

		std::string _LEFT{ "NULL" };
		std::string _RIGH{ "NULL" };
		std::string _ABOV{ "NULL" };
		std::string _BELO{ "NULL" };

		std::string _LEFT_ABOV{ "NULL" };
		std::string _LEFT_BELO{ "NULL" };
		std::string _RIGH_ABOV{ "NULL" };
		std::string _RIGH_BELO{ "NULL" };
	}_GameState_Id;

	//地图初始化默认构造函数 采用单例模式进行第一次初始化
	GameStateBase(int Width = 0, int Height = 0);
	~GameStateBase();
	GameStateBase(const GameStateBase&);
	GameStateBase& operator=(const GameStateBase&);
	TANXL_DataBase _Data_Base{};
	unsigned _Data_Width;
	unsigned _Data_Height;
	float _Half_State_Width{ 0.0f };
	float _Half_State_Height{ 0.0f };
	int _Exac_LocationX;
	int _Exac_LocationY;
	//_Adjust_Frame 用于控制当前每多少帧进行一次坐标控制
	int _Adjust_Frame;
	//_GameState_Width用于控制当前地图的显示宽度
	int _GameState_Width;
	//_GameState_Height用于控制当前地图的显示高度
	int _GameState_Height;
	//_GameState_Adjust用于记录每次自动调整的距离
	float _GameState_Adjust;
	//_Adjust_Enable用于标记是否启用了自动调整
	bool _Adjust_Enable;
	//_Adjust_Enable用于标记是否启用了移动中自动调整
	bool _Adjust_While_Move = false;
	//_Is_Adjusting用于标记是否正处于调整坐标中
	bool _Is_Adjusting;
	//_Compile_Success用于标记输入的地图数据是否编译成功
	bool _Compile_Success;
	//_MState用于记录当前加载地图区域
	Move_State _MState;
	//_Distance_Screen_Mid用于记录当前距离屏幕显示区域地图中心点的距离 取值范围0.0 ~ 1.0
	SLocation _Distance_Screen_Mid;
	//_Distance_Move用于记录当前相对于原点的移动距离
	SLocation _Distance_Move;
	std::vector<StateUnit*> _GameState;
	//用于记录当前地图中心的地图单元
	StateUnit* _CurrentMid;
	const std::string _Version{ "0.8" };
};

#endif