//_VERSION_0_3_ UPDATE LOG
// LAST_UPDATE 2022-05-16 23:50
// StateUnit类增加对每一格的ID设定
// 微调StateUnit构造函数
// 源文件代码结构调整
// 编译地图功能现在可以编译地图ID数值
// 提供一个可返回地图数据的函数
// 调整各接口的名称

#pragma once

#ifndef VECTOR
#define VECTOR
#include<vector>
#endif

#ifndef STRING
#define STRING
#include<string>
#endif

class GameEvent
{
public:
	GameEvent(std::string Name = "");
	std::string GetEventName();
	virtual void EventAction() = 0;
private:
	std::string EventName;
};

//GameEventBase

class GameEventBase
{
public:
	void RegistEvent(GameEvent* Event);
	static GameEventBase& GetEventBase();
	GameEvent* GetGameEvent(std::string EventName);
private:
	GameEventBase();
	~GameEventBase();
	GameEventBase(const GameEventBase&);
	GameEventBase& operator=(const GameEventBase&);
	std::vector<GameEvent*>GameEvents;
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
	GameEvent* GameEvents;
	bool Is_Move_Target;
	int _State_Id;
};

//GameStateBase CLASS

class GameStateBase
{
public:
	void Set_State(int Width, int Height);
	void CompileStateUnits(std::string Infor);
	//CompileStateEvent : 使用一个字符串来完成整个地图状态的设计 以英文逗号(,)为间断 以英文句号(.)为结尾
	void CompileStateEvent(std::string Infor);
	void Set_Adjust(float Adjust);
	size_t Get_StateSize();
	StateUnit* Get_StateUnit(int Pos);
	static GameStateBase& Get_StateBase(int Height = 0, int Width = 0);
	std::vector<StateUnit*>* Get_GameState();
	std::vector<bool>* Get_GameState_MoveAble();
	void Set_ExacHeight(float& Current);//可选功能 对2D棋盘上的物品微调位置
	void Set_ExacWidth(float& Current);
	int Get_StateHeight()const;
	int Get_StateWidth()const;
private:
	//地图初始化默认构造函数 采用单例模式进行第一次初始化
	GameStateBase(int Height = 0, int Width = 0);
	~GameStateBase();
	GameStateBase(const GameStateBase&);
	GameStateBase& operator=(const GameStateBase&);
	int GameState_Width;
	int GameState_Height;
	float GameState_Adjust;
	std::vector<StateUnit*>GameState;
};