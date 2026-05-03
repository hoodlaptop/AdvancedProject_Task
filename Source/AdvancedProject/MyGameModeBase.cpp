#include "MyGameModeBase.h"
#include "TestMyActor.h"

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	ATestMyActor* ActorA = GetWorld()->SpawnActor<ATestMyActor>();
	UE_LOG(LogTemp, Warning, TEXT("ActorA Init Health : %d"), ActorA->Health);
	
	ActorA->Health = 50;
	UE_LOG(LogTemp, Warning, TEXT("ActorA Modi Health : %d"), ActorA->Health);
	
	ATestMyActor* MyActorCDO = GetMutableDefault<ATestMyActor>();
	UE_LOG(LogTemp, Warning, TEXT("CDO Init Health : %d"), MyActorCDO->Health);
	
	MyActorCDO->Health = 200;
	UE_LOG(LogTemp, Warning, TEXT("MyActorCDO Modi Health : %d"), MyActorCDO->Health);
	
	ATestMyActor* ActorB = GetWorld()->SpawnActor<ATestMyActor>();
	UE_LOG(LogTemp, Warning, TEXT("ActorB Init Health : %d"), ActorB->Health);
	UE_LOG(LogTemp, Warning, TEXT("ActorA Current Health : %d"), ActorA->Health);
}
