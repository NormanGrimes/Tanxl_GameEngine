#include "Tanxl_GameState.h"
//StateUnit

void StateUnit::SetEvent(std::string GameEventName)
{
	GameEventBase* EventBase{};
	if (EventBase->GetEventBase().GetGameEvent(GameEventName))
		this->GameEvents = EventBase->GetEventBase().GetGameEvent(GameEventName);
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
	for (int i = 0, SetCount = 0; i < Infor.size(); i++)
	{
		std::string Reader{};
		if (Infor.at(i) != ',')
			Reader += Infor.at(i);
		else
		{
			this->GameState.at(SetCount++)->SetEvent(Reader);
			Reader = "";
		}
	}
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

GameStateBase::GameStateBase(int Height, int Width) :GameState_Width(Height), GameState_Height(Width), GameState(NULL) {}

GameStateBase::~GameStateBase()
{
	for (int i = 0; i < GameState.size(); i++)
		delete GameState.at(i);
	GameState.clear();
}

GameStateBase::GameStateBase(const GameStateBase&) :GameState_Width(0), GameState_Height(0) {}

GameStateBase& GameStateBase::operator=(const GameStateBase&) {}

int GameStateBase::GetStateHeight()const
{
	return this->GameState_Height;
}

int GameStateBase::GetStateWidth()const
{
	return this->GameState_Width;
}