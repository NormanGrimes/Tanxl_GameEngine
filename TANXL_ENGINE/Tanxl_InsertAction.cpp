#pragma once

#include "Tanxl_InsertAction.h"

void curse_poscallback(GLFWwindow* window, double x, double y)
{
	static InsertEventBase* IEB{ &InsertEventBase::GetInsertBase() };
#if _TANXL_INSERTACTION_CONSOLE_MOUSE_OUTPUT_
	std::cout << "(pos:" << x << "," << y << ")" << std::endl;
#endif
	IEB->Set_Mouse_Pos(x, y);
}

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

bool Key_Unit::Get_KeyStatus()
{
	return this->MoveToY;
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

int InsertEventBase::RegistEvent(Key_Unit* KU)
{
	Key_Event* KE{ new Key_Event(KU) };
	this->_KeyEventS.push_back(KE);
	return static_cast<int>(this->_KeyEventS.size()) - 1;
}

Tanxl_Coord<double> InsertEventBase::Get_Mouse_Location()
{
	return this->_Mouse_Pos;
}

void InsertEventBase::RemoveEvent()
{
	if (this->_KeyEventS.size() != 0)
		this->_KeyEventS.erase(this->_KeyEventS.end() - 1, this->_KeyEventS.end());
}

size_t InsertEventBase::Get_KeyEvent_Size()
{
	return this->_KeyEventS.size();
}

void InsertEventBase::GetInsert(GLFWwindow* window, GameStateBase* State)
{
	static double LastTime{ glfwGetTime() };
	static OpenGL_Draw* OPD{ &OpenGL_Draw::GetOpenGLBase() };
	static SoundBase* SB{ &SoundBase::GetSoundBase() };
	double MoveScale{ glfwGetTime() - LastTime };
	LastTime = glfwGetTime();
	OPD->Update_Last_Location(State);

	if (this->_Is_Key_Enable == false)
		return;

	this->_LastMove._Coord_X = 0.0f;
	this->_LastMove._Coord_Y = 0.0f;

	double Insert_Move_LengthX{ 0.0f };
	double Insert_Move_LengthY{ 0.0f };

	for (int i{ 0 }; i < this->_KeyEventS.size(); ++i)
	{
		if (glfwGetKey(window, this->_KeyEventS.at(i)->_Key_Unit->GLFW_KEY) == GLFW_PRESS)
		{
			_Is_Key_Pressed = true;
			if (this->_KeyEventS.at(i)->_Key_Unit->Unit_Type == 1)
			{
				this->_KeyEventS.at(i)->_Key_Unit->SaveLen++;
				if (this->_KeyEventS.at(i)->_Key_Unit->SaveLen > this->_KeyEventS.at(i)->_Key_Unit->MoveLen)
				{
					this->_KeyEventS.at(i)->_Key_Unit->MoveToY = !this->_KeyEventS.at(i)->_Key_Unit->MoveToY;
					this->_KeyEventS.at(i)->_Key_Unit->SaveLen = -25;

					this->_KeyEventS.at(i)->_Press_Count++;
					this->_KeyEventS.at(i)->_Is_Key_Press = true;
				}
				continue;
			}
			if (!OPD->Get_Adjust_Status())
			{
				if (this->_KeyEventS.at(i)->_Key_Unit->MoveToY)
					Insert_Move_LengthY += this->_KeyEventS.at(i)->_Key_Unit->MoveLen;
				if (this->_KeyEventS.at(i)->_Key_Unit->MoveToX)
					Insert_Move_LengthX += this->_KeyEventS.at(i)->_Key_Unit->MoveLen;
			}
		}
		else
			if (this->_KeyEventS.at(i)->_Key_Unit->Unit_Type == 1)
				this->_KeyEventS.at(i)->_Key_Unit->SaveLen = 0;
	}
	Tanxl_Coord<float> Insert_Length(
		static_cast<float>(Insert_Move_LengthX * MoveScale), 
		static_cast<float>(Insert_Move_LengthY * MoveScale));

	State->Get_Screen_Distance() += Insert_Length;
	State->Get_Move_Distance() += Insert_Length;
	this->_LastMove += Insert_Length;

	AutoCheck(State->Get_Screen_Distance()._Coord_X, State->Get_Screen_Distance()._Coord_Y, State->Get_Move_Distance()._Coord_X, State->Get_Move_Distance()._Coord_Y);
#if _TANXL_INSERTACTION_CONSOLE_BASE_OUTPUT_
	std::cout << "Move Distance X :" << State->Get_Move_Distance()._LocX << " -  Y :" << State->Get_Move_Distance()._LocY << std::endl;
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

void InsertEventBase::Set_StateRange(bool Enable)
{
	this->_Is_State_Range = Enable;
}

void InsertEventBase::Set_MultiSpeed(int Start, int End, double Adjust_Value)
{
	if (Start < 0)
		Start = 0;
	if (End > this->_KeyEventS.size())
		End = static_cast<int>(this->_KeyEventS.size());
	if (End < Start)
		return;

	while (Start < End)
	{
		if (this->_KeyEventS.at(Start)->_Key_Unit->MoveLen > 0.0f)
			this->_KeyEventS.at(Start)->_Key_Unit->MoveLen += Adjust_Value;
		else if (this->_KeyEventS.at(Start)->_Key_Unit->MoveLen < 0.0f)
			this->_KeyEventS.at(Start)->_Key_Unit->MoveLen -= Adjust_Value;
		Start++;
	}
}

void InsertEventBase::Set_Key_Enable(bool Enable)
{
	this->_Is_Key_Enable = Enable;
}

void InsertEventBase::Init_Default_Key()
{
	//InsertKey Init //多次注册会导致多次移动

	Key_Unit* MOVE_UP{ new Key_Unit(GLFW_KEY_UP, false, true, 0.5) };
	this->RegistEvent(MOVE_UP);
	MOVE_UP = new Key_Unit(GLFW_KEY_W, false, true, 0.5);
	this->RegistEvent(MOVE_UP);

	Key_Unit* MOVE_LEFT{ new Key_Unit(GLFW_KEY_LEFT, true, false, -0.5) };
	this->RegistEvent(MOVE_LEFT);
	MOVE_LEFT = new Key_Unit(GLFW_KEY_A, true, false, -0.5);
	this->RegistEvent(MOVE_LEFT);

	Key_Unit* MOVE_RIGHT{ new Key_Unit(GLFW_KEY_RIGHT, true, false, 0.5) };
	this->RegistEvent(MOVE_RIGHT);
	MOVE_RIGHT = new Key_Unit(GLFW_KEY_D, true, false, 0.5);
	this->RegistEvent(MOVE_RIGHT);

	Key_Unit* MOVE_DOWN{ new Key_Unit(GLFW_KEY_DOWN, false, true, -0.5) };
	this->RegistEvent(MOVE_DOWN);
	MOVE_DOWN = new Key_Unit(GLFW_KEY_S, false, true, -0.5);
	this->RegistEvent(MOVE_DOWN);
}

void InsertEventBase::Update_Move_Max()
{
	OpenGL_Draw* OD{ &OpenGL_Draw::GetOpenGLBase() };
	this->_Max_float *= OD->Get_Trigger_Ratio();
	this->_Max_float_Height *= OD->Get_Trigger_Ratio();
	this->_Max_float_Width *= OD->Get_Trigger_Ratio();
}

void InsertEventBase::Set_Mouse_Pos(double LocationX, double LocationY)
{
	this->_Mouse_Pos._Coord_X = LocationX;
	this->_Mouse_Pos._Coord_Y = LocationY;
}

float InsertEventBase::Get_LastMove_X()
{
	return this->_LastMove._Coord_X;
}

float InsertEventBase::Get_LastMove_Y()
{
	return this->_LastMove._Coord_Y;
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
		if (this->_KeyEventS.at(i)->_Key_Unit->Unit_Name == Event_Name)
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
	return Tanxl_ClassBase::Get_Version();
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

InsertEventBase::InsertEventBase() :Tanxl_ClassBase("0.9"),
_KeyEventS(NULL), _Is_Max_Single(false), _Max_float_Height(1), _Max_float_Width(1), _Max_float(1.0f),
_LastMove(0.0f, 0.0f), _Is_State_Range(true), _Is_Key_Pressed(false), _Is_Key_Enable(true) {}

InsertEventBase::~InsertEventBase()
{
	std::vector<Key_Event*>().swap(this->_KeyEventS);
}

InsertEventBase::InsertEventBase(const InsertEventBase&) :Tanxl_ClassBase("0.9"),
_KeyEventS(NULL), _Max_float(1.0f), _Is_Max_Single(false), _Max_float_Height(1), _Max_float_Width(1),
_LastMove(0.0f, 0.0f), _Is_State_Range(true), _Is_Key_Pressed(false), _Is_Key_Enable(true) {}

InsertEventBase& InsertEventBase::operator=(const InsertEventBase&)
{
	return *this;
}

Key_Event::Key_Event(Key_Unit* Key) :_Key_Unit(Key), _Is_Key_Press(false), _Press_Count(0) {}
