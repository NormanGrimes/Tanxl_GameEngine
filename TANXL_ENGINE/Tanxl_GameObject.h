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
// 人物信息类增加各项数值的获取接口
// 从绘制模块中移出玩家对象
// 财产组件增加获取金钱数量接口
// 游戏物品类不再继承自生命值组件
// 游戏物品类中部分功能拆解为单独的物品组件类


#ifndef _TANXL_GAME_OBJECT_
#define _TANXL_GAME_OBJECT_

#include <vector>
#include <string>

//组件类

class Health_Componment
{
public:
	Health_Componment(int Maximum_Health, int Current_Health, bool Unable_Damage = false);

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

	int Get_Money();

private:
	int _Current_Money;
};

class Character_Data
{
public:
	Character_Data();

	int Get_Attack_Damage();
	int Get_Defense_Armor();
	double Get_Move_Speed();

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

class Componment_Unite
{
public:
	bool AppendComponment(Componment* CM);
	bool RemoveComponment(std::string Name);
	void FinishComponment();

private:
	std::vector<Componment*> _Object_Content;
};

//游戏物品类

class GameObject
{
public:
	GameObject(int Max_Health, int Current_Health, bool Unable_Damage = false);
	void Add_Money(int Money);
	bool Pay_Money(int Price);
	int Get_Money();

	void RestoreHealth(int RestVal);
	void TakeDamage(int TakeVal);
	void Set_Health(int Current_Health, int Max_Health = 10);
	int Check_Health();
	int Get_MaxHealth();
	
private:

	Health_Componment _Health_Componment;
	Money_Componment _Money_Componment;
};

//主操作对象 其生命值纹理前两个为角色纹理 即Health = 10时 8为其生命值2为纹理保留值
static GameObject* Main_Character = new GameObject(10, 10);

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