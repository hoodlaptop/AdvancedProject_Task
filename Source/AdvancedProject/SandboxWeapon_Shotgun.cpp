#include "SandboxWeapon_Shotgun.h"

#include "Components/ArrowComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

ASandboxWeapon_Shotgun::ASandboxWeapon_Shotgun()
{
	PelletCount = 8;
	SpreadAngleDegrees = 8.0f;

	AmmoPerFire = 1;
	MaxAmmo = 6;
	RoF = 1.0f;
	Range = 1500.0f;
	DamagePerHit = 15.0f;

	RecoilPitch = -5.0f;
	RecoilYawMin = -1.5f;
	RecoilYawMax = 1.5f;
}

void ASandboxWeapon_Shotgun::LineTraceShotgun(FVector Direction)
{
	if (FirePoint == nullptr || GetWorld() == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s shotgun fire failed. FirePoint or World is null."), *GetName());
		return;
	}

	const FVector Start = FirePoint->GetComponentLocation();

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(GetOwner());

	for (int32 i = 0; i < PelletCount; ++i)
	{
		const FVector ShotDirection = FMath::VRandCone(
			Direction,
			FMath::DegreesToRadians(SpreadAngleDegrees)
		);

		const FVector End = Start + ShotDirection * Range;

		FHitResult Hit;
		const bool bHit = GetWorld()->LineTraceSingleByChannel(
			Hit,
			Start,
			End,
			ECC_Visibility,
			QueryParams
		);

		DrawDebugLine(
			GetWorld(),
			Start,
			End,
			bHit ? FColor::Green : FColor::Red,
			false,
			1.0f,
			0,
			1.0f
		);

		if (bHit && Hit.GetActor())
		{
			UE_LOG(LogTemp, Warning, TEXT("Shotgun hit: %s / Class: %s"), *Hit.GetActor()->GetName(), *Hit.GetActor()->GetClass()->GetName());

			UGameplayStatics::ApplyPointDamage(
				Hit.GetActor(),
				DamagePerHit,
				ShotDirection,
				Hit,
				GetInstigatorController(),
				this,
				nullptr
			);
		}
	}
}
