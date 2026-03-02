#pragma once

#include "Tanxl_InsertAction.h"

float Key_Observer::_Speed_Rato{ 1.0f };

static void curse_poscallback(GLFWwindow* window, double x, double y)
{
	static InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };
#if _TANXL_INSERTACTION_CONSOLE_MOUSE_OUTPUT_
	std::cout << "(pos:" << x << "," << y << ")" << std::endl;
#endif
	IEB->Set_Mouse_Pos(x, y);
}

InsertEventBase& InsertEventBase::GetInsertBase()
{
	static InsertEventBase* IEB{ new InsertEventBase };
	return *IEB;
}

float InsertEventBase::Get_AutoFloat(int Blocks)
{
	return (1.0f - 1.0f / Blocks);
}

Tanxl_Coord<double> InsertEventBase::Get_Mouse_Location() const
{
	return this->_Mouse_Pos;
}

void InsertEventBase::RemoveAllEvent()
{
	std::vector<int>().swap(this->_KeyNameS);
	this->_InsertCheck.Remove_Observer();
}

void InsertEventBase::GetInsert(GLFWwindow* window, GameStateBase* State, GameObject& Character)
{
	static OpenGL_Draw* OPD{ &OpenGL_Draw::GetOpenGLBase() };
	static SoundBase* SB{ &SoundBase::GetSoundBase() };
	double MoveScale{ OPD->Get_DeltaTime() };
	State->Update_Last_Location(Character);

	if (this->_Is_Key_Enable == false)
		return;

	this->_Insert_Move_Length = 0.0f;

	Character.Get_Last_Move()->_Coord_X = 0.0f;
	Character.Get_Last_Move()->_Coord_Y = 0.0f;

	if (this->_KeyNameS.size() == 0)
		return;

	for (int i{ 0 }; i < this->_KeyNameS.size(); ++i)
	{
		if (glfwGetKey(window, this->_KeyNameS.at(i)) == GLFW_PRESS)
		{
			_Is_Key_Pressed = true;
			this->_KeyCheck.Notify(this->_KeyNameS.at(i));

			if (OPD->Get_Adjust_Status())
				return;

			this->_InsertCheck.Notify(this->_KeyNameS.at(i));
		}
	}
	this->_Insert_Move_Length *= MoveScale;

	this->_Insert_Status = 0;
	if (this->_Insert_Move_Length._Coord_Y < 0)
	{
		this->_Insert_Status |= 1;
	}
	if (this->_Insert_Move_Length._Coord_X > 0)
	{
		this->_Insert_Status |= 2;
	}
	if (this->_Insert_Move_Length._Coord_Y > 0)
	{
		this->_Insert_Status |= 4;
	}
	if (this->_Insert_Move_Length._Coord_X < 0)
	{
		this->_Insert_Status |= 8;
	}

	*Character.Get_Last_Move() += this->_Insert_Move_Length;
	*Character.Get_Distance_Move() += this->_Insert_Move_Length;
	*Character.Get_Distance_Mid() += this->_Insert_Move_Length;

	AutoCheck(*Character.Get_Distance_Mid(), *Character.Get_Distance_Move());
#if _TANXL_INSERTACTION_CONSOLE_BASE_OUTPUT_
	std::cout << "Move Distance X :" << *Character.Get_Distance_Move()._Coord_X << " -  Y :" << *Character.Get_Distance_Move()._Coord_Y << std::endl;
#endif
}

void InsertEventBase::GetMouseInput(GLFWwindow* window)
{
	static SoundBase* SB{ &SoundBase::GetSoundBase() };
	static GameTips* Tips{ &GameTips::GetTipsBase() };
	static int LastMouseStatus_1{ GLFW_RELEASE };
	static int LastMouseStatus_2{ GLFW_RELEASE };

	if (this->_Is_Key_Enable == false)
		return;

	glfwSetCursorPosCallback(window, curse_poscallback);

	int Temp_Mouse_Status_1{ glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) };
	int Temp_Mouse_Status_2{ glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) };

	if (Temp_Mouse_Status_1 == GLFW_RELEASE)
	{
		if (LastMouseStatus_1 == GLFW_PRESS)
		{
			SB->Play_Sound(SOUND_MOUSE_CLICK);
			std::cout << "Mouse 1 Press" << std::endl;
			Tips->Update_Count();
			_Is_Key_Pressed = true;
		}
	}
	if (Temp_Mouse_Status_2 == GLFW_RELEASE)
	{
		if (LastMouseStatus_2 == GLFW_PRESS)
		{
			SB->Play_Sound(SOUND_MOUSE_CLICK);
			std::cout << "Mouse 2 Press" << std::endl;
			Tips->Update_Count();
			_Is_Key_Pressed = true;
		}
	}

	LastMouseStatus_1 = Temp_Mouse_Status_1;
	LastMouseStatus_2 = Temp_Mouse_Status_2;
}

void InsertEventBase::Set_MaxFloat(float Max_floatX, float Max_floatY)
{
	if (Max_floatY == 0.0f)
		this->_Maximum_Distance = Max_floatX;
	else
	{
		this->_Maximum_Distance._Coord_X = Max_floatX;
		this->_Maximum_Distance._Coord_Y = Max_floatY;
	}
}

void InsertEventBase::RegistEvent(int GLFW_KEY, MoveTo_Direction MOVETO_VERT, float Move_Length)
{
	this->_InsertCheck.Add_Observer(new Key_Observer(GLFW_KEY, MOVETO_VERT, Move_Length, &this->_Insert_Move_Length));
	this->_KeyNameS.push_back(GLFW_KEY);
}

