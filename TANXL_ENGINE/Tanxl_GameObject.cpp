#include "Tanxl_GameObject.h"

Health_Componment::Health_Componment(int Maximum_Health, int Current_Health, bool Unable_Damage) : Componment_Base("Health"),
_Maximum_Health(Maximum_Health), _Current_Health(Current_Health), _Unable_Damage(Unable_Damage), _Is_Alive(true)
{
	if (_Current_Health > _Maximum_Health)
		_Maximum_Health = _Current_Health;
}

void Health_Componment::RestoreHealth(int RestVal)
{
	if ((RestVal < 0) || this->_Unable_Damage || (this->_Is_Alive == false))
		return;
	_Current_Health += RestVal;
	if (_Current_Health > _Maximum_Health)
		_Current_Health = _Maximum_Health;
}

void Health_Componment::TakeDamage(int TakeVal)
{
	if ((TakeVal < 0) || (this->_Unable_Damage))
		return;
	_Current_Health -= TakeVal;
	if (_Current_Health < 0)
		_Current_Health = 0;
	if (_Current_Health == 0)
		this->_Is_Alive = false;
}

void Health_Componment::Set_Health(int Current_Health, int Max_Health)
{
	this->_Current_Health = Current_Health;
	this->_Maximum_Health = Max_Health;

	if (this->_Current_Health > 0)
		this->_Is_Alive = true;
}

int Health_Componment::Check_Health()
{
	return this->_Current_Health;
}

int Health_Componment::Get_MaxHealth()
{
	return this->_Maximum_Health;
}

bool Health_Componment::Is_Alive()
{
	return this->_Is_Alive;
}

Money_Componment::Money_Componment(int Init_Money) :Componment_Base("Money"), _Current_Money(Init_Money) {}

int Money_Componment::Add_Money(int Money)
{
	this->_Current_Money += Money;
	return this->_Current_Money;
}

bool Money_Componment::Pay_Money(int Price)
{
	if (this->_Current_Money >= Price)
	{
		this->_Current_Money -= Price;
		return true;
	}
	return false;
}

int Money_Componment::Get_Money()
{
	return this->_Current_Money;
}

Character_Data::Character_Data() :_Attack_Damage(0), _Defense_Armor(0), _Move_Speed(0) {}

int Character_Data::Get_Attack_Damage()
{
	return this->_Attack_Damage;
}

int Character_Data::Get_Defense_Armor()
{
	return this->_Defense_Armor;
}

double Character_Data::Get_Move_Speed()
{
	return this->_Move_Speed;
}

Componment_Base::Componment_Base(std::string Name) :_Name(Name) {}

std::string Componment_Base::GetName()
{
	return this->_Name;
}

GameObject::GameObject(int Max_Health, int Current_Health, bool Unable_Damage)
	:_Health_Componment(Max_Health, Current_Health, Unable_Damage), _Money_Componment(0) {}

void GameObject::Add_Money(int Money)
{
	this->_Money_Componment.Add_Money(Money);
}

bool GameObject::Pay_Money(int Price)
{
	return this->_Money_Componment.Pay_Money(Price);
}

int GameObject::Get_Money()
{
	return this->_Money_Componment.Get_Money();
}

void GameObject::RestoreHealth(int RestVal)
{
	this->_Health_Componment.RestoreHealth(RestVal);
}

void GameObject::TakeDamage(int TakeVal)
{
	this->_Health_Componment.TakeDamage(TakeVal);
}

void GameObject::Set_Health(int Current_Health, int Max_Health)
{
	this->_Health_Componment.Set_Health(Current_Health, Max_Health);
}

int GameObject::Check_Health()
{
	return this->_Health_Componment.Check_Health();
}

int GameObject::Get_MaxHealth()
{
	return this->_Health_Componment.Get_MaxHealth();
}

bool GameObject::Get_Is_Alive()
{
	return this->_Health_Componment.Is_Alive();
}

GameObjectBase& GameObjectBase::GetObjectBase()
{
	static GameObjectBase* ObjectBase{ new GameObjectBase };
	return *ObjectBase;
}

const std::string GameObjectBase::Get_Version()
{
	return Tanxl_ClassBase::Get_Version();
}

GameObjectBase::GameObjectBase() : Tanxl_ClassBase("0.4") {}

GameObjectBase::~GameObjectBase() {}

GameObjectBase::GameObjectBase(const GameObjectBase&) : Tanxl_ClassBase("0.4") {}

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

bool Componment_Unite::AppendComponment(Componment_Base* CM)
{
	for (auto Componment : this->_Object_Content)//根据名称添加
	{
		if (Componment->GetName() == CM->GetName())
			return false;//出现同名组件——添加失败
	}
	this->_Object_Content.push_back(CM);
	return true;
}

bool Componment_Unite::RemoveComponment(std::string Name)
{
	for (std::vector<Componment_Base*>::iterator IOCB{ this->_Object_Content.begin() }; IOCB != this->_Object_Content.end(); ++IOCB)//根据名称删除
	{
		if ((*IOCB)->GetName() == Name)
		{
			_Object_Content.erase(IOCB);
			return true;
		}
	}
	return false;
}

GameObject* Main_Character::Get_Main_Character()
{
	static GameObject* MainCharacter{ new GameObject(11, 5) };
	return MainCharacter;
}

Main_Character::Main_Character() {}

Main_Character::~Main_Character() {}

Main_Character::Main_Character(const Main_Character&) {}

Main_Character& Main_Character::operator=(const Main_Character&) { return *this; }
