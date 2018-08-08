// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "HealthComponent.h"

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
    
    if (AimComponent->GetFiringStatus() == EFiringStatus::Locked)
        AimComponent->Fire();
    
    MoveToActor(PlayerTank, AcceptanceRadius);
    
}

void ATankAIController::Possess(APawn* InPawn)
{
    Super::Possess(InPawn);

    ATank* Tank = Cast<ATank>(InPawn);

    if (ensure(Tank != nullptr))
        Tank->GetHealthComponent()->OnDie.AddUniqueDynamic(this, &ATankAIController::OnTankDestroyed);

}

void ATankAIController::OnTankDestroyed()
{
    UE_LOG(LogTemp, Warning, TEXT("OnTankDestroyed"))
}


