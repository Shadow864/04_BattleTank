// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrackComponent.h"

void UTankMovementComponent::SetTankTracks(UTankTrackComponent* LeftTrack, UTankTrackComponent* RightTrack)
{
    this->LeftTrack = LeftTrack;
    this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForeward(float Throw)
{
    if (!LeftTrack || !RightTrack)
        return;

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
    if (!LeftTrack || !RightTrack)
        return;

    LeftTrack->SetThrottle(Throw);
    RightTrack->SetThrottle(-Throw);
}