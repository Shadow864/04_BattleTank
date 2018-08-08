// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

class AController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, int32, PrevValue, int32, CurrentValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDie);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
    virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health")
    int32 InitialHealth = 100;

    UPROPERTY(BlueprintReadOnly, Category = "Health")
    int32 Health = InitialHealth;

    UPROPERTY(BlueprintReadOnly, Category = "Health")
    float HealthPercent = 1.f;

public:
    UPROPERTY(VisibleAnywhere)
    FOnHealthChanged OnHealthChanged;

    UPROPERTY(VisibleAnywhere)
    FOnDie OnDie;


};
