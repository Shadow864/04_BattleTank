// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
    GENERATED_BODY()

public:
    void Elevate(float RelativeSpeed);
	

    UPROPERTY(EditAnywhere)
    float MaxDegreesPerSecond = 10.f;
    
    UPROPERTY(EditAnywhere)
    float MaxElevationDegree = 40.f;

    UPROPERTY(EditAnywhere)
    float MinElevationDegree = 0;

};
