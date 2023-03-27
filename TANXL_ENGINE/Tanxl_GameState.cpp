#pragma once

#include "Tanxl_GameState.h"

//Core

//GameEvent

GameEvent::GameEvent(std::string Name) :_EventName(Name) {}

//GameEventBase

void GameEventBase::RegistEvent(GameEvent* Event)
{
	_GameEvents.push_back(Event);
}

GameEvent* GameEventBase::GetGameEvent(std::string EventName)
{
	for (int i = 0; i < _GameEvents.size(); i++)
		if (_GameEvents.at(i)->GetEventName() == EventName)
			return _GameEvents.at(i);
	return NULL;
}

GameEventBase& GameEventBase::GetEventBase()
{
	static GameEventBase* EventBase = new GameEventBase;
	return *EventBase;
}

//StateUnit

StateUnit::StateUnit(GameEvent* GE, int State_Id, bool MoveTarget)
	:_Is_Move_Target(MoveTarget), _GameEvents(GE), _State_Id(State_Id) {}

void StateUnit::SetEvent(std::string GameEventName, int State_Id)
{
	GameEventBase* EventBase{ &GameEventBase::GetEventBase() };
	if (EventBase->GetGameEvent(GameEventName))
		this->_GameEvents = EventBase->GetEventBase().GetGameEvent(GameEventName);
	if (State_Id != -1)
		this->_State_Id = State_Id;
}

//GameStateBase

void GameStateBase::Clear_Display_Vector()
{
	for (int i = 0; i < _GameState.size(); i++)
		delete _GameState.at(i);
	_GameState.clear();
}

void GameStateBase::Set_Display_State(int Width, int Height)
{
	this->_GameState_Width = Width;
	this->_GameState_Height = Height;
	for (int i = 0; i < _GameState.size(); i++)
		delete _GameState.at(i);
	_GameState.clear();
	//for (int i = 0; i < Width * Height; i++)
	//	_GameState.push_back(new StateUnit);
}

void GameStateBase::Set_DataAll_State(unsigned Width, unsigned Height)
{
	this->_Data_Width = Width - 1;
	this->_Data_Height = Height - 1;
}

void GameStateBase::CompileStateUnits(std::string Infor)
{
	std::string Text_Reader{};
	int Status_Id{}, State_Move{};
	for (int i = 0; i < Infor.size(); i++)
	{
		if (Infor.at(i) != ',' && Infor.at(i) != '-')
			Text_Reader += Infor.at(i);
		else if (Infor.at(i) == ',')
		{
			Status_Id = std::stoi(Text_Reader);
			this->_GameState.push_back(new StateUnit(NULL, Status_Id, State_Move));
			Text_Reader = "";
		}
		else if (Infor.at(i) == '-')
		{
			State_Move = 0;//std::stoi(Text_Reader);
			Text_Reader = "";
			Status_Id = 0;
			State_Move = 0;
		}
	}
	_Compile_Success = true;
}

void GameStateBase::CompileStateEvent(std::string Infor)//Sample  A = 0, B = 1, C = 2.
{
	std::string Text_Reader{};
	int Status_Int{};
	for (int i = 0, SetCount = 0; i < Infor.size(); i++)
	{
		if (Infor.at(i) != ',' && Infor.at(i) != '=')
			Text_Reader += Infor.at(i);
		else if (Infor.at(i) == '=')//��ȡ�Ⱥź������IDֵ
		{
			std::string Status_Reader{};
			while (Infor.at(i) != ',')
			{
				if (Infor.at(i) != ' ' && (Infor.at(i) >= '0' && Infor.at(i) <= '9'))
					Status_Reader += Infor.at(i);
			}
			Status_Int = std::stoi(Status_Reader);
		}
		else
		{
			this->_GameState.at(SetCount++)->SetEvent(Text_Reader, Status_Int);
			if (Infor.at(i) == '.')
				return;
			Text_Reader = "";
		}
	}
}

GameStateBase& GameStateBase::Get_StateBase(int Display_Width, int Display_Height)
{
	static GameStateBase GameState(Display_Width, Display_Height);
	return GameState;
}

