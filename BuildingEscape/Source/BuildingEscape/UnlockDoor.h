// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "UnlockDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnlockRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UUnlockDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUnlockDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable)
	FUnlockRequest UnlockRequest;

private:
	bool AreTargetsHitted();

	UPROPERTY(EditAnywhere)
	ATriggerVolume* UnlockingTargetOne = nullptr;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* UnlockingTargetTwo = nullptr;
	
};
