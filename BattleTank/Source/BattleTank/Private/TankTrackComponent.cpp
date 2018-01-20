// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"
#include <Components/ActorComponent.h>
#include <Components/PrimitiveComponent.h>


UTankTrackComponent::UTankTrackComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrackComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

    float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetOwner()->GetVelocity());

    FVector CorectionAccelertion = (-SlippageSpeed / DeltaTime) * GetRightVector();

    // F = m * a (but we have two tracks thats why divede by 2)
    FVector CorectionForce = CorectionAccelertion * TankRoot->GetMass() / 2.f;

    TankRoot->AddForce(CorectionForce);
}


void UTankTrackComponent::SetThrottle(float Throttle)
{
    auto ForceLocation = GetComponentLocation();
    auto Force = GetForwardVector() * Throttle * TrackMaxDrivingForce;
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

    TankRoot->AddForceAtLocation(Force, ForceLocation);
}