#include "Tanxl_SteamService.h"

void Tanxl_Inventory::OnSteamInventoryFullUpdate(SteamInventoryFullUpdate_t* callback)
{
	bool bGotResult = false;
	std::vector<SteamItemDetails_t> vecDetails;
	uint32 count = 0;
	if (_Steam_Invetory->GetResultItems(callback->m_handle, NULL, &count))
	{
		vecDetails.resize(count);
		bGotResult = _Steam_Invetory->GetResultItems(callback->m_handle, vecDetails.data(), &count);
	}

	if (bGotResult)
	{
		// For everything already in the inventory, check for update (exists in result) or removal (does not exist)
		std::list<TanxlItem*>::iterator iter;
		for (iter = _listPlayerItems.begin(); iter != _listPlayerItems.end(); /*incr at end of loop*/)
		{
			bool bFound = false;
			for (size_t i = 0; i < vecDetails.size(); i++)
			{
				if ((*iter)->GetItemId() == vecDetails[i].m_itemId)
				{
					// Update item with matching item id
					(*iter)->GetDetails() = vecDetails[i];

					// Remove elements from the result vector as we process updates (fast swap-and-pop removal)
					if (i < vecDetails.size() - 1)
						vecDetails[i] = vecDetails.back();
					vecDetails.pop_back();

					bFound = true;
					break;
				}
			}

			if (!bFound)
			{
				// No items in the full update match the existing item. Delete current iterator and advance.
				delete* iter;
				iter = _listPlayerItems.erase(iter);
			}
			else
			{
				// Increment iterator without deleting.
				++iter;
			}
		}

		// Anything remaining in the result vector is a new item, since we removed all the updates.
		for (size_t i = 0; i < vecDetails.size(); ++i)
		{
			TanxlItem* item = new TanxlItem();
			item->SetDetails(vecDetails[i]);
			_listPlayerItems.push_back(item);
		}
	}
}

Steam_Service& Steam_Service::GetServiceBase()
{
	static Steam_Service Service_Base;
	return Service_Base;
}

inline ISteamUser* Steam_Service::GetSteamUser()
{
	if (NULL == _SteamUserStats || NULL == _SteamUser)// �Ƿ��Ѽ��� Steam ����,�������޷���ȡͳ��
		return nullptr;
	if (!_SteamUser->BLoggedOn())// �û��Ƿ��ѵ�¼ ����,�������޷���ȡͳ��
		return nullptr;
	if (this->_Steam_API_InitStatus == true)
		return this->_SteamUser;
	return nullptr;
}

inline ISteamUserStats* Steam_Service::GetSteamUserStats()
{
	if (this->_Steam_API_InitStatus == true)
		return this->_SteamUserStats;
	return nullptr;
}

inline ISteamInventory* Steam_Service::GetSteamInvetory()
{
	if (this->_Steam_API_InitStatus == true)
		return this->_Steam_Invetory;
	return nullptr;
}

bool Steam_Service::Reinit_Steam()
{
#if _STEAM_REINIT_ENABLE_
	if (this->_Steam_API_InitStatus == false)
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
				_Steam_API_InitStatus = true;
				_Steam_Invetory = SteamInventory();
				_Steam_Invetory->LoadItemDefinitions();

				_SteamUser = SteamUser();
				_SteamUserStats = SteamUserStats();

				std::cout << "Current user Name :" << SteamFriends()->GetPersonaName() << std::endl;
				std::cout << "Current user State :" << SteamFriends()->GetPersonaState() << std::endl;
				std::cout << "Current user SteamId :" << SteamApps()->GetAppOwner().GetAccountID() << std::endl;
				std::cout << "Current user VAC Status :" << SteamApps()->BIsVACBanned() << std::endl;
				std::cout << "Current Language :" << SteamApps()->GetCurrentGameLanguage() << std::endl;

				std::cout << "Steam API Init Success !" << std::endl;
			}
		}
	}
#endif
	return this->_Steam_API_InitStatus;
}

bool Steam_Service::Get_InitStatus()
{
	return this->_Steam_API_InitStatus;
}

Steam_Service::Steam_Service() :_Steam_API_InitStatus(false),
_SteamUser(nullptr), _SteamUserStats(nullptr), _Steam_Invetory(nullptr)
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
			_Steam_API_InitStatus = true;
			_Steam_Invetory = SteamInventory();
			_Steam_Invetory->LoadItemDefinitions();

			_SteamUser = SteamUser();
			_SteamUserStats = SteamUserStats();

			std::cout << "Current user Name :" << SteamFriends()->GetPersonaName() << std::endl;
			std::cout << "Current user State :" << SteamFriends()->GetPersonaState() << std::endl;
			std::cout << "Current user SteamId :" << SteamApps()->GetAppOwner().GetAccountID() << std::endl;
			std::cout << "Current user VAC Status :" << SteamApps()->BIsVACBanned() << std::endl;
			std::cout << "Current Language :" << SteamApps()->GetCurrentGameLanguage() << std::endl;

			std::cout << "Steam API Init Success !" << std::endl;
		}
	}
}

Steam_Service::~Steam_Service() {}
Steam_Service::Steam_Service(const Steam_Service&) :_Steam_API_InitStatus(false),
_SteamUser(nullptr), _SteamUserStats(nullptr), _Steam_Invetory(nullptr) {}
Steam_Service& Steam_Service::operator=(const Steam_Service&) { return *this; }

