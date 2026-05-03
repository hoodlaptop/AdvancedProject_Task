#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AdvancedProjectInventoryItemInfo.h"
#include "InventoryItem.h"
#include "InventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ADVANCEDPROJECT_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	TArray<FInventoryItem> InventoryItems;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory")
	TMap<FName, FAdvancedProjectInventoryItemInfo> ItemInfoMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Title")
	TSet<FName> OwnedTitles;
	
	bool AddItem(FName ItemID, int32 Count);
	bool RemoveItem(FName ItemID, int32 Count);
	
	bool HasItem(FName ItemID) const;
	bool HasTitle(FName ItemID) const;
	
	void AddTitle(FName TitleID);
};
