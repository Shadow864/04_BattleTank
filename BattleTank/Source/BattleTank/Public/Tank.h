// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UHealthComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
	

    virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) override;
    
    UHealthComponent* GetHealthComponent() const { return HealthComponent; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UHealthComponent* HealthComponent = nullptr;

private:

   
};
