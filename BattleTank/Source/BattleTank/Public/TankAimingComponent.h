// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurretComponent;
class AProjectile;

UENUM(BlueprintType)
enum class EFiringStatus : uint8
{
    Locked,
    Aiming,
    Reloading
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

    void AimAt(const FVector& HitLocation);

protected:

private:
    void MoveBarrelTowards(const FVector& AimDirection) const;

public:	
    UFUNCTION(BlueprintCallable)
    void Initialize(UTankBarrel* TankBarrel, UTankTurretComponent* TankTurret);

    UFUNCTION(BlueprintCallable)
    void Fire();

private:
    UTankBarrel* TankBarrel = nullptr;
    UTankTurretComponent* TankTurret = nullptr;

public:
    UPROPERTY(BlueprintReadOnly)
    EFiringStatus FiringStatus = EFiringStatus::Reloading;

    UPROPERTY(EditDefaultsOnly)
    float BulletLunchSpeed = 4000;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<AProjectile> ProjectileBlueprint;

    UPROPERTY(EditDefaultsOnly)
    float ReloadTimeInSeconds = 3.f;

    double LastFireTime = 0;

};
