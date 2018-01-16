// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

    void AimAt(const FVector& HitLocation, float LunchSpeed);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
    void MoveBarrelTowards(const FVector& AimDirection) const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
    UFUNCTION(BlueprintCallable)
    void SetBarrel(UTankBarrel* TankBarrelToSet);

private:
    UTankBarrel* TankBarrel = nullptr;

};
