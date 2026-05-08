#include "AnyActor.h"

AAnyActor::AAnyActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AAnyActor::BeginPlay()
{
	Super::BeginPlay();

	TMap<int32, FString> ItemMap;

	ItemMap.Add(101, TEXT("Sword"));
	ItemMap.Add(102, TEXT("Shield"));

	ItemMap.Emplace(103, TEXT("Potion"));

	if (ItemMap.Contains(101))
	{
		FString* FoundItem = ItemMap.Find(101);
	}
	FString& ItemRef = ItemMap.FindOrAdd(104);
	ItemRef = TEXT("Bow");

	for (TPair<int32, FString>& i : ItemMap)
	{
	}

	for (TMap<int32, FString>::TIterator it = ItemMap.CreateIterator(); it; ++it)
	{
		if (it.Key() == 103)
		{
			it.RemoveCurrent();
		}
	}

	ItemMap.Remove(102);

	ItemMap.Compact();
	ItemMap.Shrink();
}

void AAnyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
