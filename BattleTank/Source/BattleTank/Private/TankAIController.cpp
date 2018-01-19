// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"


void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    ATank* ControlledTank = Cast<ATank>(GetPawn());

    if (PlayerTank)
    {
        ControlledTank->AimAt(PlayerTank->GetActorLocation());
        //ControlledTank->Fire();
    
        MoveToActor(PlayerTank, AcceptanceRadius);
    }
}

