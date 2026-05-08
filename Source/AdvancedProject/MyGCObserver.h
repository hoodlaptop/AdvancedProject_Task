#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyGCObserver.generated.h"

UCLASS()
class ADVANCEDPROJECT_API AMyGCObserver : public AActor
{
	GENERATED_BODY()

public:
	AMyGCObserver();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UMyTestObject* SafeOject;

	TWeakObjectPtr<class UMyTestObject> DangerObject;

	/*UFUNCTION()
	void TryToUseObject();
	
	FTimerHandle CrashTimerHandle;*/
};
