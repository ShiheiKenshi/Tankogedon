#include "Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Projectile.h"
#include "DrawDebugHelpers.h"

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
	if (Ammo <= 0)
	{
		if (Ammunition <= 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Orange, "Out of Stock");
			return;
		}
		else
		{
			Reload();
		}
		
	}

	if (!IsReadyToFire())
	{
		return;
	}

	if (CannonType == ECannonType::FireProjectile)
	{
		ProjectileFire();
	}
	if (CannonType == ECannonType::FireTrace)
	{
		TraceFire();
	}

	if (CannonType == ECannonType::FireRapid)
	{
		RapidFire();
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
		BombFire();
	}
	if (CannonType==ECannonType::FireTrace)
	{
		LaserFire();		
	}
	if (CannonType == ECannonType::FireRapid)
	{
		BombFire();
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
		if (Ammunition>0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, "Loading Ammo");
			GetWorld()->GetTimerManager().SetTimer(ReloadAmmoTimer, this, &ACannon::Reload, AmmoReload, false);
			Ammo += 10;
			Ammunition--;
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("Ammunition: %d"), Ammunition));
			return;
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Out of Stock");
			return;
		}
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

void ACannon::ProjectileFire()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, "Fire projectile");

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	
	if (Projectile)
	{
		Projectile->Start();
	}

	Ammo -= 1;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Ammo: %d"), Ammo));
	bReadyToFire = false;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, FireRate, false);
}

void ACannon::RapidFire()
{
	GetWorld()->GetTimerManager().SetTimer(RapidFireTimer, this, &ACannon::Rapid, FireRapidRate, true, 0.0f);
	Ammo--;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Ammo: %d"), Ammo));
	bReadyToFire = false;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, FireRate, false);
}

void ACannon::Rapid()
{
	if (CurrentAmmo == Shells)
	{
		GetWorld()->GetTimerManager().ClearTimer(RapidFireTimer);
		CurrentAmmo = 0;
		return;
	}
	CurrentAmmo++;

	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	if (Projectile)
	{
		Projectile->Start();
	}
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, FString::Printf(TEXT("Fire %d rapid shot"), CurrentAmmo));
}

void ACannon::ReloadAmmunition(int32 AmmoStock)
{
	Ammunition += AmmoStock;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Black, FString::Printf(TEXT("Ammunition: %d"), Ammunition));
}

void ACannon::TraceFire()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Fire trace");
	FHitResult hitResult;
	FCollisionQueryParams traceParams = FCollisionQueryParams();
	traceParams.AddIgnoredActor(this);
	traceParams.bReturnPhysicalMaterial = false;
	FVector Start = ProjectileSpawnPoint->GetComponentLocation();
	FVector End = Start + ProjectileSpawnPoint->GetForwardVector() * FireRange;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, Start, End, ECollisionChannel::ECC_Visibility, traceParams))
	{
		DrawDebugLine(GetWorld(),Start,hitResult.Location,FColor::Red, false, 1.0f, 0, 10);
		if (hitResult.GetActor())
		{
			AActor* OverlappedActor = hitResult.GetActor();
			UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *hitResult.GetActor()->GetName());
			OverlappedActor->Destroy();
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Yellow, false, 1.0f, 0, 5);
	}

	Ammo -= 1;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Ammo: %d"), Ammo));
	bReadyToFire = false;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, FireRate, false);
}

void ACannon::LaserFire()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, "Fire laser");
	FHitResult hitResult;
	FCollisionQueryParams laserParams = FCollisionQueryParams();
	laserParams.AddIgnoredActor(this);
	laserParams.bReturnPhysicalMaterial = false;
	FVector Start = ProjectileSpawnPoint->GetComponentLocation();
	FVector End = Start + ProjectileSpawnPoint->GetForwardVector() * FireRange;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, Start, End, ECollisionChannel::ECC_Visibility, laserParams))
	{
		DrawDebugLine(GetWorld(), Start, hitResult.Location, FColor::Red, false, 1.0f, 0, 50);
		if (hitResult.GetActor())
		{
			AActor* OverlappedActor = hitResult.GetActor();
			UE_LOG(LogTemp, Warning, TEXT("Actor: %s"), *hitResult.GetActor()->GetName());
			OverlappedActor->Destroy();
		}
	}
	else
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Blue, false, 1.0f, 0, 50);
	}
	AmmoSpecial -= 1;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Special Ammo: %d"), AmmoSpecial));
}

void ACannon::BombFire()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, "Fire Bomb");
	AProjectile* Bomb = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
	if (Bomb)
	{
		Bomb->Start();
	}
	AmmoSpecial -= 1;
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, FString::Printf(TEXT("Special Ammo: %d"), AmmoSpecial));
}

void ACannon::BeginPlay()
{
	Super::BeginPlay();
	bReadyToFire = true;
	bReadyToFireSpecial = true;
}
