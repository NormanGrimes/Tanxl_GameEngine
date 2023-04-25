#pragma once

#include "Tanxl_InsertAction.h"

Key_Unit::Key_Unit() :GLFW_KEY(NULL), MoveToX(false), MoveToY(false), MoveLen(0.0f), Unit_Type(0) 
{
	UniqueIdBase* UIB{ &UniqueIdBase::GetIdGenerator() };
	Unit_Name = UIB->GenerateAutoSeed();
	std::cout << "KeyUnit :" << Unit_Name << std::endl;
}

Key_Unit::Key_Unit(int GLKEY, bool MOVX, bool MOVY, double MOVL, std::string UNAM)
	: GLFW_KEY(GLKEY), MoveToX(MOVX), MoveToY(MOVY), MoveLen(MOVL), Unit_Type(0) 
{
	UniqueIdBase* UIB{ &UniqueIdBase::GetIdGenerator() };
	if (UNAM == "")
		UNAM = UIB->GenerateAutoSeed();
	std::cout << "KeyUnit :" << UNAM << std::endl;
}

Key_Unit::Key_Unit(int GLKEY, bool* CustomX, bool* CustomY, std::string UNAM) :
	GLFW_KEY(GLKEY), MoveToX(CustomX), MoveToY(CustomY), MoveLen(0.0f), Unit_Type(1) 
{
	UniqueIdBase* UIB{ &UniqueIdBase::GetIdGenerator() };
	if (UNAM == "")
		UNAM = UIB->GenerateAutoSeed();
	std::cout << "KeyUnit :" << UNAM << std::endl;
}

InsertEventBase& InsertEventBase::GetInsertBase()
{
	static InsertEventBase* IEB = new InsertEventBase;
	return *IEB;
}

float InsertEventBase::Get_AutoFloat(int Blocks)
{
	return (1.0f - 1.0f / Blocks);
}

void InsertEventBase::RegistEvent(Key_Unit* KU)
{
	if (KU->Unit_Type == 0)
	{
		Key_Unit* NKU = new Key_Unit(KU->GLFW_KEY, KU->MoveToX, KU->MoveToY, KU->MoveLen);
		_KeyEventS.push_back(NKU);
	}
	else
		_KeyEventS.push_back(KU);
}

void InsertEventBase::RemoveEvent()
{
	_KeyEventS.pop_back();
}

void InsertEventBase::GetInsert(GLFWwindow* window, float& MoveX, float& MoveY, float& StateX, float& StateY, float& Move_AdjustX, float& Move_AdjustY)
{
	for (int i = 0; i < _KeyEventS.size(); i++)
	{
		//std::cout << "_KeyEventS.at(i)->GLFW_KEY" << _KeyEventS.at(i)->GLFW_KEY << std::endl;
		if (glfwGetKey(window, _KeyEventS.at(i)->GLFW_KEY) == GLFW_PRESS)
		{
			_Is_Key_Pressed = true;
			if (_KeyEventS.at(i)->Unit_Type == 1)
			{
				_Is_Key_Pressed = false;
				//std::cout << "_KeyEventS.at(i).MoveToX" << _KeyEventS.at(i)->MoveToX << std::endl;
				_KeyEventS.at(i)->MoveToX = !_KeyEventS.at(i)->MoveToX;
				_KeyEventS.at(i)->MoveToY = !_KeyEventS.at(i)->MoveToY;
				//std::cout << "MoveToX" << _KeyEventS.at(i)->MoveToX << std::endl;
			}
			if (_KeyEventS.at(i)->MoveToX)
			{
				MoveX += static_cast<float>(_KeyEventS.at(i)->MoveLen);
				_Margin_X = static_cast<float>(_KeyEventS.at(i)->MoveLen);
				_Margin_Y = 0;
			}
			if (_KeyEventS.at(i)->MoveToY)
			{
				MoveY += static_cast<float>(_KeyEventS.at(i)->MoveLen);
				_Margin_Y = static_cast<float>(_KeyEventS.at(i)->MoveLen);
				_Margin_X = 0;
			}
			if (AutoCheck(&MoveX, &MoveY) == 3 && _KeyEventS.at(i)->Unit_Type == 0)
			{
				Move_AdjustX -= _Margin_X;
				Move_AdjustY -= _Margin_Y;
				StateX -= _Margin_X;
				StateY -= _Margin_Y;
			}
			//std::cout << "BUTTON PUSHED x_" << *MoveX << "y_" << *MoveY << std::endl;
			//std::cout << "BUTTON PUSHED x_" << *deputyX << "y_" << *deputyY << std::endl;
		}
	}
}