Move_State GameStateBase::Get_Move_State()
{
	return this->_MState;
}
#include <iostream>
void GameStateBase::Set_ExacHeight(double& Current, float* MoveState, float* MoveY, float* Deputy)
{
	static int EHCountS = 0;
	static int EHCountL = 0;
	if (_Adjust_Enable == false)
		return;
	//std::cout << " EHCountS  _  EHCountL" << EHCountS << " ___ " << EHCountL << std::endl;
	//std::cout << " MoveState  _" << *MoveState << " Adjust  _" << _GameState_Adjust << std::endl;
	if ((float)Current < ((float)this->Get_StateHeight()) / 2)
	{
		EHCountS++;
		if (EHCountS == this->_Adjust_Frame)
		{
			if (*MoveState < 0 && *MoveState + _GameState_Adjust > 0)
			{
				float Temp_Move = *MoveState;
				std::cout << "A Temp_Move  _" << Temp_Move << std::endl;
				std::cout << "A MoveState  _" << *MoveState << std::endl;
				*MoveY += Temp_Move;
				*Deputy += Temp_Move;
				*MoveState = 0;
				std::cout << " MoveState  _" << *MoveState << std::endl;
			}
			else
			{
				*Deputy += _GameState_Adjust;
				*MoveState += _GameState_Adjust;
				*MoveY += _GameState_Adjust;
			}
			EHCountS = 0;
			this->_Is_Adjusting = true;
		}
	}
	else
		EHCountS = 0;

	if ((float)Current > ((float)this->Get_StateHeight()) / 2)
	{
		EHCountL++;
		if (EHCountL == this->_Adjust_Frame)
		{
			if (*MoveState > _GameState_Adjust)
			{
				*Deputy -= _GameState_Adjust;
				*MoveState -= _GameState_Adjust;
				*MoveY -= _GameState_Adjust;
			}
			else if (*MoveState - _GameState_Adjust < 0)
			{
				float Temp_Move = *MoveState;
				std::cout << "B Temp_Move  _" << Temp_Move << std::endl;
				std::cout << "B MoveState  _" << *MoveState << std::endl;
				*MoveY -= Temp_Move;
				*Deputy -= Temp_Move;
				*MoveState = 0;
				std::cout << " MoveState  _" << *MoveState << std::endl;
			}
			EHCountL = 0;
			this->_Is_Adjusting = true;
		}
	}
	else
		EHCountL = 0;
}

void GameStateBase::Set_ExacWidth(double& Current, float* MoveState, float* MoveX, float* Deputy)
{
	static int EWCountS = 0;
	static int EWCountL = 0;
	if (_Adjust_Enable == false)
		return;
	//std::cout << " EWCountS  _  EWCountL" << EWCountS << " ___ " << EWCountL << std::endl;
	//std::cout << " MoveState  _" << *MoveState << " Adjust  _" << _GameState_Adjust << std::endl;
	if ((float)Current < ((float)this->Get_StateWidth()) / 2)
	{
		EWCountS++;
		if (EWCountS == this->_Adjust_Frame)
		{
			if (-*MoveState < 0 && _GameState_Adjust + -*MoveState>0)
			{
				float Temp_Move = *MoveState;
				while (Temp_Move > 2.5)
					Temp_Move -= 2.5;
				std::cout << "A Temp_Move  _" << Temp_Move << std::endl;
				std::cout << "A MoveState  _" << *MoveState << std::endl;
				*MoveX += Temp_Move;
				*Deputy += Temp_Move;
				*MoveState = 0;
				std::cout << " MoveState  _" << *MoveState << std::endl;
			}
			else
			{
				*Deputy += _GameState_Adjust;
				*MoveState += _GameState_Adjust;
				*MoveX += _GameState_Adjust;
			}
			EWCountS = 0;
			this->_Is_Adjusting = true;
		}
	}
	else
		EWCountS = 0;

	if ((float)Current > ((float)this->Get_StateWidth()) / 2)
	{
		//std::cout << " > 2.5  _" << *MoveState << std::endl;
		EWCountL++;
		if (EWCountL == this->_Adjust_Frame)
		{
			//MoveSet += _GameState_Adjust;
			if (*MoveState > _GameState_Adjust)
			{
				*Deputy -= _GameState_Adjust;
				*MoveState -= _GameState_Adjust;
				*MoveX -= _GameState_Adjust;
			}
			else if (*MoveState < _GameState_Adjust)
			{
				float Temp_Move = *MoveState;
				while (Temp_Move > 2.5)
					Temp_Move -= 2.5;
				std::cout << "B Temp_Move  _" << Temp_Move << std::endl;
				std::cout << "B MoveState  _" << *MoveState << std::endl;
				*MoveX -= Temp_Move;
				*Deputy -= Temp_Move;
				*MoveState = 0;
				std::cout << " MoveState  _" << *MoveState << std::endl;
				//*MoveState = *MoveState / 1;
			}
			EWCountL = 0;
			this->_Is_Adjusting = true;
		}
	}
	else
		EWCountL = 0;
}

void GameStateBase::Set_Adjust_Frequency(int Frame)
{
	this->_Adjust_Frame = Frame;
}

std::vector<bool>* GameStateBase::Get_GameState_MoveAble()
{
	static std::vector<bool> MAB;
	for (int i = 0; i < _GameState.size(); i++)
	{
		if (_GameState.at(i)->GetMoveAble())
			MAB.push_back(true);
		else
			MAB.push_back(false);
	}
	return &MAB;
}

