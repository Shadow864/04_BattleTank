// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AActor* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    AActor* ControlledTank = GetPawn();

    if (!ensure(PlayerTank && ControlledTank))
        return;

    UTankAimingComponent* AimComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    
    if (!ensure(AimComponent))
        return;

    AimComponent->AimAt(PlayerTank->GetActorLocation());
    
    AimComponent->Fire();
    
    MoveToActor(PlayerTank, AcceptanceRadius);
    
}

