#pragma once

#include "Tanxl_GameEvent.h"
#include "Tanxl_GameState.h"

//GameEvent

GameEvent::GameEvent(std::string Name, GameObject* Obejct) :_EventName(Name), _GameObejct(Obejct) {}

//State_ChangeEvent

State_ChangeEvent::State_ChangeEvent(std::string Name, int LocationX, int LocationY, std::string Cover_String) :
	GameEvent(Name), _LocationX(LocationX), _LocationY(LocationY), _Cover_String(Cover_String) {}

void State_ChangeEvent::CheckEvent(int LocationX, int LocationY)
{
	if ((LocationX == this->_LocationX) && (LocationY == this->_LocationY))
		this->EventAction();
}

void State_ChangeEvent::EventAction()
{
	static GameStateBase* State{ &GameStateBase::GetStateBase() };
	if ((State->Get_Exac_LocationX() == _LocationX) && (State->Get_Exac_LocationY() == _LocationY))
	{
		State->Set_State(_LocationY * State->Get_DataWidth() + _LocationX, _Cover_String);
	}
}

void State_ChangeEvent::Set_CoverString(std::string Cover_String)
{
	this->_Cover_String = Cover_String;
}

//GameEventBase

const std::string GameEventBase::Get_Version()
{
	return Tanxl_ClassBase::Get_Version();
}

void GameEventBase::RegistEvent(GameEvent* Event)
{
	this->_GameEvents.push_back(Event);
}

GameEvent* GameEventBase::GetGameEvent(std::string EventName)
{
	for (int i{ 0 }; i < this->_GameEvents.size(); ++i)
		if (this->_GameEvents.at(i)->GetEventName() == EventName)
			return this->_GameEvents.at(i);
	return nullptr;
}

bool GameEventBase::Search_GameEvent(std::string EventName)
{
	for (int i{ 0 }; i < this->_GameEvents.size(); ++i)
		if (this->_GameEvents.at(i)->GetEventName() == EventName)
			return true;
	return false;
}

void GameEventBase::Remove_GameEvent(int Event_Id)
{
	if (Event_Id < 0)
		std::vector<GameEvent*>().swap(this->_GameEvents);
	else
	{
		if (Event_Id < this->_GameEvents.size())
		{
			delete this->_GameEvents.at(Event_Id);
			this->_GameEvents.erase(this->_GameEvents.begin() + Event_Id);
		}
	}
}

void GameEventBase::Remove_GameEvent(std::string EventName)
{
	for (int i{ 0 }; i < this->_GameEvents.size(); ++i)
	{
		if (this->_GameEvents.at(i)->GetEventName() == EventName)
		{
			delete this->_GameEvents.at(i);
			this->_GameEvents.erase(this->_GameEvents.begin() + i);
		}
	}
}

GameEventBase& GameEventBase::GetEventBase()
{
	static GameEventBase* EventBase{ new GameEventBase };
	return *EventBase;
}

GameEvent_By_Location::GameEvent_By_Location(std::string Name, GameObject* Obejct) :GameEvent(Name, Obejct) {}
