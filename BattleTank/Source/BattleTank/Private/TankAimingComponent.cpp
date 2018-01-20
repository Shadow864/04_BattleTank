// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TankBarrel.h"
#include "TankTurretComponent.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UTankAimingComponent::AimAt(const FVector& HitLocation)
{
    if (!ensure(TankBarrel)) 
        return;

    auto TankName = GetOwner()->GetName();
    auto StartLocation = TankBarrel->GetSocketLocation(FName("Projectile"));
    FVector OutVelocity;

    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
        this,
        OutVelocity,
        StartLocation,
        HitLocation,
        BulletLunchSpeed,
        false,
        0,
        0,
        ESuggestProjVelocityTraceOption::DoNotTrace
    );

    if (bHaveAimSolution)
    {
        FVector AimDirection = OutVelocity.GetSafeNormal();

        MoveBarrelTowards(AimDirection);

        DrawDebugLine(
            this->GetWorld(),
            StartLocation,
            HitLocation,
            FColor::Red);
    }
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection) const
{
    if (!ensure(TankBarrel && TankTurret))
        return;

    FRotator BarrelRotator = TankBarrel->GetForwardVector().Rotation();
    FRotator AimAsRotatior = AimDirection.Rotation();
    FRotator DeltaRotation = AimAsRotatior - BarrelRotator;
    
    TankBarrel->Elevate(DeltaRotation.Pitch);
    TankTurret->Rotate(DeltaRotation.Yaw);
}

void UTankAimingComponent::Initialize(UTankBarrel* TankBarrel, UTankTurretComponent* TankTurret)
{
   this->TankBarrel = TankBarrel;
   this->TankTurret = TankTurret;
}

void UTankAimingComponent::Fire()
{
    if (!ensure(TankBarrel && ProjectileBlueprint))
        return;

    bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

    if (!isReloaded)
        return;

    FVector ProjectileLocation = TankBarrel->GetSocketLocation(FName("Projectile"));
    FRotator ProjectileRotation = TankBarrel->GetSocketRotation(FName("Projectile"));

    AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileLocation, ProjectileRotation);

    Projectile->Lunch(BulletLunchSpeed);

    LastFireTime = FPlatformTime::Seconds();
}