#include "Tanxl_GameEvent.h"

//GameEvent

GameEvent::GameEvent(std::string Name) :EventName(Name) {}

std::string GameEvent::GetEventName()
{
	return this->EventName;
}

//GameEventBase

void GameEventBase::RegistEvent(GameEvent* Event)
{
	GameEvents.push_back(Event);
}

GameEvent* GameEventBase::GetGameEvent(std::string EventName)
{
	for (int i = 0; i < GameEvents.size(); i++)
		if (GameEvents.at(i)->GetEventName() == EventName)
			return GameEvents.at(i);
	return NULL;
}

GameEventBase& GameEventBase::GetEventBase()
{
	static GameEventBase EventBase;
	return EventBase;
}

GameEventBase::GameEventBase() :GameEvents(NULL) {}

GameEventBase::~GameEventBase() { delete &GameEvents; }

GameEventBase::GameEventBase(const GameEventBase&){}

GameEventBase& GameEventBase::operator=(const GameEventBase&){}
