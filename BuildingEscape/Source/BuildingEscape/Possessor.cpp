// Fill out your copyright notice in the Description page of Project Settings.

#include "Possessor.h"
#include "CollisionQueryParams.h"
#include "GameFramework/DefaultPawn.h"
#include "ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "MainPlayerController.h"

// Sets default values for this component's properties
UPossessor::UPossessor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPossessor::BeginPlay()
{
	Super::BeginPlay();
	SetupInputComponent();
	// ...
	
}


// Called every frame
void UPossessor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/// Look for attached Input Component (only appears at runtime)
void UPossessor::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Possess", IE_Pressed, this, &UPossessor::Possess);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	}
}

void UPossessor::Possess()
{
	auto HitResult = GetFirstPawnInReach();

	if (HitResult.GetActor())
	{
		auto MyController = Cast<AMainPlayerController>(GetOwner()->GetInstigatorController());
		MyController->Possess(HitResult.GetActor()->GetInstigator());
		MyController->SetAimingComponent();
		UE_LOG(LogTemp, Error, TEXT("hitted something missing input component"))
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" hitted nothing"), *GetOwner()->GetName())
	}
}

const FHitResult UPossessor::GetFirstPawnInReach()
{
	/// Line-trace (AKA ray-cast) out to reach distance
	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
		TraceParameters
	);

	return HitResult;
}

FVector UPossessor::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation;
}

FVector UPossessor::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}
