// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Enum for firing states
UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locket
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS(meta = (BlueprintSpawnableComponent), ClassGroup = (Custom))
class UNREALBATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringStatus FiringStatus = EFiringStatus::Reloading;

	virtual void BeginPlay() override;

private:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveBarrelTowards(FVector AimDirection);
	bool IsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 6000; // 1000 m/s

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint = nullptr;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	double LastFireTime = 0;

	FVector AimDirection;
};
