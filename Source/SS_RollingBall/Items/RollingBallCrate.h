// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RollingBallCrate.generated.h"

UCLASS()
class SS_ROLLINGBALL_API ARollingBallCrate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARollingBallCrate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Components")
	UStaticMeshComponent* Crate;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Effects")
	UParticleSystem* CrateBreakableSmoke = nullptr;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Sounds")
	USoundBase* BreakSound;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Spawned Actor")
	TSubclassOf<class AActor> ActorClass;

	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
		const FHitResult& Hit );

};
