//_VERSION_0_3_ UPDATE LOG
// LAST_UPDATE 2022-05-17 22:56
// 提供一个初始预设生命值组件
// 修改头文件包含方式


#ifndef _TANXL_GAME_OBJECT_
#define _TANXL_GAME_OBJECT_

#include <vector>
#include <string>

//组件类

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
	std::vector<ComponmentBase*> CMB;
};

bool GameObjectBase::AppendComponment(ComponmentBase* CM)
{
	for (int i = 0; i < CMB.size(); i++)//根据名称添加
	{
		if (CMB.at(i)->GetName() == CM->GetName())
			return false;//出现同名组件——添加失败
	}
	CMB.push_back(CM);
	return true;
}

bool GameObjectBase::RemoveComponment(std::string Name)
{
	for (std::vector<ComponmentBase*>::iterator IOCB; IOCB!= CMB.end(); IOCB++)//根据名称删除
	{
		if (( * IOCB)->GetName() == Name)
		{
			CMB.erase(IOCB);
			return true;
		}
	}
	return false;
}

void GameObjectBase::FinishComponment()
{
	for (int i = 0; i < CMB.size(); i++)
		CMB.at(i)->Special();
}

//Componment Sample
class Unit_Life : public ComponmentBase
{
public:
	Unit_Life(int Life_Count) :ComponmentBase("Unit_Life"), _Life_Count(Life_Count) {}
	virtual void Special()
	{

	}
	void RestoreHealth()
	{
		_Life_Count++;
	}
	void TakeDamage()
	{
		_Life_Count--;
	}
	int Check_Health()
	{
		return _Life_Count;
	}
private:
	int _Life_Count;
};

#endif