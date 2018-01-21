// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrackComponent.h"
#include <Components/ActorComponent.h>
#include <Components/PrimitiveComponent.h>
#include <DrawDebugHelpers.h>


UTankTrackComponent::UTankTrackComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    OnComponentHit.AddDynamic(this, &UTankTrackComponent::OnHit);
}

void UTankTrackComponent::ApplySidewayForce()
{
    float DeltaTime = GetWorld()->GetDeltaSeconds();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

    float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

    FVector CorectionAccelertion = (-SlippageSpeed / DeltaTime) * GetRightVector();

    // F = m * a (but we have two tracks thats why divede by 2)
    FVector CorectionForce = CorectionAccelertion * TankRoot->GetMass() * 0.5f;
}

void UTankTrackComponent::SetThrottle(float Throttle)
{
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -2.f, 2.f);
}

void UTankTrackComponent::DriveTrack()
{
    UE_LOG(LogTemp, Warning, TEXT("[%s] Throttle %f"), *GetName(), CurrentThrottle);

    auto ForceLocation = GetComponentLocation();
    auto Force = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

    TankRoot->AddForceAtLocation(Force, ForceLocation);
}

void UTankTrackComponent::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    DriveTrack();
    ApplySidewayForce();
    CurrentThrottle = 0.f;

}