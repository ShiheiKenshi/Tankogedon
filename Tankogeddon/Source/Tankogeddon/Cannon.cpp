#include "Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"

ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComp;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	CannonMesh->SetupAttachment(SceneComp);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowComponent"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);
}

void ACannon::Fire()
{
	if (!IsReadyToFire())
	{
		return;
	}

	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, "Fire projectile");
		Ammo -= 1;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Ammo: %d"), Ammo));
		
	}
	if (CannonType == ECannonType::FireTrace)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Fire trace");
		Ammo -= 1;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Ammo: %d"), Ammo));
		
	}
	bReadyToFire = false;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, FireRate, false);

	if (CannonType == ECannonType::FireRapid)
	{
		if (Ammunition > 0)
		{
			const ANSICHAR* numberShots[] = { "error", "fifth", "fourth", "third","second","first" };
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("Fire %s rapid shot"), /*Ammunition*/numberShots[Ammunition]));
			Ammunition -= 1;
		}
		else
		{
			Ammunition = 5;
			Ammo -= 1;
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Ammo: %d"), Ammo));
			bReadyToFire = false;
			GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, FireRate, false);
		}
	}
}

void ACannon::FireSpecial()
{
	if (AmmoSpecial <= 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, "Out of Stock");
		return;
	}

	if (!IsReadyToFireSpecial())
	{
		return;
	}
		
	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, "Fire Bomb");
		AmmoSpecial -= 1;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Special Ammo: %d"), AmmoSpecial));
		
	}
	if (CannonType==ECannonType::FireTrace)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Fire laser");
		AmmoSpecial -= 1;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Special Ammo: %d"), AmmoSpecial));
		
	}
	if (CannonType == ECannonType::FireRapid)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "Fire Bomb");
		AmmoSpecial -= 1;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("Special Ammo: %d"), AmmoSpecial));
	}
	bReadyToFireSpecial = false;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerSpecial, this, &ACannon::ReloadSpecial, FireRate, false);
}

bool ACannon::IsReadyToFire()
{
	return bReadyToFire;
}

void ACannon::Reload()
{
	if (Ammo>0)
	{
		bReadyToFire = true;
		return;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, "Loading Ammo");
		GetWorld()->GetTimerManager().SetTimer(ReloadAmmoTimer, this, &ACannon::Reload, AmmoReload, false);
		Ammo += 10;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, "Loading Complete");
		return;
	}
}

bool ACannon::IsReadyToFireSpecial()
{
	return bReadyToFireSpecial;
}

void ACannon::ReloadSpecial()
{
	if (AmmoSpecial>0)
	{
		bReadyToFireSpecial = true;
		return;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, "Out of Stock");
	}
	
}

void ACannon::BeginPlay()
{
	Super::BeginPlay();
	bReadyToFire = true;
	bReadyToFireSpecial = true;
	Ammo = 10;
	AmmoSpecial = 5;
	
}
