//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2022-04-27 22:32
// »ù´¡°æ±¾

#ifndef VECTOR
#define VECTOR
#include<vector>
#endif

#ifndef STRING
#define STRING
#include<string>
#endif

//#ifndef GAME_EVENT_BASE_INC
//#define GAME_EVENT_BASE_INC
//#include "Tanxl_GameEvent.h"
//#endif

//StateUnit CLASS

class StateUnit
{
public:
	//void SetEvent(std::string GameEventName);
private:
	//GameEvent* GameEvents;
};

//GameStateBase CLASS

class GameStateBase
{
public:
	void SetState(int Width, int Height);
	void CompileState(std::string Infor);
	size_t GetStateSize();
	StateUnit* GetStateUnit(int Pos);
	static GameStateBase& GetStateBase(int Height = 0, int Width = 0);
	int GetStateHeight()const;
	int GetStateWidth()const;
private:
	GameStateBase(int Height = 0, int Width = 0);
	~GameStateBase();
	GameStateBase(const GameStateBase&);
	GameStateBase& operator=(const GameStateBase&);
	int GameState_Width;
	int GameState_Height;
	std::vector<StateUnit*>GameState;
};