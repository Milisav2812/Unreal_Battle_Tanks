// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.h" 
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		// TODO Subscribe to the tank's OnDeath Event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
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


void ATankAIController::OnPossessedTankDeath()
{
	if (!ensure(GetPawn())) { return; }

	// Detach from the tank once it has been destroyed
	GetPawn()->DetachFromControllerPendingDestroy();
}
