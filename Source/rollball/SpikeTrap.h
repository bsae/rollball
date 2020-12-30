// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"

#include "SpikeTrap.generated.h"

UCLASS()
class ROLLBALL_API ASpikeTrap : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ASpikeTrap();
	//*beto*
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionMesh = nullptr;

	//*beto* overlap between collision boxes functions (begin and end)
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
		if (OtherActor && (OtherActor != this) && OtherComp) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
		}
	};

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){
		if (OtherActor && (OtherActor != this) && OtherComp) {
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));
		}
	};

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//*beto*
	class UParticleSystemComponent* OurParticleSystem;
};

