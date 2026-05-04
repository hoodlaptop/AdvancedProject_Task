#include "WeaponBase.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/Pawn.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	FirePoint = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePoint"));
	FirePoint->SetupAttachment(RootComponent);

	AmmoPerFire = 1;
	CurrentAmmo = 0;
	MaxAmmo = 12;
	RoF = 1.f;
	CanFire = true;
	Range = 1000.f;
	DamagePerHit = 100.f;

	bUseRecoil = true;
	RecoilPitch = -2.0f;
	RecoilYawMin = -0.5f;
	RecoilYawMax = 0.5f;
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	CurrentAmmo = MaxAmmo;

	if (bAutoFireForTest)
	{
		StartAutoFireForTest();
	}
}

void AWeaponBase::Fire()
{
	CanFire = false;
	GetWorld()->GetTimerManager().SetTimer(TimerFireDelay, this, &AWeaponBase::HandleFireDelay, 1.f / RoF, false);
}

void AWeaponBase::HandleFireDelay()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerFireDelay);
	CanFire = true;
}

void AWeaponBase::ApplyRecoil()
{
	if (!bUseRecoil)
	{
		return;
	}

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
	{
		return;
	}

	const float RandomYaw = FMath::RandRange(RecoilYawMin, RecoilYawMax);

	OwnerPawn->AddControllerPitchInput(RecoilPitch);
	OwnerPawn->AddControllerYawInput(RandomYaw);
}

void AWeaponBase::StartAutoFireForTest()
{
	GetWorld()->GetTimerManager().SetTimer(
		AutoFireTimerHandle,
		this,
		&AWeaponBase::AutoFireOnce,
		AutoFireInterval,
		true
	);
}

void AWeaponBase::AutoFireOnce()
{
	Fire();
}
