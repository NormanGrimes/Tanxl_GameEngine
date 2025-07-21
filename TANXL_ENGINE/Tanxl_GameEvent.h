//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2022-12-10 22:48
// ��GameStateģ���ж����������д���
// ���Ӱ汾�������ȡ�ӿ�
// ���������Ż������ڴ��е���������
// ����������ע����Ϸ�¼�����
// �����¼��Ƴ�����
// �������ذ汾�¼��Ƴ�����
// ��Ϸ�¼��ṹ������Ϸ��Ʒָ���Ա
// ����ָ���¼�Ŀ��Ľӿ�
// ����һ��ʾ����Ϸ�¼�
// ��Ϸ�¼����Ϊ�̳��Ի�����
// ��ͼ�滻�¼���Ϊͨ����������Զ�ִ���¼�
// �������괥�����¼���

#pragma once

#ifndef _TANXL_GAMEEVENT_
#define _TANXL_GAMEEVENT_

#include<vector>
#include<string>

#include "Tanxl_GameObject.h"
#include "Tanxl_EngineBase.h"

class GameEvent
{
public:
	GameEvent(std::string Name = "", GameObject* Obejct = nullptr);
	std::string GetEventName();
	void Set_EventTarget(GameObject* Obejct);
	
private:
	virtual void EventAction() = 0;
	std::string _EventName;
	GameObject* _GameObejct;
};

class GameEvent_By_Location : public GameEvent
{
public:
	GameEvent_By_Location(std::string Name = "", GameObject* Obejct = nullptr);
	virtual void CheckEvent(int LocationX, int LocationY) = 0;
private:
	virtual void EventAction() = 0;
};

class State_ChangeEvent : public GameEvent
{
public:
	State_ChangeEvent(std::string Name, int LocationX, int LocationY, std::string Cover_String);

	void CheckEvent(int LocationX, int LocationY);

	void Set_CoverString(std::string Cover_String);

private:

	void EventAction();
	int _LocationX;
	int _LocationY;
	std::string _Cover_String;
};

//GameEventBase

class GameEventBase : public Tanxl_ClassBase
{
public:
	//��ȡ��ģ��İ汾��Ϣ
	const std::string Get_Version();
	//ע����Ϸ�¼� ����������¼�����ע���򲻻�����κ�Ч��
	void RegistEvent(GameEvent* Event);
	//��ȡ��Ϸ�¼�����
	static GameEventBase& GetEventBase();
	GameEvent* GetGameEvent(std::string EventName);
	//������Ϸ�¼� �鿴�Ƿ������������Ƶ���Ϸ�¼�
	bool Search_GameEvent(std::string EventName);
	void Remove_GameEvent(int Event_Id);
	void Remove_GameEvent(std::string EventName);

private:
	GameEventBase();
	~GameEventBase();
	GameEventBase(const GameEventBase&);
	GameEventBase& operator=(const GameEventBase&);

	std::vector<GameEvent*> _GameEvents;
};

#endif