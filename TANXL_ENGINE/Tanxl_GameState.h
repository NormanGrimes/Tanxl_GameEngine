//_VERSION_0_2_ UPDATE LOG
// LAST_UPDATE 2022-05-08 22:40
// ��GameEvent������������
// �������������ڶ�2D�����ϵ���Ʒ΢��λ�õĹ���
// �޸�CompileState��ȡ���������
// StateUnit�������Ƿ��ܳ�Ϊ�ƶ�Ŀ����趨
// StateUint������һ��Ĭ�Ϲ��캯��

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
	StateUnit(GameEvent* GE = NULL, bool MoveTarget = true);
	void SetEvent(std::string GameEventName);
	bool GetMoveT();
private:
	GameEvent* GameEvents;
	bool Is_Move_Target;
};

//GameStateBase CLASS

class GameStateBase
{
public:
	void SetState(int Width, int Height);
	//CompileState : ʹ��һ���ַ��������������ͼ״̬����� ��Ӣ�Ķ���Ϊ���
	void CompileState(std::string Infor);
	void SetAdjust(float Adjust);
	size_t GetStateSize();
	StateUnit* GetStateUnit(int Pos);
	static GameStateBase& GetStateBase(int Height = 0, int Width = 0);
	void SetExacHeight(float& Current);//��ѡ���� ��2D�����ϵ���Ʒ΢��λ��
	void SetExacWidth(float& Current);
	int GetStateHeight()const;
	int GetStateWidth()const;
private:
	GameStateBase(int Height = 0, int Width = 0);
	~GameStateBase();
	GameStateBase(const GameStateBase&);
	GameStateBase& operator=(const GameStateBase&);
	int GameState_Width;
	int GameState_Height;
	float GameState_Adjust;
	std::vector<StateUnit*>GameState;
};