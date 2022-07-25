//_VERSION_0_3_ UPDATE LOG
// LAST_UPDATE 2022-05-16 23:50
// StateUnit�����Ӷ�ÿһ���ID�趨
// ΢��StateUnit���캯��
// Դ�ļ�����ṹ����
// �����ͼ�������ڿ��Ա����ͼID��ֵ

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
	StateUnit(GameEvent* GE = NULL, int State_Id = 0, bool MoveTarget = true);
	void SetEvent(std::string GameEventName, int State_Id = -1);
	bool GetMoveT();
	int Get_State_Id();
	void Set_State_Id(int State_Id);
private:
	GameEvent* GameEvents;
	bool Is_Move_Target;
	int _State_Id;
};

//GameStateBase CLASS

class GameStateBase
{
public:
	void SetState(int Width, int Height);
	//CompileState : ʹ��һ���ַ��������������ͼ״̬����� ��Ӣ�Ķ���(,)Ϊ��� ��Ӣ�ľ��(.)Ϊ��β
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