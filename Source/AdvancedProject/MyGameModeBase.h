#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"


UCLASS()
class ADVANCEDPROJECT_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void BeginPlay() override;
};
