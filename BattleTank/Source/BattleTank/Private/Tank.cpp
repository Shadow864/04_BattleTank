// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "TankTurretComponent.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::AimAt(const FVector& HitLocation)
{
    TankAimingComponent->AimAt(HitLocation, BulletLunchSpeed);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::SetBarrel(UTankBarrel* BarrelToSet)
{
    if (!TankAimingComponent)
        return;

    TankAimingComponent->SetBarrel(BarrelToSet);
    TankBarrel = BarrelToSet;
}

void ATank::SetTurret(UTankTurretComponent* TurretToSet) const
{
    if (!TankAimingComponent)
        return;

    TankAimingComponent->SetTurret(TurretToSet);
}

void ATank::Fire()
{
    if (!TankBarrel)
        return;

    FVector ProjectileLocation = TankBarrel->GetSocketLocation(FName("Projectile"));
    FRotator ProjectileRotation = TankBarrel->GetSocketRotation(FName("Projectile"));
    
    GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, ProjectileLocation, ProjectileRotation);
}