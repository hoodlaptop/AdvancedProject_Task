#include "MyGCObserver.h"

#include "MyTestObject.h"

AMyGCObserver::AMyGCObserver()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMyGCObserver::BeginPlay()
{
	Super::BeginPlay();
	
	SafeOject = NewObject<UMyTestObject>(this);
	SafeOject->InitObject(TEXT("SafeObject_Mamber"));
	
	DangerObject = NewObject<UMyTestObject>(this);
	DangerObject->InitObject(TEXT("DangerObject_Mamber"));
	
	UE_LOG(LogTemp, Log, TEXT("Garbage Collection Starts Operation"));
	
	// GetWorld()->GetTimerManager().SetTimer(CrashTimerHandle, this, &AMyGCObserver::TryToUseObject, 12.f, false);
}

void AMyGCObserver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	bool bSafeIf = SafeOject != nullptr;
	bool bSafeValid = SafeOject->IsValidLowLevel();
	
	bool bDangerIf = DangerObject != nullptr;
	bool bDangerValid = DangerObject->IsValidLowLevel();
	
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Green, 
		FString::Printf(TEXT("Safe(UPROPERTY) -> if : %s, IsValid : %s"), bSafeIf ? TEXT("True") : TEXT("False"), bSafeValid ? TEXT("True") : TEXT("False")));
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, 
		FString::Printf(TEXT("Danger(UPROPERTY) -> if : %s, IsValid : %s"), bDangerIf ? TEXT("True") : TEXT("False"), bDangerValid ? TEXT("True") : TEXT("False")));
}

/*void AMyGCObserver::TryToUseObject()
{
	UE_LOG(LogTemp, Warning, TEXT("10s Try to Use"));
	DangerObject->InitObject(TEXT("Boom!!!"));
}*/
