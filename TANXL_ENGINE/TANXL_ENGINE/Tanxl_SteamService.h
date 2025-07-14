//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-07-07 11:06
// ����STEAM����ģ�飬��ʼ�ṩ����ѯ����
// ������Ϊ����ģʽ
// ��������Ӱ汾��Ϣ
// ��������ӳ�ʼ��״̬������״ִ̬�й���
// ���ӿ����Ʒ��
// ���ӳɾ�ö��
// ���ӳɾ�����ɾͽ�������
// ���������û����ݽӿ�
// ������ʼ������
// �������ɲ�����Ʒ�ӿ�
// ���Ӻ���Ƴ�����������
// ���Ӽ��ɾ�״̬�Ľӿ�
// ����������Ʒ�ӿ�
// ���ӳ�Ա�洢���ָ��
// ���ӻ�ȡ���п��Ĺ���
// ����ת�Ƶ�Դ�ļ���

#pragma once

#ifndef _TANXL_STEAMSERVICE_
#define _TANXL_STEAMSERVICE_

#include <list>
#include <vector>
#include <iostream>

#include "public/steam/steam_api.h"
#include "public/steam/isteamapps.h"

#define _STEAM_ALPHA_VERSION_ 0


enum ETanxl_Inventory_ItemDefId
{
	Tanxl_Pormise_LIMITED_ITEM			= 1,
	Tanxl_Secret_Core_LIMITED_DROP_ITEM = 2
};

enum ETanxl_Achievement_DefId
{
	NEW_ACHIEVEMENT_1_0 = 1,
	NEW_ACHIEVEMENT_1_1 = 2
};

class TanxlItem
{
public:
	SteamItemInstanceID_t GetItemId() const { return _Details.m_itemId; }
	SteamItemDef_t GetDefinition() const { return _Details.m_iDefinition; }
	uint16 GetQuantity() const { return _Details.m_unQuantity; }
	SteamItemDetails_t GetDetails() const { return this->_Details; }
	void SetDetails(SteamItemDetails_t Details) { this->_Details = Details; }
private:
	SteamItemDetails_t _Details;
};

struct Achievement_t
{
	ETanxl_Achievement_DefId m_eAchievementID;
	const char* m_pchAchievementID;
	char m_rgchName[128];
	char m_rgchDescription[256];
	bool m_bAchieved;
	int m_iIconImage;
};

#define _ACH_ID( id, name ) { id, #id, name, ""}

static Achievement_t g_rgAchievements[] =
{
	_ACH_ID(NEW_ACHIEVEMENT_1_0, "Secret"),
	_ACH_ID(NEW_ACHIEVEMENT_1_1, "100 Coins")
};

class Tanxl_Achievement
{
public:
	static Tanxl_Achievement& Get_AchievementBase();

	void UnlockAchievement(Achievement_t& achievement);

	bool CheckAchievement(Achievement_t& achievement);

	bool RequestStats();//�����û�ͳ������

private:
	Tanxl_Achievement();

	ISteamUser* _SteamUser;
	ISteamUserStats* _SteamUserStats;
};

class Tanxl_Inventory
{
public:

	static Tanxl_Inventory& Get_InventoryBase();

	const std::string Get_Version();

	void RefreshFromServer();

	void CheckForItemDrops();

	void GenerateItemsTest(ETanxl_Inventory_ItemDefId Item);

	void ConsumeInvetoryItem(ETanxl_Inventory_ItemDefId ItemInstanceId);

	bool AddPromoItem(ETanxl_Inventory_ItemDefId Item);

private:

	Tanxl_Inventory();

	~Tanxl_Inventory();
	Tanxl_Inventory(const Tanxl_Inventory&);
	Tanxl_Inventory& operator=(const Tanxl_Inventory&);

	STEAM_CALLBACK(Tanxl_Inventory, OnSteamInventoryFullUpdate, SteamInventoryFullUpdate_t, _SteamInventoryFullUpdate);

	ISteamInventory* _Steam_Invetory;
	const std::string _Version{ "0.1" };

	std::list<TanxlItem*> _listPlayerItems;

	SteamInventoryResult_t _PlaytimeRequestResult;
	bool _SteamInventoryInit_Status;
};

#endif