//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2022-12-10 22:48
// 从GameState模块中独立出来进行处理

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

#endif