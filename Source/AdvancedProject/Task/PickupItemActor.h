#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupItemActor.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class ADVANCEDPROJECT_API APickupItemActor : public AActor
{
	GENERATED_BODY()

public:
	APickupItemActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Collision;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category="Item")
	FName ItemID = TEXT("Potion");

	UPROPERTY(EditAnywhere, Category="Item")
	int32 Count = 1;

	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};
