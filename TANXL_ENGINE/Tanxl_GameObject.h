//_VERSION_0_5_ UPDATE LOG
// LAST_UPDATE 2024-04-09 18:04
// 新增装备观察者以及一个替换地图编号的装备事件

#pragma once

#ifndef _TANXL_GAME_OBJECT_
#define _TANXL_GAME_OBJECT_

#define _TANXL_GAMEOBJECT_CONSOLE_OUTPUT_  0

#if _TANXL_GAMEOBJECT_CONSOLE_OUTPUT_

#include <iostream>
#define _TANXL_GAMEOBJECT_ROLLBACK_OUTPUT_ 0

#endif

#include <vector>
#include <string>

#include "Tanxl_EngineBase.h"
#include "Tanxl_LocationBase.h"
#include "Tanxl_SteamService.h"
#include "Tanxl_ObserverBase.h"

//组件类
class Componment_Base
{
public:
	Componment_Base(std::string Name);

	std::string GetName();
private:
	std::string _Name;
};

struct Weapon
{
	Weapon(int Damage, std::string Texture);
	int _Damage;
	std::string _Texture;
};

struct Armor
{
	Armor(int Defense, std::string Texture);
	int _Defense;
	std::string _Texture;
};

struct Character_Data
{
	Character_Data();

	double _Move_Speed;
};

class Health_Componment : public Componment_Base
{
public:
	Health_Componment(int Maximum_Health, int Current_Health, bool Unable_Damage = false);

	void RestoreHealth(int RestVal);

	void TakeDamage(int TakeVal);

	void Set_Health(int Current_Health, int Max_Health);

	void God_Mode(bool Enable = true);
	// 获取当前生命值
	int Check_Health() const;
	// 获取最大生命值
	int Get_MaxHealth() const;
	// 获取当前是否为存活状态
	bool Is_Alive() const;

private:
	int _Maximum_Health;
	int _Current_Health;
	bool _Unable_Damage;
	bool _Is_Alive;
};

class Money_Componment : public Componment_Base
{
public:
	Money_Componment(int Init_Money);

	int Add_Money(int Money);

	bool Pay_Money(int Price);

	int Get_Money() const;

private:
	int _Current_Money;
};

class Coord_Componment : public Componment_Base
{
public:
	Coord_Componment();

	void Reset_Data();
	void Update_Last_Location();
	void Move_To(int Direction, float Range);
	void RollBack(int BackStatus);

	Tanxl_Coord<float>* Get_Last_Move();
	Tanxl_Coord<float>* Get_Distance_Move();
	Tanxl_Coord<float>* Get_Distance_Mid();
	Tanxl_Coord<float>* Get_Last_Distance_Mid();
	Tanxl_Coord<float>* Get_Last_Distance_Move();
private:
	//_Last_Move 用于记录上次移动距离
	Tanxl_Coord<float> _Last_Move;
	//_Distance_Move 用于记录当前相对于原点的移动距离
	Tanxl_Coord<float> _Distance_Move;
	//_Distance_Mid 用于记录当前距离屏幕显示区域地图中心点的距离 取值范围0.0 ~ 1.0
	Tanxl_Coord<float> _Distance_Mid;
	//_Last_Distance_Mid 上一次有效的方块离中心点的距离
	Tanxl_Coord<float> _Last_Distance_Mid;
	//_Last_Distance_Move 上一次有效的方块移动距离
	Tanxl_Coord<float> _Last_Distance_Move;
};

class Equipment_Componment : public Componment_Base
{
public:
	Equipment_Componment();

	int Get_Attack_Damage() const;
	int Get_Defense_Armor() const;

private:
	int _Attack_Damage;
	int _Defense_Armor;

	Weapon* _Weapon_Slot;
	Armor* _Armor_Slot;
};

class Componment_Unite
{
public:
	bool Append(Componment_Base* CM);
	bool Remove(std::string Name);
	bool Remove();

private:
	std::vector<Componment_Base*> _Object_Content;
};

//游戏物品类

class GameObject
{
public:
	GameObject(int Max_Health, int Current_Health, bool Unable_Damage = false);

	Coord_Componment* Coord();
	Health_Componment* Health();
	Money_Componment* Money();

private:
	Character_Data _Character_Data;

	Coord_Componment _Coord_Componment;
	Health_Componment _Health_Componment;
	Money_Componment _Money_Componment;
};

class Equipment_State_Replace_Observer : public Event_Observer<StateUnit>
{
public:
	Equipment_State_Replace_Observer(int Event_Id, int Replace_State_Id) :
		_Event_Id(Event_Id), _Replace_State_Id(Replace_State_Id) {}

	void EventCheck(StateUnit& State)
	{
		if (_Event_Id == State._State_Id)
			State._Extra_Status = _Replace_State_Id;
	}
private:
	int _Event_Id;
	int _Replace_State_Id;
};

//GameObjectBase

class GameObjectBase : public Tanxl_ClassBase
{
public:
	static GameObjectBase& GetObjectBase();

	const std::string Get_Version();

	GameObject* Get_Main_Character();

	void Reset_Main_Character(GameObject* Character);

private:
	EventSubject<StateUnit> _Equipment_Subject;

	GameObject* _Main_Character{ nullptr };

	GameObjectBase();
	~GameObjectBase();
	GameObjectBase(const GameObjectBase&);
	GameObjectBase& operator=(const GameObjectBase&);
};

#endif