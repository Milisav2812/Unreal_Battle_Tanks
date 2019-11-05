// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// We're making the physics constraint the root component because it does not simulate physics
	PhysicsConstraintComponent = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physics Constraint Component"));
	SetRootComponent(PhysicsConstraintComponent);
	
	Axle = CreateDefaultSubobject<UStaticMeshComponent>(FName("Axle"));
	Axle->SetupAttachment(PhysicsConstraintComponent);
	
	Wheel = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);
	
	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Axle Wheel Constraint"));
	AxleWheelConstraint->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetAttachParentActor())
	{
		PhysicsConstraintComponent->SetConstrainedComponents(
			Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent()),
			NAME_None,
			Cast<UPrimitiveComponent>(Axle),
			NAME_None
		);

		AxleWheelConstraint->SetConstrainedComponents(
			Cast<UPrimitiveComponent>(Axle),
			NAME_None,
			Cast<UPrimitiveComponent>(Wheel),
			NAME_None
		);
	}
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	// We want to apply the force in the direction of the Axle's forward vector
	Wheel->AddForce(Axle->GetForwardVector() * ForceMagnitude);
}

