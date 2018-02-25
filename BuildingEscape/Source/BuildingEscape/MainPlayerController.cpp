// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerController.h"
#include "AimingComponent.h"
#include "BuildingEscape.h"

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMainPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void AMainPlayerController::SetAimingComponent()
{
	AimingComponent = GetPawn()->FindComponentByClass<UAimingComponent>();
	if (!ensure(AimingComponent)) // TODO Solve AimingComponent founding issue
	{
		return;
	}
}

void AMainPlayerController::AimTowardsCrosshair()
{
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // Out parameter
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if (bGotHitLocation) // Has "side-effect", is going to line trace
	{
		AimingComponent->AimAt(HitLocation);
	}

}

// Get world location if linetrace trough crosshair, true if hits landscape
bool AMainPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that look direction and see what we hit (up to max range)
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return false;
}

bool AMainPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (
		GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Camera
		)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; // Line trace did't succeed
}

bool AMainPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}




