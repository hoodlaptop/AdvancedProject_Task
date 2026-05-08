#pragma once

#include "CoreMinimal.h"
#include "WeaponTemplateBase.h"
#include "TemplateWeapon_Shotgun.generated.h"

UCLASS()
class ADVANCEDPROJECT_API ATemplateWeapon_Shotgun : public AWeaponTemplateBase
{
	GENERATED_BODY()

public:
	ATemplateWeapon_Shotgun();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Shotgun")
	int32 PelletCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapon|Shotgun")
	float SpreadAngleDegrees;

	virtual void ProcessFiring_Implementation() override;
};
