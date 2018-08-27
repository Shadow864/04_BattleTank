// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include <Components/StaticMeshComponent.h>
#include <PhysicsEngine/PhysicsConstraintComponent.h>
#include <Components/SphereComponent.h>


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    SpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Spring Component"));
    SetRootComponent(SpringConstraint);

    Axle = CreateDefaultSubobject<USphereComponent>(TEXT("Axle Sphere Component"));
    Axle->SetupAttachment(SpringConstraint);

    AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Axle Wheel Component"));
    AxleWheelConstraint->SetupAttachment(Axle);

    Wheel2 = CreateDefaultSubobject<USphereComponent>(TEXT("Wheel Sphere Component"));
    Wheel2->SetupAttachment(Axle);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();


    if (!GetAttachParentActor())
    {
        return;
    }
    UE_LOG(LogTemp, Warning, TEXT("%s"), *GetAttachParentActor()->GetName());
    UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());

    if (!BodyRoot)
    {
        return;
    }

    SpringConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
    AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel2, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASprungWheel::AddDriveForce(float Force)
{
    Wheel2->AddForce(Axle->GetForwardVector() * Force);
}