﻿//_VERSION_0_7_ UPDATE LOG
// LAST_UPDATE 2022-11-27 14:54
// 提供开关自动调整坐标的接口
// 重新修订重复包含检查
// 修订部分变量名称
// 绘制模块的移动坐标归入State模块管理
// 设置启用移动中调整的功能归入State模块
// 自动调整函数增加浮点数返回最后一步调节的差值
// 增加版本变量与获取接口
// 设置显示范围的接口不再清理地图数据
// 移动状态枚举增加五种其他情况
// 范围循环测试
// 默认初始化绘制频率为每帧一次

#pragma once

#ifndef _TANXL_GAMESTATE_
#define _TANXL_GAMESTATE_

#include <iostream>
#include "Tanxl_GameEvent.h"
#include "Tanxl_DataBase.h"

enum EMove_State_EventId
{
	MoveToNO = 0,
	MoveToNW = 1,
	MoveToPW = 2,
	MoveToNH = 4,
	MoveToNWNH = 5,
	MoveToPWNH = 6,
	MoveToPH = 8,
	MoveToNWPH = 9,
	MoveToPWPH = 10
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
	SLocation& Get_Current_Distance();
	std::vector<StateUnit*>* Get_GameState();
	std::vector<bool>* Get_GameState_MoveAble();
	const std::string Get_Version();
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
	void Set_Adjust_While_Move(bool Enable);
	void Set_Enable_Adjust(bool Enable);
	void Set_Adjust_Frequency(int Frame);
	void Set_CurrentLoc(float& CurrentX, float& CurrentY);
	void Reload_State(float& CurrentX, float& CurrentY);
	bool Get_Compile_Status();
	bool Get_Adjust_Flag();
	bool Get_Adjust_While_Move();
	float Set_ExacHeight(double Current, float& MoveState, float& State_MoveY, float& Auto_Adjust_Length);//可选功能 对2D棋盘上的物品微调位置
	float Set_ExacWidth(double Current, float& MoveState, float& State_MoveX, float& Auto_Adjust_Length);
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
	//_GameState_Adjust用于记录每次自动调整的距离
	float _GameState_Adjust;
	//_Adjust_Enable用于标记是否启用了自动调整
	bool _Adjust_Enable;
	//_Adjust_Enable用于标记是否启用了移动中自动调整
	bool _Adjust_While_Move = false;
	//_Is_Adjusting用于标记是否正处于调整坐标中
	bool _Is_Adjusting;
	bool _Compile_Success;
	Move_State _MState;//用于记录当前加载地图区域
	//_SLoc用于记录当前距离地图中心点的距离
	SLocation _Distance_Mid;
	std::vector<StateUnit*> _GameState;
	std::vector<StateUnit*>* _GameStateX[9]{};
	//用于记录当前地图中心的地图单元
	StateUnit* _CurrentMid;
	const std::string _Version{ "0.7" };
};

#endif