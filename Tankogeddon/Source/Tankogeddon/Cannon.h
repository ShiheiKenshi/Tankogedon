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

	void FireSpecial();
	bool IsReadyToFireSpecial();
	void ReloadSpecial();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* CannonMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	ECannonType CannonType = ECannonType::FireProjectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	float FireRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	float AmmoReload = 2.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	float FireRange = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	int Damage = 1;

	UPROPERTY()
	int Ammo = 0;

	UPROPERTY()
	int AmmoSpecial = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire params")
	int Ammunition = 5;

	bool bReadyToFire = true;
	bool bReadyToFireSpecial = true;

	FTimerHandle ReloadTimer;
	FTimerHandle ReloadTimerSpecial;
	FTimerHandle ReloadAmmoTimer;

};
