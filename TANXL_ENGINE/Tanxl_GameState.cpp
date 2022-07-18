#include "Tanxl_GameState.h"

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

GameEventBase::~GameEventBase() { delete& GameEvents; }

GameEventBase::GameEventBase(const GameEventBase&) {}

GameEventBase& GameEventBase::operator=(const GameEventBase&) { return *this; }


//StateUnit

StateUnit::StateUnit(GameEvent* GE, bool MoveTarget)
	:Is_Move_Target(MoveTarget), GameEvents(GE) {}

void StateUnit::SetEvent(std::string GameEventName)
{
	GameEventBase* EventBase{};
	if (EventBase->GetEventBase().GetGameEvent(GameEventName))
		this->GameEvents = EventBase->GetEventBase().GetGameEvent(GameEventName);
}

bool StateUnit::GetMoveT()
{
	return this->Is_Move_Target;
}

//GameStateBase

void GameStateBase::SetState(int Width, int Height)
{
	this->GameState_Width = Width;
	this->GameState_Height = Height;
	for (int i = 0; i < GameState.size(); i++)
		delete GameState.at(i);
	GameState.clear();
	for (int i = 0; i < Width * Height; i++)
		GameState.push_back(new StateUnit);
}

void GameStateBase::CompileState(std::string Infor)
{
	std::string Reader{};
	for (int i = 0, SetCount = 0; i < Infor.size(); i++)
	{
		if (Infor.at(i) != ',')
			Reader += Infor.at(i);
		else
		{
			this->GameState.at(SetCount++)->SetEvent(Reader);
			Reader = "";
		}
	}
}

void GameStateBase::SetAdjust(float Adjust)
{
	this->GameState_Adjust = Adjust;
}

size_t GameStateBase::GetStateSize()
{
	return GameState.size();
}

StateUnit* GameStateBase::GetStateUnit(int Pos)
{
	return this->GameState.at(Pos);
}

GameStateBase& GameStateBase::GetStateBase(int Height, int Width)
{
	static GameStateBase GameState(Height, Width);
	return GameState;
}

void GameStateBase::SetExacHeight(float& Current)
{
	static int EHCount = 0;
	int LevelCount = 0;
	float SingleBlock = 2.0f / GameState_Height;
	while (SingleBlock < Current)
	{
		SingleBlock += 2.0f / GameState_Height;
		LevelCount++;
	}
	if (SingleBlock - Current > Current - (SingleBlock - 2.0f / GameState_Height))
	{
		EHCount++;
		if (EHCount == 10)
			Current -= GameState_Adjust;
	}
	else
	{
		EHCount++;
		if (EHCount == 10)
			Current += GameState_Adjust;
	}
}

void GameStateBase::SetExacWidth(float& Current)
{
	static int EWCount = 0;
	int LevelCount = 0;
	float SingleBlock = 2.0f / GameState_Width;
	while (SingleBlock < Current)
	{
		SingleBlock += 2.0f / GameState_Width;
		LevelCount++;
	}
	if (SingleBlock - Current > Current - (SingleBlock - 2.0f / GameState_Width))
	{
		EWCount++;
		if (EWCount == 10)
			Current -= GameState_Adjust;
	}
	else
	{
		EWCount++;
		if (EWCount == 10)
			Current += GameState_Adjust;
	}
}

GameStateBase::GameStateBase(int Height, int Width) :
	GameState_Width(Height), GameState_Height(Width), GameState(NULL),GameState_Adjust(0.0f) {}

GameStateBase::~GameStateBase()
{
	for (int i = 0; i < GameState.size(); i++)
		delete GameState.at(i);
	GameState.clear();
}

GameStateBase::GameStateBase(const GameStateBase&) :GameState_Width(0), GameState_Height(0),GameState_Adjust(0) {}

GameStateBase& GameStateBase::operator=(const GameStateBase&) { return *this; }

int GameStateBase::GetStateHeight()const
{
	return this->GameState_Height;
}

int GameStateBase::GetStateWidth()const
{
	return this->GameState_Width;
}