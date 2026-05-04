#include "WeaponTemplateBase.h"

void AWeaponTemplateBase::Fire()
{
	if (!CanFire)
	{
		return;
	}

	if (CheckAmmo())
	{
		PlayEffects();
		ProcessFiring();
		ApplyRecoil();
		UpdateAmmo();

		Super::Fire();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s has no ammo."), *GetName());
	}
}

void AWeaponTemplateBase::Reload_Implementation()
{
	CurrentAmmo = MaxAmmo;
}

bool AWeaponTemplateBase::CheckAmmo_Implementation()
{
	return AmmoPerFire <= CurrentAmmo;
}

void AWeaponTemplateBase::ProcessFiring_Implementation()
{
}

void AWeaponTemplateBase::UpdateAmmo_Implementation()
{
	CurrentAmmo -= AmmoPerFire;
}
