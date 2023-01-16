#pragma once

#include "Tanxl_InsertAction.h"

Key_Unit::Key_Unit() :GLFW_KEY(NULL), MoveToX(false), MoveToY(false), MoveLen(0.0f) {}

Key_Unit::Key_Unit(int GLKEY, bool MOVX, bool MOVY, double MOVL)
	: GLFW_KEY(GLKEY), MoveToX(MOVX), MoveToY(MOVY), MoveLen(MOVL) {}

InsertEventBase& InsertEventBase::GetInsertBase()
{
	static InsertEventBase* IEB = new InsertEventBase;
	return *IEB;
}

float InsertEventBase::Get_AutoFloat(int Blocks)
{
	return (1.0f - 1.0f / Blocks);
}

void InsertEventBase::RegistEvent(Key_Unit KU)
{
	_KeyEventS.push_back(KU);
}

void InsertEventBase::GetInsert(GLFWwindow* window, float* MoveX, float* MoveY, float* StateX, float* StateY)
{
	for (int i = 0; i < _KeyEventS.size(); i++)
	{
		if (glfwGetKey(window, _KeyEventS.at(i).GLFW_KEY) == GLFW_PRESS)
		{
			_Is_Key_Pressed = true;
			if (_KeyEventS.at(i).MoveToX)
			{
				*MoveX += _KeyEventS.at(i).MoveLen;
				_Margin_X = _KeyEventS.at(i).MoveLen;
				_Margin_Y = 0;
			}
			if (_KeyEventS.at(i).MoveToY)
			{
				*MoveY += _KeyEventS.at(i).MoveLen;
				_Margin_Y = _KeyEventS.at(i).MoveLen;
				_Margin_X = 0;
			}
			if (AutoCheck(MoveX, MoveY) == 3)
			{
				if (StateX != NULL && StateY != NULL)
				{
					*StateX -= _Margin_X;
					*StateY -= _Margin_Y;
				}
			}
			//std::cout << "BUTTON PUSHED x_" << *MoveX << "y_" << *MoveY << std::endl;
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

unsigned InsertEventBase::AutoCheck(float* MoveX, float* MoveY)
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

//UnImportant µ¥ÀýÊµÏÖ

InsertEventBase::InsertEventBase() :_KeyEventS(NULL), _Is_Max_Single(false), _Max_float_Height(1), _Max_float_Width(1),
_Max_float(1.0f), _PTB(NULL), _Max_Line(0), _Margin_X(0.0f), _Margin_Y(0.0f), _Is_State_Range(true), _Is_Key_Pressed(false) {}

InsertEventBase::~InsertEventBase()
{
	for (int i = 0; i < _KeyEventS.size(); i++)
		delete & _KeyEventS.at(i);
	_KeyEventS.clear();
}

InsertEventBase::InsertEventBase(const InsertEventBase&) :
	_KeyEventS(NULL), _Max_float(1.0f), _PTB(NULL), _Max_Line(0), _Is_Max_Single(false), 
	_Max_float_Height(1), _Max_float_Width(1),_Margin_X(0.0f), _Margin_Y(0.0f), _Is_State_Range(true), _Is_Key_Pressed(false) {}

InsertEventBase& InsertEventBase::operator=(const InsertEventBase&)
{
	return *this;
}