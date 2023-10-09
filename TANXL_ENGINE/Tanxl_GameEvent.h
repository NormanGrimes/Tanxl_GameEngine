//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2022-12-10 22:48
// 从GameState模块中独立出来进行处理
// 增加版本变量与获取接口
// 析构函数优化清理内存中的遗留数据
// 新增搜索已注册游戏事件功能

#pragma once

#ifndef _TANXL_GAMEEVENT_
#define _TANXL_GAMEEVENT_

#include<vector>
#include<string>

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
	const std::string Get_Version();
	void RegistEvent(GameEvent* Event);
	static GameEventBase& GetEventBase();
	GameEvent* GetGameEvent(std::string EventName);
	//搜索游戏事件 查看是否已添加相关名称的游戏事件
	bool Search_GameEvent(std::string EventName);
private:
	GameEventBase();
	~GameEventBase();
	GameEventBase(const GameEventBase&);
	GameEventBase& operator=(const GameEventBase&);
	std::vector<GameEvent*> _GameEvents;
	const std::string _Version{ "0.1" };
};

#endif