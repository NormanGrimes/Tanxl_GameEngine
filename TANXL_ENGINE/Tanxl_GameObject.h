//_VERSION_0_4_ UPDATE LOG
// LAST_UPDATE 2023-01-03 14:31
// 修复迭代器未初始化的错误
// 增加固定的生命值组件
// 增加组件结构体
// 针对for循环的简易效率更新
// 范围循环测试


#ifndef _TANXL_GAME_OBJECT_
#define _TANXL_GAME_OBJECT_

#include <vector>
#include <string>

//组件类
class Health_Componment
{
public:
	Health_Componment(int Life_Cnt, bool Unable_Damage = false) :_Life_Count(Life_Cnt), _Unable_Damage(Unable_Damage) {};

	void RestoreHealth(int RestVal)
	{
		if (RestVal < 0 || this->_Unable_Damage)
			return;
		_Life_Count += RestVal;
	}

	void TakeDamage(int TakeVal)
	{
		if (TakeVal < 0 || this->_Unable_Damage)
			return;
		_Life_Count -= TakeVal;
	}

	int Check_Health()
	{
		return _Life_Count;
	}

private:
	int _Life_Count;
	bool _Unable_Damage;
};

class ComponmentBase
{
public:
	ComponmentBase(std::string Name) :ComponmentName(Name) {}
	std::string GetName()
	{
		return this->ComponmentName;
	}
	virtual void Special() = 0;
private:
	std::string ComponmentName;
};

//游戏物品结构
struct GameObjectContent
{
	Health_Componment _Health_COM;
	std::vector<ComponmentBase*> _CMB;
};

//游戏物品类

class GameObjectBase
{
	bool AppendComponment(ComponmentBase* CM);
	bool RemoveComponment(std::string Name);
	void FinishComponment();
private:
	GameObjectContent _GOC;
};

bool GameObjectBase::AppendComponment(ComponmentBase* CM)
{
	for (auto Componment : _GOC._CMB)//根据名称添加
	{
		if (Componment->GetName() == CM->GetName())
			return false;//出现同名组件——添加失败
	}
	_GOC._CMB.push_back(CM);
	return true;
}

bool GameObjectBase::RemoveComponment(std::string Name)
{
	for (std::vector<ComponmentBase*>::iterator IOCB{ _GOC._CMB.begin() }; IOCB != _GOC._CMB.end(); ++IOCB)//根据名称删除
	{
		if ((*IOCB)->GetName() == Name)
		{
			_GOC._CMB.erase(IOCB);
			return true;
		}
	}
	return false;
}

void GameObjectBase::FinishComponment()
{
	for (int i = 0; i < _GOC._CMB.size(); ++i)
		_GOC._CMB.at(i)->Special();
}

#endif