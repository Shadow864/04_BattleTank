// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include <CollisionQueryParams.h>


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto tank = GetControlledTank();

    if (!tank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Tank not controlled"), *tank->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("%s"), *tank->GetName());
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank())
        return;

    FVector HitResult;
    
    if (GetSightRayHitLocation(HitResult))
    {
        UE_LOG(LogTemp, Warning, TEXT("%s"), *HitResult.ToString());
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto CrosshairScreenPosition = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
    
        FVector LookDirection;

    if (GetLookDirection(CrosshairScreenPosition, LookDirection))
    {
        return GetLookVectorHitLocation(LookDirection, HitLocation);
    }
    
    return false;
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const
{

    FVector TraceStart = PlayerCameraManager->GetCameraLocation();
    FVector TraceEnd = TraceStart + LookDirection * 10000000;

    FHitResult HitResult;

    GetWorld()->LineTraceSingleByChannel(
        HitResult,
        TraceStart, 
        TraceEnd,
        ECC_Visibility);

    if (!HitResult.bBlockingHit)
        return false;

    HitLocation = HitResult.Location;
    return true;
}

bool ATankPlayerController::GetLookDirection(const FVector2D& ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWordLocation;
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWordLocation, LookDirection);
}
