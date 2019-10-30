// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class UNREALBATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnPossessedTankDeath();

	// This method gets called when the AI Tank gets possessed
	virtual void SetPawn(APawn* InPawn) override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 7000; // When the AI tank gets this close to our tank, it stops

	UTankAimingComponent* TankAimingComponent = nullptr;
};
