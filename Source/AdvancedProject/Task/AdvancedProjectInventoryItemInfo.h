#pragma once

#include "CoreMinimal.h"
#include "AdvancedProjectInventoryItemInfo.generated.h"

USTRUCT(BlueprintType)
struct ADVANCEDPROJECT_API FAdvancedProjectInventoryItemInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStack = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName RequiredTitle;
};
