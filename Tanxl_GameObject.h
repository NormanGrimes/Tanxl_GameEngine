//_VERSION_0_4_ UPDATE LOG
// LAST_UPDATE 2023-01-03 14:31
// 修复迭代器未初始化的错误
// 增加固定的生命值组件
// 增加组件结构体
// 针对for循环的简易效率更新
// 范围循环测试
// 移除游戏组件结构体
// 生命值组件增加最大生命值设定


#ifndef _TANXL_GAME_OBJECT_
#define _TANXL_GAME_OBJECT_

#include <vector>
#include <string>

//组件类
class Health_Componment
{
public:
	Health_Componment(int Maximum_Health, int Current_Health, bool Unable_Damage = false) :
		_Maximum_Health(Maximum_Health), _Current_Health(Current_Health), _Unable_Damage(Unable_Damage) {};

	void RestoreHealth(int RestVal)
	{
		if (RestVal < 0 || this->_Unable_Damage)
			return;
		_Current_Health += RestVal;
		if (_Current_Health > _Maximum_Health)
			_Current_Health = _Maximum_Health;
	}

	void TakeDamage(int TakeVal)
	{
		if (TakeVal < 0 || this->_Unable_Damage)
			return;
		_Current_Health -= TakeVal;
	}

	int Check_Health()
	{
		return _Current_Health;
	}

private:
	int _Maximum_Health;
	int _Current_Health;
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

//游戏物品类

class GameObjectBase
{
	bool AppendComponment(ComponmentBase* CM);
	bool RemoveComponment(std::string Name);
	void FinishComponment();
private:
	Health_Componment* _Health_COM;
	std::vector<ComponmentBase*> _Object_Content;
};

bool GameObjectBase::AppendComponment(ComponmentBase* CM)
{
	for (auto Componment : this->_Object_Content)//根据名称添加
	{
		if (Componment->GetName() == CM->GetName())
			return false;//出现同名组件——添加失败
	}
	this->_Object_Content.push_back(CM);
	return true;
}

bool GameObjectBase::RemoveComponment(std::string Name)
{
	for (std::vector<ComponmentBase*>::iterator IOCB{ this->_Object_Content.begin() }; IOCB != this->_Object_Content.end(); ++IOCB)//根据名称删除
	{
		if ((*IOCB)->GetName() == Name)
		{
			_Object_Content.erase(IOCB);
			return true;
		}
	}
	return false;
}

void GameObjectBase::FinishComponment()
{
	for (int i{ 0 }; i < this->_Object_Content.size(); ++i)
		this->_Object_Content.at(i)->Special();
}

#endif