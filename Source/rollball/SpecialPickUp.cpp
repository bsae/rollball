// Fill out your copyright notice in the Description page of Project Settings.


#include "SpecialPickUp.h"

// Sets default values
ASpecialPickUp::ASpecialPickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create the physical mesh that will be seen
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = VisualMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));
	if(CylinderVisualAsset.Succeeded()){
		VisualMesh->SetStaticMesh(CylinderVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	// create the collision mesh that the player will interact with
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ASpecialPickUp::OnOverlapBegin);
	CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &ASpecialPickUp::OnOverlapEnd);
	CollisionMesh->SetupAttachment(RootComponent);

	// create the color for the actor
	SpecialPickUpColor = CreateDefaultSubobject<UMaterial>(TEXT("Special Pick Up Color"));

}

// Called when the game starts or when spawned
void ASpecialPickUp::BeginPlay()
{
	Super::BeginPlay();
	VisualMesh->SetMaterial(0, SpecialPickUpColor); // set the color at the start of play
	
}

// Called every frame
void ASpecialPickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// if the coin has been picked up, respawn it after 5 seconds
	// time check accounts for if the times are on edge cases where the times will reset to 0 from 59
	if(this->wasPickedUp == true){
		currentTime = FDateTime::UtcNow();
		if((currentTime - pickedUpTime) >= fiveSecondSpan){
			this->SetActorHiddenInGame(false);
			this->wasPickedUp=false;
		}
	}


	FRotator NewRotation = GetActorRotation();
	float DeltaRotation = DeltaTime;
	NewRotation.Yaw += DeltaRotation * 30.0f; //rotate by 30 degrees
	SetActorRotation(NewRotation);
}

