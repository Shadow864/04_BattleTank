// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"
#include <Components/ActorComponent.h>
#include <Components/PrimitiveComponent.h>
#include <DrawDebugHelpers.h>
#include "SprungWheel.h"
#include "SpawnActorComponent.h"


UTankTrackComponent::UTankTrackComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrackComponent::SetThrottle(float Throttle)
{
    DriveTrack(Throttle);
}

void UTankTrackComponent::DriveTrack(float CurrentThrottle)
{
    TArray<ASprungWheel*> Wheels = GetWheels();


    float Force = TrackMaxDrivingForce * CurrentThrottle / Wheels.Num();
  
    for (ASprungWheel* Wheel : GetWheels())
    {
        Wheel->AddDriveForce(Force);
    }
}


TArray<class ASprungWheel*> UTankTrackComponent::GetWheels() const
{
    TArray<ASprungWheel*> Wheels;
    TArray<USceneComponent*> Childrens;
    GetChildrenComponents(true, Childrens);

    for (USceneComponent* Child : Childrens)
    {
        USpawnActorComponent* Spawner = Cast<USpawnActorComponent>(Child);
        if (!Spawner)
            continue;

        AActor* SpawnedActor = Spawner->GetSpawnedActor();
       
        ASprungWheel* Wheel = Cast<ASprungWheel>(SpawnedActor);
        if (!Wheel)
            continue;

        Wheels.Add(Wheel);
    }

    return Wheels;

}