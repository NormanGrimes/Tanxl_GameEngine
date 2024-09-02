#pragma once

#include "Tanxl_GameEvent.h"

//GameEvent

GameEvent::GameEvent(std::string Name, GameObject* Obejct) :_EventName(Name), _GameObejct(Obejct) {}

//GameEventBase

const std::string GameEventBase::Get_Version()
{
	return this->_Version;
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
