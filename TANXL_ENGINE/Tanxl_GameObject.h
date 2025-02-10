//_VERSION_0_4_ UPDATE LOG
// LAST_UPDATE 2023-01-03 14:31
// 修复迭代器未初始化的错误
// 增加固定的生命值组件
// 增加组件结构体
// 针对for循环的简易效率更新
// 范围循环测试
// 移除游戏组件结构体
// 生命值组件增加最大生命值设定
// 游戏物品类增加包含生命值组件的构造函数
// 生命值组件增加生命值设置功能
// 移除游戏物品类的生命值组件成员改为公有继承生命值组件
// 新增物品基类原基类改为游戏物品类
// 增加物品组件的状态与设置和获取函数
// 生命值组件增加伤害溢出判断
// 生命值组件增加最大生命值获取接口
// 新增金币组件
// 新增记录人物攻击力防御力移动速度的属性组件
// 游戏物品构造函数增加是否可受到伤害的参数
// 增加武器与护甲基础类


#ifndef _TANXL_GAME_OBJECT_
#define _TANXL_GAME_OBJECT_

#include <vector>
#include <string>

//组件类

class Health_Base
{
public:
	Health_Base(int Maximum_Health, int Current_Health, bool Unable_Damage = false);

	void RestoreHealth(int RestVal);

	void TakeDamage(int TakeVal);

	void Set_Health(int Current_Health, int Max_Health = 10);
	// 获取当前生命值
	int Check_Health();
	// 获取最大生命值
	int Get_MaxHealth();

private:
	int _Maximum_Health;
	int _Current_Health;
	bool _Unable_Damage;
};

class Money_Componment
{
public:
	Money_Componment(int Init_Money);

	int Add_Money(int Money);

	bool Pay_Money(int Price);

private:
	int _Current_Money;
};

class Character_Data
{
public:
	Character_Data();

private:
	int _Attack_Damage;
	int _Defense_Armor;
	double _Move_Speed;
};

class Weapon
{
public:
	Weapon(int Damage);

	int Get_DamageVal();
private:
	int _Damage;
};

class Armor
{
public:
	Armor(int Defense);

	int Get_DefenseVal();
private:
	int _Defense;
};

class Componment
{
public:
	Componment(std::string Name);
	std::string GetName();
	virtual void Special() = 0;
	void Set_Special_Status(bool Enable);
	bool Get_Special_Status();
private:
	std::string _Name;
	bool _Is_Special_Enable;
};

//游戏物品类

class GameObject : public Health_Base
{
public:
	GameObject(int Max_Health, int Current_Health, bool Unable_Damage = false);
	void Add_Money(int Money);
	bool Pay_Money(int Price);

	bool AppendComponment(Componment* CM);
	bool RemoveComponment(std::string Name);
	void FinishComponment();
private:

	Money_Componment _Money_Componment;
	std::vector<Componment*> _Object_Content;
};

//GameObjectBase

class GameObjectBase
{
public:
	static GameObjectBase& GetObjectBase();

	const std::string Get_Version();

private:
	const std::string _Version{ "0.4" };

	GameObjectBase();
	~GameObjectBase();
	GameObjectBase(const GameObjectBase&);
	GameObjectBase& operator=(const GameObjectBase&);

};

#endif