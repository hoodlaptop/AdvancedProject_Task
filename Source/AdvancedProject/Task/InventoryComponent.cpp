#include "InventoryComponent.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool UInventoryComponent::AddItem(FName ItemID, int32 Count)
{
	if (Count <= 0)
	{
		return false;
	}

	FAdvancedProjectInventoryItemInfo* ItemInfo = ItemInfoMap.Find(ItemID);
	if (ItemInfo == nullptr)
	{
		return false;
	}

	for (FInventoryItem& Item : InventoryItems)
	{
		if (Item.ItemID == ItemID)
		{
			Item.Count += Count;
			return true;
		}
	}

	FInventoryItem NewItem;
	NewItem.ItemID = ItemID;
	NewItem.Count = Count;

	InventoryItems.Add(NewItem);
	return true;
}

bool UInventoryComponent::RemoveItem(FName ItemID, int32 Count)
{
	if (Count <= 0)
	{
		return false;
	}

	for (int32 i = 0; i < InventoryItems.Num(); ++i)
	{
		if (InventoryItems[i].ItemID == ItemID)
		{
			if (InventoryItems[i].Count < Count)
			{
				return false;
			}

			InventoryItems[i].Count -= Count;

			if (InventoryItems[i].Count <= 0)
			{
				InventoryItems.RemoveAt(i);
			}

			return true;
		}
	}

	return false;
}

bool UInventoryComponent::HasItem(FName ItemID) const
{
	for (const FInventoryItem& Item : InventoryItems)
	{
		if (Item.ItemID == ItemID && Item.Count > 0)
		{
			return true;
		}
	}

	return false;
}

bool UInventoryComponent::HasTitle(FName ItemID) const
{
	return OwnedTitles.Contains(ItemID);
}

void UInventoryComponent::AddTitle(FName TitleID)
{
	if (!TitleID.IsNone())
	{
		OwnedTitles.Add(TitleID);
	}
}
