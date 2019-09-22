// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALBATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;

	// Rotate the turret and elevate the barrel so they point to the crosshair
	// so a shot could be fired at that location
	void AimTowardsCrosshair();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