void InsertEventBase::Set_MaxFloat(float Max_float)
{
	this->_Is_Max_Single = false;
	this->_Max_float = Max_float;
}

void InsertEventBase::Set_MaxFloat_Height(float Max_float)
{
	this->_Is_Max_Single = true;
	this->_Max_float_Height = Max_float;
}

void InsertEventBase::Set_MaxFloat_Width(float Max_float)
{
	this->_Is_Max_Single = true;
	this->_Max_float_Width = Max_float;
}

void InsertEventBase::Set_MaxLine(int Max_Line)
{
	this->_Max_Line = Max_Line;
}

void InsertEventBase::Get_MoveData(std::vector<bool>* PVB)
{
	this->_PTB = PVB;
}

void InsertEventBase::Set_StateRange(bool Enable)
{
	this->_Is_State_Range = Enable;
}

float InsertEventBase::Get_Margin_X()
{
	return this->_Margin_X;
}

float InsertEventBase::Get_Margin_Y()
{
	return this->_Margin_Y;
}

bool InsertEventBase::Get_Key_Pressed()
{
	bool Temp_Element = _Is_Key_Pressed;
	_Is_Key_Pressed = false;
	return Temp_Element;
}

bool InsertEventBase::RemoveEvent(std::string Event_Name)
{
	for (int i = 0; i < _KeyEventS.size(); i++)
	{
		if (_KeyEventS.at(i)->Unit_Name == Event_Name)
		{
			_KeyEventS.erase(_KeyEventS.begin() + i);
			return true;
		}
	}
	return false;
}

unsigned InsertEventBase::AutoCheck(float* MoveX, float* MoveY, float* DeptX, float* DeptY)
{
	unsigned Return_Value = 0;

	if (!_Is_State_Range)
		return 3;

	if (_Is_Max_Single)
		_Max_float = _Max_float_Width;

	if (*MoveX > _Max_float)
		*MoveX = _Max_float;
	else if (*MoveX < -_Max_float)
		*MoveX = -_Max_float;
	else
		Return_Value |= 1;

	if (_Is_Max_Single)
		_Max_float = _Max_float_Height;

	if (*MoveY > _Max_float)
		*MoveY = _Max_float;
	else if (*MoveY < -_Max_float)
		*MoveY = -_Max_float;
	else
		Return_Value |= 2;

	return Return_Value;
}

//UnImportant 单例实现

