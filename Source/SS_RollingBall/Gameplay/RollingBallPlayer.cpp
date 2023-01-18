// Fill out your copyright notice in the Description page of Project Settings.


#include "RollingBallPlayer.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARollingBallPlayer::ARollingBallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	RootComponent = MeshComponent;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(MeshComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	MeshComponent->OnComponentHit.AddDynamic(this,&ARollingBallPlayer::OnHit);
}

// Called when the game starts or when spawned
void ARollingBallPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	JumpImpulse = MaxJumpImpulse;
	
	MeshComponent->SetSimulatePhysics(true);
	if(MeshComponent->IsSimulatingPhysics())
	{
		HorizontalForce *= MeshComponent->GetMass(); 
		JumpImpulse *= MeshComponent->GetMass(); 	
	}
}


// Called to bind functionality to input
void ARollingBallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ARollingBallPlayer::Jump);
	PlayerInputComponent->BindAxis("MoveRight",this,&ARollingBallPlayer::MoveRight);
}

void ARollingBallPlayer::MoveRight(float value)
{
	const FVector Right = CameraComponent->GetRightVector() * HorizontalForce * value;
	MeshComponent->AddForce(Right);
}

void ARollingBallPlayer::Jump()
{
	if(JumpCounter >= MaxJumpCounter) return;
	
	MeshComponent->AddImpulse(FVector(0.0f,0.0f,JumpImpulse));
	++JumpCounter;
}

void ARollingBallPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(const float HitDir = Hit.Normal.Z; HitDir > 0.8f)
	{
		if(JumpImpulse == 0)
			JumpImpulse = MaxJumpImpulse;
			
		JumpCounter = 0;
	}
}

