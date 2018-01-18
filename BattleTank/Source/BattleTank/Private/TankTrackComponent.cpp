// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"
#include <Components/ActorComponent.h>
#include <Components/PrimitiveComponent.h>




void UTankTrackComponent::SetThrottle(float Throttle)
{
    auto Name = GetName();
    UE_LOG(LogTemp, Warning, TEXT("%s Throttle %f"), *Name, Throttle);

    auto ForceLocation = GetComponentLocation();
    auto Force = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

    TankRoot->AddForceAtLocation(Force, ForceLocation);
}