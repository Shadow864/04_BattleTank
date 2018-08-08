// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthComponent.h"
#include <GameFramework/Controller.h>


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

    Health = InitialHealth;
}

float UHealthComponent::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
    int32 PrevHealth = Health;
    int32 DamagePoints = FMath::RoundToInt(DamageAmount);
    Health -= DamagePoints;

    Health = FMath::Clamp(Health, 0, InitialHealth);

    if (PrevHealth != Health)
    {
        HealthPercent = static_cast<float>(Health) / static_cast<float>(InitialHealth);
        OnHealthChanged.Broadcast(PrevHealth, Health);
        if (Health == 0)
            OnDie.Broadcast();
    }

    return DamageAmount;
}
