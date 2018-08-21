// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include <Components/StaticMeshComponent.h>
#include <PhysicsEngine/PhysicsConstraintComponent.h>


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Spring Component"));
    SetRootComponent(Spring);

    Wheel = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Wheel Component"));
    Wheel->AttachToComponent(Spring, FAttachmentTransformRules::KeepRelativeTransform);

    
    //Spring->AttachToComponent(Mass, FAttachmentTransformRules::KeepRelativeTransform);
    //Spring->

   

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

    Spring->SetConstrainedComponents(BodyRoot, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

