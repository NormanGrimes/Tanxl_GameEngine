//_VERSION_0_2_ UPDATE LOG
// LAST_UPDATE 2022-05-08 22:51
// 组件类架构基本确定
// 物品基类提供添加组件功能
// 物品基类提供删除组件功能
// 游戏物品类增加一键执行所有组件功能的函数

#ifndef VECTOR//检查是否已经包含VECTOR
#define VECTOR
#include <vector>
#endif

#ifndef STRING//检查是否已经包含STRING
#define STRING
#include <string>
#endif

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