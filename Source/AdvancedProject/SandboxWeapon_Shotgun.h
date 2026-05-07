#pragma once

#include "CoreMinimal.h"
#include "SandboxWeaponBase.h"
#include "SandboxWeapon_Shotgun.generated.h"

UCLASS()
class ADVANCEDPROJECT_API ASandboxWeapon_Shotgun : public ASandboxWeaponBase
{
	GENERATED_BODY()

public:
	ASandboxWeapon_Shotgun();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Shotgun")
	int32 PelletCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Shotgun")
	float SpreadAngleDegrees;

	UFUNCTION(BlueprintCallable)
	void LineTraceShotgun(FVector Direction);
};
