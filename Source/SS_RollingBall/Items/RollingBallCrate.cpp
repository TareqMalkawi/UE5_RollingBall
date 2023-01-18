// Fill out your copyright notice in the Description page of Project Settings.


#include "RollingBallCrate.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ARollingBallCrate::ARollingBallCrate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Crate = CreateDefaultSubobject<UStaticMeshComponent>("Crate");

	Crate->OnComponentHit.AddDynamic(this,&ARollingBallCrate::OnHit);
}

// Called when the game starts or when spawned
void ARollingBallCrate::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARollingBallCrate::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(Hit.Normal.Z > 0.0f)
	{
		// spawn emitter
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),BreakSound,GetActorLocation());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),CrateBreakableSmoke,GetActorLocation(),GetActorRotation());
		
		GetWorld()->SpawnActor<AActor>(ActorClass,GetActorLocation() + FVector(0.0f,0.0f,50.0f),GetActorRotation());
		Destroy();
	}
}


