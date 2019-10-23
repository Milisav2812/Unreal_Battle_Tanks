// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.h" 
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto AITank = GetPawn();
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	// UE_LOG(LogTemp, Warning, TEXT("AI Tank: %s, Player: %s"), *AITank->GetName(), *PlayerTank->GetName())

	if (!ensure(PlayerTank && AITank)) { return; }
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards the player
	TankAimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(TankAimingComponent)) { return; }

	TankAimingComponent->AimAt(PlayerTank->GetTargetLocation());

	if (TankAimingComponent->GetFiringStatus() == EFiringStatus::Locked)
	{
		TankAimingComponent->Fire();
	}
}
