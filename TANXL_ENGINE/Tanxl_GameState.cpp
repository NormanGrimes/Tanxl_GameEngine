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
	static GameEventBase EventBase;
	return EventBase;
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

void GameStateBase::Set_State(int Width, int Height)
{
	this->_GameState_Width = Width;
	this->_GameState_Height = Height;
	for (int i = 0; i < GameState.size(); i++)
		delete GameState.at(i);
	GameState.clear();
	for (int i = 0; i < Width * Height; i++)
		GameState.push_back(new StateUnit);
}

void GameStateBase::CompileStateUnits(std::string Infor)
{
	std::string Text_Reader{};
	int Status_Id{}, State_Move{};
	for (int i = 0, SetCount = 0; i < Infor.size(); i++)
	{
		if (Infor.at(i) != ',' && Infor.at(i) != '-')
			Text_Reader += Infor.at(i);
		else if (Infor.at(i) != '-')
		{
			Status_Id = std::stoi(Text_Reader);
			Text_Reader = "";
		}
		else
		{
			State_Move = std::stoi(Text_Reader);
			Text_Reader = "";
			this->GameState.push_back(new StateUnit(NULL, Status_Id, State_Move));
			Status_Id = 0;
			State_Move = 0;
		}
	}
}

void GameStateBase::CompileStateEvent(std::string Infor)//Sample  A = 0, B = 1, C = 2.
{
	std::string Text_Reader{};
	int Status_Int{};
	for (int i = 0, SetCount = 0; i < Infor.size(); i++)
	{
		if (Infor.at(i) != ',' && Infor.at(i) != '=')
			Text_Reader += Infor.at(i);
		else if (Infor.at(i) == '=')//读取等号后的数字ID值
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
			this->GameState.at(SetCount++)->SetEvent(Text_Reader, Status_Int);
			if (Infor.at(i) == '.')
				return;
			Text_Reader = "";
		}
	}
}

GameStateBase& GameStateBase::Get_StateBase(int Height, int Width)
{
	static GameStateBase GameState(Height, Width);
	return GameState;
}

void GameStateBase::Set_ExacHeight(float& Current)
{
	static int EHCount = 0;
	int LevelCount = 0;
	float SingleBlock = 2.0f / _GameState_Height;
	while (SingleBlock < Current)
	{
		SingleBlock += 2.0f / _GameState_Height;
		LevelCount++;
	}
	if (SingleBlock - Current > Current - (SingleBlock - 2.0f / _GameState_Height))
	{
		EHCount++;
		if (EHCount == 10)
			Current -= _GameState_Adjust;
	}
	else
	{
		EHCount++;
		if (EHCount == 10)
			Current += _GameState_Adjust;
	}
}

void GameStateBase::Set_ExacWidth(float& Current)
{
	static int EWCount = 0;
	int LevelCount = 0;
	float SingleBlock = 2.0f / _GameState_Width;
	while (SingleBlock < Current)
	{
		SingleBlock += 2.0f / _GameState_Width;
		LevelCount++;
	}
	if (SingleBlock - Current > Current - (SingleBlock - 2.0f / _GameState_Width))
	{
		EWCount++;
		if (EWCount == 10)
			Current -= _GameState_Adjust;
	}
	else
	{
		EWCount++;
		if (EWCount == 10)
			Current += _GameState_Adjust;
	}
}

std::vector<bool>* GameStateBase::Get_GameState_MoveAble()
{
	static std::vector<bool> MAB;
	for (int i = 0; i < GameState.size(); i++)
	{
		if (GameState.at(i)->GetMoveAble())
			MAB.push_back(true);
		else
			MAB.push_back(false);
	}
	return &MAB;
}

GameStateBase::GameStateBase(int Height, int Width) :
	_GameState_Width(Height), _GameState_Height(Width), GameState(NULL), _GameState_Adjust(0.0f), _SLoc(SLocation(0.0f, 0.0f)) {}

GameStateBase::~GameStateBase()
{
	for (int i = 0; i < GameState.size(); i++)
		delete GameState.at(i);
	GameState.clear();
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
}

void GameStateBase::Set_Adjust(float Adjust)
{
	this->_GameState_Adjust = Adjust;
}

size_t GameStateBase::Get_StateSize()
{
	return GameState.size();
}

StateUnit* GameStateBase::Get_StateUnit(int Pos)
{
	return this->GameState.at(Pos);
}

GameStateBase::GameStateBase(const GameStateBase&) :_GameState_Width(0), _GameState_Height(0), _GameState_Adjust(0), _SLoc(SLocation(0.0f, 0.0f)) {}

GameStateBase& GameStateBase::operator=(const GameStateBase&) { return *this; }

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
	return &this->GameState;
}

//SLocation

SLocation::SLocation(float LocX, float LocY) :_LocX(LocX), _LocY(LocY) {}