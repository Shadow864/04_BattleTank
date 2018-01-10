// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"


void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());;
}

ATank* ATankAIController::GetPlayerTank() const
{
   APlayerController* player_controller =  GetWorld()->GetFirstPlayerController();

   if (!player_controller)
   {
       return nullptr;
   }

   return Cast<ATank>(player_controller->GetPawn());
}

