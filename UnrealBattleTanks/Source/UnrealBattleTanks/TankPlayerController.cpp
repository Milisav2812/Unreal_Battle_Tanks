// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;

	ATank* ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Possessed tank: %s"), *ControlledTank->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("NO POSSESSED TANK"), *ControlledTank->GetName())
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}
