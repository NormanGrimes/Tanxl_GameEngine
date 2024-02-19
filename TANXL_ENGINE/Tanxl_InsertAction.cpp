﻿#pragma once

#include "Tanxl_InsertAction.h"

Key_Unit::Key_Unit() :GLFW_KEY(NULL), MoveToX(false), MoveToY(false), MoveLen(0.0f), Unit_Type(0), SaveLen(0)
{
	RandomBase* UIB{ &RandomBase::GetRandomBase() };
	this->Unit_Name = UIB->GenerateAutoSeed();
#if _TANXL_INSERTACTION_CONSOLE_RANDOM_OUTPUT_
	std::cout << "KeyUnit :" << this->Unit_Name << std::endl;
#endif
}

Key_Unit::Key_Unit(int GLKEY, bool MOVX, bool MOVY, double MOVL, std::string UNAM)
	: GLFW_KEY(GLKEY), MoveToX(MOVX), MoveToY(MOVY), MoveLen(MOVL), Unit_Type(0), SaveLen(0)
{
	RandomBase* UIB{ &RandomBase::GetRandomBase() };
	if (UNAM == "")
		this->Unit_Name = UIB->GenerateAutoSeed();
	else
		this->Unit_Name = UNAM;
#if _TANXL_INSERTACTION_CONSOLE_RANDOM_OUTPUT_
	std::cout << "KeyUnit X :" << this->Unit_Name << "  Unit_Type :" << Unit_Type << std::endl;
#endif
}

Key_Unit::Key_Unit(int GLKEY, std::string UNAM) :
	GLFW_KEY(GLKEY), MoveLen(3), MoveToX(false), MoveToY(false), Unit_Type(1), SaveLen(0)
{
	RandomBase* UIB{ &RandomBase::GetRandomBase() };
	if (UNAM == "")
		this->Unit_Name = UIB->GenerateAutoSeed();
	else
		this->Unit_Name = UNAM;
#if _TANXL_INSERTACTION_CONSOLE_RANDOM_OUTPUT_
	std::cout << "KeyUnit X :" << this->Unit_Name << "  Unit_Type :" << Unit_Type << std::endl;
#endif
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
	_KeyEventS.push_back(KU);
}

void InsertEventBase::RemoveEvent()
{
	_KeyEventS.pop_back();
}

void InsertEventBase::GetInsert(GLFWwindow* window, GameStateBase* State)
{
	static OpenGL_Draw* OPD{ &OpenGL_Draw::GetOpenGLBase() };
	OPD->Update_Last_Location(State);
	this->_Margin_X = 0.0f;
	this->_Margin_Y = 0.0f;
	for (int i{ 0 }; i < this->_KeyEventS.size(); ++i)
	{
		if (glfwGetKey(window, this->_KeyEventS.at(i)->GLFW_KEY) == GLFW_PRESS)
		{
			_Is_Key_Pressed = true;
			if (this->_KeyEventS.at(i)->Unit_Type == 1)
			{
				this->_KeyEventS.at(i)->SaveLen++;
				if (this->_KeyEventS.at(i)->SaveLen > this->_KeyEventS.at(i)->MoveLen)
				{
					this->_KeyEventS.at(i)->MoveToY = !this->_KeyEventS.at(i)->MoveToY;
					this->_KeyEventS.at(i)->SaveLen = -25;
				}
				continue;
			}
			if (this->_KeyEventS.at(i)->MoveToY)
			{
				State->Get_Screen_Distance()._Location_Y += static_cast<float>(this->_KeyEventS.at(i)->MoveLen);
				State->Get_Move_Distance()._Location_Y += static_cast<float>(this->_KeyEventS.at(i)->MoveLen);
				this->_Margin_Y += static_cast<float>(this->_KeyEventS.at(i)->MoveLen);
			}
			if (this->_KeyEventS.at(i)->MoveToX)
			{
				State->Get_Screen_Distance()._Location_X += static_cast<float>(this->_KeyEventS.at(i)->MoveLen);
				State->Get_Move_Distance()._Location_X += static_cast<float>(this->_KeyEventS.at(i)->MoveLen);
				this->_Margin_X += static_cast<float>(this->_KeyEventS.at(i)->MoveLen);
			}
		}
		else
			if (this->_KeyEventS.at(i)->Unit_Type == 1)
				this->_KeyEventS.at(i)->SaveLen = 0;
	}
	AutoCheck(State->Get_Screen_Distance()._Location_X, State->Get_Screen_Distance()._Location_Y, State->Get_Move_Distance()._Location_X, State->Get_Move_Distance()._Location_Y);
#if _TANXL_INSERTACTION_CONSOLE_BASE_OUTPUT_
	std::cout << "Move Distance X :" << State->Get_Move_Distance()._LocX << " -  Y :" << State->Get_Move_Distance()._LocY << std::endl;
#endif
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
	bool Temp_Element{ _Is_Key_Pressed };
	this->_Is_Key_Pressed = false;
	return Temp_Element;
}

