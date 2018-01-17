// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "UnrealMathUtility.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.0f);
    float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    float NewElevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegree, MaxElevationDegree);
    FRotator NewRelativeRotation = FRotator(NewElevation, 0, 0);
   
    UE_LOG(LogTemp, Warning, TEXT("%s Elevation"), *NewRelativeRotation.ToString());
    //GetOwner()->SetActorRelativeRotation(FRotator(NewElevation, 0, 0));
    SetRelativeRotation(NewRelativeRotation);
}