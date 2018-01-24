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
    Reloading,
    OutOfAmmo
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
    void BeginPlay() override;

    void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
    void MoveBarrelTowards(const FVector& AimDirection);
  
    bool IsReloading() const;
  
    bool IsBarrelMoving() const;

    bool IsOutOfAmmo() const;

public:	
    UFUNCTION(BlueprintCallable)
    void Initialize(UTankBarrel* TankBarrel, UTankTurretComponent* TankTurret);

    UFUNCTION(BlueprintCallable)
    void Fire();

    EFiringStatus GetFiringStatus() const;

private:
    UTankBarrel* TankBarrel = nullptr;
    UTankTurretComponent* TankTurret = nullptr;

    FVector AimDirection;
public:
    UPROPERTY(BlueprintReadOnly)
    EFiringStatus FiringStatus = EFiringStatus::Reloading;

    UPROPERTY(EditDefaultsOnly)
    float BulletLunchSpeed = 4000;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<AProjectile> ProjectileBlueprint;

    UPROPERTY(EditDefaultsOnly)
    float ReloadTimeInSeconds = 3.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float NumberOfRockets= 3;
    
    double LastFireTime = 0;

};
