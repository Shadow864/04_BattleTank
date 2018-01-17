// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "TankBarrel.h"
#include "TankTurretComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(const FVector& HitLocation, float LunchSpeed)
{
    if (!TankBarrel) return;

    auto TankName = GetOwner()->GetName();
    auto StartLocation = TankBarrel->GetSocketLocation(FName("Projectille"));
    FVector OutVelocity;

    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
        this,
        OutVelocity,
        StartLocation,
        HitLocation,
        LunchSpeed,
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

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrel(UTankBarrel* TankBarrelToSet)
{
    TankBarrel = TankBarrelToSet;
}

void UTankAimingComponent::SetTurret(UTankTurretComponent* TankTurretToSet)
{
    TankTurret = TankTurretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(const FVector& AimDirection) const
{
    FRotator BarrelRotator = TankBarrel->GetForwardVector().Rotation();
    FRotator AimAsRotatior = AimDirection.Rotation();
    FRotator DeltaRotation = AimAsRotatior - BarrelRotator;
    
    if (TankBarrel)
        TankBarrel->Elevate(DeltaRotation.Pitch);

    if (TankTurret)
        TankTurret->Rotate(DeltaRotation.Yaw);

}
