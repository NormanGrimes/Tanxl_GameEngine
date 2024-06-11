#include "Tanxl_GameObject.h"

Health_Componment::Health_Componment(int Maximum_Health, int Current_Health, bool Unable_Damage) :
	_Maximum_Health(Maximum_Health), _Current_Health(Current_Health), _Unable_Damage(Unable_Damage) {};

void Health_Componment::RestoreHealth(int RestVal)
{
	if (RestVal < 0 || this->_Unable_Damage)
		return;
	_Current_Health += RestVal;
	if (_Current_Health > _Maximum_Health)
		_Current_Health = _Maximum_Health;
}

void Health_Componment::TakeDamage(int TakeVal)
{
	if (TakeVal < 0 || this->_Unable_Damage)
		return;
	_Current_Health -= TakeVal;
}

int Health_Componment::Check_Health()
{
	return _Current_Health;
}

ComponmentBase::ComponmentBase(std::string Name) :ComponmentName(Name) {}

std::string ComponmentBase::GetName()
{
	return this->ComponmentName;
}

const std::string GameObjectBase::Get_Version()
{
	return this->_Version;
}

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
