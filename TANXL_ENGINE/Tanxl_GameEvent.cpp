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
	_GameEvents.push_back(Event);
}

GameEvent* GameEventBase::GetGameEvent(std::string EventName)
{
	for (int i = 0; i < _GameEvents.size(); ++i)
		if (_GameEvents.at(i)->GetEventName() == EventName)
			return _GameEvents.at(i);
	return nullptr;
}

GameEventBase& GameEventBase::GetEventBase()
{
	static GameEventBase* EventBase = new GameEventBase;
	return *EventBase;
}
