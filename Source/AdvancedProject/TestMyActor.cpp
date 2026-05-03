#include "TestMyActor.h"

ATestMyActor::ATestMyActor()
{
	PrimaryActorTick.bCanEverTick = true;

	
	Health = 100;
}

void ATestMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATestMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

