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

#pragma once

#ifndef _TANXL_GAMEEVENT_
#define _TANXL_GAMEEVENT_

#include<vector>
#include<string>
#include "Tanxl_GameObject.h"

class GameEvent
{
public:
	GameEvent(std::string Name = "", GameObject* Obejct = nullptr);
	std::string GetEventName();
	void Set_EventTarget(GameObject* Obejct);
	virtual void EventAction() = 0;
private:
	std::string _EventName;
	GameObject* _GameObejct;
};

//GameEventBase

class GameEventBase
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
	const std::string _Version{ "0.1" };
};

#endif