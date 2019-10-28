// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// No need to protect pointer in constructor
	// Likely to be a success binding
	// TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	// TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	UE_LOG(LogTemp, Warning, TEXT("Actual Damage: %f"), ActualDamage)
	ActualDamage = FMath::Clamp<float>(ActualDamage, 0, Health);
	UE_LOG(LogTemp, Warning, TEXT("Clamped Damage: %f"), ActualDamage)

	Health -= ActualDamage;
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health)
	if (Health <= 0)
	{
		SetLifeSpan(0.001f);
	}
	return ActualDamage;
}
