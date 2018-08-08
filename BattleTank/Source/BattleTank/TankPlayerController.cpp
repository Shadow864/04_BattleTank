// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include <CollisionQueryParams.h>
#include "TankAimingComponent.h"
#include "Tank.h"
#include "HealthComponent.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    ensure(AimingComponent);
    OnAimingComponentAdded(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetPawn())
        return;

    UTankAimingComponent* AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

    if (!ensure(AimingComponent))
        return;

    FVector HitResult;
    
    if (GetSightRayHitLocation(HitResult))
    {
        AimingComponent->AimAt(HitResult);
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


void ATankPlayerController::Possess(APawn* InPawn)
{
    Super::Possess(InPawn);
    
    ATank* Tank = Cast<ATank>(InPawn);

    if (ensure(Tank != nullptr))
        Tank->GetHealthComponent()->OnDie.AddUniqueDynamic(this, &ATankPlayerController::OnTankDestroyed);

}

void ATankPlayerController::OnTankDestroyed()
{
    UE_LOG(LogTemp, Warning, TEXT("OnTankDestroyed"))
}
