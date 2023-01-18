// Fill out your copyright notice in the Description page of Project Settings.


#include "RollingBallObstacle.h"

#include "SS_RollingBall/Gameplay/RollingBallGameModeBase.h"
#include "SS_RollingBall/Gameplay/RollingBallPlayer.h"

// Sets default values
ARollingBallObstacle::ARollingBallObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Base = CreateDefaultSubobject<UStaticMeshComponent>("Base");
	RootComponent = Base;

	Obstacle = CreateDefaultSubobject<UStaticMeshComponent>("Obstacle");
	Obstacle->SetupAttachment(Base);
	
	Base->OnComponentBeginOverlap.AddDynamic(this,&ARollingBallObstacle::OnOverlapBegin);
	Base->OnComponentEndOverlap.AddDynamic(this,&ARollingBallObstacle::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ARollingBallObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARollingBallObstacle::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(Cast<ARollingBallPlayer>(OtherActor))
	{
		Entered();
	}
}

void ARollingBallObstacle::Entered_Implementation()
{
	ARollingBallGameModeBase* GameMode = Cast<ARollingBallGameModeBase>(GetWorld()->GetAuthGameMode());
	if(GameMode && DecreaseHealth)
	{
		GameMode->UpdateHealth();
	}
}

void ARollingBallObstacle::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(Cast<ARollingBallPlayer>(OtherActor))
	{
		Exit();
	}
}

void ARollingBallObstacle::Exit_Implementation()
{
	// GEngine->AddOnScreenDebugMessage(-1,15,FColor::Red,FString::Printf(TEXT("HHHHHHHHHHHHHH")));
}



