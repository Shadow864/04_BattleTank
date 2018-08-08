// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "HealthComponent.h"

// Sets default values
ATank::ATank()
{
 
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName(TEXT("HealthComponent")));
}  


float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
    return  HealthComponent->TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}