void InsertEventBase::RegistEvent(int GLFW_KEY, bool* BindStatus)
{
	this->_KeyCheck.Add_Observer(new Press_Observer(GLFW_KEY, BindStatus));
	this->_KeyNameS.push_back(GLFW_KEY);
}

void InsertEventBase::Set_StateRange(bool Enable)
{
	this->_Is_State_Range = Enable;
}

void InsertEventBase::Set_MultiSpeed(double Adjust_Value)
{
	Key_Observer::Set_Speed_Ratio(static_cast<float>(Adjust_Value));
}

void InsertEventBase::Set_Key_Enable(bool Enable)
{
	this->_Is_Key_Enable = Enable;
}

void InsertEventBase::Init_Default_Key()
{
	//InsertKey Init //多次注册会导致多次移动
	this->RegistEvent(GLFW_KEY_UP, MOVETO_VERT, 0.5f);
	this->RegistEvent(GLFW_KEY_W, MOVETO_VERT, 0.5f);
	this->RegistEvent(GLFW_KEY_LEFT, MOVETO_PARA, -0.5f);
	this->RegistEvent(GLFW_KEY_A, MOVETO_PARA, -0.5f);
	this->RegistEvent(GLFW_KEY_RIGHT, MOVETO_PARA, 0.5f);
	this->RegistEvent(GLFW_KEY_D, MOVETO_PARA, 0.5f);
	this->RegistEvent(GLFW_KEY_DOWN, MOVETO_VERT, -0.5f);
	this->RegistEvent(GLFW_KEY_S, MOVETO_VERT, -0.5f);
}

void InsertEventBase::Set_Mouse_Pos(double LocationX, double LocationY)
{
	this->_Mouse_Pos._Coord_X = LocationX;
	this->_Mouse_Pos._Coord_Y = LocationY;
}

void InsertEventBase::Set_Trigger_Range(float Ratio)
{
	this->_Maximum_Distance *= static_cast<double>(Ratio);
}

void InsertEventBase::Reset_Move_Range()
{
	this->_Maximum_Distance = 1.0f;
}

bool InsertEventBase::Get_Key_Pressed()
{
	bool Temp_Element{ _Is_Key_Pressed };
	this->_Is_Key_Pressed = false;
	return Temp_Element;
}

bool InsertEventBase::Check_Key_Press(GLFWwindow* Window)
{
	for (int i{ 32 }; i < 96; ++i)
		if (glfwGetKey(Window, i) == GLFW_PRESS)
			return true;
	for (int i{ 256 }; i < 348; ++i)
		if (glfwGetKey(Window, i) == GLFW_PRESS)
			return true;
	return false;
}

short InsertEventBase::Get_Reach_Edge() const
{
	return this->_Is_Reach_Edge;
}

unsigned InsertEventBase::Get_Insert_Status() const
{
	static unsigned Insert_Mask{ this->_Insert_Status };
	if (Insert_Mask & this->_Insert_Status)
		return Insert_Mask & this->_Insert_Status;
	else
	{
		Insert_Mask = this->_Insert_Status;
		return this->_Insert_Status;
	}
}

const std::string InsertEventBase::Get_Version()
{
	return Tanxl_ClassBase::Get_Version();
}

void InsertEventBase::AutoCheck(Tanxl_Coord<float>& Screen_Move, Tanxl_Coord<float>& Move_Distance)
{
	this->_Is_Reach_Edge = 0;

	if (!this->_Is_State_Range)
		return;

	if (Screen_Move._Coord_X > this->_Maximum_Distance._Coord_X)
	{
		this->_Is_Reach_Edge += 2;
		Move_Distance._Coord_X -= (Screen_Move._Coord_X - this->_Maximum_Distance._Coord_X);
		Screen_Move._Coord_X = this->_Maximum_Distance._Coord_X;

	}
	else if (Screen_Move._Coord_X < -this->_Maximum_Distance._Coord_X)
	{
		this->_Is_Reach_Edge += 1;
		Move_Distance._Coord_X -= (Screen_Move._Coord_X + this->_Maximum_Distance._Coord_X);
		Screen_Move._Coord_X = -this->_Maximum_Distance._Coord_X;
	}

	if (Screen_Move._Coord_Y > this->_Maximum_Distance._Coord_Y)
	{
		this->_Is_Reach_Edge += 8;
		Move_Distance._Coord_Y -= (Screen_Move._Coord_Y - this->_Maximum_Distance._Coord_Y);
		Screen_Move._Coord_Y = this->_Maximum_Distance._Coord_Y;
	}
	else if (Screen_Move._Coord_Y < -this->_Maximum_Distance._Coord_Y)
	{
		this->_Is_Reach_Edge += 4;
		Move_Distance._Coord_Y -= (Screen_Move._Coord_Y + this->_Maximum_Distance._Coord_Y);
		Screen_Move._Coord_Y = -this->_Maximum_Distance._Coord_Y;
	}
#if _TANXL_INSERTACTION_CONSOLE_AUTO_OUTPUT_
	std::cout << "this->_Margin_X " << this->_Margin_X << " this->_Margin_Y " << this->_Margin_X << std::endl;
#endif
}

//UnImportant 单例实现

InsertEventBase::InsertEventBase() :Tanxl_ClassBase("0.9"),
_Is_State_Range(true), _Is_Key_Pressed(false), _Is_Key_Enable(true) {}

InsertEventBase::~InsertEventBase() {}

InsertEventBase::InsertEventBase(const InsertEventBase&) :Tanxl_ClassBase("0.9"),
_Is_State_Range(true), _Is_Key_Pressed(false), _Is_Key_Enable(true) {}

InsertEventBase& InsertEventBase::operator=(const InsertEventBase&)
{
	return *this;
}