void GameStateBase::Set_Move_State(int NX, int PX, int NY, int PY)
{
	this->_MState._Move_NX = NX;
	this->_MState._Move_PX = PX;
	this->_MState._Move_NY = NY;
	this->_MState._Move_PY = PY;

	int Line_Width = this->_MState._Move_PX - this->_MState._Move_NX;
	int Coum_Width = this->_MState._Move_PX - this->_MState._Move_PY;

	//TODO
}

void GameStateBase::Set_Move_State(int Event_Id)
{
	switch (Event_Id)
	{
	case MoveToNW:
		this->_MState._Move_NX++;
		this->_MState._Move_PX++;
		break;
	case MoveToPW:
		this->_MState._Move_NX--;
		this->_MState._Move_PX--;
		break;
	case MoveToNH:
		this->_MState._Move_NY++;
		this->_MState._Move_PY++;
		break;
	case MoveToPH:
		this->_MState._Move_NY--;
		this->_MState._Move_PY--;
		break;
	}
}

void GameStateBase::Reload_State(float& CurrentX, float& CurrentY)
{

}

GameStateBase::GameStateBase(int Width, int Height) :
	_GameState_Width(Height), _GameState_Height(Width), _GameState(NULL), _GameState_Adjust(0.0f),
	_SLoc(SLocation(0.0f, 0.0f)), _Compile_Success(false), _CurrentMid(NULL), _MState(0), _Data_Height(Height),
	_Data_Width(Width), _Is_Adjusting(false), _Adjust_Frame(3), _Adjust_Enable(false) {}

GameStateBase::~GameStateBase()
{
	for (int i = 0; i < _GameState.size(); i++)
		delete _GameState.at(i);
	_GameState.clear();
}

//unimportant Stuff (GET/SET)

//GameEvent

std::string GameEvent::GetEventName()
{
	return this->_EventName;
}

//GameEventBase

GameEventBase::GameEventBase() :_GameEvents(NULL) {}

GameEventBase::~GameEventBase() { delete& _GameEvents; }

GameEventBase::GameEventBase(const GameEventBase&) {}

GameEventBase& GameEventBase::operator=(const GameEventBase&) { return *this; }

//StateUnit

bool StateUnit::GetMoveAble()
{
	return this->_Is_Move_Target;
}

int StateUnit::Get_State_Id()
{
	return this->_State_Id;
}

void StateUnit::Set_State_Id(int State_Id)
{
	this->_State_Id = State_Id;
}

//GameStateBase

void GameStateBase::Set_CurrentLoc(float& CurrentX, float& CurrentY)
{
	this->_SLoc._LocX = CurrentX;
	this->_SLoc._LocY = CurrentY;
	float Compare_Width = 2.0f / _GameState_Width;
	float Compare_Height = 2.0f / _GameState_Height;
	if (_SLoc._LocX < Compare_Width || _SLoc._LocX > Compare_Width ||
		_SLoc._LocY < Compare_Height || _SLoc._LocY > Compare_Height)
	{
		//TODO reload Map
	}
}

unsigned GameStateBase::Get_DataHeight()const
{
	return this->_Data_Height;
}

unsigned GameStateBase::Get_DataWidth()const
{
	return this->_Data_Width;
}

void GameStateBase::Set_Adjust(float Adjust)
{
	this->_GameState_Adjust = Adjust;
}

void GameStateBase::Set_Enable_Adjust(bool Enable)
{
	this->_Adjust_Enable = Enable;
}

size_t GameStateBase::Get_StateSize()
{
	return _GameState.size();
}

StateUnit* GameStateBase::Get_StateUnit(int Pos)
{
	return this->_GameState.at(Pos);
}

GameStateBase::GameStateBase(const GameStateBase&) :_GameState_Width(0), _GameState_Height(0), _GameState_Adjust(0),
_SLoc(SLocation(0.0f, 0.0f)), _Compile_Success(false), _CurrentMid(NULL), _MState(0), _Data_Height(0), _Data_Width(0),
_Is_Adjusting(false), _Adjust_Frame(3), _Adjust_Enable(false) {}

GameStateBase& GameStateBase::operator=(const GameStateBase&) { return *this; }

bool GameStateBase::Get_Compile_Status()
{
	return this->_Compile_Success;
}

void GameStateBase::Set_Adjust_Flag(bool Adjust_Flag)
{
	this->_Is_Adjusting = Adjust_Flag;
}

bool GameStateBase::Get_Adjust_Flag()
{
	return this->_Is_Adjusting;
}

int GameStateBase::Get_StateHeight()const
{
	return this->_GameState_Height;
}

int GameStateBase::Get_StateWidth()const
{
	return this->_GameState_Width;
}

std::vector<StateUnit*>* GameStateBase::Get_GameState()
{
	return &this->_GameState;
}

//Move_State

Move_State::Move_State(int NX, int PX, int NY, int PY) :_Move_NX(NY), _Move_NY(NY), _Move_PX(PX), _Move_PY(PY) {}

//SLocation

SLocation::SLocation(float LocX, float LocY) :_LocX(LocX), _LocY(LocY) {}