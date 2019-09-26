// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALBATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATank* GetAIControlledTank() const;
	ATank* GetPlayerTank() const;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
};
