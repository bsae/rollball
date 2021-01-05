// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Misc/DateTime.h"
#include "Materials/Material.h"
#include "Misc/Timespan.h"

#include "SpecialPickUp.generated.h"

UCLASS()
class ROLLBALL_API ASpecialPickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpecialPickUp();
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* CollisionMesh;
	UPROPERTY(VisibleAnywhere)
	UMaterial* SpecialPickUpColor;
	UPROPERTY(VisibleAnywhere)
	bool wasPickedUp = false; // to check if the coin has been picked up
	UPROPERTY(VisibleAnywhere)
	FDateTime pickedUpTime;
	UPROPERTY(VisibleAnywhere)
	FDateTime currentTime;
	UPROPERTY(VisibleAnywhere)
	FTimespan fiveSecondSpan = FTimespan(0,0,5);

	// want to 
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult){
		if (OtherActor && (OtherActor != this) && OtherComp) {
			//OtherActor->Keys+=2; // this pickup is worth 2 points
			this->wasPickedUp=true;
			this->SetActorHiddenInGame(true);
			this->pickedUpTime=FDateTime::UtcNow();
		}
	};

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){
		if (OtherActor && (OtherActor != this) && OtherComp) {
			// this->isOverlapped=false;
		}
	};


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
