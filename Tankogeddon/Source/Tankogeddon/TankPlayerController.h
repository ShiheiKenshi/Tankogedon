#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

UCLASS()
class TANKOGEDDON_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY()
	class ATankPawn* TankPawn;

	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	FVector GetMousePosition() { return MousePosition; };

protected:
	virtual void BeginPlay() override;

	void MoveForward(float Value);
	void MoveSide(float Value);
	void RotateRight(float Value);

	void Fire();
	void FireSpecial();

	FVector MousePosition;
};
