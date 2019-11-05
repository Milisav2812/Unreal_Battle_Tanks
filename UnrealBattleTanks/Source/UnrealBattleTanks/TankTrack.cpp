// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

#include "Components/SceneComponent.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float Throttle)
{
	auto CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	// Moving the Wheels - NEW Code
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = ForceApplied / Wheels.Num();

	for (auto Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> Wheels;
	TArray<USceneComponent*> Children;
	GetChildrenComponents(true, Children);

	for (auto Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (SpawnPointChild)
		{
			auto SpawnedChild = SpawnPointChild->GetSpawnedWheel();
			if (SpawnedChild)
			{
				Wheels.Add(SpawnedChild);
			}
		}
	}

	return Wheels;
}