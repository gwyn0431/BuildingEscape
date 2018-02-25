// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "Possessor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UPossessor : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UPossessor();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// How far ahead of the player can we reach in cm
	float Reach = 1000.f;

	UInputComponent* InputComponent = nullptr;

	//Setup (assumed) attached input component
	void SetupInputComponent();

	void Possess();

	// Return Hit for first physics body in reach
	const FHitResult GetFirstPawnInReach();

	// Returns current start of reach line
	FVector GetReachLineStart();

	// Returns current end of reach line
	FVector GetReachLineEnd();
		
	
};
