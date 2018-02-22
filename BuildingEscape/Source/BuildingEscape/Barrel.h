// Copyright © gwyn0431 

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Barrel.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1  is max downward speed, +1 is max up movement
	void Elevate(float RelativeSpeed);

private: 
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxDegreesPerSecond = 10; 
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MaxElevationDegrees = 40;
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float MinElevationDegrees = 0;
};
