#include "TankPlayerController.h"
#include "TankPawn.h"
#include <DrawDebugHelpers.h>

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATankPlayerController::MoveSide);
	InputComponent->BindAxis("RotateRight", this, &ATankPlayerController::RotateRight);
	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ATankPlayerController::Fire);
	InputComponent->BindAction("FireSpecial", EInputEvent::IE_Pressed, this, &ATankPlayerController::FireSpecial);
	InputComponent->BindAction("CannonSwap", EInputEvent::IE_Pressed, this, &ATankPlayerController::ChangeCannonSlots);
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	FVector MouseDirection;
	DeprojectMousePositionToWorld(MousePosition, MouseDirection);
	FVector PawnPosition = TankPawn->GetActorLocation();
	MousePosition.Z = PawnPosition.Z;
	FVector direction = MousePosition - PawnPosition;
	direction.Normalize();
	MousePosition = PawnPosition + direction * 1000;
	//DrawDebugLine(GetWorld(), PawnPosition, MousePosition, FColor::Yellow, false, 0.01f, 0, 5);
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	
	TankPawn = Cast<ATankPawn>(GetPawn());
}

void ATankPlayerController::MoveForward(float Value)
{
	if (TankPawn)
	{
		TankPawn->MoveForward(Value);
	}

}

void ATankPlayerController::MoveSide(float Value)
{
	if (TankPawn)
	{
		TankPawn->MoveSide(Value);
	}
}

void ATankPlayerController::RotateRight(float Value)
{
	if (TankPawn)
	{
		TankPawn->RotateRight(Value);
	}
}

void ATankPlayerController::Fire()
{
	if (TankPawn)
	{
		TankPawn->Fire();
	}
}

void ATankPlayerController::FireSpecial()
{
	if (TankPawn)
	{
		TankPawn->FireSpecial();
	}
}

void ATankPlayerController::ChangeCannonSlots()
{
	if (TankPawn)
	{
		TankPawn->ChangeCannonSlots();
	}
}
