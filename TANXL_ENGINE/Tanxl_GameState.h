//_VERSION_0_2_ UPDATE LOG
// LAST_UPDATE 2022-05-08 22:40
// 将GameEvent类整合至此类

#ifndef VECTOR
#define VECTOR
#include<vector>
#endif

#ifndef STRING
#define STRING
#include<string>
#endif

class GameEvent
{
public:
	GameEvent(std::string Name = "");
	std::string GetEventName();
	virtual void EventAction() = 0;
private:
	std::string EventName;
};

//GameEventBase

class GameEventBase
{
public:
	void RegistEvent(GameEvent* Event);
	static GameEventBase& GetEventBase();
	GameEvent* GetGameEvent(std::string EventName);
private:
	GameEventBase();
	~GameEventBase();
	GameEventBase(const GameEventBase&);
	GameEventBase& operator=(const GameEventBase&);
	std::vector<GameEvent*>GameEvents;
};

//StateUnit CLASS

class StateUnit
{
public:
	void SetEvent(std::string GameEventName);
private:
	GameEvent* GameEvents;
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