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
    PrimaryActorTick.TickGroup = TG_PostPhysics;

//    this->

    SpringConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Spring Component"));
    SetRootComponent(SpringConstraint);

    Axle = CreateDefaultSubobject<USphereComponent>(TEXT("Axle Sphere Component"));
    Axle->SetupAttachment(SpringConstraint);

    AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("Axle Wheel Component"));
    AxleWheelConstraint->SetupAttachment(Axle);

    Wheel2 = CreateDefaultSubobject<USphereComponent>(TEXT("Wheel Sphere Component"));
    //Wheel2->bGenerateOverlapEvents = true;
    Wheel2->SetNotifyRigidBodyCollision(true);
    Wheel2->SetupAttachment(Axle);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
    
    Wheel2->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

    SetupConstraint();
}

void ASprungWheel::SetupConstraint()
{
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

    TotalForce = 0;
}

void ASprungWheel::AddDriveForce(float Force)
{
    TotalForce += Force;
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    Wheel2->AddForce(Axle->GetForwardVector() * TotalForce);
}
