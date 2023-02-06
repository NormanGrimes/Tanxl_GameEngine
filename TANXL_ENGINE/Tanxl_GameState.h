//_VERSION_0_5_ UPDATE LOG
// LAST_UPDATE 2022-09-20 22:38
// ����һ������ֵ���ڱ���Ƿ����Զ���������
// �޸��Զ��������ʱ��ʱ�̵�����
// �޸����һ�ε��ڵ��ж�������������
// ����΢�����꺯���Ľӿ�������������
// ΢�����һ���Ż�float�������ʹ֮�����ȶ�
// ������Կ����Զ�����Ƶ�ʵĹ���

#pragma once

#ifndef VECTOR
#define VECTOR
#include<vector>
#endif

#ifndef STRING
#define STRING
#include<string>
#endif

enum EMove_State_EventId
{
	MoveToNW = 0,
	MoveToPW = 1,
	MoveToNH = 2,
	MoveToPH = 3
};

struct Move_State
{
	Move_State(int NX = 0, int PX = 0, int NY = 0, int PY = 0);
	int _Move_NX;
	int _Move_PX;
	int _Move_NY;
	int _Move_PY;
};

struct SLocation
{
	SLocation(float LocX, float LocY);
	float _LocX;
	float _LocY;
};

class GameEvent
{
public:
	GameEvent(std::string Name = "");
	std::string GetEventName();
	virtual void EventAction() = 0;
private:
	std::string _EventName;
};

//GameEventBase

class GameEventBase
{
public:
	//ע����Ϸ�¼� ����������¼�����ע���򲻻�����κ�Ч��
	void RegistEvent(GameEvent* Event);
	static GameEventBase& GetEventBase();
	GameEvent* GetGameEvent(std::string EventName);
private:
	GameEventBase();
	~GameEventBase();
	GameEventBase(const GameEventBase&);
	GameEventBase& operator=(const GameEventBase&);
	std::vector<GameEvent*> _GameEvents;
};

//StateUnit CLASS

class StateUnit
{
public:
	StateUnit(GameEvent* GE = NULL, int State_Id = 0, bool MoveTarget = true);
	void SetEvent(std::string GameEventName, int State_Id = -1);
	bool GetMoveAble();
	int Get_State_Id();
	void Set_State_Id(int State_Id);
private:
	GameEvent* _GameEvents;
	bool _Is_Move_Target;
	int _State_Id;
};

//GameStateBase CLASS

class GameStateBase
{
public:
	
	size_t Get_StateSize();
	StateUnit* Get_StateUnit(int Pos);
	//��Get_StateBase : ����State������ ע�⣡���е�Height��Width������ָ��������ʾ�������С
	static GameStateBase& Get_StateBase(int Height = 0, int Width = 0);
	Move_State Get_Move_State();
	std::vector<StateUnit*>* Get_GameState();
	std::vector<bool>* Get_GameState_MoveAble();
	void Set_Move_State(int NX, int PX, int NY, int PY);
	void Set_Move_State(int Event_Id);
	void Set_Display_State(int Width, int Height);
	void Set_DataAll_State(unsigned Width, unsigned Height);
	void Set_Adjust_Flag(bool Adjust_Flag);
	void CompileStateUnits(std::string Infor);
	//��CompileStateEvent : ʹ��һ���ַ��������������ͼ״̬����� ��Ӣ�Ķ���(,)Ϊ��� ��Ӣ�ľ��(.)Ϊ��β
	void CompileStateEvent(std::string Infor);
	void Set_Adjust(float Adjust);
	void Set_ExacHeight(double& Current, float& MoveSet, float* MoveState = NULL, float* MoveY = NULL, float* Deputy = NULL);//��ѡ���� ��2D�����ϵ���Ʒ΢��λ��
	void Set_ExacWidth(double& Current, float& MoveSet, float* MoveState = NULL, float* MoveY = NULL, float* Deputy = NULL);
	void Set_Adjust_Frequency(int Frame);
	void Set_CurrentLoc(float& CurrentX, float& CurrentY);
	void Reload_State(float& CurrentX, float& CurrentY);
	bool Get_Compile_Status();
	bool Get_Adjust_Flag();
	unsigned Get_DataHeight()const;
	unsigned Get_DataWidth()const;
	//��Get_StateHeight : ��ȡ��ǰ��Ҫ���Ƶ�State�ĸ߶�ֵ
	int Get_StateHeight()const;
	//��Get_StateWidth : ��ȡ��ǰ��Ҫ���Ƶ�State�Ŀ��ֵ
	int Get_StateWidth()const;
private:
	//��ͼ��ʼ��Ĭ�Ϲ��캯�� ���õ���ģʽ���е�һ�γ�ʼ��
	GameStateBase(int Height = 0, int Width = 0);
	~GameStateBase();
	GameStateBase(const GameStateBase&);
	GameStateBase& operator=(const GameStateBase&);
	unsigned _Data_Width;
	unsigned _Data_Height;
	//_Adjust_Frame ���ڿ��Ƶ�ǰÿ����֡����һ���������
	int _Adjust_Frame;
	int _GameState_Width;
	int _GameState_Height;
	float _GameState_Adjust;
	bool _Is_Adjusting;
	bool _Compile_Success;
	Move_State _MState;//���ڼ�¼��ǰ���ص�ͼ����
	SLocation _SLoc;//���ڼ�¼��ǰ��ͼ���ĵ�
	std::vector<StateUnit*> _GameState;
	//���ڼ�¼��ǰ��ͼ���ĵĵ�ͼ��Ԫ
	StateUnit* _CurrentMid;
};