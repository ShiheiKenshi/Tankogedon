#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStruct.h"
#include "Cannon.generated.h"

UCLASS()
class TANKOGEDDON_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACannon();

	void Fire();
	bool IsReadyToFire();
	void Reload();
	void Rapid();
	void ReloadAmmunition(int32 AmmoStock);

	void FireSpecial();
	bool IsReadyToFireSpecial();
	void ReloadSpecial();

	void ProjectileFire();
	void RapidFire();
	void TraceFire();

	void LaserFire();
	void BombFire();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* CannonMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	ECannonType CannonType = ECannonType::FireProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	float FireRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	float AmmoReload = 2.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	float FireRange = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	int32 Damage = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 Ammo = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 AmmoSpecial = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 Shells = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float FireRapidRate = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 Ammunition = 0;

	bool bReadyToFire = true;
	bool bReadyToFireSpecial = true;

	FTimerHandle ReloadTimer;
	FTimerHandle ReloadTimerSpecial;
	FTimerHandle ReloadAmmoTimer;
	FTimerHandle RapidFireTimer;

private:
	int32 CurrentAmmo = 0;
};