Tanxl_Achievement& Tanxl_Achievement::Get_AchievementBase()
{
	static Tanxl_Achievement* Achievement{ new Tanxl_Achievement() };
	return *Achievement;
}

void Tanxl_Achievement::UnlockAchievement(Achievement_t& achievement)
{
	achievement.m_bAchieved = true;
	achievement.m_iIconImage = 0;
	if (_SteamUserStats != nullptr)
		_SteamUserStats->SetAchievement(achievement.m_pchAchievementID);
}

bool Tanxl_Achievement::CheckAchievement(Achievement_t& achievement)
{
	bool Is_Unlock{ false };
	if (_SteamUserStats != nullptr)
		_SteamUserStats->GetAchievementAndUnlockTime(achievement.m_pchAchievementID, &Is_Unlock, nullptr);
	return Is_Unlock;
}

bool Tanxl_Achievement::RequestStats()
{
	if (NULL == _SteamUserStats || NULL == _SteamUser)// �Ƿ��Ѽ��� Steam ����,�������޷���ȡͳ��
		return false;
	if (!_SteamUser->BLoggedOn())// �û��Ƿ��ѵ�¼ ����,�������޷���ȡͳ��
		return false;
	return _SteamUserStats->RequestCurrentStats();
}

Tanxl_Achievement::Tanxl_Achievement()
{
	std::cout << "Achievement Init Called" << std::endl;
	Steam_Service* Service{ &Steam_Service::GetServiceBase() };
	Service->Reinit_Steam();
	_SteamUser = Service->GetSteamUser();
	_SteamUserStats = Service->GetSteamUserStats();
}

Tanxl_Inventory& Tanxl_Inventory::Get_InventoryBase()
{
	static Tanxl_Inventory* Inventory{ new Tanxl_Inventory() };
	return *Inventory;
}

const std::string Tanxl_Inventory::Get_Version()
{
	return Tanxl_ClassBase::Get_Version();
}

void Tanxl_Inventory::RefreshFromServer()
{
	if (!_SteamInventoryInit_Status)
		return;
	_Steam_Invetory->GetAllItems(NULL);
}

void Tanxl_Inventory::CheckForItemDrops()
{
	if (!_SteamInventoryInit_Status)
		return;
	_Steam_Invetory->TriggerItemDrop(&_PlaytimeRequestResult, Tanxl_Secret_Core_LIMITED_DROP_ITEM);
	std::cout << "Item Drop Called !" << std::endl;

	std::list<TanxlItem*>::iterator iter;
	for (iter = _listPlayerItems.begin(); iter != _listPlayerItems.end(); ++iter)
	{
		std::cout << "InstanceId :" << (*iter)->GetItemId() << std::endl;
	}
	std::cout << std::endl;
}

void Tanxl_Inventory::GenerateItemsTest(ETanxl_Inventory_ItemDefId Item)
{
	std::vector<SteamItemDef_t> newItems;
	newItems.push_back(Item);
	_Steam_Invetory->GenerateItems(NULL, newItems.data(), NULL, (uint32)newItems.size());
}

void Tanxl_Inventory::ConsumeInvetoryItem(ETanxl_Inventory_ItemDefId ItemInstanceId)
{
	_Steam_Invetory->ConsumeItem(NULL, ItemInstanceId, 1);
}

bool Tanxl_Inventory::AddPromoItem(ETanxl_Inventory_ItemDefId Item)
{
	return _Steam_Invetory->AddPromoItem(NULL, Item);
}

ECurren_Language Tanxl_Inventory::Get_User_Language()
{
	if(SteamApps() == nullptr)
		return ECurren_Language::LANGUAGE_ENGLISH;

	std::string UserLanguage{ SteamApps()->GetCurrentGameLanguage() };
	/*if (UserLanguage == "schinese")
		return ECurren_Language::LANGUAGE_CHINESE;
	else */if (UserLanguage == "russian")
		return ECurren_Language::LANGUAGE_RUSSIAN;
	else
		return ECurren_Language::LANGUAGE_ENGLISH;
}

Tanxl_Inventory::Tanxl_Inventory() :_PlaytimeRequestResult(k_SteamInventoryResultInvalid), _SteamInventoryInit_Status(false),
_SteamInventoryFullUpdate(this, &Tanxl_Inventory::OnSteamInventoryFullUpdate), _Steam_Invetory(nullptr), Tanxl_ClassBase("0.1")
{
	Steam_Service* Service{ &Steam_Service::GetServiceBase() };
	Service->Reinit_Steam();
	_Steam_Invetory = Service->GetSteamInvetory();
	if (Service->Get_InitStatus())
		_Steam_Invetory->LoadItemDefinitions();
}

Tanxl_Inventory::~Tanxl_Inventory() {};

Tanxl_Inventory::Tanxl_Inventory(const Tanxl_Inventory&) :_PlaytimeRequestResult(k_SteamInventoryResultInvalid), _SteamInventoryInit_Status(false),
_SteamInventoryFullUpdate(this, &Tanxl_Inventory::OnSteamInventoryFullUpdate), _Steam_Invetory(nullptr), Tanxl_ClassBase("0.1") {}

Tanxl_Inventory& Tanxl_Inventory::operator=(const Tanxl_Inventory&) { return *this; }