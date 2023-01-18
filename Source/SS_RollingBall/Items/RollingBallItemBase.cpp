// Fill out your copyright notice in the Description page of Project Settings.


#include "RollingBallItemBase.h"

#include "SS_RollingBall/Gameplay/RollingBallGameModeBase.h"
#include "SS_RollingBall/Gameplay/RollingBallPlayer.h"

// Sets default values
ARollingBallItemBase::ARollingBallItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;
	
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this,&ARollingBallItemBase::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ARollingBallItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARollingBallItemBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<ARollingBallPlayer>(OtherActor))
	{
		Collected();
	}
}

void ARollingBallItemBase::Collected_Implementation()
{
	// inform game mode.
	ARollingBallGameModeBase* GameMode = Cast<ARollingBallGameModeBase>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		GameMode->ItemCollected();
	}
}


