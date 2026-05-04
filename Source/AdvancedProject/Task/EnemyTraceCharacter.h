#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyTraceCharacter.generated.h"

UCLASS()
class ADVANCEDPROJECT_API AEnemyTraceCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemyTraceCharacter();
	
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Trace")
	float TraceRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Trace")
	float TraceInterval;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy|Trace")
	bool bDrawDebug;
	
	float TraceElapsedTime;
	bool bTracePending;
	
	void StartAsyncTrace();
	
	void OnAsyncTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data);

};
