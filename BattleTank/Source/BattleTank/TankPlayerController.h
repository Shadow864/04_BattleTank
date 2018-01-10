// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Public/Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
    GENERATED_BODY()


    UPROPERTY(EditAnywhere)
    float CrossHairXLocation = 0.5f;

    UPROPERTY(EditAnywhere)
    float CrossHairYLocation = 0.33333f;

    ATank* GetControlledTank() const;

    virtual void BeginPlay() override;
    
    virtual void Tick(float DeltaTime) override;

    //Start moving the barrel so that a shoot would hit where
    // the crossharintersects the world
    void AimTowardsCrosshair();

    bool GetSightRayHitLocation(FVector& HitLocation) const;
    bool GetLookDirection(const FVector2D& ScreenLocation, FVector& LookDirection) const;

    bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const;
};
