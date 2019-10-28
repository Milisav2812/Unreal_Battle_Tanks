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
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 10000; // When the AI tank gets this close to our tank, it stops

	UTankAimingComponent* TankAimingComponent = nullptr;
};
