// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"

#include "DrawDebugHelpers.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;

	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) { return; }

	FoundAimingComponent(TankAimingComponent);
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// TODO Subscribe to the tank's OnDeath Event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	// We might have dispossessed the tank upon death
	TankAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) { return; }

	FVector HitLocation;
	bool bHitLocation = GetSightRayHitLocation(HitLocation);
	if (bHitLocation)
	{
		TankAimingComponent->AimAt(HitLocation);
	}
}


// Get World Location of line trace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that look direction and see what we hit (up to max range)
		return GetLookVectorHitLocation(OutHitLocation, LookDirection);
	}
	return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& OutHitLocation, FVector LookDirection) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation() + 10;
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	/* DrawDebugLine(
		GetWorld(),
		StartLocation,
		EndLocation,
		FColor(255, 0, 0),
		false, -1, 0,
		12.333
	);
	*/

	FCollisionQueryParams LineTraceParams = FCollisionQueryParams(FName(TEXT("")), false, GetPawn());

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility,
		LineTraceParams
		)
	)
	{
		// UE_LOG(LogTemp, Warning, TEXT("LineTraceSingleByChannel HIT SOMETHING"))
		OutHitLocation = HitResult.Location;
		return true;
	}
	// UE_LOG(LogTemp, Error, TEXT("LineTraceSingleByChannel MISSED"))
	OutHitLocation = FVector(0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	// "De-project" the screen position of the crosshair to a world direction
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);
}
