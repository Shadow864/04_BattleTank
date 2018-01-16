// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


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
    if (!Barrel) return;

    auto TankName = GetOwner()->GetName();
    auto StartLocation = Barrel->GetSocketLocation(FName("Projectille"));
    FVector OutVelocity;

    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
        this,
        OutVelocity,
        StartLocation,
        HitLocation,
        LunchSpeed,
        ESuggestProjVelocityTraceOption::DoNotTrace
    );

    if (bHaveAimSolution)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"), *TankName, *OutVelocity.GetSafeNormal().ToString());

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

void UTankAimingComponent::SetBarrel(UStaticMeshComponent* BarrelToSet)
{
    Barrel = BarrelToSet;
}

