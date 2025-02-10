#include "Tanxl_GameObject.h"

Health_Base::Health_Base(int Maximum_Health, int Current_Health, bool Unable_Damage) :
	_Maximum_Health(Maximum_Health), _Current_Health(Current_Health), _Unable_Damage(Unable_Damage) {};

void Health_Base::RestoreHealth(int RestVal)
{
	if (RestVal < 0 || this->_Unable_Damage)
		return;
	_Current_Health += RestVal;
	if (_Current_Health > _Maximum_Health)
		_Current_Health = _Maximum_Health;
}

void Health_Base::TakeDamage(int TakeVal)
{
	if (TakeVal < 0 || this->_Unable_Damage)
		return;
	_Current_Health -= TakeVal;
	if (_Current_Health < 0)
		_Current_Health = 0;
}

void Health_Base::Set_Health(int Current_Health, int Max_Health)
{
	this->_Current_Health = Current_Health;
	this->_Maximum_Health = Max_Health;
}

int Health_Base::Check_Health()
{
	return this->_Current_Health;
}

int Health_Base::Get_MaxHealth()
{
	return this->_Maximum_Health;
}

Money_Componment::Money_Componment(int Init_Money) :_Current_Money(Init_Money) {}

int Money_Componment::Add_Money(int Money)
{
	this->_Current_Money += Money;
	return this->_Current_Money;
}

bool Money_Componment::Pay_Money(int Price)
{
	if (this->_Current_Money > Price)
	{
		this->_Current_Money -= Price;
		return true;
	}
	return false;
}

Character_Data::Character_Data() :_Attack_Damage(0), _Defense_Armor(0), _Move_Speed(0) {};

Componment::Componment(std::string Name) :_Name(Name), _Is_Special_Enable(false) {}

std::string Componment::GetName()
{
	return this->_Name;
}

void Componment::Set_Special_Status(bool Enable)
{
	this->_Is_Special_Enable = Enable;
}

bool Componment::Get_Special_Status()
{
	return this->_Is_Special_Enable;
}

GameObject::GameObject(int Max_Health, int Current_Health, bool Unable_Damage)
	:Health_Base(Max_Health, Current_Health, Unable_Damage), _Money_Componment(Money_Componment(0)) {}

void GameObject::Add_Money(int Money)
{
	this->_Money_Componment.Add_Money(Money);
}

bool GameObject::Pay_Money(int Price)
{
	return this->_Money_Componment.Pay_Money(Price);
}

bool GameObject::AppendComponment(Componment* CM)
{
	for (auto Componment : this->_Object_Content)//根据名称添加
	{
		if (Componment->GetName() == CM->GetName())
			return false;//出现同名组件——添加失败
	}
	this->_Object_Content.push_back(CM);
	return true;
}

bool GameObject::RemoveComponment(std::string Name)
{
	for (std::vector<Componment*>::iterator IOCB{ this->_Object_Content.begin() }; IOCB != this->_Object_Content.end(); ++IOCB)//根据名称删除
	{
		if ((*IOCB)->GetName() == Name)
		{
			_Object_Content.erase(IOCB);
			return true;
		}
	}
	return false;
}

void GameObject::FinishComponment()
{
	for (int i{ 0 }; i < this->_Object_Content.size(); ++i)
		this->_Object_Content.at(i)->Special();
}

GameObjectBase& GameObjectBase::GetObjectBase()
{
	static GameObjectBase* ObjectBase{ new GameObjectBase };
	return *ObjectBase;
}

const std::string GameObjectBase::Get_Version()
{
	return this->_Version;
}

GameObjectBase::GameObjectBase() {}

GameObjectBase::~GameObjectBase() {}

GameObjectBase::GameObjectBase(const GameObjectBase&) {}

GameObjectBase& GameObjectBase::operator=(const GameObjectBase&) { return *this; }

Weapon::Weapon(int Damage) :_Damage(Damage) {}

int Weapon::Get_DamageVal()
{
	return this->_Damage;
}

Armor::Armor(int Defense) :_Defense(Defense) {}

int Armor::Get_DefenseVal()
{
	return this->_Defense;
}
