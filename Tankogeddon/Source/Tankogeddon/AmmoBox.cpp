#include "AmmoBox.h"
#include "Components/StaticMeshComponent.h"
#include "Cannon.h"
#include "TankPawn.h"
#include "GameFramework/Pawn.h"

AAmmoBox::AAmmoBox()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComponent;

	AmmoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
	AmmoMesh->SetupAttachment(SceneComponent);
	AmmoMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AmmoMesh->SetCollisionProfileName("OverlapAll");
	AmmoMesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnMeshOverlapBegin);

}

void AAmmoBox::OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATankPawn* TankPawn = Cast<ATankPawn>(OtherActor);
	if (TankPawn)
	{
		TankPawn->SetupCannon(FirstCannonClass);
		//Destroy();
		ACannon* Cannon = TankPawn->GetCannon();
		if (Cannon)
		{
			Cannon->ReloadAmmunition(Cartridge);
		}
	}
}

