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

	int Check_Health();

private:
	int _Maximum_Health;
	int _Current_Health;
	bool _Unable_Damage;
};

class ComponmentBase
{
public:
	ComponmentBase(std::string Name);
	std::string GetName();
	virtual void Special() = 0;
private:
	std::string ComponmentName;
};

//游戏物品类

class GameObjectBase : public Health_Componment
{
public:
	GameObjectBase(int Max_Health, int Current_Health);

	const std::string Get_Version();

	bool AppendComponment(ComponmentBase* CM);
	bool RemoveComponment(std::string Name);
	void FinishComponment();
private:
	std::vector<ComponmentBase*> _Object_Content;

	const std::string _Version{ "0.4" };
};

#endif