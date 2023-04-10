#pragma once

#include "Tanxl_GameEvent.h"

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
