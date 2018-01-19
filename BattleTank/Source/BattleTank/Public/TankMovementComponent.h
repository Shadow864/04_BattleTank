// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrackComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
    GENERATED_BODY()

   UFUNCTION(BlueprintCallable)
   void SetTankTracks(UTankTrackComponent* LeftTrack, UTankTrackComponent* RightTrack);

    UFUNCTION(BlueprintCallable)
    void IntendMoveForeward(float Throw);

    UFUNCTION(BlueprintCallable)
    void IntendMoveRight(float Throw);

public:
    void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;


private:
    UTankTrackComponent* LeftTrack = nullptr;
    UTankTrackComponent* RightTrack = nullptr;
};
