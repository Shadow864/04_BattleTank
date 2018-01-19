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

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
    auto AIForwardIntetion = MoveVelocity.GetSafeNormal();

    auto ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntetion);
    IntendMoveForeward(ForwardThrow);

    auto CrossProduct = FVector::CrossProduct(TankForward, AIForwardIntetion);
    auto SteeringMagnitude = CrossProduct.Size();
    auto ZSign = FMath::Abs(CrossProduct.Z) / CrossProduct.Z;
    auto RightThrow = SteeringMagnitude * ZSign;
    UE_LOG(LogTemp, Warning, TEXT("RighThrow %f"), RightThrow);

    IntendMoveRight(RightThrow);
}