InsertEventBase::InsertEventBase() :_KeyEventS(NULL), _Is_Max_Single(false), _Max_float_Height(1), _Max_float_Width(1),
_Max_float(1.0f), _PTB(NULL), _Max_Line(0), _Margin_X(0.0f), _Margin_Y(0.0f), _Is_State_Range(true), _Is_Key_Pressed(false) 
{
	//InsertKey Init //多次注册会导致多次移动

	/*Key_Unit MOVE_UP;
	MOVE_UP.GLFW_KEY = GLFW_KEY_UP;
	MOVE_UP.MoveLen = 0.01;
	MOVE_UP.MoveToY = true;
	MOVE_UP.Unit_Type = 0;
	this->RegistEvent(MOVE_UP);
	MOVE_UP.GLFW_KEY = GLFW_KEY_W;
	this->RegistEvent(MOVE_UP);*/
	// OR ↓
	Key_Unit MOVE_UP = Key_Unit(GLFW_KEY_UP, false, true, 0.01);
	this->RegistEvent(&MOVE_UP);
	MOVE_UP = Key_Unit(GLFW_KEY_W, false, true, 0.01);
	this->RegistEvent(&MOVE_UP);

	/*Key_Unit MOVE_LEFT;
	MOVE_LEFT.GLFW_KEY = GLFW_KEY_LEFT;
	MOVE_LEFT.MoveLen = -0.01;
	MOVE_LEFT.MoveToX = true;
	MOVE_LEFT.Unit_Type = 0;
	this->RegistEvent(MOVE_LEFT);
	MOVE_LEFT.GLFW_KEY = GLFW_KEY_A;
	this->RegistEvent(MOVE_LEFT);*/
	// OR ↓
	Key_Unit MOVE_LEFT = Key_Unit(GLFW_KEY_LEFT, true, false, -0.01);
	this->RegistEvent(&MOVE_LEFT);
	MOVE_LEFT = Key_Unit(GLFW_KEY_A, true, false, -0.01);
	this->RegistEvent(&MOVE_LEFT);

	/*Key_Unit MOVE_RIGHT;
	MOVE_RIGHT.GLFW_KEY = GLFW_KEY_RIGHT;
	MOVE_RIGHT.MoveLen = 0.01;
	MOVE_RIGHT.MoveToX = true;
	MOVE_RIGHT.Unit_Type = 0;
	this->RegistEvent(MOVE_RIGHT);
	MOVE_RIGHT.GLFW_KEY = GLFW_KEY_D;
	this->RegistEvent(MOVE_RIGHT);*/
	// OR ↓
	Key_Unit MOVE_RIGHT = Key_Unit(GLFW_KEY_RIGHT, true, false, 0.01);
	this->RegistEvent(&MOVE_RIGHT);
	MOVE_RIGHT = Key_Unit(GLFW_KEY_D, true, false, 0.01);
	this->RegistEvent(&MOVE_RIGHT);

	/*Key_Unit MOVE_DOWN;
	MOVE_DOWN.GLFW_KEY = GLFW_KEY_DOWN;
	MOVE_DOWN.MoveLen = -0.01;
	MOVE_DOWN.MoveToY = true;
	MOVE_RIGHT.Unit_Type = 0;
	this->RegistEvent(MOVE_DOWN);
	MOVE_DOWN.GLFW_KEY = GLFW_KEY_S;
	this->RegistEvent(MOVE_DOWN);*/
	// OR ↓
	Key_Unit MOVE_DOWN = Key_Unit(GLFW_KEY_DOWN, false, true, -0.01);
	this->RegistEvent(&MOVE_DOWN);
	MOVE_DOWN = Key_Unit(GLFW_KEY_S, false, true, -0.01);
	this->RegistEvent(&MOVE_DOWN);
}

InsertEventBase::~InsertEventBase()
{
	for (int i = 0; i < _KeyEventS.size(); i++)
		delete & _KeyEventS.at(i);
	_KeyEventS.clear();
}

InsertEventBase::InsertEventBase(const InsertEventBase&) :
	_KeyEventS(NULL), _Max_float(1.0f), _PTB(NULL), _Max_Line(0), _Is_Max_Single(false),
	_Max_float_Height(1), _Max_float_Width(1), _Margin_X(0.0f), _Margin_Y(0.0f), _Is_State_Range(true), _Is_Key_Pressed(false) 
{
	Key_Unit MOVE_UP = Key_Unit(GLFW_KEY_UP, false, true, 0.01);
	this->RegistEvent(&MOVE_UP);
	MOVE_UP = Key_Unit(GLFW_KEY_W, false, true, 0.01);
	this->RegistEvent(&MOVE_UP);

	Key_Unit MOVE_LEFT = Key_Unit(GLFW_KEY_LEFT, true, false, -0.01);
	this->RegistEvent(&MOVE_LEFT);
	MOVE_LEFT = Key_Unit(GLFW_KEY_A, true, false, -0.01);
	this->RegistEvent(&MOVE_LEFT);

	Key_Unit MOVE_RIGHT = Key_Unit(GLFW_KEY_RIGHT, true, false, 0.01);
	this->RegistEvent(&MOVE_RIGHT);
	MOVE_RIGHT = Key_Unit(GLFW_KEY_D, true, false, 0.01);
	this->RegistEvent(&MOVE_RIGHT);

	Key_Unit MOVE_DOWN = Key_Unit(GLFW_KEY_DOWN, false, true, -0.01);
	this->RegistEvent(&MOVE_DOWN);
	MOVE_DOWN = Key_Unit(GLFW_KEY_S, false, true, -0.01);
	this->RegistEvent(&MOVE_DOWN);
}

InsertEventBase& InsertEventBase::operator=(const InsertEventBase&)
{
	return *this;
}