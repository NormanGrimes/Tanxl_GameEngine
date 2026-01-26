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
// 新增一个示例游戏事件
// 游戏事件类改为继承自基础类
// 地图替换事件改为通过检查坐标自动执行事件
// 增加坐标触发的事件类
// 新增观察者模式的类定义
// 观察者模式增加模板定义
// 类定义源码移入源文件
// 观察者类增加默认构造函数
// 观察者模式相关定义移入头文件

#pragma once

#ifndef _TANXL_GAMEEVENT_
#define _TANXL_GAMEEVENT_

#include<vector>
#include<string>

#include "Tanxl_GameObject.h"
#include "Tanxl_EngineBase.h"

enum EStateEvent
{
	STATE_NO_EVENT,
	STATE_EVENT_01,
	STATE_EVENT_02,
	STATE_EVENT_03,
	STATE_EVENT_04,
	STATE_EVENT_05,
	STATE_EVENT_06,
	STATE_EVENT_07,
};

class GameEvent
{
public:
	GameEvent(std::string Name = "", GameObject* Obejct = nullptr);
	std::string GetEventName();
	void Set_EventTarget(GameObject* Obejct);
	
private:
	virtual void EventAction() = 0;
	std::string _EventName;
	GameObject* _GameObejct;
};

template<typename Tanxl_TypeName>
class Event_Observer
{
public:
	virtual void EventCheck(Tanxl_TypeName& Tanxl_Type) = 0;
	virtual ~Event_Observer();
};

template<typename Tanxl_TypeName>
class EventSubject
{
public:
	void Add_Observer(Event_Observer<Tanxl_TypeName>* Observer);

	void Remove_Observer(Event_Observer<Tanxl_TypeName>* Observer);

	void Notify(Tanxl_TypeName Tanxl_Type);

private:
	std::vector<Event_Observer<Tanxl_TypeName>*> _ObserverS;
};

class GameEvent_By_Location : public GameEvent
{
public:
	GameEvent_By_Location(std::string Name = "", GameObject* Obejct = nullptr);
	virtual void CheckEvent(int LocationX, int LocationY) = 0;
private:
	virtual void EventAction() = 0;
};

class State_ChangeEvent : public GameEvent
{
public:
	State_ChangeEvent(std::string Name, int LocationX, int LocationY, std::string Cover_String);

	void CheckEvent(int LocationX, int LocationY);

	void Set_CoverString(std::string Cover_String);

private:

	void EventAction();
	int _LocationX;
	int _LocationY;
	std::string _Cover_String;
};

//GameEventBase

class GameEventBase : public Tanxl_ClassBase
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
};

template<typename Tanxl_TypeName>
Event_Observer<Tanxl_TypeName>::~Event_Observer() {}

template<typename Tanxl_TypeName>
inline void EventSubject<Tanxl_TypeName>::Add_Observer(Event_Observer<Tanxl_TypeName>* Observer)
{
	if (Observer)
		this->_ObserverS.push_back(Observer);
}

template<typename Tanxl_TypeName>
void EventSubject<Tanxl_TypeName>::Remove_Observer(Event_Observer<Tanxl_TypeName>* Observer)
{
	auto Location{ std::find(this->_ObserverS.begin(), this->_ObserverS.end(), Observer) };
	if (Location != this->_ObserverS.end())
		this->_ObserverS.erase(Location);
}

template<typename Tanxl_TypeName>
void EventSubject<Tanxl_TypeName>::Notify(Tanxl_TypeName Tanxl_Type)
{
	for (const auto& Observer : this->_ObserverS)
		Observer->EventCheck(Tanxl_Type);
}

#endif