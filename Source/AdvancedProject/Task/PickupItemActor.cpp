#include "PickupItemActor.h"

#include "InventoryComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "InventoryComponent.h"

APickupItemActor::APickupItemActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	Collision->SetSphereRadius(80.0f);
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	Collision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Collision);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APickupItemActor::BeginPlay()
{
	Super::BeginPlay();

	Collision->OnComponentBeginOverlap.AddDynamic(this, &APickupItemActor::OnOverlapBegin);
}

void APickupItemActor::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
)
{
	if (OtherActor == nullptr || OtherActor == this)
	{
		return;
	}

	UInventoryComponent* Inventory = OtherActor->FindComponentByClass<UInventoryComponent>();

	if (Inventory == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap actor has no InventoryComponent: %s"), *OtherActor->GetName());
		return;
	}

	const bool bAdded = Inventory->AddItem(ItemID, Count);

	if (bAdded)
	{
		UE_LOG(LogTemp, Log, TEXT("Picked up item: %s / Count: %d"), *ItemID.ToString(), Count);
		Destroy();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to pick up item: %s"), *ItemID.ToString());
	}
}