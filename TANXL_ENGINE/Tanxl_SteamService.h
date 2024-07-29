//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-07-07 11:06
// 新增STEAM服务模块，初始提供库存查询服务
// 库存类改为单例模式
// 库存类增加版本信息
// 库存类增加初始化状态并根据状态执行功能

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

	static Tanxl_Inventory& Get_InventoryBase()
	{
		static Tanxl_Inventory* Inventory{ new Tanxl_Inventory() };
		return *Inventory;
	}

	const std::string Get_Version()
	{
		return this->_Version;
	}

	void RefreshFromServer()
	{
		if (!_SteamInventoryInit_Status)
			return;
		SteamInventory()->GetAllItems(NULL);
	}

	void CheckForItemDrops()
	{
		if (!_SteamInventoryInit_Status)
			return;
		SteamInventory()->TriggerItemDrop(&_PlaytimeRequestResult, Tanxl_Pormise_LIMITED_DROP_ITEM);
	}

private:

	Tanxl_Inventory() :_PlaytimeRequestResult(k_SteamInventoryResultInvalid)
	{
		_SteamInventoryInit_Status = false;
		if (SteamAPI_RestartAppIfNecessary(1929530))
		{
			std::cout << "Fail to init SteamAPI_RestartAppIfNecessary(1929530) !" << std::endl;

			if (!SteamAPI_Init())
			{
				
				std::cout << "Fail to init Steam API !" << std::endl;
			}
			else
			{
				_SteamInventoryInit_Status = true;

				std::cout << "Current user Name :" << SteamFriends()->GetPersonaName() << std::endl;
				std::cout << "Current user State :" << SteamFriends()->GetPersonaState() << std::endl;
				std::cout << "Current user SteamId :" << SteamApps()->GetAppOwner().GetAccountID() << std::endl;
				std::cout << "Current user VAC Status :" << SteamApps()->BIsVACBanned() << std::endl;
			}
		}
	}
	~Tanxl_Inventory() {};
	Tanxl_Inventory(const Tanxl_Inventory&) :_PlaytimeRequestResult(k_SteamInventoryResultInvalid) {}
	Tanxl_Inventory& operator=(const Tanxl_Inventory&) { return *this; }

	const std::string _Version{ "0.1" };

	SteamInventoryResult_t _PlaytimeRequestResult;
	bool _SteamInventoryInit_Status;
};

#endif