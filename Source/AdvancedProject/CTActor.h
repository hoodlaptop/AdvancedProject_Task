#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CTActor.generated.h"

UCLASS()
class ADVANCEDPROJECT_API ACTActor : public AActor
{
	GENERATED_BODY()

public:
	ACTActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void StartAsyncTrace();

	void OnAsyncTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data);
};
