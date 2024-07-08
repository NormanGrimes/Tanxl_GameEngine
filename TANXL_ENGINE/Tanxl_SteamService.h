//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-07-07 11:06
// ����STEAM����ģ�飬��ʼ�ṩ����ѯ����

#pragma once

#ifndef _TANXL_STEAMSERVICE_
#define _TANXL_STEAMSERVICE_

#include "public/steam/steam_api.h"
#include "public/steam/isteamapps.h"

enum ETanxl_Inventory_ItemDefId
{
	Tanxl_Pormise_LIMITED_DROP_ITEM = 1,
};


class Tanxl_Inventory
{
public:
	Tanxl_Inventory() :_PlaytimeRequestResult(k_SteamInventoryResultInvalid) {};

	void RefreshFromServer()
	{
		SteamInventory()->GetAllItems(NULL);
	}

	void CheckForItemDrops()
	{
		SteamInventory()->TriggerItemDrop(&_PlaytimeRequestResult, Tanxl_Pormise_LIMITED_DROP_ITEM);
	}

private:
	SteamInventoryResult_t _PlaytimeRequestResult;
};

#endif