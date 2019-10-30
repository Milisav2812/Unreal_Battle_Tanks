// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

UCLASS()
class UNREALBATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* TankAimingComponent);

private:
	// This method gets called when the AI Tank gets possessed
	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossessedTankDeath();

	// Rotate the turret and elevate the barrel so they point to the crosshair
	// so a shot could be fired at that location
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	bool GetLookVectorHitLocation(FVector& OutHitLocation, FVector LookDirection) const;
	// De-project screen location to world
	// Returns a vector that points to where the crosshair is
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	UPROPERTY(EditAnywhere)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000; // cm

	UTankAimingComponent* TankAimingComponent = nullptr;
};