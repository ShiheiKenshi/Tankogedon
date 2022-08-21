#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankPlayerController.h"
#include <Kismet/KismetMathLibrary.h>
#include <Math/UnrealMathUtility.h>
#include "Components/ArrowComponent.h"
#include "Cannon.h"

ATankPawn::ATankPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	RootComponent = BoxCollision;
	
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(BoxCollision);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(BoxCollision);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bInheritYaw = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("CannonSetupPoint"));
	CannonSetupPoint->SetupAttachment(TurretMesh);
}



void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Movement
	MoveTank(DeltaTime);

	//Tank Rotation
	float yawRotation = RotationSpeed * targetRotateRightAxisValue * DeltaTime;
	FRotator currentRotation = GetActorRotation();
	yawRotation += currentRotation.Yaw;
	FRotator newRotation = FRotator(0.0f, yawRotation, 0.0f);
	SetActorRotation(newRotation);

	//Turret Rotation
	if (TankController)
	{
		FVector mousePosition = TankController->GetMousePosition();
		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mousePosition);
		FRotator TurretRotation = TurretMesh->GetComponentRotation();
		targetRotation.Pitch = TurretRotation.Pitch;
		targetRotation.Roll = TurretRotation.Roll;

		FRotator newTurretRotation = FMath::Lerp(TurretRotation, targetRotation, TurretRotationInterpolationKey);
		//UE_LOG(LogTemp, Warning, TEXT("targetRotation: %s, LerpRotation: %s"), *targetRotation.ToString(), *newTurretRotation.ToString());

		TurretMesh->SetWorldRotation(newTurretRotation);
	}
}

void ATankPawn::MoveTank(float DTime)
{
	FVector CurrentLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector RightVector = GetActorRightVector();
	FVector ForwardPosition = ForwardVector * MoveSpeed * targetForwardAxisValue * DTime;
	FVector SidePosition = RightVector * MoveSpeed * targetRightAxisValue * DTime;
	FVector movePosition = CurrentLocation + ForwardPosition + SidePosition;
	SetActorLocation(movePosition, true);
}

void ATankPawn::MoveForward(float Value)
{
	targetForwardAxisValue = Value;
}

void ATankPawn::MoveSide(float Value)
{
	targetRightAxisValue = Value;
}

void ATankPawn::RotateRight(float Value)
{
	targetRotateRightAxisValue = Value;
}

void ATankPawn::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}

void ATankPawn::FireSpecial()
{
	if (Cannon)
	{
		Cannon->FireSpecial();
	}
}

void ATankPawn::SetupCannon(TSubclassOf<ACannon> newCannonClass)
{
	if (!newCannonClass)
	{
		return;
	}
	if (Cannon)
	{
		Cannon->Destroy();
	}

	FirstSlotCannonClass = newCannonClass;

	FActorSpawnParameters spawnParams;
	spawnParams.Instigator = this;
	spawnParams.Owner = this;

	Cannon = GetWorld()->SpawnActor<ACannon>(newCannonClass,spawnParams);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void ATankPawn::ChangeFirstSlotCannon()
{
	SetupCannon(FirstSlotCannonClass);
}

void ATankPawn::ChangeCannonSlots()
{
	ChangeSlotCannonClass = FirstSlotCannonClass;
	FirstSlotCannonClass = SecondSlotCannonClass;
	SecondSlotCannonClass = ChangeSlotCannonClass;

	SetupCannon(FirstSlotCannonClass);
}

ACannon* ATankPawn::GetCannon() const
{
	return Cannon;
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	TankController = Cast<ATankPlayerController>( GetController());
	SetupCannon(FirstSlotCannonClass);
}