bool InsertEventBase::RemoveEvent(std::string Event_Name)
{
	for (int i{ 0 }; i < this->_KeyEventS.size(); ++i)
	{
		if (this->_KeyEventS.at(i)->Unit_Name == Event_Name)
		{
			this->_KeyEventS.erase(_KeyEventS.begin() + i);
			return true;
		}
	}
	return false;
}

short InsertEventBase::Get_Reach_Edge()
{
	return this->_Is_Reach_Edge;
}

const std::string InsertEventBase::Get_Version()
{
	return this->_Version;
}

void InsertEventBase::AutoCheck(float& Screen_MoveX, float& Screen_MoveY, float& Move_DistanceX, float& Move_DistanceY)
{
	this->_Is_Reach_Edge = 0;

	if (!this->_Is_State_Range)
		return;

	if (this->_Is_Max_Single)
		this->_Max_float = this->_Max_float_Width;
	if (Screen_MoveX > this->_Max_float)
	{
		this->_Is_Reach_Edge += 2;
		Move_DistanceX -= (Screen_MoveX - this->_Max_float);
		Screen_MoveX = this->_Max_float;

	}
	else if (Screen_MoveX < -this->_Max_float)
	{
		this->_Is_Reach_Edge += 1;
		Move_DistanceX -= (Screen_MoveX + this->_Max_float);
		Screen_MoveX = -this->_Max_float;
	}

	if (this->_Is_Max_Single)
		this->_Max_float = this->_Max_float_Height;

	if (Screen_MoveY > this->_Max_float)
	{
		this->_Is_Reach_Edge += 8;
		Move_DistanceY -= (Screen_MoveY - this->_Max_float);
		Screen_MoveY = this->_Max_float;
	}
	else if (Screen_MoveY < -this->_Max_float)
	{
		this->_Is_Reach_Edge += 4;
		Move_DistanceY -= (Screen_MoveY + this->_Max_float);
		Screen_MoveY = -this->_Max_float;
	}
#if _TANXL_INSERTACTION_CONSOLE_AUTO_OUTPUT_
	std::cout << "this->_Margin_X " << this->_Margin_X << " this->_Margin_Y " << this->_Margin_X << std::endl;
#endif
}

//UnImportant 单例实现

