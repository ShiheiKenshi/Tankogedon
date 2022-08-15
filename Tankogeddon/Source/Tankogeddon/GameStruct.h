// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStruct.generated.h"

UENUM(BlueprintType)
enum class ECannonType : uint8
{
	FireTrace = 0 UMETA (DisplayName "Use Trace"),
	FireProjectile = 1 UMETA(DisplayName "Use Projectile"),
	FireRapid = 2 UMETA (DisplayName "Use Rapid shots")
};


UCLASS()
class TANKOGEDDON_API UGameStruct : public UObject
{
	GENERATED_BODY()
	
};
