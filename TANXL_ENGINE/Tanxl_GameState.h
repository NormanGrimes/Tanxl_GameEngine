//_VERSION_0_6_ UPDATE LOG
// LAST_UPDATE 2022-10-10 22:37
// 增加清理地图数据容器的接口
// 修复Set_Display_State中的重复添加地图单元的问题
// 地图数据改用特定接口获取

#pragma once

#ifndef VECTOR
#define VECTOR
#include<vector>
#endif

#ifndef STRING
#define STRING
#include<string>
#endif

enum EMove_State_EventId
{
	MoveToNW = 0,
	MoveToPW = 1,
	MoveToNH = 2,
	MoveToPH = 3
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

class GameEvent
{
public:
	GameEvent(std::string Name = "");
	std::string GetEventName();
	virtual void EventAction() = 0;
private:
	std::string _EventName;
};

//GameEventBase

class GameEventBase
{
public:
	//注册游戏事件 如果仅定义事件而不注册则不会产生任何效果
	void RegistEvent(GameEvent* Event);
	static GameEventBase& GetEventBase();
	GameEvent* GetGameEvent(std::string EventName);
private:
	GameEventBase();
	~GameEventBase();
	GameEventBase(const GameEventBase&);
	GameEventBase& operator=(const GameEventBase&);
	std::vector<GameEvent*> _GameEvents;
};

//StateUnit CLASS

class StateUnit
{
public:
	StateUnit(GameEvent* GE = NULL, int State_Id = 0, bool MoveTarget = true);
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
	std::vector<StateUnit*>* Get_GameState();
	std::vector<bool>* Get_GameState_MoveAble();
	void Clear_Display_Vector();
	void Set_Move_State(int NX, int PX, int NY, int PY);
	void Set_Move_State(int Event_Id);
	void Set_Display_State(int Width, int Height);
	void Set_DataAll_State(unsigned Width, unsigned Height);
	void Set_Adjust_Flag(bool Adjust_Flag);
	void CompileStateUnits(std::string Infor);
	//↓CompileStateEvent : 使用一个字符串来完成整个地图状态的设计 以英文逗号(,)为间断 以英文句号(.)为结尾
	void CompileStateEvent(std::string Infor);
	void Set_Adjust(float Adjust);
	void Set_ExacHeight(double& Current, float* MoveState = NULL, float* MoveY = NULL, float* Deputy = NULL);//可选功能 对2D棋盘上的物品微调位置
	void Set_ExacWidth(double& Current, float* MoveState = NULL, float* MoveY = NULL, float* Deputy = NULL);
	void Set_Adjust_Frequency(int Frame);
	void Set_CurrentLoc(float& CurrentX, float& CurrentY);
	void Reload_State(float& CurrentX, float& CurrentY);
	bool Get_Compile_Status();
	bool Get_Adjust_Flag();
	unsigned Get_DataHeight()const;
	unsigned Get_DataWidth()const;
	//↓Get_StateHeight : 获取当前需要绘制的State的高度值
	int Get_StateHeight()const;
	//↓Get_StateWidth : 获取当前需要绘制的State的宽度值
	int Get_StateWidth()const;
private:
	//地图初始化默认构造函数 采用单例模式进行第一次初始化
	GameStateBase(int Width = 0, int Height = 0);
	~GameStateBase();
	GameStateBase(const GameStateBase&);
	GameStateBase& operator=(const GameStateBase&);
	unsigned _Data_Width;
	unsigned _Data_Height;
	//_Adjust_Frame 用于控制当前每多少帧进行一次坐标控制
	int _Adjust_Frame;
	//_GameState_Width用于控制当前地图的显示宽度
	int _GameState_Width;
	//_GameState_Height用于控制当前地图的显示高度
	int _GameState_Height;
	float _GameState_Adjust;
	bool _Is_Adjusting;
	bool _Compile_Success;
	Move_State _MState;//用于记录当前加载地图区域
	SLocation _SLoc;//用于记录当前地图中心点
	std::vector<StateUnit*> _GameState;
	//用于记录当前地图中心的地图单元
	StateUnit* _CurrentMid;
};