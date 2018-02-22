// Copyright © gwyn0431 

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1  is max left-hand speed, +1 is max righ-hand movement
	void Rotate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 25;

};
