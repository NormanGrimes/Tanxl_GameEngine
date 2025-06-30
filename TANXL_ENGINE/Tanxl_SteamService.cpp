#include "Tanxl_SteamService.h"

void Tanxl_Inventory::OnSteamInventoryFullUpdate(SteamInventoryFullUpdate_t* callback)
{
	bool bGotResult = false;
	std::vector<SteamItemDetails_t> vecDetails;
	uint32 count = 0;
	if (SteamInventory()->GetResultItems(callback->m_handle, NULL, &count))
	{
		vecDetails.resize(count);
		bGotResult = SteamInventory()->GetResultItems(callback->m_handle, vecDetails.data(), &count);
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