InsertEventBase::InsertEventBase() :_KeyEventS(NULL), _Is_Max_Single(false), _Max_float_Height(1), _Max_float_Width(1),
_Max_float(1.0f), _PTB(nullptr), _Margin_X(0.0f), _Margin_Y(0.0f), _Is_State_Range(true), _Is_Key_Pressed(false) 
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
	Key_Unit* MOVE_UP{ new Key_Unit(GLFW_KEY_UP, false, true, 0.01) };
	this->RegistEvent(MOVE_UP);
	MOVE_UP = new Key_Unit(GLFW_KEY_W, false, true, 0.01);
	this->RegistEvent(MOVE_UP);

	/*Key_Unit MOVE_LEFT;
	MOVE_LEFT.GLFW_KEY = GLFW_KEY_LEFT;
	MOVE_LEFT.MoveLen = -0.01;
	MOVE_LEFT.MoveToX = true;
	MOVE_LEFT.Unit_Type = 0;
	this->RegistEvent(MOVE_LEFT);
	MOVE_LEFT.GLFW_KEY = GLFW_KEY_A;
	this->RegistEvent(MOVE_LEFT);*/
	// OR ↓
	Key_Unit* MOVE_LEFT{ new Key_Unit(GLFW_KEY_LEFT, true, false, -0.01) };
	this->RegistEvent(MOVE_LEFT);
	MOVE_LEFT = new Key_Unit(GLFW_KEY_A, true, false, -0.01);
	this->RegistEvent(MOVE_LEFT);

	/*Key_Unit MOVE_RIGHT;
	MOVE_RIGHT.GLFW_KEY = GLFW_KEY_RIGHT;
	MOVE_RIGHT.MoveLen = 0.01;
	MOVE_RIGHT.MoveToX = true;
	MOVE_RIGHT.Unit_Type = 0;
	this->RegistEvent(MOVE_RIGHT);
	MOVE_RIGHT.GLFW_KEY = GLFW_KEY_D;
	this->RegistEvent(MOVE_RIGHT);*/
	// OR ↓
	Key_Unit* MOVE_RIGHT{ new Key_Unit(GLFW_KEY_RIGHT, true, false, 0.01) };
	this->RegistEvent(MOVE_RIGHT);
	MOVE_RIGHT = new Key_Unit(GLFW_KEY_D, true, false, 0.01);
	this->RegistEvent(MOVE_RIGHT);

	/*Key_Unit MOVE_DOWN;
	MOVE_DOWN.GLFW_KEY = GLFW_KEY_DOWN;
	MOVE_DOWN.MoveLen = -0.01;
	MOVE_DOWN.MoveToY = true;
	MOVE_RIGHT.Unit_Type = 0;
	this->RegistEvent(MOVE_DOWN);
	MOVE_DOWN.GLFW_KEY = GLFW_KEY_S;
	this->RegistEvent(MOVE_DOWN);*/
	// OR ↓
	Key_Unit* MOVE_DOWN{ new Key_Unit(GLFW_KEY_DOWN, false, true, -0.01) };
	this->RegistEvent(MOVE_DOWN);
	MOVE_DOWN = new Key_Unit(GLFW_KEY_S, false, true, -0.01);
	this->RegistEvent(MOVE_DOWN);
}

InsertEventBase::~InsertEventBase()
{
	for (int i{ 0 }; i < this->_KeyEventS.size(); ++i)
		delete & this->_KeyEventS.at(i);
	this->_KeyEventS.clear();
}

InsertEventBase::InsertEventBase(const InsertEventBase&) :
	_KeyEventS(NULL), _Max_float(1.0f), _PTB(nullptr), _Is_Max_Single(false),
	_Max_float_Height(1), _Max_float_Width(1), _Margin_X(0.0f), _Margin_Y(0.0f), _Is_State_Range(true), _Is_Key_Pressed(false) 
{
	Key_Unit* MOVE_UP{ new Key_Unit(GLFW_KEY_UP, false, true, 0.01) };
	this->RegistEvent(MOVE_UP);
	MOVE_UP = new Key_Unit(GLFW_KEY_W, false, true, 0.01);
	this->RegistEvent(MOVE_UP);

	Key_Unit* MOVE_LEFT{ new Key_Unit(GLFW_KEY_LEFT, true, false, -0.01) };
	this->RegistEvent(MOVE_LEFT);
	MOVE_LEFT = new Key_Unit(GLFW_KEY_A, true, false, -0.01);
	this->RegistEvent(MOVE_LEFT);

	Key_Unit* MOVE_RIGHT{ new Key_Unit(GLFW_KEY_RIGHT, true, false, 0.01) };
	this->RegistEvent(MOVE_RIGHT);
	MOVE_RIGHT = new Key_Unit(GLFW_KEY_D, true, false, 0.01);
	this->RegistEvent(MOVE_RIGHT);

	Key_Unit* MOVE_DOWN{ new Key_Unit(GLFW_KEY_DOWN, false, true, -0.01) };
	this->RegistEvent(MOVE_DOWN);
	MOVE_DOWN = new Key_Unit(GLFW_KEY_S, false, true, -0.01);
	this->RegistEvent(MOVE_DOWN);
}

InsertEventBase& InsertEventBase::operator=(const InsertEventBase&)
{
	return *this;
}