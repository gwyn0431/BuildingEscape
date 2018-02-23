// Fill out your copyright notice in the Description page of Project Settings.

#include "UnlockDoor.h"
#include "Projectile.h"

#define OUT

UUnlockDoor::UUnlockDoor()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UUnlockDoor::BeginPlay()
{
	Super::BeginPlay();

	auto Owner = GetOwner();
	if (!UnlockingTargetOne || !UnlockingTargetTwo)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing UnlockingTarget to shoot at."), *GetOwner()->GetName())
	}
	
}

void UUnlockDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if (AreTargetsHitted())
	{
		UnlockRequest.Broadcast();
	}
}

bool UUnlockDoor::AreTargetsHitted() {
	// Find all overlapping actors
	TArray<AActor*> TargetOneOverlappingActors;
	TArray<AActor*> TargetTwoOverlappingActors;
	if (!UnlockingTargetOne || !UnlockingTargetTwo) { return false; }

	UnlockingTargetOne->GetOverlappingActors(OUT TargetOneOverlappingActors);
	UnlockingTargetTwo->GetOverlappingActors(OUT TargetTwoOverlappingActors);

	for (const auto* OverlappingActor : TargetOneOverlappingActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *OverlappingActor->GetName())
	}

	if (TargetOneOverlappingActors.Num() > 0 && TargetTwoOverlappingActors.Num() > 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

