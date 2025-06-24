//_VERSION_0_1_ UPDATE LOG
// LAST_UPDATE 2023-07-07 11:06
// 新增STEAM服务模块，初始提供库存查询服务
// 库存类改为单例模式
// 库存类增加版本信息
// 库存类增加初始化状态并根据状态执行功能
// 增加库存物品类
// 增加成就枚举
// 增加成就类与成就解锁功能
// 增加请求用户数据接口
// 修正初始化流程
// 增加生成测试物品接口
// 增加宏控制程序启动条件
// 增加检测成就状态的接口

#pragma once

#ifndef _TANXL_STEAMSERVICE_
#define _TANXL_STEAMSERVICE_

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
	static Tanxl_Achievement& Get_AchievementBase()
	{
		static Tanxl_Achievement* Achievement{ new Tanxl_Achievement() };
		return *Achievement;
	}

	void UnlockAchievement(Achievement_t& achievement)
	{
		achievement.m_bAchieved = true;
		achievement.m_iIconImage = 0;
		if (_SteamUserStats != nullptr)
			_SteamUserStats->SetAchievement(achievement.m_pchAchievementID);
	}

	bool CheckAchievement(Achievement_t& achievement)
	{
		bool Is_Unlock{ false };
		if (_SteamUserStats != nullptr)
			_SteamUserStats->GetAchievementAndUnlockTime(achievement.m_pchAchievementID, &Is_Unlock, nullptr);
		return Is_Unlock;
	}

	bool RequestStats()//请求用户统计数据
	{
		if (NULL == SteamUserStats() || NULL == SteamUser())// 是否已加载 Steam 若否,则我们无法获取统计
			return false;
		if (!SteamUser()->BLoggedOn())// 用户是否已登录 若否,则我们无法获取统计
			return false;
		return SteamUserStats()->RequestCurrentStats();
	}

private:
	Tanxl_Achievement()
	{
		std::cout << "Achievement Init Called" << std::endl;
		_SteamUser = SteamUser();
		_SteamUserStats = SteamUserStats();
	}

	ISteamUser* _SteamUser;
	ISteamUserStats* _SteamUserStats;
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
		SteamInventory()->TriggerItemDrop(&_PlaytimeRequestResult, Tanxl_Secret_Core_LIMITED_DROP_ITEM);
		//std::cout << "Item Drop Called !" << std::endl;
	}

	void GenerateItemsTest(ETanxl_Inventory_ItemDefId Item)
	{
		std::vector<SteamItemDef_t> newItems;
		newItems.push_back(Item);
		SteamInventory()->GenerateItems(NULL, newItems.data(), NULL, (uint32)newItems.size());
	}

private:

	Tanxl_Inventory() :_PlaytimeRequestResult(k_SteamInventoryResultInvalid), _SteamInventoryInit_Status(false)
	{
		if (SteamAPI_RestartAppIfNecessary(1929530))
		{
			std::cout << "Fail to init SteamAPI_(1929530) !" << std::endl;
#if _STEAM_ALPHA_VERSION_
			exit(0);
#endif
		}
		else
		{
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
				
				std::cout << "Steam API Init Success !" << std::endl;
			}
		}
	}

	~Tanxl_Inventory() {};
	Tanxl_Inventory(const Tanxl_Inventory&) :_PlaytimeRequestResult(k_SteamInventoryResultInvalid), _SteamInventoryInit_Status(false){}
	Tanxl_Inventory& operator=(const Tanxl_Inventory&) { return *this; }

	const std::string _Version{ "0.1" };

	SteamInventoryResult_t _PlaytimeRequestResult;
	bool _SteamInventoryInit_Status;
};

class TanxlItem
{
public:
	SteamItemInstanceID_t GetItemId() const { return _Details.m_itemId; }
	SteamItemDef_t GetDefinition() const { return _Details.m_iDefinition; }
	uint16 GetQuantity() const { return _Details.m_unQuantity; }
private:
	friend class Tanxl_Inventory;
	SteamItemDetails_t _Details;
};

#endif