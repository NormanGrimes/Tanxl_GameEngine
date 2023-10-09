#pragma once

#include "Tanxl_GameEvent.h"

//GameEvent

GameEvent::GameEvent(std::string Name) :_EventName(Name) {}

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

GameEventBase& GameEventBase::GetEventBase()
{
	static GameEventBase* EventBase{ new GameEventBase };
	return *EventBase;
}
