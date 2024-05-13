//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2022-12-10 22:48
// ��GameStateģ���ж����������д���
// ���Ӱ汾�������ȡ�ӿ�
// ���������Ż������ڴ��е���������
// ����������ע����Ϸ�¼�����
// �����¼��Ƴ�����

#pragma once

#ifndef _TANXL_GAMEEVENT_
#define _TANXL_GAMEEVENT_

#include<vector>
#include<string>

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
private:
	GameEventBase();
	~GameEventBase();
	GameEventBase(const GameEventBase&);
	GameEventBase& operator=(const GameEventBase&);

	std::vector<GameEvent*> _GameEvents;
	const std::string _Version{ "0.1" };
};

#endif