// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurretComponent.h"

void UTankTurretComponent::Rotate(float RelativeSpeed)
{
    RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.f, 1.0f);
    float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    float Rotation = RelativeRotation.Yaw + RotationChange;

    SetRelativeRotation(FRotator(0, Rotation, 0));
}