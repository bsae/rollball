// Fill out your copyright notice in the Description page of Project Settings.


#include "SpikeTrap.h"

// *beto* additional header files for shapes and meshes needed
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"


// Sets default values
ASpikeTrap::ASpikeTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// *beto* the constructor (how to initialize itself)
	// create the mesh object which is the root of the class
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//VisualMesh->SetupAttachment(RootComponent);
	RootComponent = VisualMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if(CubeVisualAsset.Succeeded()){
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	// *beto* create the collision box
	CollisionMesh = CreateDefaultSubobject<UBoxComponent>(FName("Collision Mesh"));
	// CollisionMesh->BoxExtent(FVector(1.0f, 1.0f, 1.0f)); // caused an error : boxextent takes more than 1 argument?
	
	CollisionMesh->OnComponentBeginOverlap.AddDynamic(this, &ASpikeTrap::OnOverlapBegin);
	CollisionMesh->OnComponentEndOverlap.AddDynamic(this, &ASpikeTrap::OnOverlapEnd);
	CollisionMesh->SetupAttachment(RootComponent); // connects the collision mesh to the visual mesh

	MaterialColor1 = CreateDefaultSubobject<UMaterial>(TEXT("Material 1"));
	MaterialColor2 = CreateDefaultSubobject<UMaterial>(TEXT("Material 2"));
}

// Called when the game starts or when spawned
void ASpikeTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpikeTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));
	NewLocation.Z += DeltaHeight * 20.0f; //scales the height by a factor of 20.0
	float DeltaRotation = DeltaTime * 20.f; //rotate by 20 degrees per second
	NewRotation.Yaw += DeltaRotation;

	SetActorLocationAndRotation(NewLocation, NewRotation);

}

