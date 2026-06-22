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
// 增加消耗物品接口
// 增加成员存储库存指针
// 增加获取所有库存的功能
// 定义转移到源文件中
// 库存组件改为继承自引擎基础类
// 增加对玩家当前语言的获取
// 增加基础类用于初始化SteamAPI
// 多个成员函数设为常量
// 获取用户语言接口增加中文与日语的获取
// 新增一个测试成就
// 基础类转为静态类
// 构造函数的初始化流程转移到初始化接口
// 增加应用程序信息获取接口
// 修复库存功能未启用的问题
// 代码整理
// 基础类初始化时不载入库存类的物品
// 移除成就类的私有指针
// 成就检查接口内部调用更短的函数

#pragma once

#ifndef _TANXL_STEAMSERVICE_
#define _TANXL_STEAMSERVICE_

#include <list>
#include <vector>
#include <iostream>

#include "public/steam/steam_api.h"
#include "public/steam/isteamapps.h"
#include "Tanxl_EngineBase.h"

#define _STEAM_ALPHA_VERSION_ 0
#define _STEAM_REINIT_ENABLE_ 0


enum ETanxl_Inventory_ItemDefId
{
	Tanxl_Pormise_LIMITED_ITEM			= 1,
	Tanxl_Secret_Core_LIMITED_DROP_ITEM = 2,

	Tanxl_Item_Collection_01			= 10001
};

enum ETanxl_Achievement_DefId
{
	ACHIEVEMENT_SECRET_PROPERTY = 1,
	ACHIEVEMENT_BAG_OF_MONEY	= 2,
	ACHIEVEMENT_PLENTY_OF_MONEY	= 3
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
	_ACH_ID(ACHIEVEMENT_SECRET_PROPERTY, "Secret"),
	_ACH_ID(ACHIEVEMENT_BAG_OF_MONEY, "100 Coins"),
	_ACH_ID(ACHIEVEMENT_PLENTY_OF_MONEY, "500 Coins")
};

class Steam_Service
{
public:
	static ISteamUser* GetSteamUser();
	static ISteamApps* GetSteamApps();
	static ISteamUserStats* GetSteamUserStats();
	static ISteamInventory* GetSteamInvetory();

	static bool Reinit_Steam();
	static int Get_InitStatus();

private:
	Steam_Service();
	~Steam_Service();
	Steam_Service(const Steam_Service&);
	Steam_Service& operator=(const Steam_Service&);

	static ISteamUser* _SteamUser;
	static ISteamApps* _SteamApps;
	static ISteamUserStats* _SteamUserStats;
	static ISteamInventory* _Steam_Invetory;

	static int _Steam_API_InitStatus;
};

class Tanxl_Achievement
{
public:
	static Tanxl_Achievement& Get_AchievementBase();

	void UnlockAchievement(Achievement_t& achievement);

	bool CheckAchievement(Achievement_t& achievement);

	bool RequestStats();//请求用户统计数据

private:
	Tanxl_Achievement();
};

class Tanxl_Inventory : public Tanxl_ClassBase
{
public:

	static Tanxl_Inventory* Get_InventoryBase();

	const std::string Get_Version();

	void RefreshFromServer();

	void CheckForItemDrops();

	void GenerateItemsTest(ETanxl_Inventory_ItemDefId Item);

	void ConsumeInvetoryItem(ETanxl_Inventory_ItemDefId ItemInstanceId);

	bool AddPromoItem(ETanxl_Inventory_ItemDefId Item);

	ECurren_Language Get_User_Language();

private:

	Tanxl_Inventory();

	~Tanxl_Inventory();
	Tanxl_Inventory(const Tanxl_Inventory&);
	Tanxl_Inventory& operator=(const Tanxl_Inventory&);

	STEAM_CALLBACK(Tanxl_Inventory, OnSteamInventoryFullUpdate, SteamInventoryFullUpdate_t, _SteamInventoryFullUpdate);

	ISteamInventory* _Steam_Invetory;

	std::list<TanxlItem*> _listPlayerItems;

	SteamInventoryResult_t _PlaytimeRequestResult;
	bool _SteamInventoryInit_Status;
};

#endif