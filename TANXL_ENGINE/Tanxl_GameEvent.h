//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2022-12-10 22:48
// 从GameState模块中独立出来进行处理
// 增加版本变量与获取接口
// 析构函数优化清理内存中的遗留数据
// 新增搜索已注册游戏事件功能
// 增加事件移除功能
// 增加重载版本事件移除功能
// 游戏事件结构增加游戏物品指针成员
// 增加指定事件目标的接口

#pragma once

#ifndef _TANXL_GAMEEVENT_
#define _TANXL_GAMEEVENT_

#include<vector>
#include<string>
#include "Tanxl_GameObject.h"

class GameEvent
{
public:
	GameEvent(std::string Name = "", GameObject* Obejct = nullptr);
	std::string GetEventName();
	void Set_EventTarget(GameObject* Obejct);
	virtual void EventAction() = 0;
private:
	std::string _EventName;
	GameObject* _GameObejct;
};

//GameEventBase

class GameEventBase
{
public:
	//获取此模块的版本信息
	const std::string Get_Version();
	//注册游戏事件 如果仅定义事件而不注册则不会产生任何效果
	void RegistEvent(GameEvent* Event);
	//获取游戏事件基类
	static GameEventBase& GetEventBase();
	GameEvent* GetGameEvent(std::string EventName);
	//搜索游戏事件 查看是否已添加相关名称的游戏事件
	bool Search_GameEvent(std::string EventName);
	void Remove_GameEvent(int Event_Id);
	void Remove_GameEvent(std::string EventName);
private:
	GameEventBase();
	~GameEventBase();
	GameEventBase(const GameEventBase&);
	GameEventBase& operator=(const GameEventBase&);

	std::vector<GameEvent*> _GameEvents;
	const std::string _Version{ "0.1" };
};

#endif