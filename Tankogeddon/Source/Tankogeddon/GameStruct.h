#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/ObjectMacros.h"
#include "GameStruct.generated.h"

UENUM(BlueprintType)
enum class ECannonType : uint8
{
	FireTrace = 0 UMETA (DisplayName "Use Trace"),
	FireProjectile = 1 UMETA(DisplayName "Use Projectile"),
	FireRapid = 2 UMETA (DisplayName "Use Rapid shots")
};

USTRUCT()
struct FDamageData
{
	GENERATED_BODY();

	float DamageValue;

	AActor* Instigator;

	AActor* DamageMaker;
};

UCLASS()
class TANKOGEDDON_API UGameStruct : public UObject
{
	GENERATED_BODY()
	
};
