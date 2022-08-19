#pragma once

#include "Tanxl_InsertAction.h"

Key_Unit::Key_Unit() :GLFW_KEY(NULL), MoveToX(false), MoveToY(false), MoveLen(0.0f) {}

Key_Unit::Key_Unit(int GLKEY, bool MOVX, bool MOVY, float MOVL)
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

void InsertEventBase::GetInsert(GLFWwindow* window, float* MoveX, float* MoveY)
{
	for (int i = 0; i < _KeyEventS.size(); i++)
	{
		if (glfwGetKey(window, _KeyEventS.at(i).GLFW_KEY) == GLFW_PRESS)
		{
			if (_KeyEventS.at(i).MoveToX/* &&
				((*MoveX >= 0 && i + 1 < static_cast<int>(_PTB->size()) && _PTB->at(static_cast<std::vector<bool, std::allocator<bool>>::size_type>(i) + 1))
					|| (*MoveX < 0 && i - 1 >= 0 && _PTB->at(static_cast<std::vector<bool, std::allocator<bool>>::size_type>(i) - 1)))*/)
				*MoveX += _KeyEventS.at(i).MoveLen;
			if (_KeyEventS.at(i).MoveToY/* &&
				(*MoveY >= 0 && i + _Max_Line < static_cast<int>(_PTB->size()) && _PTB->at(static_cast<std::vector<bool, std::allocator<bool>>::size_type>(i) + _Max_Line))
				|| (*MoveY < 0 && i - _Max_Line >= 0 && _PTB->at(static_cast<std::vector<bool, std::allocator<bool>>::size_type>(i) - _Max_Line))*/)
				*MoveY += _KeyEventS.at(i).MoveLen;
			AutoCheck(MoveX, MoveY);
			std::cout << "BUTTON PUSHED x_" << *MoveX << "y_" << *MoveY << std::endl;
		}
	}
}

void InsertEventBase::Set_MaxFloat(float Max_float)
{
	this->_Max_float = Max_float;
}

void InsertEventBase::Set_MaxLine(int Max_Line)
{
	this->_Max_Line = Max_Line;
}

void InsertEventBase::Get_MoveData(std::vector<bool>* PVB)
{
	this->_PTB = PVB;
}

void InsertEventBase::AutoCheck(float* MoveX, float* MoveY)
{
	if (*MoveX >= _Max_float)
		*MoveX = _Max_float;
	else if (*MoveX <= -_Max_float)
		*MoveX = -_Max_float;

	if (*MoveY >= _Max_float)
		*MoveY = _Max_float;
	else if (*MoveY <= -_Max_float)
		*MoveY = -_Max_float;
}

//UnImportant µ¥ÀýÊµÏÖ

InsertEventBase::InsertEventBase() :_KeyEventS(NULL), _Max_float(1.0f), _PTB(NULL), _Max_Line(0) {}

InsertEventBase::~InsertEventBase()
{
	for (int i = 0; i < _KeyEventS.size(); i++)
		delete & _KeyEventS.at(i);
	_KeyEventS.clear();
}

InsertEventBase::InsertEventBase(const InsertEventBase&) :_KeyEventS(NULL), _Max_float(1.0f), _PTB(NULL), _Max_Line(0) {}

InsertEventBase& InsertEventBase::operator=(const InsertEventBase&)
{
	return *this;
}