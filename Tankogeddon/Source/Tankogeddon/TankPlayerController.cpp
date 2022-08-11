#include "TankPlayerController.h"
#include "TankPawn.h"

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::MoveForward);

	InputComponent->BindAxis("MoveRight", this, &ATankPlayerController::MoveSide);
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
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
